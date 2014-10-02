#ifndef GPR_H
#define GPR_H

#include "../registry/registry.hpp"
#include "../memory/memory.hpp"
#include "../skeleton/skeleton.hpp"

#define SYSCALL_CIN 8
#define SYSCALL_COUT 4
#define SYSCALL_END 10

namespace spam {
  class GPR {
      private:
      public:
        int pc;
        Registry registry;
        Memory memory;

        GPR();
        GPR(Registry * rp, Memory * mp);
        int addi(int rdest, int rsrc, int imm);
        int b(char* label);
        int beqz(int rsrc, char* label);
        int bge(int rsrc1, int rsrc2, char* label);
        int bne(int rsrc1, int rsrc2, char* label);
        int la(int rdest, char* variable);
        int lb(int rdest, int offset, int rsrc);
        int li(int rdest, int imm);
        int subi(int rdest, int rsrc, int imm);
        int syscall();
        int decode_label(char* label);
        int run();
        int end();
  };
}

#endif
