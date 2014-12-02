#ifndef LATCH_EX_MEM_H
#define LATCH_EX_MEM_H

namespace spam {
  class LatchExMem {
    public:
      int result;

      std::string instruction = "";
      char* input = (char*)""; // from syscall
  };
}

#endif
