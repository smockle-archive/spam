#ifndef TEST_PIPE_H
#define TEST_PIPE_H

#include "pipe-gpr.hpp"
#include "../utilities.hpp"

namespace spam {
  class TestPipeGPR {
    public:
      // Instance to use during testing
      PipeGPR p;

      // Pipeline methods
      int test_fetch();
      int test_decode();
      int test_execute();
      int test_access_memory();
      int test_cache();

      // Instruction methods
      int test_add();
      int test_addi();
      int test_la();
      int test_lb();
      int test_li();
      int test_subi();
      int test_syscall();
      int test_nop();
      int test_end();
  };

}


#endif
