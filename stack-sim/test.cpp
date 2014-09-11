#include "stack-sim.hpp"
#include "../skeleton/skeleton.hpp"

#define X 3
#define Y 7
#define Z 6

int main(int argc, char ** argv){

  bool  isVerbose = false;

  int   passing = 0;
  int   failing = 0;
  int   run = 4;

  if(argc > 1 && strcmp(argv[1], "-v") == 0) isVerbose = true;

  StackSim s;

  s.m.store(X_ADDR, (char *)X);
  s.m.store(Y_ADDR, (char *)Y);
  s.m.store(Z_ADDR, (char *)Z);

  s.push(X_ADDR);
  s.push(Y_ADDR);
  s.push(Z_ADDR);

  if(!isVerbose) {
  }

  return 0;
}
