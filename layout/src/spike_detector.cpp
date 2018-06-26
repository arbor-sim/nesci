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

#include "nesci/layout/spike_detector.hpp"

namespace nesci {
namespace layout {

SpikeDetector::SpikeDetector(const std::string& name) : Device(name) {}

SpikeDetector::SpikeDetector(const Device& device) : Device(device) {}

SpikeDetector::SpikeDetector(Device&& device) : Device(device) {}

std::string SpikeDetector::GetPath() const {
	return Device::GetPath() + SuffixIfNotEmpty(attribute_) +
		SuffixIfNotEmpty(neuron_id_);
}

void SpikeDetector::SetAttribute(const std::string& attribute) {
	attribute_ = attribute;
}

void SpikeDetector::SetNeuronId(const std::string& neuron_id) {
	neuron_id_ = neuron_id;
}

}  // namespace layout
}  // namespace nesci
