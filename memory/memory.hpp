#ifndef BufferConstants

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

#define INST_SIZE 32
#define OPCODE_SIZE 8
#define ADDR_SIZE 24

#endif

#ifndef MEMORY_H
#define MEMORY_H

class Memory {
private:
  char* d[DBUF_SIZE]; /* Data buffer */
  char* t[TBUF_SIZE]; /* Text buffer */
  char* s[STCK_SIZE]; /* Stack buffer */
public:
  Memory(); /* Constructor */
  bool store (char type, char* line);
  char* read (int address);
  void  dump ();
};

#endif
