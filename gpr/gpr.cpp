#include "gpr.hpp"

// I consulted the following resources for help:
// http://www.cplusplus.com/doc/tutorial/control/

spam::GPR::GPR() {
  pc = 0;
};

spam::GPR::GPR(Registry * rp, Memory * mp) {
  pc = 0;
  registry = *rp;
  memory = *mp;
};

int spam::GPR::addi(int rdest, int rsrc, int imm) {
  return FAIL;
}

int spam::GPR::b(int label_addr) {
  return FAIL;
}

int spam::GPR::beqz(int rsrc, int label_addr) {
  return FAIL;
}

int spam::GPR::bge(int rsrc1, int rsrc2, int label_addr) {
  if (rsrc1 == rsrc2) {
    std::cout << COLOR_WARNING << "Destination and source register addresses are identical. It's more common to compare two different registers." << std::endl;
  }

  return FAIL;
}

int spam::GPR::bne(int rsrc1, int rsrc2, int label_addr) {
  if (rsrc1 == rsrc2) {
    std::cout << COLOR_WARNING << "Destination and source register addresses are identical. It's more common to compare two different registers." << std::endl;
  }
  return FAIL;
}

int spam::GPR::la(int rdest, int variable_addr) {
  return FAIL;
}

int spam::GPR::lb(int rdest, int offset, int rsrc) {
  if (rdest == rsrc) {
    std::cout << COLOR_WARNING << "Destination and source register addresses are identical. It's more common to compare two different registers." << std::endl;
  }
  return FAIL;
}

int spam::GPR::li(int rdest, int imm) {
  return FAIL;
}

int spam::GPR::subi(int rdest, int rsrc, int imm) {
  return FAIL;
}

int spam::GPR::syscall() {
  int op = registry.load(V0_ADDR);
  switch (op) {
    case SYSCALL_CIN:
      break;
    case SYSCALL_COUT:
      break;
    case SYSCALL_END:
      end();
      break;
    default:
      return FAIL;
  }
  return op;
}

int spam::GPR::run() {
  return FAIL;
}

int spam::GPR::end() {
  pc = -1;
  return SUCCESS;
}
