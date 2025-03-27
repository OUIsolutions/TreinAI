local windows_build_done = false
function windowsi64_build()
    if windows_build_done then
        return
    end
    windows_build_done = true
    silver_chain_organize()

    os.execute("mkdir -p release")

    local image = darwin.ship.create_machine("debian:latest")
    image.provider = CONTANIZER
    image.add_comptime_command("apt-get update")
    image.add_comptime_command("apt-get -y install mingw-w64")
    local compiler = "x86_64-w64-mingw32-gcc"
    if LAUNGUAGE == "cpp" then
        compiler = "x86_64-w64-mingw32-g++"
    end
    image.start({
        volumes = {
            { "./release", "/release" },
            { "./src",     "/src" },
            { "./dependencies",     "/dependencies" }
        },
        command = compiler.." --static -DDEFINE_DEPENDENCIES  /src/main.c -o /release/windows64.exe -lws2_32"
    })
end
