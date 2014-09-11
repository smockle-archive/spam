#include "memory.hpp"
#include <iostream>

using namespace std;

Memory::Memory() {
  std::fill(d, d + DBUF_SIZE, 0);
  std::fill(t, t + TBUF_SIZE, 0);
  std::fill(s, s + STCK_SIZE, 0);
};

bool Memory::store(char type, char* line) {

  return false;
}

void Memory::dump() {
  cout << "d:" << endl;
  cout << d << endl << endl;
  cout << "t:" << endl;
  cout << t << endl << endl;
  cout << "s:" << endl;
  cout << s << endl << endl;
}
