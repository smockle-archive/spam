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
    std::cerr << COLOR_ERROR << "File not found. Check that the input file exists." << std::endl;
    #endif
    return IO_ERROR;
  }

  // Read file line-by-line into the correct memory sections.
  std::ifstream input(filename);
  int mem_t_addr = T_BASE_ADDR;
  int mem_d_addr = D_BASE_ADDR;
  char buffer = 'z';
  std::map <std::string, int> conversion_table;

  for (std::string line; getline(input, line);) {
    line = trim(tolower(line));

    // if it's got an octothorpe, it's a comment
    int index = line.find('#');
    if (index == 0) continue;
    else if (index > 0) {
        line = line.substr(0, index);
    }

    // if it's got a colon, it's a label
    index = line.find(':');
    if (index >= 0) {
      int stop = line.find(' ');
      std::string label;

      label = line.substr(0, (stop >= 0) ? stop : std::string::npos);
      label = label.substr(0, label.length() - 1);

      if      (buffer == 'd') conversion_table[label] = mem_d_addr;
      else if (buffer == 't') conversion_table[label] = mem_t_addr;

      // if it has a space, we want to use the below code
      // to add it to the data section
      if(stop < 0) continue;
    }
    else if (line.compare(".data") == 0) {
      buffer = 'd';
      continue;
    } else if (line.compare(".text") == 0) {
      buffer = 't';
      continue;
    } else if (line.compare("") == 0) {
      continue;
    }

    memory->lineCount++;

    if (buffer == 'd') {
      memory->store(mem_d_addr, &line[0]);
      mem_d_addr += MAX_DATA_SIZE;
    } else if (buffer == 't') {
      memory->store(mem_t_addr, &line[0]);
      mem_t_addr++;
    }
  }

  // Loop through the entire program, replacing all instances of `label`
  // with the proper address
  // Note: we must also check already-processed memory.
  for(auto itr = conversion_table.begin(); itr != conversion_table.end(); ++itr) {
    for(int x = D_BASE_ADDR; x < mem_d_addr; x += MAX_DATA_SIZE) {
        std::string instruction = "";

        int inc = x;
        char c = *memory->read(inc);
        while(c != '\0' && c != '\n') {
          instruction += c;
          inc++;
          c = *memory->read(inc);
        }

        int index = instruction.find(itr->first);
        // If we couldn't find the given label, let's have a sleepover.
        // Fight fires with dreams and fly cars in video games.
        // Remember what it's like to have fun.
        // If we couldn't find the given label, let's walk to the sky.
        // Vary the lines our sparklers make spelling our names in the air.
        // Remember what it's like to be a kid.
        // If we couldn't find the given label, let's ditch school.
        // Light cigs behind the bulletin board by that statue of the mascot.
        // Remember what it's like to be a punk.
        if(index < 0) continue;
        if(instruction.at(index + itr->first.length()) != ':') continue;

        char addr_cp[256] = {};
        std::sprintf(addr_cp, "%d", itr->second);

        std::string addr_str(addr_cp);

        instruction.replace(index, itr->first.length(), addr_str);
        memory->store(x, (char*)instruction.c_str());
    }
    for(int y = T_BASE_ADDR; y < mem_t_addr; y++) {
        std::string instruction(memory->read(y));

        int index = instruction.find(itr->first);
        // If we couldn't find the given label, let's have a sleepover.
        // Fight fires with dreams and fly cars in video games.
        // Remember what it's like to have fun.
        // If we couldn't find the given label, let's walk to the sky.
        // Vary the lines our sparklers make spelling our names in the air.
        // Remember what it's like to be a kid.
        // If we couldn't find the given label, let's ditch school.
        // Light cigs behind the bulletin board by that statue of the mascot.
        // Remember what it's like to be a punk.
        if(index < 0) continue;
        if(index + itr->first.length() < instruction.length()) {
            char c = instruction.at(index + itr->first.length());
            if(c != ' ' && c != ',') continue;
        }

        char addr_cp[256] = {};
        std::sprintf(addr_cp, "%d", itr->second);

        std::string addr_str(addr_cp);

        instruction.replace(index, itr->first.length(), addr_str);
        memory->store(y, (char*)instruction.c_str());
    }
  }

  return SUCCESS;
}

int spam::Skeleton::do_registry() {
   registry = new Registry();
   
   return SUCCESS;
}

