#!/usr/bin/env python

import os
import sys
import subprocess

valid_stages = ['conan', 'cmake', 'build', 'test', 'deliver']
valid_os = ['Windows', 'Linux', 'OSX']
valid_compilers = {
    'Windows': ['Visual Studio'],
    'Linux': ['gcc'],
    'OSX': ['apple-clang', 'gcc']
}
valid_channels = ['develop', 'stable']

visual_studio_version_year_map = {
    '15': '2017'
}


def execute(command, arguments):
    call_arguments = [command]
    call_arguments.extend(arguments)
    return_value = subprocess.call(call_arguments)
    if return_value == 0:
        print('\033[92m')
    else:
        print('\033[91m')
    print('$ ' + command + ' ' + ' '.join(arguments) + '\033[0m')


def get_conan_flags(compiler, compiler_version):
    conan_flags = []

    conan_flags.extend(['-s', 'compiler=%s' % compiler])
    conan_flags.extend(['-s', 'compiler.version="%s"' % compiler_version])
    conan_flags.extend(['-s', 'arch=x86_64'])
    conan_flags.extend(['-s', 'build_type=Release'])

    if compiler == 'Visual Studio':
        conan_flags.extend(['-s', 'compiler.runtime=MT'])
    elif compiler == 'gcc':
        conan_flags.extend(['-s', 'compiler.libcxx=libstdc++11'])
    elif compiler == 'apple-clang':
        conan_flags.extend(['-s', 'compiler.libcxx=libc++'])

    return conan_flags


def main(argv):
    if len(argv) != 5:
        print('usage: .gitlab-ci.py stage os compiler compiler_version')
        sys.exit(-1)

    stage = argv[1]
    operating_system = argv[2]
    compiler = argv[3]
    compiler_version = argv[4]

    if not stage in valid_stages:
        print('Invalid stage, possible values: %s' % ', '.join(valid_stages))
        sys.exit(-1)

    if not operating_system in valid_os:
        print('Invalid operating system, possible values: %s' %
              ', '.join(valid_os))
        sys.exit(-1)

    if not compiler in valid_compilers[operating_system]:
        print('Invalid compiler for %s, possible values: %s' %
              (operating_system, ', '.join(valid_compilers[operating_system])))
        sys.exit(-1)

    if stage == 'conan':
        execute('mkdir', ['build'])
        os.chdir('build')
        if operating_system == 'Linux':
            execute('export', ['CC=gcc'])
            execute('export', ['CXX=g++'])
        execute('conan',
                ['remote', 'update', 'rwth-vr--bintray',
                 'https://api.bintray.com/conan/rwth-vr/conan'])
        execute('conan', ['user', '-p', os.environ['CONAN_PASSWORD'],
                          '-r', 'rwth-vr--bintray', os.environ['CONAN_LOGIN_USERNAME']])
        execute('conan', [
                'install', '--build=missing'].extend(get_conan_flags(compiler, compiler_version)))

    elif stage == 'cmake':
        os.chdir('build')

        cmake_flags = []

        if compiler == 'Visual Studio':
            cmake_flags.extend(['-G', 'Visual Studio %s %s Win64' %
                                (compiler_version, visual_studio_version_year_map[compiler_version])])
        else:
            cmake_flags.append('-DCMAKE_BUILD_TYPE=Release')

        execute('cmake', cmake_flags.append('..'))

    elif stage == 'build':
        build_flags = []
        if compiler == 'Visual Studio':
            build_flags.extend(['--config', 'Release'])
        os.chdir('build')
        execute('cmake', ['--build', '.'].extend(build_flags))

    elif stage == 'test':
        os.chdir('build')
        if operating_system == 'OSX':
            os.environ['CTEST_OUTPUT_ON_FAILURE'] = '1'
        execute('cmake', ['-C', 'Release'])

    elif stage == 'deliver':
        channel = os.environ['channel']
        version = os.environ['version']
        if channel not in valid_channels:
            print('Invalid channel: %s possible values: %s' %
                  (channel, ', '.join(valid_channels)))
            sys.exit(-1)
        conan_flags = ' '.join(get_conan_flags(compiler, compiler_version))
        execute('conan', ['export-pkg', '.', 'nesci/%s@RWTH-VR/%s' %
                          (version, channel), '-f'].extend(conan_flags))
        execute('conan', ['test', './test_package', 'nesci/%s@RWTH-VR/%s' %
                          (version, channel)].extend(conan_flags))
        execute('conan', ['upload', 'nesci/%s@RWTH-VR/%s' % (version, channel),
                          '--all', '--force', '-r=rwth-vr--bintray'].extend(conan_flags))


if (__name__ == '__main__'):
    main(sys.argv)
