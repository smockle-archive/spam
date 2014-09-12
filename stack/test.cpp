#include <string.h>
#include <iostream>
#include <sstream>

#include "stack.hpp"

#include "test.hpp"

#define X 3
#define Y 7
#define Z 6

int main(int argc, char ** argv){

  bool isVerbose = false;

  if(argc > 1 && strcmp(argv[1], "-v") == 0) isVerbose = true;

  int tests_run = 6;
  int tests_passed = tests_run;
  int tests_failed;

  tests_passed += spam::test_init();
  tests_passed += spam::test_push();
  tests_passed += spam::test_pop ();
  tests_passed += spam::test_add ();
  tests_passed += spam::test_mul ();
  tests_passed += spam::test_end ();

  tests_failed = tests_run - tests_passed;

  if (tests_run > 0) {
    std::cout << "RESULTS:" << std::endl;
    std::cout << "\t" << tests_run << " " << ((tests_run != 1) ? "tests" : "test") << " run." << std::endl;
  }

  if (tests_passed > 0) {
    std::cout << "\t" << COLOR_GREEN << tests_passed << " " << ((tests_run != 1) ? "tests" : "test") << " passed." << COLOR_STOP << std::endl;
  } else {
    std::cout << "\t" << tests_passed << " tests passed." << std::endl;
  }

  if (tests_failed > 0) {
    std::cout << "\t" << COLOR_RED << tests_failed << " " << ((tests_run != 1) ? "tests" : "test") << " failed." << COLOR_STOP << std::endl;
  } else {
    std::cout << "\t" << tests_failed << " tests failed." << std::endl;
  }

  return (tests_failed == 0) ? SUCCESS: FAIL;
}

int spam::test_init() {

  Stack s;

  s.m.store(X_ADDR, (char *)"3");
  s.m.store(Y_ADDR, (char *)"7");
  s.m.store(Z_ADDR, (char *)"6");

  char* memline;
  memline = s.m.read(X_ADDR);

  return (strcmp(memline, (char *)"3") == 0) ? SUCCESS : FAIL;
}

int spam::test_push() {

  Stack s;

  s.m.store(X_ADDR, (char *)"3");
  s.m.store(Y_ADDR, (char *)"7");
  s.m.store(Z_ADDR, (char *)"6");

  char* memline;
  memline = s.m.read(X_ADDR);

  if(!s.push(X_ADDR)) {
    std::cout << COLOR_RED << "Error: " << COLOR_STOP;
    std::cout << "push() returned false, true was expected." << std::endl;
    return FAIL;
  }

  if(strcmp(memline, s.m.read(S_BASE_ADDR)) != 0) {
    std::cout << COLOR_RED << "Error: " << COLOR_STOP;
    std::cout << "push() failed to load " << memline << "onto the stack." << std::endl;
    return FAIL;
  }

  if(s.sp != 0) {
    std::cout << COLOR_RED << "Error: " << COLOR_STOP;
    std::cout << "push() failed to increment stack pointer." << std::endl;
    return FAIL;
  }

  if(!s.push(Y_ADDR)) {
    std::cout << COLOR_RED << "Error: " << COLOR_STOP;
    std::cout << "second push() returned false, true was expected." << std::endl;
    return FAIL;
  }

  return SUCCESS;
}

