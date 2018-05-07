#include "nesci/consumer/consumer.hpp"
#include "nesci/layout/layout.hpp"
#include "nesci/producer/producer.hpp"

#include <iostream>

int main() {
  nesci::layout::Greet();
  std::cout << std::endl;
  nesci::producer::Greet();
  std::cout << std::endl;
  nesci::consumer::Greet();
  std::cout << std::endl;
}