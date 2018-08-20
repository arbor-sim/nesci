# -------------------------------------------------------------------------------
# nesci -- neuronal simulator conan interface
#
# Copyright (c) 2018 RWTH Aachen University, Germany,
# Virtual Reality & Immersive Visualization Group.
# -------------------------------------------------------------------------------
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
# -------------------------------------------------------------------------------

import pynesci


def test_pynesci_consumer_arbor_multimeter():
    arbor_multimeter = pynesci.consumer.ArborMultimeter(
        "SomeArborMultimeterName")


def test_pynesci_consumer_arbor_multimeter_get_timestep_data():
    arbor_multimeter = pynesci.consumer.ArborMultimeter(
        "SomeArborMultimeterName")
    some_node = pynesci.Node()
    arbor_multimeter.SetNode(some_node)
    assert len(arbor_multimeter.GetTimestepData("0.0", "Attribute1")) == 0


def test_pynesci_consumer_arbor_multimeter_get_time_series_data():
    arbor_multimeter = pynesci.consumer.ArborMultimeter(
        "SomeArborMultimeterName")
    some_node = pynesci.Node()
    arbor_multimeter.SetNode(some_node)
    assert len(arbor_multimeter.GetTimeSeriesData(
        "0.0", "Attribute1")) == 0


def test_pynesci_consumer_arbor_multimeter_get_neuron_ids():
    arbor_multimeter = pynesci.consumer.ArborMultimeter(
        "SomeArborMultimeterName")
    some_node = pynesci.Node()
    arbor_multimeter.SetNode(some_node)
    arbor_multimeter.GetDatum("0.0", "Attribute1", "aasdad")
