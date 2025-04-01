//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.globals.h"
//silver_chain_scope_end

char *agent_make_dir_resume(cJSON *args, void *pointer) {
    const char *model = (const char*)pointer;
    cJSON *path = cJSON_GetObjectItem(args, "path");
    if (!cJSON_IsString(path)) {
        return NULL;
    }

    DtwStringArray *all_items = dtw.list_files_recursively(path->valuestring, false);
    cJSON *all_items_cjson = cJSON_CreateArray();
    for (int i = 0; i < all_items->size; i++) {
        char *current_file = all_items->strings[i];
        bool is_hidden = dtw_starts_with(current_file, ".");
        if (!is_hidden) {
            char *joined = dtw.concat_path(path->valuestring, current_file);
            char *content = dtw.load_string_file_content(joined);
            if (content) {
                char *resume = make_resume((ModelProps*)pointer, content);
                if (resume) {
                    cJSON_AddItemToArray(all_items_cjson, cJSON_CreateString(resume));
                    free(resume);
                }
                free(content);
            }
            free(joined);
        }
    }
    dtw.string_array.free(all_items);
    char *all_items_string = cJSON_PrintUnformatted(all_items_cjson);
    cJSON_Delete(all_items_cjson);
    printf("%s %s MADE DIR RESUME: %s\n", YELLOW, model, path->valuestring, RESET);
    return all_items_string;
}

void configure_make_dir_resume_callbacks(OpenAiInterface *openAi, const char *model) {
    OpenAiCallback *callback = new_OpenAiCallback(agent_make_dir_resume, (void*)model, "make_dir_resume", "make a resume of all files in a directory", false);
    OpenAiInterface_add_parameters_in_callback(callback, "path", "Pass the path you want to make a resume of.", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}