int spam::Skeleton::do_stack(int argc, char** argv) {
  // Verify number of arguments.
  if (argc < 3) {
    #ifndef TEST
    std::cerr << COLOR_ERROR << "Not enough arguments. Correct syntax is \"spam stack <input_file>\"." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  // Verify correctness of first argument,
  // i.e. was the stack method called?
  if (strcmp(argv[1], "stack") != 0
   && strcmp(argv[1], "s") != 0) {
     #ifndef TEST
     std::cerr << COLOR_ERROR << "Invalid arguments. Correct syntax is \"spam stack <input_file>\"." << std::endl;
     #endif
     return ARGUMENT_ERROR;
  }

  // Verify correctness of second argument,
  // i.e. verify file exists.
  if (!spam::Skeleton::file_exists(argv[2])) {
    #ifndef TEST
    std::cerr << COLOR_ERROR << "File not found. Check that the input file exists." << std::endl;
    #endif
    return IO_ERROR;
  }

  // Load file into memory.
  do_memory(argv[2]);

  // Initialize stack.
  Stack stack(memory);
  stack.run();

  return SUCCESS;
}

int spam::Skeleton::do_accumulator(int argc, char** argv) {
  // Verify number of arguments.
  if (argc < 3) {
    #ifndef TEST
    std::cerr << COLOR_ERROR << "Not enough arguments. Correct syntax is \"spam accumulator <input_file>\"." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  // Verify correctness of first argument,
  // i.e. was the accumulator method called?
  if (strcmp(argv[1], "accumulator") != 0
   && strcmp(argv[1], "a") != 0) {
     #ifndef TEST
     std::cerr << COLOR_ERROR << "Invalid arguments. Correct syntax is \"spam accumulator <input_file>\"." << std::endl;
     #endif
     return ARGUMENT_ERROR;
  }

  // Verify correctness of second argument,
  // i.e. verify file exists.
  if (!file_exists(argv[2])) {
    #ifndef TEST
    std::cerr << COLOR_ERROR << "File not found. Check that the input file exists." << std::endl;
    #endif
    return IO_ERROR;
  }

  // Load file into memory.
  do_memory(argv[2]);

  // Initialize stack.
  Accumulator accumulator(memory);
  accumulator.run();

  return SUCCESS;
}

int spam::Skeleton::do_gpr(int argc, char** argv) {
  // Verify number of arguments.
  if (argc < 3) {
    #ifndef TEST
    std::cerr << COLOR_ERROR << " Not enough arguments. Correct syntax is \"spam gpr <input_file>\"." << std::endl;
    #endif
    return ARGUMENT_ERROR;
  }

  // Verify correctness of first argument,
  // i.e. was the accumulator method called?
  if (strcmp(argv[1], "gpr") != 0
   && strcmp(argv[1], "g") != 0) {
     #ifndef TEST
     std::cerr << COLOR_ERROR << " Invalid arguments. Correct syntax is \"spam gpr <input_file>\"." << std::endl;
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
  do_registry();

  GPR gpr(registry, memory);
  gpr.run();

  return SUCCESS;
}

int spam::Skeleton::do_help() {
  #ifndef TEST
  std::cout << "Commands:" << std::endl;
  std::cout << "\tspam stack <input_file>" << std::endl;
  std::cout << "\tspam accumulator <input_file>" << std::endl;
  std::cout << "\tspam gpr <input_file>" << std::endl;
  std::cout << "\tspam help" << std::endl;
  #endif

  return SUCCESS;
}

#ifndef TEST

int main(int argc, char** argv) {
  spam::Skeleton skeleton;

  if (argc > 1) {
    if (strcmp(argv[1], "stack") == 0
     || strcmp(argv[1], "s") == 0) {
      skeleton.do_stack(argc, argv);
    }
    else if (strcmp(argv[1], "accumulator") == 0
          || strcmp(argv[1], "a") == 0) {
      skeleton.do_accumulator(argc, argv);
    }
    else if (strcmp(argv[1], "gpr") == 0
          || strcmp(argv[1], "g") == 0) {
      skeleton.do_gpr(argc, argv);
    }
    else if (strcmp(argv[1], "help") == 0
          || strcmp(argv[1], "-h") == 0
          || strcmp(argv[1], "--help") == 0) {
      skeleton.do_help();
    }
    else {
      std::cout << COLOR_EXCEPTION << "Unknown argument: " << argv[1] << ". Run \"spam help\" for a list of valid options." << std::endl;
      skeleton.do_help();
      return ARGUMENT_ERROR;
    }
  }
  else {
      std::cerr << COLOR_ERROR << "Must specify at least one argument. Run \"spam help\" for a list of valid options." << std::endl;
      return ARGUMENT_ERROR;
  }

  return SUCCESS;
}

#endif

// spam stack "input.s"
// spam accumulator "input.s"
// spam help
