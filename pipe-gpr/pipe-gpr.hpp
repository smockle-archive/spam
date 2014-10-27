#ifndef PIPE_GPR_H
#define PIPE_GPR_H

#include <iterator>

#include "../memory/memory.hpp"
#include "../registry/registry.hpp"
#include "latches/latchifid.hpp"
#include "latches/latchidex.hpp"
#include "latches/latchexmem.hpp"
#include "latches/latchmemwb.hpp"

namespace spam {
  class PipeGPR {
    int lol = 0;
    public:
      int pc = 0;
      Memory memory;
      Registry registry;

      LatchIFID  if_id_old;
      LatchIFID  if_id_new;
      LatchIDEX  id_ex_old;
      LatchIDEX  id_ex_new;
      LatchExMem ex_mem_old;
      LatchExMem ex_mem_new;
      LatchMemWB mem_wb_old;
      LatchMemWB mem_wb_new;

      int fetch();
      int decode();
      int execute();
      int access_memory();
  };
}

#endif