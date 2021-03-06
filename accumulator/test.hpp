#pragma once
#ifndef TEST_SKELETON_H
#define TEST_SKELETON_H

#define TEST_ADDRESS 300

#include "accumulator.hpp"
#include "../utilities.hpp"

namespace spam {
  class TestAccumulator {
    public:
      Accumulator accumulator;

      TestAccumulator();
      int test_accumulator_load();
      int test_accumulator_store();
      int test_accumulator_add();
      int test_accumulator_multiply();
      int test_accumulator_end();
  };
}

#endif
