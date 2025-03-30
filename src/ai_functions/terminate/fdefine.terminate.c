//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end

char *agent_terminate(cJSON *args, void *pointer){
    const char *model = (const char*)pointer;
    printf("%s %s TERMINATED CONVERSATION\n",YELLOW,model, RESET);
    exit(0);
    return NULL;
}

void configure_terminate_callbacks(OpenAiInterface *openAi,ModelProps *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_terminate, (void*)model, "terminate", "terminate the conversation", false);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}