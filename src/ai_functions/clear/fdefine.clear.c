//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end

char *agent_clear(cJSON *args, void *pointer){
    ModelProps *props = (ModelProps*)pointer;
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    printf("%s %s CLEARED SCREEN\n",YELLOW,props->model, RESET);
    return (char*)"cleared";
}
void configure_clear_callbacks(OpenAiInterface *openAi,const char *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_clear, (void*)model, "clear", "clear the screen", false);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}