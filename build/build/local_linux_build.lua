

function create_objects_ar()
    local compiler = "gcc"
    if LAUNGUAGE == "cpp" then
        compiler = "g++"
    end
    os.execute("mkdir -p libs")
    local itens = {
      {command=compiler.." -c dependencies/doTheWorld.c -o libs/doTheWorld.o",entrie_path="dependencies/doTheWorld.c",out_path="libs/doTheWorld.o"},
    {command=compiler.." -c dependencies/BearHttpsClient.c -o libs/BearHttpsClient.o -DBEARSSL_HTTPS_MOCK_CJSON_DEFINE",entrie_path="dependencies/BearHttpsClient.c",out_path="libs/BearHttpsClient.o"},
    {command=compiler.." -c dependencies/CArgvParse.c -o libs/CArgvParse.o",entrie_path="dependencies/CArgvParse.c",out_path="libs/CArgvParse.o"},
    }

    for _, item in ipairs(itens) do
        
        local executor = function()
            os.execute(item.command)
        end
        local side_effect_verifier = function()            
            return darwin.dtw.generate_sha_from_file(item.out_path)
        end

        local sha =darwin.dtw.generate_sha_from_file(item.entrie_path)
        cache_execution({ "create .o object", item.entrie_path,item.out_path, item.command ,sha}, executor, side_effect_verifier)
    end


end 
function local_linux_build()

    create_objects_ar()
    local compiler = "gcc"
    if LAUNGUAGE == "cpp" then
        compiler = "g++"
    end
    local compilation =compiler.." -o "..PROJECT_NAME .." src/main.c libs/doTheWorld.o libs/BearHttpsClient.o libs/CArgvParse.o "
    print("compilation: ", compilation)
    os.execute(compilation)
   
end