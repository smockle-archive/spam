#ifndef LATCH_ID_EX_H
#define LATCH_ID_EX_H

namespace spam {
  class LatchIDEX {
    public:
      int rs = -1;
      int rt = -1;

      int pc = 0;

      char* instruction = (char*)"";
  };
}

#endif
