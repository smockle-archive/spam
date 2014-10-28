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

      int add(int rdest, int rsrc1, int rsrc2);
      int addi(int rdest, int rsrc, int imm);
      int b(int label_addr);
      int beqz(int rsrc, int label_addr);
      int bge(int rsrc1, int rsrc2, int label_addr);
      int bne(int rsrc1, int rsrc2, int label_addr);
      int la(int rdest, int variable_addr);
      int lb(int rdest, int offset, int rsrc);
      int li(int rdest, int imm);
      int subi(int rdest, int rsrc, int imm);
      int syscall();
      int nop();
      int end();
  };
}

#endif
