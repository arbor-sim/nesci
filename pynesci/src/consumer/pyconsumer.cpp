//------------------------------------------------------------------------------
// nesci -- neural simulator conan interface
//
// Copyright (c) 2017-2018 RWTH Aachen University, Germany,
// Virtual Reality & Immersive Visualisation Group.
//------------------------------------------------------------------------------
//                                 License
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//------------------------------------------------------------------------------

#include "pyconsumer.hpp"
#include <string>
#include "nesci/consumer/arbor_multimeter.hpp"
#include "nesci/consumer/device.hpp"
#include "nesci/consumer/multimeter.hpp"
#include "nesci/consumer/nest_multimeter.hpp"

namespace pynesci {
namespace consumer {

namespace {
std::string Greet() { return "G'day!"; }
}  // namespace

SUPPRESS_WARNINGS_BEGIN

// cppcheck-suppress unusedFunction
BOOST_PYTHON_MODULE(_pyconsumer) {
  def("Greet", &Greet);
  expose<nesci::consumer::Device>();
  expose<nesci::consumer::Multimeter>();
  expose<nesci::consumer::NestMultimeter>();
  expose<nesci::consumer::ArborMultimeter>();
}
SUPPRESS_WARNINGS_END

}  // namespace consumer
}  // namespace pynesci
