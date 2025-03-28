local alreay_amalamated_done = false
function amalgamation_build()
    print("\tstart almagamation")
    if alreay_amalamated_done then
        return
    end
    alreay_amalamated_done = true


    local runtime = darwin.camalgamator.generate_amalgamation("src/main.c")
    runtime = "#define DEFINE_DEPENDENCIES\n" .. runtime
  
    darwin.dtw.write_file("release/"..PROJECT_NAME..".c", runtime)



end
