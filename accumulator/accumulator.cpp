#include "accumulator.hpp"

// I consulted the following resources for help:
// http://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
// http://www.cplusplus.com/forum/general/13135/
// http://stackoverflow.com/questions/10847237/how-to-convert-from-int-to-char

spam::Accumulator::Accumulator() {
  a = 0;
};

spam::Accumulator::Accumulator(Memory * mp) {
  a = 0;
  memory = *mp;
};

int spam::Accumulator::load(int address) {
  // Verify address is positive.
  if (address < 0) {
    #ifndef TEST
    std::cout << COLOR_ERROR << " Memory address cannot be a negative integer." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  std::string value = memory.read(address);

  // Verify value can be converted to integer.
  if (std::regex_match(value, std::regex("[0-9]+"))) {
    a = atoi(value.c_str());
  } else {
    #ifndef TEST
    std::cout << COLOR_ERROR << " Value at memory address cannot be converted to an integer." << std::endl;
    #endif
    return TYPE_ERROR;
  }

  return SUCCESS;
}

int spam::Accumulator::store(int address) {
  // Verify address is positive.
  if (address < 0) {
    #ifndef TEST
    std::cout << COLOR_ERROR << " Memory address cannot be a negative integer." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  std::string s = std::to_string(a);
  memory.store(address, (char *) s.c_str());

  return SUCCESS;
}

int spam::Accumulator::add(int address) {
  // Verify address is positive.
  if (address < 0) {
    #ifndef TEST
    std::cout << COLOR_ERROR << " Memory address cannot be a negative integer." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  std::string value = memory.read(address);

  // Verify value can be converted to integer.
  if (std::regex_match(value, std::regex("[0-9]+"))) {
    a = a + atoi(value.c_str());
  } else {
    #ifndef TEST
    std::cout << COLOR_ERROR << " Value at memory address cannot be converted to an integer." << std::endl;
    #endif
    return TYPE_ERROR;
  }

  return SUCCESS;
}

int spam::Accumulator::multiply(int address) {
  // Verify address is positive.
  if (address < 0) {
    #ifndef TEST
    std::cout << COLOR_ERROR << " Memory address cannot be a negative integer." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  std::string value = memory.read(address);

  // Verify value can be converted to integer.
  if (std::regex_match(value, std::regex("[0-9]+"))) {
    a = a * atoi(value.c_str());
  } else {
    #ifndef TEST
    std::cout << COLOR_ERROR << " Value at memory address cannot be converted to an integer." << std::endl;
    #endif
    return TYPE_ERROR;
  }

  return SUCCESS;
}

int spam::Accumulator::end() {
  return SUCCESS;
}
