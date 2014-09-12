#include "accumulator.hpp"

// I consulted the following resources for help:
// http://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
// http://www.cplusplus.com/forum/general/13135/
// http://stackoverflow.com/questions/10847237/how-to-convert-from-int-to-char

Accumulator::Accumulator(Memory memory) {
  a = 0;
};

int Accumulator::load(int address) {
  if (address < 0) {
    std::cout << COLOR_ERROR << " Memory address cannot be a negative integer." << std::endl;
    return FAIL;
  }

  std::string value = spam::memory.read(address);

  if (std::regex_match(value, std::regex("[0-9]+"))) {
    a = atoi(value.c_str());
  } else {
    std::cout << COLOR_ERROR << " Value at memory address cannot be converted to an integer." << std::endl;
    return FAIL;
  }

  return SUCCESS;
}

int Accumulator::store(int address) {
  if (address < 0) {
    std::cout << COLOR_ERROR << " Memory address cannot be a negative integer." << std::endl;
    return FAIL;
  }

  std::string s = std::to_string(a);
  spam::memory.store(address, (char *) s.c_str());

  return SUCCESS;
}

int Accumulator::add(int address) {
  if (address < 0) {
    std::cout << COLOR_ERROR << " Memory address cannot be a negative integer." << std::endl;
    return FAIL;
  }

  std::string value = spam::memory.read(address);

  if (std::regex_match(value, std::regex("[0-9]+"))) {
    a = a + atoi(value.c_str());
  } else {
    std::cout << COLOR_ERROR << " Value at memory address cannot be converted to an integer." << std::endl;
    return FAIL;
  }

  return SUCCESS;
}

int Accumulator::multiply(int address) {
  if (address < 0) {
    std::cout << COLOR_ERROR << " Memory address cannot be a negative integer." << std::endl;
    return FAIL;
  }

  std::string value = spam::memory.read(address);

  if (std::regex_match(value, std::regex("[0-9]+"))) {
    a = a * atoi(value.c_str());
  } else {
    std::cout << COLOR_ERROR << " Value at memory address cannot be converted to an integer." << std::endl;
    return FAIL;
  }

  return SUCCESS;
}

int Accumulator::end() {
  return SUCCESS;
}
