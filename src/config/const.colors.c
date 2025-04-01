
#ifdef __linux__
const char* GREEN = "\033[0;32m";
const char* BLUE = "\033[0;34m";
const char* YELLOW = "\033[0;33m";
const char* RED = "\033[0;31m";
const char* RESET = "\033[0m";
const char* PURPLE = "\033[0;35m";
#else
const char* GREEN = "";
const char* BLUE = "";
const char* YELLOW = "";
const char* RED = "";
const char* RESET = "";
const char* PURPLE = "";
#endif