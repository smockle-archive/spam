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
    int offset = 0;
    for(char& c : ln) {
      d[address + offset - D_BASE_ADDR] = c;
      offset++;
    }
    d[address + offset - D_BASE_ADDR] = '\0';
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

char* Memory::readInstruction(int address) {
  if(address < 0) {
    std::cout << COLOR_ERROR << "Negative addresses are not allowed." << std::endl;
    std::cout << "Address given was " << address << std::endl;
    return (char*)'\n';
  }
  if(address < T_BASE_ADDR || address >= S_BASE_ADDR) {
    std::cout << COLOR_ERROR << "Given address must reference an instruction";
    std::cout << "(addresses " << T_BASE_ADDR << "-" << (S_BASE_ADDR - 1) << ")." << std::endl;
    std::cout << "Address given was " << address << std::endl;
    return (char*)'\n';
  }

  std::string s = "";
  int i = 0;
  char c = t[address - T_BASE_ADDR].c_str()[i];

  while(c != '\0' && c != '\n') {
    s += c;
    i++;
    c = t[address - T_BASE_ADDR].c_str()[i];
  }
  return (char*)s.c_str();
}

void Memory::dump() {
  cout << "d:" << d << endl;
  cout << "t:" << t << endl;
  cout << "s:" << s << endl;
  cout << endl;
}
