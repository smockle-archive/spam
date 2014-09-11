#ifndef ReturnConstants
#define ReturnConstants 1

#define SUCCESS 0
#define FAIL -1
#define ARGUMENT_ERROR -10
#define IO_ERROR -20

#endif

#ifndef ColorConstants
#define ColorConstants 1

#define COLOR_RED "\033[0;31m"
#define COLOR_GREEN "\033[0;32m"
#define COLOR_YELLOW "\033[0;33m"

#define COLOR_STOP "\033[0m"

#define COLOR_ERROR "\033[0;31mError:\033[0m"
#define COLOR_EXCEPTION "\033[0;33mError:\033[0m"
#define COLOR_SUCCESS "\033[0;32mSuccess:\033[0m"

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
