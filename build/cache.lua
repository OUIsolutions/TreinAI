

function cache_execution(entries,executor,side_efect_verifier)
    local ident = false
    local entreis_data  = darwin.json.dumps_to_string(entries,ident)
    local entries_sha = darwin.dtw.generate_sha(entreis_data)
    
    local side_effect_sha = darwin.dtw.load_file(".cacherag/"..entries_sha)
    if side_effect_sha then
        local side_effect_verification = side_efect_verifier()


        if side_effect_sha == side_effect_verification and side_effect_verification then
            print("cached: ",entreis_data)
            return
        end
    end
    print("executing: ",entreis_data)

    executor()
    local side_effect_verification = side_efect_verifier()
    darwin.dtw.write_file(".cacherag/"..entries_sha,side_effect_verification)

end 