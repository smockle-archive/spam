#pragma once
#ifndef LATCHES_HPP
#define LATCHES_HPP

#include <string>

namespace spam {

  class LatchIFID {
    public:
      std::string instruction = "";
  };
  class LatchIDEX {
    public:
      int rs = -1;
      int rt = -1;

      int pc = 0;

      std::string instruction = "";
  };
  class LatchExMem {
    public:
      int result;

      std::string instruction = "";
      std::string input = ""; // from syscall
  };
  class LatchMemWB {
    public:
      int result;

      std::string instruction = "";
  };


}

#endif
