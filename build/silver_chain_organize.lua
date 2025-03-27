
local silver_chain_organize_done = false
function silver_chain_organize()
    if silver_chain_organize_done then
        return
    end
    silver_chain_organize_done = true
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
end 