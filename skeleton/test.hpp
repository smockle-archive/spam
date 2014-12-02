#pragma once
#ifndef TEST_SKELETON_H
#define TEST_SKELETON_H

#include "skeleton.hpp"

namespace spam {
  class TestSkeleton {
    public:
      Skeleton skeleton;

      int test_file_exists();
      int test_do_memory();
      int test_do_stack();
      int test_do_accumulator();
      int test_do_gpr();
      int test_do_help();
      int test_pluralize_test();
  };
  std::string pluralize_test(int i);
}

#endif
