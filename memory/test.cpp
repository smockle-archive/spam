#include <iostream>
#include <string.h>
#include "memory.hpp"
#include "../skeleton/skeleton.hpp"

using namespace std;

int main(int argc, char ** argv) {

  bool  isVerbose = false;
  bool  isDataClear = false;
  bool  isTextClear = false;
  bool  isStackClear = false;
  bool  isAllClear = false;
  bool  isHelloWorld = false;
  char* c;

  int   passing = 0;
  int   failing = 0;
  int   run = 2;


  if(argc > 1 && strcmp(argv[1], "-v") == 0) isVerbose = true;

  Memory m;


  isDataClear  = (m.read(D_BASE_ADDR) == 0);
  isTextClear  = (m.read(T_BASE_ADDR) == 0);
  isStackClear = (m.read(S_BASE_ADDR) == 0);

  isAllClear = (isDataClear && isTextClear && isStackClear);

  if(isVerbose) {
    cout << endl << "%%%%%%%% TESTING MEMORY %%%%%%%%" << endl << endl;
    cout << "=== Is the memory properly being cleared? ===" << endl;
    cout << "Memory m content dump:" << endl;
    m.dump();
    cout << "assert (each array has a 0 at its base address) : ";
    cout <<
    (isAllClear ? "true" : "false") << endl;
    if(!isAllClear) {
      cout << "The following memory regions did not pass:" << endl;
      if(!isDataClear)  cout << "- data"  << endl;
      if(!isTextClear)  cout << "- text"  << endl;
      if(!isStackClear) cout << "- stack" << endl;
    }
    cout << "================================" << endl;
    cout << endl;
  }
  if(!isVerbose) {
    cout << (isAllClear ? COLOR_SUCCESS : COLOR_ERROR) << " ";
    cout << "Memory initialization test ";
    cout << (isAllClear ? "passed" : "failed");
    cout << "." << endl;
  }
  (isAllClear ? passing++ : failing++);

  isHelloWorld = m.store(T_BASE_ADDR, (char *)"hello world");
  c = m.read(T_BASE_ADDR);

  if(isVerbose) {
    cout << "=== Can we write to memory properly? ===" << endl;
    cout << "assert (storing \"hello world\" works) : ";
    cout << (isHelloWorld ? "true" : "false") << endl;
    cout << "memory @ T_BASE_ADDR: " << c << endl;
    cout << "assert (\"hello world\" is present in the text buffer) : ";
    cout << (isHelloWorld ? "true" : "false") << endl;
    cout << "================================" << endl;
    cout << endl;
  }
  if(!isVerbose) {
    cout << (isHelloWorld ? COLOR_SUCCESS : COLOR_ERROR) << " ";
    cout << "Memory write test ";
    cout << (isHelloWorld ? "passed" : "failed");
    cout << "." << endl;
  }
  (isHelloWorld ? passing++ : failing++);

  cout << "RESULTS:" << endl;
  cout << "\t" << run << " tests run." << endl;
  cout << "\t" << COLOR_GREEN << passing << " tests passed." << COLOR_STOP << endl;
  cout << "\t" << COLOR_RED << failing << " tests failed." << COLOR_STOP << endl;

  if(isVerbose) cout << "%%%%%%%% END TEST %%%%%%%%" << endl << endl;

  return (failing == 0) ? SUCCESS : FAIL;
}
