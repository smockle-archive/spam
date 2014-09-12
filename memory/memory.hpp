#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <string.h>
#include "../utilities.hpp"

class Memory {
private:
  char **d[DBUF_SIZE]; /* Data buffer */
  char **t[TBUF_SIZE]; /* Text buffer */
  char **s[STCK_SIZE]; /* Stack buffer */
public:
  bool store (int address, char* line);
  char* read (int address);
  void  dump ();
};

#endif
