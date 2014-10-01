#ifndef TEST_GPR_H
#define TEST_GPR_H

#include "gpr.hpp"
#include "../utilities.hpp"

namespace spam {
  class TestGPR {
    public:
      GPR gpr;

      TestGPR();
      int test_gpr_addi();
      int test_gpr_b();
      int test_gpr_beqz();
      int test_gpr_bge();
      int test_gpr_bne();
      int test_gpr_la();
      int test_gpr_lb();
      int test_gpr_li();
      int test_gpr_subi();
      int test_gpr_syscall();
      int test_gpr_decode_label();
      int test_gpr_end();
  };
}

#endif
