#ifndef PIPE_GPR_H
#define PIPE_GPR_H

#include <iterator>

#include "../memory/memory.hpp"
#include "../registry/registry.hpp"
#include "latches/latchifid.hpp"
#include "latches/latchidex.hpp"

namespace spam {
  class PipeGPR {
    int lol = 0;
    public:
      int pc = 0;
      Memory memory;
      Registry registry;

      LatchIFID if_id_old;
      LatchIFID if_id_new;
      LatchIDEX id_ex_old;
      LatchIDEX id_ex_new;

      int fetch();
      int decode();
  };
}

#endif
