#-------------------------------------------------------------------------------
# nesci -- neural simulator conan interface
#
# Copyright (c) 2018 RWTH Aachen University, Germany,
# Virtual Reality & Immersive Visualization Group.
#-------------------------------------------------------------------------------
#                                  License
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#-------------------------------------------------------------------------------

from conans import ConanFile, CMake

class nesci(ConanFile):
    name = "nesci"
    version = "18.05"
    license = "Apache License, Version 2.0"
    description = """nesci -- neural simulator conan interface"""
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = "*"
    url = "https://devhub.vr.rwth-aachen.de/VR-Group/nesci"

    requires = (("catch/1.12.0@RWTH-VR/thirdparty"),
                 ("cpplint/e8ffd7c@RWTH-VR/thirdparty"),
                 ("cppcheck/1.82@RWTH-VR/thirdparty"),
                 ("conduit/0.3.1@RWTH-VR/thirdparty"))
    generators = "cmake"

    def configure(self):
        if (self.settings.os == "Windows"):
            self.options["conduit"].shared = False

    def imports(self):
       self.copy("*.dll", dst="consumer/tests/Debug", src="bin")
       self.copy("*.dll", dst="consumer/tests/Release", src="bin")
       self.copy("*.dll", dst="consumer/tests", src="bin")
       self.copy("*.so", dst="consumer/tests", src="lib")
       self.copy("*.dylib", dst="consumer/tests", src="lib")

       self.copy("*.dll", dst="layout/tests/Debug", src="bin")
       self.copy("*.dll", dst="layout/tests/Release", src="bin")
       self.copy("*.dll", dst="layout/tests", src="bin")
       self.copy("*.so", dst="layout/tests", src="lib")
       self.copy("*.dylib", dst="layout/tests", src="lib")

       self.copy("*.dll", dst="producer/tests/Debug", src="bin")
       self.copy("*.dll", dst="producer/tests/Release", src="bin")
       self.copy("*.dll", dst="producer/tests", src="bin")
       self.copy("*.so", dst="producer/tests", src="lib")
       self.copy("*.dylib", dst="producer/tests", src="lib")

    def package(self):
        self.copy("*.hpp", dst="include", src="layout/include")
        self.copy("*.hpp", dst="include", src="producer/include")
        self.copy("*.hpp", dst="include", src="consumer/include")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so*", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False, symlinks=True)

    def package_info(self):
        self.cpp_info.libs = ["layout", "consumer", "producer"]
