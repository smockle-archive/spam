#ifndef ReturnConstants
#define ReturnConstants 1

#define SUCCESS 1
#define FAIL 0
#define ARGUMENT_ERROR -10
#define IO_ERROR -20

#endif

#ifndef SKELETON_H
#define SKELETON_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

namespace spam {
  bool file_exists(std::string filename);
  int do_stack(int argc, char** argv);
  int do_accumulator(int argc, char** argv);
  int do_help();
}

#endif
