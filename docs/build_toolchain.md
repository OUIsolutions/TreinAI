### Build ToolChain Explanation
### IMPORTANT:
### For understand these part, read [Build Instructions](/docs/build_instructions.md) first


The Build process use [darwin](https://github.com/OUIsolutions/Darwin) to build the project  in mode full folder, 
witch means, it recursively list over the folder [Build Folder](/build/) and execute the code inside, starting 
by the [main.lua](/build/main.lua) file.

the build code use the following dependencies:


### LuaArgv
[LuaArgv](https://github.com/OUIsolutions/LuaArgv) is a simple lib to parse argv, and its used to detect the build actions

### LuaDotheWorld
[LuaDoTheWorld](https://github.com/OUIsolutions/LuaDoTheWorld) its a wrapper of the original [DoTheWorld](https://github.com/OUIsolutions/LuaDoTheWorld) project, and [LuaDoTheWorld](https://github.com/OUIsolutions/LuaDoTheWorld) provides a series of 
function, to manipulate files and directories, like hashers, listings, read and write in files, etc.

### LuaShip
[LuaShip](https://github.com/OUIsolutions/LuaShip) its a Podman/Docker wrapper , that its used to create some releases such as:

- release/AiRagTemplate64.exe
- release/AiRagTemplate.deb
- release/AiRagTemplatei32.exe
- release/AiRagTemplate.out
- release/AiRagTemplate.rpm

all the builds functions,are located  in the [build functions](/build/build) part


### LuaSilverChain
[LuaSilverChain](https://github.com/OUIsolutions/LuaSilverChain) its a wrapper of the original [SilverChain](https://github.com/OUIsolutions/SilverChain) project, and [LuaSilverChain](https://github.com/OUIsolutions/LuaSilverChain) its used to organize the import order of the C codes,by making each type of file ,import others in a specific order, for example in the follwing tree:
```txt
src/
├── actions
│   ├── configure_model
│   │   ├── fdeclare.configure_model.h
│   │   └── fdefine.configure_model.c
│   ├── list_models
│   │   ├── fdeclare.list_models.h
│   │   └── fdefine.list_models.c
│   ├── remove_model
│   │   ├── fdeclare.remove_model.h
│   │   └── fdefine.remove_model.c
│   ├── resset
│   │   ├── fdeclare.resset.h
│   │   └── fdefine.resset.c
│   ├── set_model_as_default
│   │   ├── fdeclare.set_model_as_default.h
│   │   └── fdefine.set_model_as_default.c
│   └── start
│       ├── fdeclare.start.h
│       └── fdefine.start.c
├── ai_functions
│   ├── fdeclare.ai_functions.h
│   └── fdefine.ai_functions.c
├── assets
│   ├── fdeclare.assets.h
│   ├── fdefine.asset.c
│   ├── globals.assets.c
│   └── types.assets.h
├── chat
│   ├── fdeclare.chat.h
│   └── fdefine.chat.c
├── config
│   ├── consts.actions.h
│   ├── consts.flags.h
│   ├── consts.paths.h
│   └── macros.colrors.h
├── confjson
│   ├── fdeclare.conf_json.h
│   └── fdefine.conf_json.c
├── globals.main_obj.c
├── imports
│   ├── imports.consts.h
│   ├── imports.dep_declare.h
│   ├── imports.fdeclare.h
│   ├── imports.fdefine.h
│   ├── imports.fdefine,list_models.h
│   ├── imports.globals.h
│   ├── imports.macros.h
│   └── imports.types.h
├── main.c
├── model_props
│   ├── fdeclare.model_props.h
│   ├── fdefine.model_props.c
│   └── types.model_props.h
├── namespace
│   ├── fdeclare.namespace.h
│   ├── fdefine.namespace.c
│   └── globals.namespace.c
└── src_dependencies
    ├── dep_declare.dependencies.h
    └── fdefine.dependencies.c
```

all the files that starts with **fdefine** will "see" the files of **globals** , witch will see the files of fdeclare, and so on, this way, the code will be compiled in the right order, and the code will be more organized.

check: [silverchain_organize.lua](/build/silver_chain_organize.lua) for see the order of importations:

```lua
    darwin.silverchain.generate({
        src = "src",
        project_short_cut = "PROJECT_NAME",
        tags = { 
            "dep_declare",
            "macros",
            "types",
            "consts",
            "fdeclare",
            'globals',
            "fdefine",
    }})
```

### LuaCAmalgamator
[LuaCAmalgamator](https://github.com/OUIsolutions/LuaCAmalgamator) its a wrapper of the original [CAmalgamator](https://github.com/OUIsolutions/CAmalgamator) project, and [LuaCAmalgamator](https://github.com/OUIsolutions/LuaCAmalgamator) its used to create a single file from the C files, this way, the code will be more organized, and the code will be more easy to read, and to maintain.

check [amalgamation_build.lua](/build/build/amalgamation_build.lua) for see the amalgamation process:

```lua
local already_amalgamated_done = false
function amalgamation_build()
    if already_amalgamated_done then
        return
    end
    already_amalgamated_done = true


    local runtime = darwin.camalgamator.generate_amalgamation("src/main.c")
    runtime = "#define DEFINE_DEPENDENCIES\n" .. runtime
  
    darwin.dtw.write_file("release/"..PROJECT_NAME.." .c", runtime)


end

```

### key_obfuscate
key obfuscate its responsable to create the encryption key, and its used to create a file called **src/macros.encrypt_key.h** containing a macro called **AiRagTemplate_get_key** that its used to get the encryption key, check [key_obfuscate](https://github.com/OUIsolutions/key_obfuscate) for more details