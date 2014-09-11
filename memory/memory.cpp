#include "memory.hpp"
#include <iostream>
#include <string.h>

using namespace std;

Memory::Memory() {
  
};

bool Memory::store(char type, char* line) {
  return false;
}

char* Memory::read(int address) {
  if(address >= S_BASE_ADDR) {
    return s[address - S_BASE_ADDR];
  }
  if(address >= T_BASE_ADDR) {
    return t[address - T_BASE_ADDR];
  }
  if(address >= D_BASE_ADDR) {
    return d[address - D_BASE_ADDR];
  }
  return (char*)'\n';
}

void Memory::dump() {
  cout << "d:" << endl;
  cout << d << endl << endl;
  cout << "t:" << endl;
  cout << t << endl << endl;
  cout << "s:" << endl;
  cout << s << endl << endl;
}