int spam::test_pop() {
  Stack s;

  s.m.store(X_ADDR, (char *)"3");
  s.m.store(Y_ADDR, (char *)"7");
  s.m.store(Z_ADDR, (char *)"6");

  s.push(X_ADDR);
  s.push(Y_ADDR);

  //if pop fails internally
  if(!s.pop(X_ADDR)) {
    std::cout << COLOR_RED << "Error: " << COLOR_STOP;
    std::cout << "pop() returned false, true was expected." << std::endl;
    return FAIL;
  }
  //if the value we popped wasn't what we expected to pop
  if(strcmp(s.m.read(X_ADDR), s.m.read(Y_ADDR)) != 0) {
    std::cout << COLOR_RED << "Error: " << COLOR_STOP;
    std::cout << "pop() stored " << s.m.read(X_ADDR) << "at X_ADDR, expected "
     << s.m.read(Y_ADDR) << "." << std::endl;
    return FAIL;
  }
  //if the stack pointer is misaligned
  if(s.sp != 0) {
    std::cout << COLOR_RED << "Error: " << COLOR_STOP;
    std::cout << "pop() misaligned the stack pointer." << std::endl;
    return FAIL;
  }

  //if pop fails internally on a second try
  if(!s.pop(Z_ADDR)) {
    std::cout << COLOR_RED << "Error: " << COLOR_STOP;
    std::cout << "pop() returned false on the second run, true was expected." << std::endl;
    return FAIL;
  }
  //if the value we popped wasn't what we expected to pop (3 isn't stored anymore)
  if(strcmp(s.m.read(Z_ADDR), "3") != 0) {
    std::cout << COLOR_RED << "Error: " << COLOR_STOP;
    std::cout << "pop() stored " << s.m.read(X_ADDR) << "at X_ADDR, expected "
     << s.m.read(Y_ADDR) << "." << std::endl;
    return FAIL;
  }
  //if the stack pointer is misaligned
  if(s.sp != -1) {
    std::cout << COLOR_RED << "Error: " << COLOR_STOP;
    std::cout << "pop() misaligned the stack pointer." << std::endl;
    return FAIL;
  }

  return SUCCESS;
}

int spam::test_add() {
  Stack s;

  s.m.store(X_ADDR, (char *)"3");
  s.m.store(Y_ADDR, (char *)"7");
  s.m.store(Z_ADDR, (char *)"6");

  s.push(X_ADDR);
  s.push(Y_ADDR);

  if(!s.add()) {
    std::cout << COLOR_RED << "Error: " << COLOR_STOP;
    std::cout << "add() failed internally. May not have had enough arguments." << std::endl;
    return FAIL;
  }

  int sum = atoi(s.m.read(S_BASE_ADDR + s.sp));
  //if we didn't add them as numbers properly
  if(sum != 10) {
    std::cout << COLOR_RED << "Error: " << COLOR_STOP;
    std::cout << "add() failed to add properly. (Result: " << sum << ")" << std::endl;
    return FAIL;
  }
  //if the stack pointer is misaligned
  if(s.sp != 0) {
    std::cout << COLOR_RED << "Error: " << COLOR_STOP;
    std::cout << "add() misaligned the stack pointer." << std::endl;
    return FAIL;
  }

  return SUCCESS;
}

int spam::test_mul() {
  Stack s;

  s.m.store(X_ADDR, (char *)"3");
  s.m.store(Y_ADDR, (char *)"7");
  s.m.store(Z_ADDR, (char *)"6");

  s.push(X_ADDR);
  s.push(Y_ADDR);

  if(!s.mul()) {
    std::cout << COLOR_RED << "Error: " << COLOR_STOP;
    std::cout << "mul() failed internally. May not have had enough arguments." << std::endl;
    return FAIL;
  }

  int product = atoi(s.m.read(S_BASE_ADDR + s.sp));
  //if we didn't multiply them as numbers properly
  if(product != 21) {
    std::cout << COLOR_RED << "Error: " << COLOR_STOP;
    std::cout << "mul() failed to add properly. (Result: " << product << ")" << std::endl;
    return FAIL;
  }
  //if the stack pointer is misaligned
  if(s.sp != 0) {
    std::cout << COLOR_RED << "Error: " << COLOR_STOP;
    std::cout << "mul() misaligned the stack pointer." << std::endl;
    return FAIL;
  }
  return SUCCESS;
}

//don't really think end is there for much except exiting
int spam::test_end(){
  Stack s;
  return (!s.end() ? SUCCESS : FAIL);
}
