//------------------------------------------------------------------------------
// nest in situ vis
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

#include "nesci/consumer/nest_multimeter.hpp"

#include <cmath>

#include <string>
#include <vector>

#include "nesci/layout/multimeter.hpp"

namespace nesci {
namespace consumer {

NestMultimeter::NestMultimeter(const std::string& name)
    : consumer::Multimeter{name} {}

std::vector<double> NestMultimeter::GetTimestepData(
    const std::string& time, const std::string& attribute) const {
  std::vector<double> retval;
  const auto neuron_ids{GetNeuronIds(time, attribute)};
  retval.reserve(neuron_ids.size());

  layout::Multimeter path(GetName());
  path.SetTime(time);
  path.SetAttribute(attribute);

  for (auto curr_neuron_id : neuron_ids) {
    path.SetNeuronId(curr_neuron_id);
    retval.push_back(GetValue(path));
  }
  return retval;
}

std::vector<double> NestMultimeter::GetTimeSeriesData(
    const std::string& attribute, const std::string& neuron_id) const {
  std::vector<double> retval;
  const auto timesteps = GetTimesteps();
  retval.reserve(timesteps.size());

  layout::Multimeter path(GetName());
  path.SetAttribute(attribute);
  path.SetNeuronId(neuron_id);
  for (auto time : timesteps) {
    path.SetTime(time);
    retval.push_back(GetValue(path));
  }
  return retval;
}

double NestMultimeter::GetDatum(const std::string& time,
                                const std::string& attribute,
                                const std::string& neuron_id) const {
  layout::Multimeter path(GetName());
  path.SetTime(time);
  path.SetAttribute(attribute);
  path.SetNeuronId(neuron_id);
  return GetValue(path);
}

}  // namespace consumer
}  // namespace nesci
