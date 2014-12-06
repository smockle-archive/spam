#pragma once
#ifndef MICROBOARD_H
#define MICROBOARD_H

#include "../utilities.hpp"
#include "../scoreboard.hpp"

namespace spam {
  // A simulator using a scoreboard.
  public class Microboard {
    friend class MicroboardTest;
    private:
      Scoreboard s;

      IntFU  intfu;
      FpAdd  fpadd;
      FpMult fpmult;
      FpMem  fpmem;

      bool fetch();
      bool issue();
      bool read_operands();
      bool execute();
      bool write();
    public:
      Microboard(Memory m, Registry r);
      bool run();
  }
}

#endif
