#include <iostream>
#include <string.h>
#include "memory.hpp"

using namespace std;

int main(int argc, char ** argv) {

  bool  isVerbose = false;
  bool  isDataClear = false;
  bool  isTextClear = false;
  bool  isStackClear = false;
  char* c;


  if(argc > 1 && strcmp(argv[1], "-v") == 0) isVerbose = true;

  Memory m;

  cout << endl << "%%%%%%%% TESTING MEMORY %%%%%%%%" << endl << endl;
  cout << "=== Is the memory properly being cleared? ===" << endl;
  if(isVerbose) cout << "Memory m content dump:" << endl;
  if(isVerbose) m.dump();
  cout << "assert (each array has a 0 at its base address) : ";
  isDataClear  = (m.read(D_BASE_ADDR) == 0);
  isTextClear  = (m.read(T_BASE_ADDR) == 0);
  isStackClear = (m.read(S_BASE_ADDR) == 0);
  cout << ((isDataClear && isTextClear && isStackClear) ? "true" : "false") << endl;
  if(isVerbose && !(isDataClear && isTextClear && isStackClear)) {
    cout << "The following memory regions did not pass:" << endl;
    if(!isDataClear)  cout << "- data"  << endl;
    if(!isTextClear)  cout << "- text"  << endl;
    if(!isStackClear) cout << "- stack" << endl;
  }
  cout << "================================" << endl;
  cout << endl;

  cout << "=== Can we write to memory properly? ===" << endl;
  cout << "assert (storing \"hello world\" works) : ";
  cout << (m.store(T_BASE_ADDR, (char *)"hello world") ? "true" : "false") << endl;
  c = m.read(T_BASE_ADDR);
  if(isVerbose) cout << "memory @ T_BASE_ADDR: " << c << endl;
  cout << "assert (\"hello world\" is present in the text buffer) : ";
  cout << ((strcmp(c, "hello world") == 0) ? "true" : "false") << endl;
  cout << "================================" << endl;
  cout << endl;

  cout << "%%%%%%%% END TEST %%%%%%%%" << endl << endl;

  return 0;
}
