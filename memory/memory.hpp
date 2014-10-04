#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <string.h>
#include <string>
#include "../utilities.hpp"

class Memory {
private:
  std::string d[DBUF_SIZE] = {}; /* Data buffer */
  std::string t[TBUF_SIZE] = {}; /* Text buffer */
  std::string s[STCK_SIZE] = {}; /* Stack buffer */
public:
  int lineCount;

  bool store (int address, char* line);
  char* read (int address);
  void  dump ();
};

#endif
