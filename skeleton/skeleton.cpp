#include "skeleton.hpp"

// I consulted the following resources for help:
// http://www.cplusplus.com/reference/fstream/ifstream/open/
// http://www.cplusplus.com/reference/cstring/strcmp/
// http://www.cplusplus.com/forum/unices/36461/
// http://stackoverflow.com/questions/7868936/c-read-file-line-by-line

bool spam::Skeleton::file_exists(std::string filename) {
  std::ifstream ifs;
  bool exists;
  ifs.open (filename, std::ifstream::in);
  exists = ifs.good();
  ifs.close();
  return exists;
}

int spam::Skeleton::do_memory(std::string filename) {
  // Verify correctness of argument,
  // i.e. verify file exists.
  if (!spam::Skeleton::file_exists(filename)) {
    #ifndef TEST
    std::cerr << COLOR_ERROR << " File not found. Check that the input file exists." << std::endl;
    #endif
    return IO_ERROR;
  }

  // Read file line-by-line into memory.
  std::ifstream input(filename);
  int mem_addr = T_BASE_ADDR;
  for (std::string line; getline(input, line);) {
    memory->store(mem_addr, &line[0]);
    mem_addr++;
  }

  return SUCCESS;
}

int spam::Skeleton::do_stack(int argc, char** argv) {
  // Verify number of arguments.
  if (argc < 3) {
    #ifndef TEST
    std::cerr << COLOR_ERROR << " Not enough arguments. Correct syntax is \"spam stack <input_file>\"." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  // Verify correctness of first argument,
  // i.e. was the stack method called?
  if (strcmp(argv[1], "stack") != 0
   && strcmp(argv[1], "s") != 0) {
     #ifndef TEST
     std::cerr << COLOR_ERROR << " Invalid arguments. Correct syntax is \"spam stack <input_file>\"." << std::endl;
     #endif
     return ARGUMENT_ERROR;
  }

  // Verify correctness of second argument,
  // i.e. verify file exists.
  if (!spam::Skeleton::file_exists(argv[2])) {
    #ifndef TEST
    std::cerr << COLOR_ERROR << " File not found. Check that the input file exists." << std::endl;
    #endif
    return IO_ERROR;
  }

  // Load file into memory.
  do_memory(argv[2]);

  // Initialize stack.
  Stack stack(memory);

  return SUCCESS;
}

int spam::Skeleton::do_accumulator(int argc, char** argv) {
  // Verify number of arguments.
  if (argc < 3) {
    #ifndef TEST
    std::cerr << COLOR_ERROR << " Not enough arguments. Correct syntax is \"spam accumulator <input_file>\"." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  // Verify correctness of first argument,
  // i.e. was the accumulator method called?
  if (strcmp(argv[1], "accumulator") != 0
   && strcmp(argv[1], "a") != 0) {
     #ifndef TEST
     std::cerr << COLOR_ERROR << " Invalid arguments. Correct syntax is \"spam accumulator <input_file>\"." << std::endl;
     #endif
     return ARGUMENT_ERROR;
  }

  // Verify correctness of second argument,
  // i.e. verify file exists.
  if (!file_exists(argv[2])) {
    #ifndef TEST
    std::cerr << COLOR_ERROR << " File not found. Check that the input file exists." << std::endl;
    #endif
    return IO_ERROR;
  }

  // Load file into memory.
  do_memory(argv[2]);

  // Initialize stack.
  Accumulator accumulator(memory);

  return SUCCESS;
}

int spam::Skeleton::do_help() {
  #ifndef TEST
  std::cout << "Commands:" << std::endl;
  std::cout << "\tspam stack <input_file>" << std::endl;
  std::cout << "\tspam accumulator <input_file>" << std::endl;
  std::cout << "\tspam help" << std::endl;
  #endif

  return SUCCESS;
}

#ifndef TEST

int main(int argc, char** argv) {
  spam::Skeleton skeleton;

  if (argc > 0) {
    if (strcmp(argv[1], "stack") == 0
     || strcmp(argv[1], "s") == 0) {
      skeleton.do_stack(argc, argv);
    }
    else if (strcmp(argv[1], "accumulator") == 0
          || strcmp(argv[1], "a") == 0) {
      skeleton.do_accumulator(argc, argv);
    }
    else if (strcmp(argv[1], "help") == 0
          || strcmp(argv[1], "-h") == 0
          || strcmp(argv[1], "--help") == 0) {
      skeleton.do_help();
    }
    else {
      std::cout << COLOR_EXCEPTION << " Unknown argument: " << argv[1] << ". Run \"spam help\" for a list of valid options." << std::endl;
      skeleton.do_help();
      return ARGUMENT_ERROR;
    }
  }
  else {
      std::cerr << COLOR_ERROR << " Must specify at least one argument. Run \"spam help\" for a list of valid options." << std::endl;
      return ARGUMENT_ERROR;
  }

  return SUCCESS;
}

#endif

// spam stack "input.s"
// spam accumulator "input.s"
// spam help
