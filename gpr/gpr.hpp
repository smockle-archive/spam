#ifndef GPR_H
#define GPR_H

#import "../registry/registry.hpp"
#import "../memory/memory.hpp"

namespace spam {
  class GPR {
      private:
      public:
          Registry r;
          Memory m;

          int addi(int rdest, int rsrc, int imm);
          int b(char* label);
          int beqz(int rsrc1, int rsrc2, char* label);
          int bge(int rsrc1, int rsrc2, char* label);
          int bne(int rsrc1, int rsrc2, char* label);
          int la(int rdest, int addr);
          int lb(int rdest, int addr);
          int li(int rdest, int imm);
          int subi(int rdest, int rsrc, int imm);
          int syscall();

          int decodeLabel(char* label);
  };
}

#endif
