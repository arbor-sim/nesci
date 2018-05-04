#include "consumer/consumer.hpp"
#include "layout/layout.hpp"
#include "producer/producer.hpp"

#include <iostream>

int main() {
  layout::Greet();
  std::cout << std::endl;
  producer::Greet();
  std::cout << std::endl;
  consumer::Greet();
  std::cout << std::endl;
}