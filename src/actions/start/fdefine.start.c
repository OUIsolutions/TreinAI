//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end


OpenAiInterface* initialize_openai_interface( ModelProps *props){

    OpenAiInterface *openAi = openai.openai_interface.newOpenAiInterface(props->url, props->key, props->model);
    if(!openAi){
      printf("%sError: %s%s\n", RED, "No openai interface found", RESET);
      return NULL;
    }
    Asset * main_system_rules = get_asset("system_instructions.json");
    if(!main_system_rules){
      printf("%sError: %s%s\n", RED, "No system instructions found", RESET);
      return NULL;
    }
    openai.openai_interface.add_system_prompt(openAi, main_system_rules->data);
    
    char name_message[100];
    snprintf(name_message,sizeof(name_message)-1,"your model base  its %s",props->model);

    openai.openai_interface.add_system_prompt(openAi,name_message);
    configure_get_context_doc_callbacks(openAi, props->model);
    configure_list_recursively_callbacks(openAi,props->model);
    configure_read_file_callbacks(openAi,props->model);
    configure_move_item_callbacks(openAi,props->model);
    configure_copy_item_callbacks(openAi,props->model);
    configure_write_file_callbacks(openAi, props->model);
    configure_execute_command_callbacks(openAi,props->model);
    configure_remove_file_callbacks(openAi,props->model);
    configure_save_url_to_file(openAi,props->model);
    configure_get_url(openAi,props->model);
    configure_set_context_doc(openAi, props->model);
    configure_terminate_callbacks(openAi,props->model);
    configure_make_dir_resume_callbacks(openAi,props);
    CTextStack *context_resume = newCTextStack_string("Avaliable Context Documentations:\n\n\n");

    DtwStringArray *librarys  = dtw.list_files_recursively(CONTEX_DIR,false);
    for(int i = 0; i < librarys->size; i++){
      char *current = librarys->strings[i];
      char *path = dtw.concat_path(CONTEX_DIR,current);
      char *content =dtw.load_string_file_content(path);
      if(content){
          printf("%sMAKING RESUME FOR: %s%s\n", YELLOW, current, RESET);
          char *resume = make_resume(props,content);
          if(resume){
            CTextStack_format(context_resume,"THESE ITS A RESUME,CALL get_context_doc for better information\n");
            CTextStack_format(context_resume,"context name: %s\n",current);
            CTextStack_format(context_resume,"resume:\n");

            CTextStack_format(context_resume,"%s\n",resume);
            CTextStack_text(context_resume,"============================================\n");
            free(resume);
          } 
          free(content);
      }
      free(path);
    }

    dtw.string_array.free(librarys);
    openai.openai_interface.add_system_prompt(openAi,context_resume->rendered_text);
    CTextStack_free(context_resume);
    printf("%sWelcome to the %s, runing: %s interface%s\n", BLUE, NAME_CHAT, props->model , RESET);
    return openAi;
}

int start_action(){

    ModelProps *props = collect_model_props();
    if(!props){
        return 1;
    }

    OpenAiInterface *openAi = initialize_openai_interface(props);
    if(!openAi){
        freeModelProps(props);
        return 1;
    }
    
    while (true){
        printf("%s >Your Message:%s", GREEN,PURPLE);
        char *message = collect_user_input();
        
        if(strcmp(message,"exit") == 0){
          free(message);
          break;
        }
        if(strcmp(message,"clear") == 0){
          #ifdef _WIN32
            system("cls");
          #else
            system("clear");
          #endif
          free(message);
          continue;
        }
        if(strcmp(message,"resset") == 0){

          printf("%sConversation reset.%s\n", GREEN, RESET);
          #ifdef _WIN32
            system("cls");
          #else
            system("clear");
          #endif
          openai.openai_interface.free(openAi);
          openAi = initialize_openai_interface(props);
          free(message);
          continue;
        }
        openai.openai_interface.add_user_prompt(openAi, message);

        OpenAiResponse *response =  OpenAiInterface_make_question_finish_reason_treated(openAi);
        if(openai.openai_interface.error(response)){
          printf("%sError: %s%s\n", RED, openai.openai_interface.get_error_message(response), RESET);
          free(message);
          break;
        }
        const char *first_answer = openai.response.get_content_str(response,0);
        if(first_answer == NULL){
          printf("%sError: %s%s\n", RED, "No answer found", RESET);
          free(message);
          break;
        }
        printf("%s < %s: %s%s\n", BLUE,props->model, first_answer, RESET);
        openai.openai_interface.add_response_to_history(openAi, response,0);
        free(message);
    }  
    freeModelProps(props);
    openai.openai_interface.free(openAi);

    return 0;
}