### Json Model Config

every time you call any action of the CLI, it accesses the config JSON. The **config JSON** is a JSON that is encrypted and saved into the user's home directory. The config JSON is used to store the models, URLs, and keys from the user, and it's saved in this format:

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

### The JSON location
The JSON location is defined by your encrypted key + the home directory of the user. It's implemented in the function [create_user_config_models_path](/src/model_props/fdefine.model_props.c).

You can get the path location by putting a simple printf on the global **config_path** variable.

```c
printf("config path: %s\n",config_path);
```
### The JSON Encryption
The JSON is encrypted on every save and decrypted on every read. The encryption is made by the functions **dtw.encryption.write_string_file_content_hex** and **dtw.encryption.load_string_file_content_hex** in all the [actions](/src/actions/) files. The global encryption object localized at [globals](/src/globals.main_obj.c) is initialized at the beginning of the [main](/src/main.c) file, and it uses the **--encrypt_key** you pass on the build part, which is transformed into the macro **AiRagTemplate_get_key**.