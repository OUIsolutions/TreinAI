//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.globals.h"
//silver_chain_scope_end

char *make_resume(ModelProps *props,const char *content){
    if (strlen(content) < 500) {
        return strdup(content);
    }
    OpenAiInterface *openAi = openai.openai_interface.newOpenAiInterface(props->url, props->key, props->model);
    openai.openai_interface.set_cache(openAi,CACHE_POINT,true);
    openai.openai_interface.add_system_prompt(openAi,"make the resume of at most 1/5 of the original size");    
    openai.openai_interface.add_system_prompt(openAi, "make the resume for AI understand");
    openai.openai_interface.add_system_prompt(openAi,"always put functions,class,methods,global variables, and other code-related information in the resume");
    openai.openai_interface.add_system_prompt(openAi, "dont add extra informations, just the resume");
    CTextStack *text = newCTextStack_string_format("make a resume of %s",content);
    openai.openai_interface.add_user_prompt(openAi,text->rendered_text);
    OpenAiResponse *response =  openai.openai_interface.make_question(openAi);
    if(openai.openai_interface.error(response)){
        printf("%sError: %s%s\n", RED, openai.openai_interface.get_error_message(response), RESET);
        openai.openai_interface.free(openAi);
        CTextStack_free(text);
        return NULL;
    }
    const char *first_answer = openai.response.get_content_str(response,0);
    if(first_answer == NULL){
        printf("%sError: %s%s\n", RED, "No answer found", RESET);
        openai.openai_interface.free(openAi);
        CTextStack_free(text);
        return NULL;
    }
    char *copy_first_answer = strdup(first_answer);
    openai.openai_interface.free(openAi);
    CTextStack_free(text);
    return copy_first_answer;
}