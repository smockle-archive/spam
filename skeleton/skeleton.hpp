#ifndef SKELETON_H
#define SKELETON_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <regex>
#include <map>
#include "../utilities.hpp"
#include "../memory/memory.hpp"
#include "../registry/registry.hpp"
#include "../stack/stack.hpp"
#include "../accumulator/accumulator.hpp"
#include "../gpr/gpr.hpp"
#include "../pipe-gpr/pipe-gpr.hpp"

namespace spam {
  class Skeleton {
    public:
      Memory * memory = new Memory();
      Registry * registry = new Registry();

      bool file_exists(std::string filename);
      int do_memory(std::string filename);
      int do_registry();
      int do_stack(int argc, char** argv);
      int do_accumulator(int argc, char** argv);
      int do_gpr(int argc, char** argv);
      int do_pipe_gpr(int argc, char** argv);
      int do_help();
  };
}

#endif
