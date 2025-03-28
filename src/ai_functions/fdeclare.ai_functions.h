//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.consts.h"
//silver_chain_scope_end


void configure_list_recursively_callbacks(OpenAiInterface *openAi,const char *model);

char *agent_read_file(cJSON *args, void *pointer);

void configure_read_file_callbacks(OpenAiInterface *openAi,const char *model);

char *agent_write_file(cJSON *args, void *pointer);

void configure_write_file_callbacks(OpenAiInterface *openAi,const char *model);

char *agent_execute_command(cJSON *args, void *pointer);

void configure_execute_command_callbacks(OpenAiInterface *openAi,const char *model);

char *agent_remove_file(cJSON *args, void *pointer);

void configure_remove_file_callbacks(OpenAiInterface *openAi,const char *model);

char *agent_terminate(cJSON *args, void *pointer);

void configure_terminate_callbacks(OpenAiInterface *openAi,const char *model);

char *agent_clear(cJSON *args, void *pointer);


void configure_clear_callbacks(OpenAiInterface *openAi,const char *model);