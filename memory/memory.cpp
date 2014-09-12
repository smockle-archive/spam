#include "memory.hpp"

using namespace std;

bool Memory::store(int address, char* line) {
  if(address >= S_BASE_ADDR) {
    s[address - S_BASE_ADDR] = line;
    return true;
  }
  else if(address >= T_BASE_ADDR) {
    t[address - T_BASE_ADDR] = line;
    return true;
  }
  else if(address >= D_BASE_ADDR) {
    d[address - D_BASE_ADDR] = line;
    return true;
  }
  else return false;
}

char* Memory::read(int address) {
  if(address < 0) {
    cout << "Error: negative addresses are not allowed. Address given was ";
    cout << address << endl;
    return (char*)'\n';
  }

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
  cout << "d:" << d << endl;
  cout << "t:" << t << endl;
  cout << "s:" << s << endl;
  cout << endl;
}
