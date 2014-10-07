#include "memory.hpp"

using namespace std;

bool Memory::store(int address, char* line) {
  if(address >= S_BASE_ADDR) {
    s[address - S_BASE_ADDR].assign(line);
    return true;
  }
  else if(address >= T_BASE_ADDR) {
    t[address - T_BASE_ADDR].assign(line);
    return true;
  }
  else if(address >= D_BASE_ADDR) {
    std::string ln = line;
    if(ln.find(" ") == std::string::npos) return false;
    int offset = 0;
    for(char& c : ln) {
      d[address + offset - D_BASE_ADDR] = c;
      offset++;
    }
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
    return (char *)s[address - S_BASE_ADDR].c_str();
  }
  if(address >= T_BASE_ADDR) {
    return (char *)t[address - T_BASE_ADDR].c_str();
  }
  if(address >= D_BASE_ADDR) {
    char c = d[address - D_BASE_ADDR];
    std::string sd(1, c);
    return (char *)sd.c_str();
  }
  return (char*)'\n';
}

void Memory::dump() {
  cout << "d:" << d << endl;
  cout << "t:" << t << endl;
  cout << "s:" << s << endl;
  cout << endl;
}
