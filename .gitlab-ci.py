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


def execute(command):
    return_value = subprocess.call(command)
    if return_value == 0:
        print('\033[92m $' + command + '\033[0m')
    else:
        print('\033[91m $' + command + '\033[0m')


def get_conan_flags(compiler, compiler_version):
    conan_flags = []

    conan_flags.append('-s compiler="%s"' % compiler)
    conan_flags.append('-s compiler.version="%s"' % compiler_version)
    conan_flags.append('-s arch=x86_64')
    conan_flags.append('-s build_type=Release')

    if compiler == 'Visual Studio':
        conan_flags.append('-s compiler.runtime=MT')
    elif compiler == 'gcc':
        conan_flags.append('-s compiler.libcxx=libstdc++11')
    elif compiler == 'apple-clang':
        conan_flags.append('-s compiler.libcxx=libc++')

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
        execute('mkdir build')
        os.chdir('build')
        if operating_system == 'Linux':
            execute('export CC=gcc')
            execute('export CXX=g++')
        execute(
            'conan remote update rwth-vr--bintray https://api.bintray.com/conan/rwth-vr/conan')
        execute('conan user -p %s -r rwth-vr--bintray %s' %
                (os.environ['CONAN_PASSWORD'], os.environ['CONAN_LOGIN_USERNAME']))
        execute('conan install --build=missing %s ..' %
                ' '.join(get_conan_flags(compiler, compiler_version)))

    elif stage == 'cmake':
        os.chdir('build')

        cmake_flags = []

        if compiler == 'Visual Studio':
            cmake_flags.append('-G "Visual Studio %s %s Win64"' %
                               (compiler_version, visual_studio_version_year_map[compiler_version]))
        else:
            cmake_flags.append('-DCMAKE_BUILD_TYPE=Release')

        execute('cmake %s ..' % ' '.join(cmake_flags))

    elif stage == 'build':
        build_flags = []
        if compiler == 'Visual Studio':
            build_flags.append('--config Release')
        os.chdir('build')
        execute('cmake --build . %s' % ' '.join(build_flags))

    elif stage == 'test':
        os.chdir('build')
        if operating_system == 'OSX':
            os.environ['CTEST_OUTPUT_ON_FAILURE'] = '1'
        execute('ctest -C Release')

    elif stage == 'deliver':
        channel = os.environ['channel']
        version = os.environ['version']
        if channel not in valid_channels:
            print('Invalid channel: %s possible values: %s' %
                  (channel, ', '.join(valid_channels)))
            sys.exit(-1)
        conan_flags = ' '.join(get_conan_flags(compiler, compiler_version))
        execute('conan export-pkg . nesci/%s@RWTH-VR/%s %s -f' %
                (version, channel, conan_flags))
        execute('conan test ./test_package nesci/%s@RWTH-VR/%s %s' %
                (version, channel, conan_flags))
        execute('conan upload nesci/%s@RWTH-VR/%s --all --force -r=rwth-vr--bintray ' %
                (version, channel))


if (__name__ == '__main__'):
    main(sys.argv)
