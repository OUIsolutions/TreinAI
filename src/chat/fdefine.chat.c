//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.globals.h"
//silver_chain_scope_end

char * collect_user_input(){
  fflush(stdout);
  char *buffer = (char*)malloc(100);
  int buffer_size = 100;
  int i = 0;
  char last_char = '\0';
  while(true){

    char c = getchar();
    if(c == '\n' && last_char != '\\'){
      buffer[i] = '\0';
      break;
    }

    if(i >= buffer_size - 2){
      buffer_size *= 2;
      buffer = (char*)realloc(buffer, buffer_size);
    }

    buffer[i] = c;
    last_char = c;
    i++;
  }
  return buffer;
}

bool ask_yes_or_no() {
    // Ask the user the question
    
    printf("%s(%sy%s/%sn%s): ",YELLOW, GREEN, YELLOW, RED, YELLOW);
    while(true){
      char *user_input = collect_user_input();
      // Check the user's response
      if (strcasecmp(user_input, "y") == 0) {
          free(user_input); // Clean up
        return true;     
      }
      if(strcasecmp(user_input, "yes") == 0){
          free(user_input); // Clean up
          return true;
      }
      if(strcasecmp(user_input, "no") == 0){
          free(user_input); // Clean up
          return false;
      }
      if(strcasecmp(user_input, "n") == 0){
          free(user_input); // Clean up
          return false;
      }
      printf("%sPlease enter %syes%s or %sno%s: ",RED, YELLOW, RED, YELLOW, RESET);
      free(user_input); // Clean up
  
    }

}