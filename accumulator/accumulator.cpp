#import "accumulator.hpp"

// I consulted the following resources for help:
// http://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
// http://www.cplusplus.com/forum/general/13135/

Accumulator::Accumulator() {
  a = 0;
};

int Accumulator::loadi(int value) {
  a = value;
  return SUCCESS;
}

int Accumulator::load(int address) {
  std::string value = memory.read(address);

  if (std::regex_match(value, std::regex("[0-9]+"))) {
    a = atoi(value.c_str());
  } else {
    std::cout << COLOR_ERROR << " Value at memory address cannot be converted to an int." << std::endl;
    return FAIL;
  }

  return SUCCESS;
}

int Accumulator::store(int address) {
  return SUCCESS;
}

int Accumulator::add(int address) {
  return SUCCESS;
}

int Accumulator::multiply(int address) {
  return SUCCESS;
}

int Accumulator::end() {
  return SUCCESS;
}
