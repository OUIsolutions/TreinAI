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
    printf("%s %s EXECUTED COMMAND: %s\n", YELLOW, model, command->valuestring, RESET);
    const int READ_SIZE = 100;
    char *output = calloc(READ_SIZE+1,sizeof(char));

    int output_allocated = READ_SIZE+1;
    int output_size = 0;
    FILE *fp = popen(command->valuestring, "r");
    if (fp == NULL) {
        free(output);
        return NULL; 
    }
    while(true){
        if((output_size + READ_SIZE) > output_allocated){
            output_allocated = READ_SIZE + (output_allocated * 2);
            output = realloc(output, output_allocated);
        }

        int total_read =  fread(output + output_size, sizeof(char), READ_SIZE-1, fp);
        printf("total_read: %d\n", total_read);
        if(total_read <= 0){
            break;
        }

        output_size += total_read;
        output[output_size] = '\0';

    }

    int result = pclose(fp);
    char *result_str = (char*)malloc(strlen(output) + 100);
    sprintf(result_str, "status: %d\nOutput:\n%s", result, output);
    free(output);
    return result_str;
}

void configure_execute_command_callbacks(OpenAiInterface *openAi,const char *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_execute_command, (void*)model, "execute_command", "execute a command", false);
    OpenAiInterface_add_parameters_in_callback(callback, "command", "Pass the command you want to execute.", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}