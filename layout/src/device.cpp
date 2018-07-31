//------------------------------------------------------------------------------
// nesci -- neural simulator conan interface
//
// Copyright (c) 2018 RWTH Aachen University, Germany,
// Virtual Reality & Immersive Visualization Group.
//------------------------------------------------------------------------------
//                                  License
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

#include "nesci/layout/device.hpp"
#include <sstream>
#include <string>
#include "nesci/layout/utility.hpp"

namespace nesci {
namespace layout {

Device::Device(const std::string& name) : name_(name) {}

std::string Device::GetPath() const { return name_ + SuffixIfNotEmpty(time_); }

std::string Device::SuffixIfNotEmpty(const std::string& suffix) {
  return suffix != "" ? "/" + suffix : "";
}

void Device::SetTime(const std::string& time) { time_ = time; }

void Device::SetTime(double time) { SetTime(utility::to_string(time)); }

}  // namespace layout
}  // namespace nesci
