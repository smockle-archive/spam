#include "gpr.hpp"

spam::GPR::GPR() {
  self = 0;
  pc = 0;
};

spam::GPR::GPR(Registry * rp, Memory * mp) {
  self = 0;
  pc = 0;
  registry = *rp;
  memory = *mp;
};

int spam::GPR::addi(int rdest, int rsrc, int imm) {
  return FAIL;
}

int spam::GPR::b(char* label) {
  return FAIL;
}

int spam::GPR::beqz(int rsrc1, int rsrc2, char* label) {
  return FAIL;
}

int spam::GPR::bge(int rsrc1, int rsrc2, char* label) {
  return FAIL;
}

int spam::GPR::bne(int rsrc1, int rsrc2, char* label) {
  return FAIL;
}

int spam::GPR::la(int rdest, int addr) {
  return FAIL;
}

int spam::GPR::lb(int rdest, int addr) {
  return FAIL;
}

int spam::GPR::li(int rdest, int imm) {
  return FAIL;
}

int spam::GPR::subi(int rdest, int rsrc, int imm) {
  return FAIL;
}

int spam::GPR::syscall() {
  return FAIL;
}

int spam::GPR::decode_label(char* label) {
  return FAIL;
}

int spam::GPR::run() {
  return FAIL;
}

int spam::Accumulator::end() {
  pc = -1;
  #ifndef TEST
  std::cout << "Output: " << self << std::endl;
  #endif
  return SUCCESS;
}
