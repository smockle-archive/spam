#pragma once
#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "../utilities.hpp"

namespace spam {
  class Scoreboard {
    std::string instructions[MAX_INSTRUCTION_COUNT] = { "" };
    int head = 0;    // increments when instruction has been completed
    int tail = -1;   // increments when instruction has been fetched; is -1 when empty
    int thorax = 0;  // increments when instruction has been issued

    bool busy[FUNCTIONAL_UNIT_COUNT] = { false };

    public:
      bool isBusy(int fuid);
      bool isWAW();
      bool isFull();
      bool isEmpty();

      int  push(std::string instruction);
      std::string pop();
      std::string peek();

      int issue(std::string instruction);
      std::string ipeek();
  };
}

#endif
