## Build Instructions

### Build Requirements 
#### Darwin 
For Build the project you must have [Darwin](https://github.com/OUIsolutions/Darwin) installed on version 0.2.0
if you are on linux you can install darwin with:

```bash
curl -L https://github.com/OUIsolutions/Darwin/releases/download/0.2.0/darwin.c -o darwin.c &&
gcc darwin.c -o darwin.out &&
sudo mv darwin.out /usr/bin/darwin
```

### Local Build from Linux
make a local build to test with the following command it will create the **AiRagTemplatetest.out** file
```bash
darwin run_blueprint build/ --mode folder local_linux_build --encrypt_key "your_encryption_key"
```

### Full Build from Docker or Podman
You must have podman or docker installed on your machine to build in these way, you can set what you want to use on the [build/config.lua](/build/config.lua) file.

if you want to make a full build to all platforms you can use the following command, it will create the following files:
```bash
 darwin run_blueprint build/ --mode folder amalgamation_build alpine_static_build windowsi32_build windowsi64_build rpm_static_build debian_static_build -encrypt_key "your_encryption_key"
```

Output files:
- release/AiRagTemplate64.exe
- release/AiRagTemplate.c
- release/AiRagTemplate.deb
- release/AiRagTemplatei32.exe
- release/AiRagTemplate.out
- release/AiRagTemplate.rpm

### Build Configurations
All build configurations are in the **build/config.lua** file.
the default its: 
```lua
PROJECT_NAME = "AiRagTemplate"
CONTANIZER   = "podman"
VERSION      = "0.0.9"
LICENSE      = "MIT"
URL          = "https://github.com/OUIsolutions/Ai-RagTemplate"
DESCRIPITION = "A Rag Based Template for C"
FULLNAME     = "Ai-RagTemplate"
EMAIL        = "mateusmoutinho01@gmail.com"
SUMARY       = "A Rag Based Template for C"
YOUR_CHANGES = "--"
```


### Making your own build
you can make your own build by using the following commands:
```bash
darwin run_blueprint build/ --mode folder --encrypt_key "your_encryption_key" 
```

than you can compile with gcc in the way you want:
- single unit compilation:
```bash
 gcc src/main.c -DDEFINE_DEPENDENCIES -o my_executable
```
- multi_compilation:
```bash
mkdir libs
#these its required because doTheWorld already have cjson
gcc -c dependencies/BearHttpsClient.c -o libs/BearHttpsClient.o  -DBEARSSL_HTTPS_MOCK_CJSON_DEFINE
gcc -c  dependencies/CArgvParse.c -o libs/CArgvParse.o
gcc -c dependencies/doTheWorld.c -o libs/doTheWorld.o
gcc src/main.c -o TreinAI libs/BearHttpsClient.o libs/doTheWorld.o libs/CArgvParse.o
```


### Testing Releases
you can launch a container to test your releases with the following command:
these will launch a container with **distro_name** with the **release** folder mounted
```bash
darwin run_blueprint build/ --mode folder test_container distro_name
```
exemple:
```bash
darwin run_blueprint build/ --mode folder test_container alpine
```