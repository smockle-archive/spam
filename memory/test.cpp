#include "memory.cpp"
#include <stdio.h>
#include <string.h>

using namespace std;

int main(int argc, char ** argv) {

  bool isVerbose = false;
  bool isDataClear = false;
  bool isTextClear = false;
  bool isStackClear = false;

  if(argc > 1 && strcmp(argv[1], "-v") == 0) isVerbose = true;

  Memory::Memory m;

  cout << "=== Is the memory properly being cleared? ===" << endl;
  if(isVerbose) cout << "Memory m content dump:" << endl << endl;
  if(isVerbose) m.dump();
  cout << "assert d[0], t[0], s[0] == 0 : ";
  isDataClear  = (m.read(D_BASE_ADDR) == (char*)'0');
  isTextClear  = (m.read(T_BASE_ADDR) == (char*)'0');
  isStackClear = (m.read(S_BASE_ADDR) == (char*)'0');
  cout << (isDataClear && isTextClear && isStackClear) << endl;
  if(isVerbose && !(isDataClear && isTextClear && isStackClear)) {
    cout << "The following memory regions did not pass:" << endl;
    if(!isDataClear)  cout << "- data"  << endl;
    if(!isTextClear)  cout << "- text"  << endl;
    if(!isStackClear) cout << "- stack" << endl;
  }
  
  return 0;
}
