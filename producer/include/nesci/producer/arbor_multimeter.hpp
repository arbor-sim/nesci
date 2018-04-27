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

#ifndef PRODUCER_INCLUDE_NESCI_PRODUCER_ARBOR_MULTIMETER_HPP_
#define PRODUCER_INCLUDE_NESCI_PRODUCER_ARBOR_MULTIMETER_HPP_

#include <string>

#include "nesci/producer/device.hpp"

// namespace nesci {
// namespace producer {

// class ArborMultimeter final : public Device {
//  public:
//   struct Datum {
//     double time;
//     std::string attribute;
//     std::string id;
//     double value;
//   };

//   explicit ArborMultimeter(const std::string& name);
//   ArborMultimeter(const ArborMultimeter&) = default;
//   ArborMultimeter(ArborMultimeter&&) = default;
//   ~ArborMultimeter() override = default;

//   ArborMultimeter& operator=(const ArborMultimeter&) = default;
//   ArborMultimeter& operator=(ArborMultimeter&&) = default;

//   void Record(const Datum& datum, conduit::Node* node);

//  private:
//   std::string ConstructPath(const Datum& datum);
//   double ConstructTimestep(const Datum& datum);

//   std::string name_;
// };

// }  // namespace producer
// }  // namespace nesci

#endif  // PRODUCER_INCLUDE_NESCI_PRODUCER_ARBOR_MULTIMETER_HPP_
