to configure a ai function ,you must create 2 files on 
src/ai_functions/<function_name>
1 - fdeclare<function_name>.h
2 - fdefine<function_name>.c
the fdeclare<function_name>.h file must contain the function signature
the fdefine<function_name>.c file must contain the function implementation
the function signature must be declared in the fdeclare<function_name>.h file
and the function implementation must be declared in the fdefine<function_name>.c file

must be 2 functions defined, following the example below

~~~c
char *agent_<function_name>(cJSON *args, void *pointer){
    const char *model = (const char*)pointer;
    cJSON *path = cJSON_GetObjectItem(args, "path");
    cJSON *content = cJSON_GetObjectItem(args, "content");
    if(!cJSON_IsString(path) || !cJSON_IsString(content)){
        return NULL;
    }

    if(dtw.entity_type(path->valuestring) == DTW_FOLDER_TYPE){
        printf("%s REMOVE THE FOLDER '%s' TO SAVE THE FILE%s",RED,path->valuestring,RESET);
        bool remove = ask_yes_or_no();
        if(remove){
            dtw.remove_any(path->valuestring);
        }
        else{
            return (char*)"user canceled";
        }
    }

    long size;
    bool is_binary;
    char *temp_content = (char *)dtw.load_any_content(path->valuestring, &size, &is_binary);

    dtw.write_string_file_content(path->valuestring, content->valuestring);

   
    printf("%s %s APLY THE MODIFCATIONS IN: '%s'%s",YELLOW,model, path->valuestring, PURPLE);
    bool aply = ask_yes_or_no();
    if(!aply){
        //means that file already exists
        if(temp_content){
            dtw.write_any_content(path->valuestring, temp_content, size);
        }
        //means the file not existed before
        else{
           dtw.remove_any(path->valuestring);
        }
        release_if_not_null(temp_content,free);
        return (char*)"user canceled";
    }

    release_if_not_null(temp_content,free);
    return (char*)"file wrotted";
}

void configure_<function_name>(OpenAiInterface *openAi,const char *model){
    OpenAiCallback *callback = new_OpenAiCallback(agent_write_file, (void*)model, "write_file", "write a file content", false);
    OpenAiInterface_add_parameters_in_callback(callback, "path", "Pass the path you want to write.", "string", true);
    OpenAiInterface_add_parameters_in_callback(callback, "content", "Pass the content you want to write.", "string", true);
    OpenAiInterface_add_callback_function_by_tools(openAi, callback);
}
~~~

if its a operation that changes something in the system, you must ask the user if he wants to do the operation


you also need to add the configuration in **src/actions/start/fdefine.start.c** in the **initialize_openai_interface** 
you also must configure  **assets/system_instructions.json** to call the function, based on it needs