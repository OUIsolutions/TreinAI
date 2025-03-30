### Build Workflow
### IMPORTANT:
### For understand these part, read [build_instructions.md](/docs/build_instructions.md) and [build_toolchain.md](/docs/build_toolchain.md) first

### [main.lua](/build/main.lua)
- verify if its to test a container 
  - if its to test a container , creates and launch that container and end build

- creates the encryption key (basically its creates a file called **src/macros.encrypt_key.h** ) containing 
  a macro called **TreinAI_get_key** that its used to get the encryption key 
  check [key_obfuscate](https://github.com/OUIsolutions/key_obfuscate) for more details
  
- Installs the dependencies
- create the assets embed vars [Assets docs](/assets/docs/assets_embed_vars.md)
- make silver chain src organization read [build_toolchain.md](/assets/docs/build_toolchain.md) for more details
- create the [build_functions](/build/build_funcs.lua) and stores on a table, to be able to be called correlated to command lines
- iterate over the build functions and call the function that matches the command line

### Build Functions

- [amalgamation_build](/build/build/amalgamation_build.lua) generate the **release/TreinAI.c** file that contains all the source code of the project
- [alpine_static_build.lua](/build/build/alpine_static_build.lua) build the project using alpine linux and static linking and generates the **release/TreinAI.out** binary
- [debian_static_build.lua](/build/build/debian_static_build.lua) build the **release/TreinAI.deb** package
- [local_linux_build.lua](/build/build/local_linux_build.lua) build the project using the local linux and generates the **TreinAI** binary in the root folder of the project
- [rpm_static_build.lua](/build/build/rpm_static_build.lua) build the **release/TreinAI.rpm** package
- [windows64_build.lua](/build/build/windows64_build.lua) build the project using windows 64bits and generates the **release/TreinAI64.exe** binary
- [windowsi32_build.lua](/build/build/windowsi32_build.lua) build the project using windows 32bits and generates the **release/TreinAIi32.exe** binary
