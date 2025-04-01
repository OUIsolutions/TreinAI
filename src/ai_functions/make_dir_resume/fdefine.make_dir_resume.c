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

    CTextStack *dir_resume = newCTextStack_string("");
    DtwStringArray *all_items = dtw.list_files_recursively(path->valuestring, true);
    for (int i = 0; i < all_items->size; i++) {
        char *current_file = all_items->strings[i];
        printf("%s %s MAKING A RESUME OF: %s\n", YELLOW, props->model, current_file, RESET);
        bool is_hidden = dtw_starts_with(current_file, ".");
        if (!is_hidden) {
            char *content = dtw.load_string_file_content(current_file);
            if (content) {
                char *resume = make_resume(props, content);
                if (resume) {
                    CTextStack_format(dir_resume, "path_name: %s\n", current_file);
                    CTextStack_format(dir_resume, "resume: %s\n", resume);
                    CTextStack_text(dir_resume, "============================================\n");
                    free(resume);
                }
                free(content);
            }
        }
    }
    dtw.string_array.free(all_items);
    char *dir_resume_string = dir_resume->rendered_text;
    CTextStack_free(dir_resume);
    printf("%s %s MADE DIR RESUME: %s\n", YELLOW, model, path->valuestring, RESET);
    return dir_resume_string;
}

void configure_make_dir_resume_callbacks(OpenAiInterface *openAi, ModelProps *props) {
    OpenAiCallback *callback = new_OpenAiCallback(agent_make_dir_resume, (void*)props, "make_dir_resume", "make a resume of all files in a directory", false);
    OpenAiInterface_add_parameters_in_callback(callback, "path", "Pass the path you want to make a resume of.", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}