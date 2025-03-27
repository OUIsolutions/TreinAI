### Project Workflow and use case

When the project starts at [main.c](/src/main.c) the first thing that it's to create the 
globals objects located in [globals](/src/globals.main_obj.c): 
### Globals 
- **args_obj** object to store the argv keys , check[C-argv-parser](https://github.com/OUIsolutions/C-argv-parser)
for more details

- **config_path** object to store the path of the [config_json](/docs/json_model_config.md) file
    that uses the macro **AiRagTemplate_get_key** and **AiRagTemplate_key_size** to get the encryption key

- **encryption** object to read and write the [config_json](/docs/json_model_config.md) file and encrypt the data
  check [DoTheWorld Encryption Docs](https://github.com/OUIsolutions/DoTheWorld/blob/main/docs/encryption.md) for more details


after it , it gets the **action** from the user,  which correspond to the first **argv[1]**argument of the program
and then, call one of the actions functions located at [actions](/src/actions/)

### Actions

### int configure_model();

The `configure_model` function, located in `src/actions/configure_model/fdefine.configure_model.c`, is responsible for configuring a language model. It checks if the necessary arguments (`model`, `key`, and `url`) have been provided. If any are missing, it displays an error message. Otherwise, it reads the content of the configuration file, checks if the model already exists, and updates or adds the model to the configuration file in JSON format. The function uses encryption to read and write the configuration file.

- **Functionality**: Configures a language model by checking for required arguments and updating the configuration file.
- **Error Handling**: Displays error messages if `model`, `key`, or `url` are not provided.
- **File Operations**: Reads and writes to the configuration file using encryption.
- **JSON Handling**: Manages the JSON structure of the configuration file, adding or updating model entries as needed.

### int list_model();

The `list_models` function, located in `src/actions/list_models/fdefine.list_models.c`, is responsible for listing all configured language models. It reads the encrypted configuration file, parses the JSON content, and then iterates through the array of models to display their details.

- **Functionality**: Lists all configured language models by reading and parsing the configuration file.
- **Error Handling**: Displays an error message if no models are found or if the configuration file cannot be parsed.
- **File Operations**: Reads the configuration file using encryption.
- **JSON Handling**: Parses the JSON structure of the configuration file to extract model information.
- **Output**: Prints the model name, URL, and whether it is set as the default model for each model in the configuration.

### int resset();

The `resset` function, located in `src/actions/resset/fdefine.resset.c`, is responsible for resetting the configuration by removing the configuration file.

- **Functionality**: Resets the configuration by deleting the configuration file.
- **File Operations**: Uses `dtw.remove_any` to remove the configuration file.
- **Error Handling**: No specific error handling is implemented; it simply returns 0 after attempting to remove the file

### int set_model_as_default();

The `set_model_as_default` function, located in `src/actions/set_model_as_default/fdefine.set_model_as_default.c`, is responsible for setting a specific model as the default model in the configuration.

- **Functionality**: Sets a specified model as the default by updating the configuration file.
- **Error Handling**: 
  - Displays an error message if no model is provided.
  - Displays an error message if no models are found in the configuration file.
  - Displays an error message if the specified model is not found.
- **File Operations**: Reads and writes to the configuration file using encryption.
- **JSON Handling**: 
  - Parses the JSON content of the configuration file.
  - Removes all existing 'default' flags from the models.
  - Adds a 'default' flag to the specified model if found.
- **Output**: Updates the configuration file with the new default model setting.