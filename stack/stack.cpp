#include "stack.hpp"

#define PUSH "push"
#define POP  "pop"
#define ADD  "add"
#define MUL  "mul"
#define END  "end"

Stack::Stack() { }

Stack::Stack(Memory * mp) {
  m = *mp;
}

int Stack::run() {
  int    pc = 0;
  int    addr;
  char * op;

  std::string instr;

  while(pc >= 0) {
    instr = m.read(T_BASE_ADDR);
    op = (char * )instr.substr(0, instr.find(" ")).c_str(); //may need to be find() - 1
    addr = spam::valueof(m.read(T_BASE_ADDR));

    if (strcmp(op, PUSH) == 0) {
      push(addr);
    }
    else if (strcmp(op, POP) == 0) {
      pop(addr);
    }
    else if (strcmp(op, ADD) == 0) {
      add();
    }
    else if (strcmp(op, MUL) == 0) {
      mul();
    }
    else if (strcmp(op, END) == 0) {
      pc = (end() ? -1 : pc);
    }
  }
  std::cout << "End stack run." << std::endl;
  return SUCCESS;
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
