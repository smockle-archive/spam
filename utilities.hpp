#ifndef BufferConstants
#define BufferConstants 1

  // Data spec
  #define DBUF_SIZE 256
  #define TBUF_SIZE 256
  #define STCK_SIZE 256

  #define D_BASE_ADDR 256
  #define T_BASE_ADDR 512
  #define S_BASE_ADDR 768

  /*
   * Instruction encoding details:
   * won't be relevant until we
   * hit section 4 of the homework.
   */

  #define X_ADDR 256
  #define Y_ADDR 257
  #define Z_ADDR 258

  #define INST_SIZE 32
  #define OPCODE_SIZE 8
  #define ADDR_SIZE 24

#endif

#ifndef ReturnConstants
#define ReturnConstants 1

  #define SUCCESS 0
  #define FAIL -1
  #define ARGUMENT_ERROR -10
  #define IO_ERROR -20
  #define TYPE_ERROR -30

#endif

#ifndef ColorConstants
#define ColorConstants 1

  #define COLOR_RED "\033[0;31m"
  #define COLOR_GREEN "\033[0;32m"
  #define COLOR_YELLOW "\033[0;33m"

  #define COLOR_STOP "\033[0m"

  #define COLOR_ERROR "\033[0;31mError:\033[0m"
  #define COLOR_EXCEPTION "\033[0;33mError:\033[0m"
  #define COLOR_SUCCESS "\033[0;32mSuccess:\033[0m"

#endif
