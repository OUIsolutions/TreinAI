//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain
#include "../../src/imports/imports.globals.h"
//silver_chain_scope_end

bool is_file_native_ignorable(cJSON *native_ignorables,int total_ignorables, const char *file){
    CTextStack *converted_file = newCTextStack_string(file);
    for(int j = 0; j < total_ignorables; j++){
        cJSON *ignorable_file = cJSON_GetArrayItem(native_ignorables, j);
        if(CTextStack_index_of(converted_file,ignorable_file->valuestring) != -1){
            CTextStack_free(converted_file);
            return true;
        }
    }
    CTextStack_free(converted_file);
    return false;
}
bool is_file_a_hiden_file(const char *file){
    long size = strlen(file);
    for(int i = 1; i < size; i++){
        if(file[i-1] == '\\' || file[i-1] == '/'){
            if(file[i] == '.'){
                return true;
            }
        }
    }
    return false;
}

DtwStringArray *parse_git_ignore(const char *git_ignore){
    
    DtwStringArray *parsed = newDtwStringArray();
    CTextArray *lines = CTextArray_split(git_ignore, "\n");
    for(int i = 0; i <lines->size; i++){
        CTextStack *item =lines->stacks[i]; 
        CTextStack_self_replace(item, "\n", "");
        CTextStack_self_replace(item, "\r", "");
        CTextStack_self_replace(item, "\t", "");
        CTextStack_self_trim(item);

        if(strcmp(item->rendered_text, "") == 0){
            continue;
        }
        if(CTextStack_starts_with(item, "#")){
            continue;
        }
        dtw.string_array.append(parsed,item->rendered_text);
    }
    CTextArray_free(lines);
    return parsed;
}

DtwStringArray *try_to_get_git_ignore(const char *listage_path){
    
    long size = strlen(listage_path);
    for(int i = 0; i < size; i++){
        if(listage_path[i] == '\\' || listage_path[i] == '/'){
            CTextStack *item = newCTextStack_string(listage_path);
            CTextStack_self_substr(item, 0, i);
            char *possible_git_ignore =dtw.concat_path(item->rendered_text,".gitignore");
            CTextStack_free(item);
            printf("possible_git_ignore: %s\n", possible_git_ignore);
            char *possible_git_ignore_content = dtw.load_string_file_content(possible_git_ignore);
            free(possible_git_ignore);
            if(possible_git_ignore_content){
                DtwStringArray *parsed = parse_git_ignore(possible_git_ignore_content);
                free(possible_git_ignore_content);
                return parsed;
            }
        }
    }
    char *possible_git_ignore = dtw.concat_path(listage_path,"/.gitignore");
    char *possible_git_ignore_content = dtw.load_string_file_content(possible_git_ignore);
    free(possible_git_ignore);
    if(possible_git_ignore_content){
        DtwStringArray *parsed = parse_git_ignore(possible_git_ignore_content);
        free(possible_git_ignore_content);
        return parsed;
    }
    return NULL;
}

DtwStringArray *list_files_recursively_not_incluidng_ignorable_files(const char *listage_path){
    
    Asset *ignorable_files = get_asset("ignorable_files.json");
    if(!ignorable_files){
        printf("%sError: %s%s\n", RED, "File ignorable_files.json not found", RESET);
        return NULL;
    }
    cJSON *parsed_ignorable_files = cJSON_Parse(ignorable_files->data);
    if(!parsed_ignorable_files){
        printf("%sError: %s%s\n", RED, "Error parsing ignorable_files.json", RESET);
        return NULL;
    }

    DtwStringArray *git_ignore = try_to_get_git_ignore(listage_path);
    if(git_ignore){
        for(int i = 0; i < git_ignore->size; i++){
            char *item = git_ignore->strings[i];
           printf("git_ignore: (%s)\n", item);
        }
    }
    printf("--------------------\n");

    int total_ignorable_files = cJSON_GetArraySize(parsed_ignorable_files);

    DtwStringArray *filtered = newDtwStringArray();
    DtwStringArray *all= dtw.list_files_recursively(listage_path,true);
    for (int i = 0; i < all->size; i++){
        char *file = all->strings[i];
  
        if(is_file_native_ignorable(parsed_ignorable_files,total_ignorable_files,file)){
            continue;
        }
        if(is_file_a_hiden_file(file)){
            continue;
        }

        DtwStringArray_append(filtered, file);
    }
    
    DtwStringArray_free(all);
    return filtered;
}