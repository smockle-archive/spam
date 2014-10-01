#ifndef BufferConstants
#define BufferConstants 1

  // Data spec
  #define DBUF_SIZE 256
  #define TBUF_SIZE 256
  #define STCK_SIZE 256

  #define D_BASE_ADDR 256
  #define T_BASE_ADDR 512
  #define S_BASE_ADDR 768

  #define E_LEN 32

  /*
   * Instruction encoding details:
   * won't be relevant until we
   * hit section 4 of the homework.
   */

  #define X_ADDR 256
  #define A_ADDR 257
  #define B_ADDR 258
  #define C_ADDR 259

  #define Y_ADDR 257
  #define Z_ADDR 258

  #define T1_ADDR 0
  #define T2_ADDR 1
  #define T3_ADDR 2
  #define T4_ADDR 3
  #define V0_ADDR 29
  #define A0_ADDR 30
  #define A1_ADDR 31

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

#ifndef Utilities
#define Utilities 1

  #include <algorithm>
  #include <functional>
  #include <cctype>
  #include <locale>
  #include <iostream>
  #include <string>

  namespace spam {
    // SOURCE: http://stackoverflow.com/a/217605/1923134
    // trim from start
    inline std::string ltrim(std::string s) {
      s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
      return s;
    }

    // trim from end
    inline std::string rtrim(std::string s) {
      s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
      return s;
    }

    // trim from both ends
    inline std::string trim(std::string s) {
      return ltrim(rtrim(s));
    }

    inline std::string tolower(std::string s) {
      int i = 0;
      for (char c : s) {
        s[i] = std::tolower(c);
        i++;
      }
      return s;
    }

    inline int valueof(std::string s) {
      if (s.find(" ") == std::string::npos) {
        #ifndef TEST
        std::cout << COLOR_EXCEPTION << " valueof() was passed a string without spaces. Data is usually in the form \"X: 3\"." << std::endl;
        #endif
        return FAIL;
      }
      return atoi(s.substr(s.find(" ")).c_str());
    }
  }

#endif
