//------------------------------------------------------------------------------
// nesci -- neuronal simulator conan interface
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

#ifndef CONSUMER_INCLUDE_NESCI_CONSUMER_SPIKE_DETECTOR_HPP_
#define CONSUMER_INCLUDE_NESCI_CONSUMER_SPIKE_DETECTOR_HPP_

#include <string>
#include <vector>
#include "nesci/consumer/device.hpp"

namespace nesci {
namespace consumer {

class SpikeDetector : public nesci::consumer::Device {
 public:
  SpikeDetector() = delete;
  explicit SpikeDetector(const std::string& name);
  SpikeDetector(const SpikeDetector&) = default;
  SpikeDetector(SpikeDetector&&) = default;
  ~SpikeDetector() override = default;

  std::vector<std::uint64_t> GetNeuronIds(const std::string& time);
};

}  // namespace consumer
}  // namespace nesci

#endif  // CONSUMER_INCLUDE_NESCI_CONSUMER_SPIKE_DETECTOR_HPP_
