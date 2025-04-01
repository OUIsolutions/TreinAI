//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end

char *agent_make_dir_resume(cJSON *args, void *pointer) {
    ModelProps *props = (ModelProps*)pointer;
    cJSON *path = cJSON_GetObjectItem(args, "path");
    if (!cJSON_IsString(path)) {
        return NULL;
    }
    printf("%s %s MADE DIR RESUME OF: '%s' (THESE PROCESS CAN CONSUME A LOT OF TOKENS) %s", YELLOW, props->model, path->valuestring, RESET);
    bool aply = ask_yes_or_no();
    if(!aply){
        return (char*)"user denied the operation";
    }


    CTextStack *dir_resume = newCTextStack_string("");
    DtwStringArray *all_items = dtw.list_files_recursively(path->valuestring, false);
    for (int i = 0; i < all_items->size; i++) {
        char *current_file = all_items->strings[i];
        bool is_hidden = dtw_starts_with(current_file, ".");
        if (!is_hidden) {
            char *joined = dtw_concat_path(path->valuestring, current_file);
            char *content = dtw.load_string_file_content(joined);
            if (content) {
              printf("%s %s MAKING A RESUME OF: %s\n", YELLOW, props->model, current_file, RESET);

                char *resume = make_resume(props, content);
                if (resume) {
                    CTextStack_format(dir_resume, "path_name: %s\n", current_file);
                    CTextStack_format(dir_resume, "resume: %s\n", resume);
                    CTextStack_text(dir_resume, "============================================\n");
                    free(resume);
                }
                free(content);
            }
            free(joined);
        }
    }
    dtw.string_array.free(all_items);
    return CTextStack_self_transform_in_string_and_self_clear(dir_resume);
}

void configure_make_dir_resume_callbacks(OpenAiInterface *openAi, ModelProps *props) {
    OpenAiCallback *callback = new_OpenAiCallback(agent_make_dir_resume, (void*)props, "make_dir_resume", "make a resume of all files in a directory", false);
    OpenAiInterface_add_parameters_in_callback(callback, "path", "Pass the path you want to make a resume of.", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}