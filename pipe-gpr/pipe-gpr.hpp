#ifndef PIPE_GPR_H
#define PIPE_GPR_H

#include <iterator>

#include "../memory/memory.hpp"
#include "../registry/registry.hpp"
#include "latches/latchifid.hpp"
#include "latches/latchidex.hpp"
#include "latches/latchexmem.hpp"
#include "latches/latchmemwb.hpp"

#define SYSCALL_CIN 8
#define SYSCALL_COUT 4
#define SYSCALL_END 10

namespace spam {
  class PipeGPR {
    public:
      int pc = 0;
      int cycles = 0;
      int instructions_executed = 0;
      int nops = 0;
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

      PipeGPR(Registry * r, Memory * m);

      int fetch();
      int decode();
      int execute();
      int access_memory();
      int cache();
      int run();

      int add(int rsrc1, int rsrc2);
      int addi(int rsrc, int imm);
      int la(int variable_addr);
      int lb(int offset, int rsrc);
      int li(int imm);
      int subi(int rsrc, int imm);
      int syscall();
      int nop();
      int end();
  };
}

#endif
