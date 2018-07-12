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

#ifndef LAYOUT_INCLUDE_NESCI_LAYOUT_SPIKE_DETECTOR_HPP_
#define LAYOUT_INCLUDE_NESCI_LAYOUT_SPIKE_DETECTOR_HPP_

#include <string>

#include "nesci/layout/device.hpp"

namespace nesci {
namespace layout {

	class SpikeDetector : public Device {
	public:
		SpikeDetector() = delete;
		explicit SpikeDetector(const std::string& name);
		SpikeDetector(const SpikeDetector&) = default;
		explicit SpikeDetector(const Device& device);
		SpikeDetector(SpikeDetector&&) = default;
		explicit SpikeDetector(Device&& device);
		~SpikeDetector() override = default;

		SpikeDetector& operator=(const SpikeDetector&) = default;
		SpikeDetector& operator=(SpikeDetector&&) = default;

		std::string GetPath() const override;

	};

}  // namespace layout
}  // namespace nesci

#endif  // LAYOUT_INCLUDE_NESCI_LAYOUT_SPIKE_DETECTOR_HPP_