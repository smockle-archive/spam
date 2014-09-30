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
// Process Memory.t (commands)
std::string command = "";
std::string argument = "";
int arg = -1;

pc = T_BASE_ADDR;
while (pc >= T_BASE_ADDR) {
  // Get MIPS command string from Memory.t at position pc.
  command = spam::trim(spam::tolower(m.read(pc)));

  // Split MIPS command string into MIPS command and MIPS argument.
  if (command.find(" ") != std::string::npos) {
    argument = spam::trim(command.substr(command.find(" ")).c_str());
    command = command.substr(0, command.find(" ")).c_str();
  }

  // Match MIPS argument with spam::Accumulator argument
  if (argument.compare("x") == 0) {
    arg = X_ADDR;
  } else if (argument.compare("a") == 0) {
    arg = A_ADDR;
  } else if (argument.compare("b") == 0) {
    arg = B_ADDR;
  } else if (argument.compare("c") == 0) {
    arg = C_ADDR;
  }

  // Match MIPS command with spam::Accumulator command
  if (command.compare("push") == 0) {
    push(arg);
  } else if (command.compare("pop") == 0) {
    pop(arg);
  } else if (command.compare("add") == 0) {
    add();
  } else if (command.compare("mul") == 0) {
    mul();
  } else if (command.compare("end") == 0) {
    end();
  }



  // Prepare for next command
  command = "";
  argument = "";
  pc++;
}

// All commands have executed
return SUCCESS;
}

bool Stack::push(int a) {
  sp++;
  std::string tmp = m.read(a);
  m.store(S_BASE_ADDR + sp, (char *)(" " + tmp).c_str());
  return (strcmp((char * )(" " + tmp).c_str(), m.read(S_BASE_ADDR + sp)) == 0);
}
bool Stack::pop (int a) {
  std::string tmp = m.read(S_BASE_ADDR + sp); //just for proving it worked
  tmp = tmp.substr(1);
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
  #ifndef TEST
  std::cout << "Output: " << m.read(S_BASE_ADDR + sp) << std::endl;
  #endif
  return true;
}
