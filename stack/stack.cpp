#include "stack.hpp"

Stack::Stack() { }

Stack::Stack(Memory * mp) {
  m = *mp;
}

int Stack::run() {

  return FAIL;
}

bool Stack::push(int a) {
  sp++;
  m.store(S_BASE_ADDR + sp, m.read(a));
  return (strcmp(m.read(a), m.read(S_BASE_ADDR + sp)) == 0);
}
bool Stack::pop (int a) {
  char * tmp = m.read(S_BASE_ADDR + sp); //just for proving it worked
  m.store(a, m.read(S_BASE_ADDR + sp));
  m.store(S_BASE_ADDR + sp, (char *)"\0");
  sp--;
  return (strcmp(m.read(a), tmp) == 0);
}
bool Stack::add () {
  if(sp < 1) return false;

  char * a = m.read(S_BASE_ADDR + sp--);
  char * b = m.read(S_BASE_ADDR + sp--);

  int ia = atoi(a);
  int ib = atoi(b);

  std::string s = std::to_string(ia + ib);
  m.store(S_BASE_ADDR + ++sp, (char *)s.c_str());

  return true;
}
bool Stack::mul () {
  if(sp < 1) return false;

  char * a = m.read(S_BASE_ADDR + sp--);
  char * b = m.read(S_BASE_ADDR + sp--);

  int ia = atoi(a);
  int ib = atoi(b);

  std::string s = std::to_string(ia * ib);
  m.store(S_BASE_ADDR + ++sp, (char *)s.c_str());

  return true;
}
bool Stack::end () {
  return false;
}
