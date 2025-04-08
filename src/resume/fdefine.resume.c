//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../imports/imports.globals.h"
//silver_chain_scope_end

char *make_resume(ModelProps *props, const char *content) {
    OpenAiInterface *openAi = openai.openai_interface.newOpenAiInterface(props->url, props->key, props->model); 
    Asset *role_system = get_asset("make_resume_role_system.json");
    if(!role_system){
        printf("%sError: %s%s\n", RED, "Role make_resume_role_system.json not found", RESET);
        openai.openai_interface.free(openAi);
        return NULL;
    }
    openai.openai_interface.add_system_prompt(openAi, role_system->data);
    
    CTextStack *text = newCTextStack_string_format("make a resume of %s", content);
    openai.openai_interface.add_user_prompt(openAi, text->rendered_text);

    //==================cache test 
      
    DtwHash *hasher = dtw.hash.newHash();
    char *model = cJSON_GetObjectItem(openAi->body_object, "model")->valuestring;
    dtw.hash.digest_string(hasher,model);
    char *menssages = cJSON_Print(openAi->messages);
    dtw.hash.digest_string(hasher, menssages);
    free(menssages);

    


    OpenAiResponse *response = openai.openai_interface.make_question(openAi);
    if (openai.openai_interface.error(response)) {
        printf("%sError: %s%s\n", RED, openai.openai_interface.get_error_message(response), RESET);
        openai.openai_interface.free(openAi);
        CTextStack_free(text);
        return NULL;
    }
    const char *first_answer = openai.response.get_content_str(response, 0);
    if (first_answer == NULL) {
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