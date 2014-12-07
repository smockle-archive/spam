#pragma once
#ifndef MICROBOARD_H
#define MICROBOARD_H

#include "../utilities.hpp"

#include "scoreboard.hpp"
#include "functional-units.hpp"

#include "../memory/memory.hpp"
#include "../registry/registry.hpp"

namespace spam {
  // A simulator using a scoreboard.
  class Microboard {
    friend class TestMicroboard;
    private:
      Scoreboard s;
      Scoreboard sold;

      Memory memory;
      Registry registry;

      IntFU  intfu;
      FpAdd  fpadd;
      FpMult fpmult;
      FpMem  fpmem;

      int pc = 0;

      int fetch();
      int issue();
      int read_operands();
      int execute();
      int write();
    public:
      Microboard();
      Microboard(Memory m, Registry r);

      bool run();
  };
}

#endif
