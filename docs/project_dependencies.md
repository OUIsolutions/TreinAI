These Project Use the Following Dependencies:
### [C-argv-parser](https://github.com/OUIsolutions/C-argv-parser)
its used to parse the command line arguments, its used in the [main.c](/src/main.c) to parse the command line arguments.
and used by all [actions](/src/actions) to parse the arguments of the actions.


### [BearHttpsClient](https://github.com/OUIsolutions/BearHttpsClient)
[BearHttpsClient](https://github.com/OUIsolutions/BearHttpsClient) its used by [ClientSDKOpenAI](https://github.com/SamuelHenriqueDeMoraisVitrio/ClientSDKOpenAI) to access api urls with https.

### [ClientSDKOpenAI](https://github.com/SamuelHenriqueDeMoraisVitrio/ClientSDKOpenAI)  
[ClientSDKOpenAI](https://github.com/SamuelHenriqueDeMoraisVitrio/ClientSDKOpenAI) its the main sdk of the project, it uses [BearHttpsClient](https://github.com/OUIsolutions/BearHttpsClient) to access the api urls.
providing all ai functions necessary to build the agents.
the sdk implementations in the project are located in [fdefine.start.c](/src/actions/start/fdefine.start.c) (main chat) and on
[fdefine.ai_functions.c](/src/ai_functions/fdefine.ai_functions.c)(functions that can be called by AI)


### [DoTheWorld](https://github.com/OUIsolutions/DoTheWorld) 
[DoTheWorld](https://github.com/OUIsolutions/DoTheWorld) its responsible for dealing with files and directories, so its used to 
the [fdefine.ai_functions.c](/src/ai_functions/fdefine.ai_functions.c) to access directories and files, and its also used to read 
 and write the **.oui_models.json** (json that store user models)

### [cJSON](https://github.com/DaveGamble/cJSON) 
Its used to parse and dump the **.oui_models.json** file, its mostly used in the [confjson](/src/confjson/) and on [model_props](/src/model_props/)