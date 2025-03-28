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
    printf("%s %s EXECUTED COMMAND: %s\n", YELLOW, model, command->valuestring, RESET);
    const int READ_SIZE = 100;

    char *output = calloc(READ_SIZE+1,sizeof(char));
    int output_allocated = READ_SIZE+1;
    int output_size = 0;
    FILE *fp = popen(command->valuestring, "r");
    if (fp) {
        while(true){
            if(output_size + READ_SIZE > output_allocated){
                output_allocated = READ_SIZE + (output_allocated * 2);
                output = realloc(output, output_allocated);
            }

            int total_read =  fread(output + output_size, 1, READ_SIZE-1, fp);
            if(total_read <= 0){
                break;
            }
            output_size += total_read;
            output[output_size] = '\0';
        }
        fclose(fp);
    }
    printf("chegou aqui\n");
    char *result_str = (char*)malloc(strlen(output) + 100);
    sprintf(result_str, "status: %s\nOutput: %s", result, output);
    printf("%s %s OUTPUT: %s\n", YELLOW, model, output);
    free(output);
    return result_str;
}

void configure_execute_command_callbacks(OpenAiInterface *openAi,const char *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_execute_command, (void*)model, "execute_command", "execute a command", false);
    OpenAiInterface_add_parameters_in_callback(callback, "command", "Pass the command you want to execute.", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}