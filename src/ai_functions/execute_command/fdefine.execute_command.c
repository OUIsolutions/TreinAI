//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end

char *agent_execute_command(cJSON *args, void *pointer){
    const char *model = (const char*)pointer;
    cJSON *command = cJSON_GetObjectItem(args, "command");
    if(!cJSON_IsString(command)){
        return NULL;
    }
    int result = system(command->valuestring);
    printf("%s %s EXECUTED COMMAND: %s\n",YELLOW,model, command->valuestring, RESET);
    char *result_str = (char*)malloc(20);
    sprintf(result_str, "%d", result);
    return result_str;
}

void configure_execute_command_callbacks(OpenAiInterface *openAi,const char *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_execute_command, (void*)model, "execute_command", "execute a command", false);
    OpenAiInterface_add_parameters_in_callback(callback, "command", "Pass the command you want to execute.", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}