#include "accumulator.hpp"

// I consulted the following resources for help:
// http://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
// http://www.cplusplus.com/forum/general/13135/
// http://stackoverflow.com/questions/10847237/how-to-convert-from-int-to-char

spam::Accumulator::Accumulator() {
  self = 0;
  pc = 0;
};

spam::Accumulator::Accumulator(Memory * mp) {
  self = 0;
  pc = 0;
  memory = *mp;
};

int spam::Accumulator::load(int address) {
  // Verify address is positive.
  if (address < 0) {
    #ifndef TEST
    std::cout << COLOR_ERROR << " Memory address cannot be a negative integer. (load, " << address << ")" << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  std::string value = memory.read(address);
  self = atoi(value.c_str());

  return SUCCESS;
}

int spam::Accumulator::store(int address) {
  // Verify address is positive.
  if (address < 0) {
    #ifndef TEST
    std::cout << COLOR_ERROR << " Memory address cannot be a negative integer. (store)" << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  std::string s = " " + std::to_string(self);
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
  self = self + atoi(value.c_str());

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
  self = self * atoi(value.c_str());

  return SUCCESS;
}

int spam::Accumulator::run() {

  // Process Memory.t (commands)
  std::string command = "";
  std::string argument = "";
  int arg = -1;

  pc = T_BASE_ADDR;
  while (pc >= T_BASE_ADDR) {
    // Get MIPS command string from Memory.t at position pc.
    command = trim(tolower(memory.read(pc)));

    // Split MIPS command string into MIPS command and MIPS argument.
    if (command.find(" ") != std::string::npos) {
      argument = trim(command.substr(command.find(" ")).c_str());
      command = command.substr(0, command.find(" ")).c_str();
    }

    // Match MIPS argument with spam::Accumulator argument
    if (argument.compare("x") == 0) {
      arg = X_ADDR;
    } else if (argument.compare("a") == 0) {
      arg = A_ADDR;
    } else if (argument.compare("b") == 0) {
      arg = B_ADDR;
    } else if (argument.compare("c") == 0) {
      arg = C_ADDR;
    }

    // Match MIPS command with spam::Accumulator command
    if (command.compare("load") == 0) {
      load(arg);
    } else if (command.compare("stor") == 0) {
      store(arg);
    } else if (command.compare("add") == 0) {
      add(arg);
    } else if (command.compare("mul") == 0) {
      multiply(arg);
    } else if (command.compare("end") == 0) {
      end();
    }



    // Prepare for next command
    command = "";
    argument = "";
    pc++;
  }

  // All commands have executed
  return SUCCESS;
}

int spam::Accumulator::end() {
  pc = -1;
  std::cout << "Output: " << self << std::endl;
  return SUCCESS;
}
