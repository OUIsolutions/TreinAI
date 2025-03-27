### Json Model Config

every time you call any action of the cli,it access the config json
the **config json** its a json that its encrypted and saved into the user home directory
the config json its used to store the models, urls, and keys from the user,and its saved into these
format:

```json
[ 
    {
        "model":        "grok-2-latest",
        "key":  "your_key",
        "url":  "https://api.x.ai/v1/chat/completions",
        "default":      true
    },
    {
        "model":        "gpt-3.5-turbo",
        "key":  "your_key",
        "url":  "https://openai.com/v1/chat/completions",
    }
    
]

```

### The json location
the json location its defined by your encrypted key +  the home directory of the user
its implemented on function [create_user_config_models_path](/src/model_props/fdefine.model_props.c)

you can get the path location putting a simple printf on the global **config_path** variable

```c
printf("config path: %s\n",config_path);
```
### The Json Encryption
the json its encrypted on every save and decrypted on every read, the encryption its made by the functions
**dtw.encryption.write_string_file_content_hex**  and **dtw.encryption.load_string_file_content_hex** on all the 
[actions](/src/actions/) files.
The global encryption object localized at [gobals](/src/globals.main_obj.c) its initialized in the beginning of the [main](/src/main.c) file, and uses the  **--encrypt_key** you pass on the build part, that its transformed on the 
macro **AiRagTemplate_get_key**