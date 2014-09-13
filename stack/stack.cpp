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
  int    safety = 0;
  int    addr;
  char * op;

  std::string instr;

  while(pc >= 0 && pc < m.lineCount) {
    instr = m.read(T_BASE_ADDR + pc++);
    std::cout << instr << std::endl;
    if (strcmp((char *)instr.c_str(), MUL) == 0
     || strcmp((char *)instr.c_str(), ADD) == 0
     || strcmp((char *)instr.c_str(), END) == 0) {
       op = (char *)instr.c_str();
    }
    else if (instr.find(" ") == std::string::npos) {
      //safety++;
      continue;
    } else {
        std::cout << "DEBUG: instr = " << instr << std::endl;
        op = (char * )(instr.substr(0, 1).c_str()); //may need to be find() - 1
        addr = spam::valueof(instr.substr(instr.find(" ")));
    }

    std::cout << "DEBUG: op = " << op << std::endl;

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
      end();
    }
    else {
      std::cout << COLOR_ERROR << " Invalid instruction." << std::endl;
    }
  }

  return SUCCESS;
}

bool Stack::push(int a) {
  sp++;
  std::string tmp = m.read(a);
  m.store(S_BASE_ADDR + sp, (char *)(" " + tmp).c_str());
  std::cout << "DEBUG: (push) tmp: " << tmp << std::endl;
  std::cout << "DEBUG: (push) m.read: " << m.read(S_BASE_ADDR + sp) << std::endl;
  return (strcmp((char * )(" " + tmp).c_str(), m.read(S_BASE_ADDR + sp)) == 0);
}
bool Stack::pop (int a) {
  std::string tmp = m.read(S_BASE_ADDR + sp); //just for proving it worked
  std::cout << "DEBUG: (pop)  tmp: " << tmp << std::endl;
  m.store(a, m.read(S_BASE_ADDR + sp));
  m.store(S_BASE_ADDR + sp, (char *)"\0");
  sp--;
  return (strcmp(m.read(a), tmp.c_str()) == 0);
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
  pc = -1;
  std::cout << "Output: " << m.read(S_BASE_ADDR + sp) << std::endl;
  return true;
}
