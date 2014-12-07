#pragma once
#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "../utilities.hpp"

namespace spam {
  class Scoreboard {
    friend class TestMicroboard;
    std::pair<std::string, int> instructions[MAX_INSTRUCTION_COUNT]; // first is instruction, second is state
    int head = 0;    // increments when instruction has been completed
    int tail = -1;   // increments when instruction has been fetched; is -1 when empty
    int thorax = 0;  // increments when instruction has been issued
    int abdomen = 0; // increments when operands for instruction have been read

    bool busy[FUNCTIONAL_UNIT_COUNT] = { false };
    int getFUID();
    int * extract_source_operands(int ops[2]);

    public:
      bool isFUBusy();
      bool isWAW();

      bool isRegisterBusy();        // checks issued instructions, but not instructions in the FUs
      bool isRAW();                 // checks each FU's instruction

      bool isFull();
      bool isEmpty();

      int  push(std::string instruction);
      std::string pop();
      std::string peek();
      std::string ipeek();
      std::string ropeek();

      int issue();
      int read_operands();
  };
}

#endif
