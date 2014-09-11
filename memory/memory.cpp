#include "memory.hpp"

using namespace std;

Memory::Memory() {

};

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
  cout << "d:" << endl;
  cout << d << endl << endl;
  cout << "t:" << endl;
  cout << t << endl << endl;
  cout << "s:" << endl;
  cout << s << endl << endl;
}
