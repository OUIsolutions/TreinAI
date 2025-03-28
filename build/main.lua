---@class Darwin
darwin = darwin


function main()
    local first_action = darwin.argv.get_next_unused()

    if first_action == "test_container" then
        local container_name = darwin.argv.get_next_unused()
        if container_name == nil then
            print("Please provide a container name")
            return
        end
        os.execute("mkdir -p release")
        local image = darwin.ship.create_machine(container_name .. ":latest")
        image.provider = CONTANIZER

        image.start({
            flags = { "-it" },
            volumes = {
                { "./release", "/release" },
            },
        })

        return
    end

  

    local encrypt_key = darwin.argv.get_flag_arg_by_index({ "encrypt_key"}, 1)
    if not encrypt_key then
        print("Please provide an encrypt_key")
        return
    end
    darwin.silverchain.remove("src")

    create_encrypt_key(encrypt_key)

    Install_dependencies()
    create_assets()
    silver_chain_organize()

    local build_funcs = create_build_funcs()


    darwin.dtw.remove_any("release")
    darwin.dtw.remove_any(".cache")
    local i = 1
    for name, buld_lambda in pairs(build_funcs) do
        local existe = darwin.argv.one_of_args_exist(name)
        if existe then
            print("\n=========================================================================================")
            print("\tstarted of build:", i, "\n")
            buld_lambda()
            print("\n\tA build [" .. i .. "] finished")
            print("=========================================================================================\n\n")
            i = i + 1
        end
    end

    darwin.dtw.move_any_overwriting("release/alpine_static_bin.out","release/"..PROJECT_NAME..".out")
    darwin.dtw.move_any_overwriting("release/windows64.exe","release/"..PROJECT_NAME.."64.exe")
    darwin.dtw.move_any_overwriting("release/windowsi32.exe","release/"..PROJECT_NAME.."i32.exe")
    darwin.dtw.move_any_overwriting("release/debian_static.deb","release/"..PROJECT_NAME..".deb")
    darwin.dtw.move_any_overwriting("release/rpm_static_build.rpm","release/"..PROJECT_NAME..".rpm")

end
