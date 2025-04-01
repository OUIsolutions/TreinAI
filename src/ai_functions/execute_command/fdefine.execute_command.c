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
    printf("%s %s EXECUTE COMMAND: '%s'%s",YELLOW,model, command->valuestring, PURPLE);
    bool aply = ask_yes_or_no();
    if(!aply){
        return strdup("user denied the command execution");
    }
    
    char *full_command = (char*)malloc(strlen(command->valuestring) + 100);
    if(!full_command){
        return strdup("Error internal.");
    }
    sprintf(full_command, "%s  &> cache.txt", command->valuestring);
    int result = system(full_command);    
    free(full_command);
    char *output = dtw.load_string_file_content("cache.txt");
    if(!output){
        return strdup("Error internal.");
    }

    dtw.remove_any("cache.txt");
    char *result_str = (char*)malloc(strlen(output) + 100);
    sprintf(result_str, "status: %d\nOutput:\n%s", result, output);
    free(output);
    printf("%s %s EXECUTED COMMAND: %s%s\n", YELLOW, model, command->valuestring, RESET);
    return result_str;
}

void configure_execute_command_callbacks(OpenAiInterface *openAi,const char *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_execute_command, (void*)model, "execute_command", "execute a command", true);
    OpenAiInterface_add_parameters_in_callback(callback, "command", "Pass the command you want to execute.", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}
