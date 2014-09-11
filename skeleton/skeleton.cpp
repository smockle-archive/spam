#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

// I consulted the following resources for help:
// http://www.cplusplus.com/reference/fstream/ifstream/open/
// http://www.cplusplus.com/reference/cstring/strcmp/

bool file_exists(std::string filename) {
  std::ifstream ifs;
  bool exists;
  ifs.open (filename, std::ifstream::in);
  exists = ifs.good();
  ifs.close();
  return exists;
}

void do_stack(int argc, char** argv) {
  // Verify number of arguments.
  if (argc < 3) {
    std::cout << "Error: Not enough arguments. Correct syntax is \"spam stack <input_file>\"." << std::endl;
  }

  // Verify correctness of first argument,
  // i.e. was the stack method called?
  if (std::strcmp(argv[1], "stack") != 0
   && std::strcmp(argv[1], "s") != 0) {
     std::cout << "Error: Invalid arguments. Correct syntax is \"spam stack <input_file>\"." << std::endl;
  }

  // Verify correctness of second argument,
  // i.e. verify file exists.
  if (!file_exists(argv[2])) {
    std::cout << "Error: File not found. Check that the input file exists." << std::endl;
  }
}

void do_accumulator(int argc, char** argv) {
  // Verify number of arguments.
  if (argc < 3) {
    std::cout << "Error: Not enough arguments. Correct syntax is \"spam accumulator <input_file>\"." << std::endl;
  }

  // Verify correctness of first argument,
  // i.e. was the accumulator method called?
  if (std::strcmp(argv[1], "accumulator") != 0
   && std::strcmp(argv[1], "a") != 0) {
     std::cout << "Error: Invalid arguments. Correct syntax is \"spam accumulator <input_file>\"." << std::endl;
  }

  // Verify correctness of second argument,
  // i.e. verify file exists.
  if (!file_exists(argv[2])) {
    std::cout << "Error: File not found. Check that the input file exists." << std::endl;
  }
}

void do_help() {
  std::cout << "Commands:" << std::endl;
  std::cout << "\tspam stack <input_file>" << std::endl;
  std::cout << "\tspam accumulator <input_file>" << std::endl;
  std::cout << "\tspam help" << std::endl;
}

int main(int argc, char** argv) {
  if (argc > 0) {
    if (std::strcmp(argv[1], "stack") == 0
     || std::strcmp(argv[1], "s") == 0) {
      do_stack(argc, argv);
    }
    else if (std::strcmp(argv[1], "accumulator") == 0
          || std::strcmp(argv[1], "a") == 0) {
      do_accumulator(argc, argv);
    }
    else if (std::strcmp(argv[1], "help") == 0
          || std::strcmp(argv[1], "-h") == 0
          || std::strcmp(argv[1], "--help") == 0) {
      do_help();
    }
    else {
      std::cout << "Exception: Unknown argument: " << argv[1] << ". Run \"spam help\" for a list of valid options." << std::endl;
      do_help();
    }
  }
  else {
      std::cout << "Error: Must specify at least one argument. Run \"spam help\" for a list of valid options." << std::endl;
  }
  return 1;
}

// spam stack "input.s"
// spam accumulator "input.s"
// spam help
