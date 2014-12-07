#pragma once
#ifndef TEST_MB_H
#define TEST_MB_H

#include "microboard.hpp"

#include "../memory/memory.hpp"
#include "../registry/registry.hpp"

#include "../utilities.hpp"

namespace spam {
  class TestMicroboard {
    private:
      Microboard mb;
    public:
      TestMicroboard();

      int test_fetch();
      int test_issue();
      int test_read_operands();
      int test_execute();
      int test_write();
  };
}

#endif
