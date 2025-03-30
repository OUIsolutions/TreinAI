//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end

char * collect_user_input(){
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

    if(i >= buffer_size - 1){
      buffer_size *= 2;
      buffer = (char*)realloc(buffer, buffer_size);
    }

    buffer[i] = c;
    last_char = c;
    i++;
  }
  return buffer;
}

