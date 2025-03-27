

key_obfuscate = function()
    private_key_obfuscate = {}
    public_key_obfuscate = {}
    private_key_obfuscate.create_for = function(props,randonizer,procedural_props,project_name,code, already_existed_integers,bytes_to_save,total_scope)

        local var_name = project_name.."_scope_"..total_scope

        local predictibble =  private_key_obfuscate.make_predicible_operation(randonizer,procedural_props,project_name, already_existed_integers,bytes_to_save)
        
        code.append(private_key_obfuscate.create_padding(total_scope).."for(int "..var_name.." = "..predictibble.code.."; "..var_name.." < "..(predictibble.eval+1) .."; "..var_name.."++){\\\n")


    end 

    private_key_obfuscate.create_if = function(props,randonizer,procedural_props,project_name,code, already_existed_integers,bytes_to_save,total_scope)


        local predictibble =  private_key_obfuscate.make_predicible_operation(randonizer,procedural_props,project_name, already_existed_integers,bytes_to_save)
        
        local comparation = randonizer.choice({"==","<",">","<=",">=","~="})
        local dif = 0
        if comparation == "<"then
            dif = 1
        end
        if comparation == ">"then
            dif = -1
        end
        if comparation == "~="then
            dif = 2
        end


        code.append(private_key_obfuscate.create_padding(total_scope))
        code.append("if(")
        code.append(predictibble.code)
        code.append(" ")
        code.append(comparation)
        code.append(" ")
        code.append(predictibble.eval+dif)
        code.append("){\\\n")


    end 




    private_key_obfuscate.create_integer = function(props,randonizer,procedural_props,project_name,code, already_existed_integers,bytes_to_save,total_scope)

        local index = #already_existed_integers + 1
        local name = project_name.."_integer_"..index
        code.append(private_key_obfuscate.create_padding(total_scope).."int "..name.." = ")
        local predictibble =  private_key_obfuscate.make_predicible_operation(randonizer,procedural_props,project_name, already_existed_integers,bytes_to_save)
        code.append(predictibble.code)
        code.append(";")
        code.append("/*create:")
        code.append(predictibble.eval)
        code.append("*/")
        code.append("\\\n")
        --code.append(predictibble.evalated_str)
        already_existed_integers[index] = predictibble.eval
        if props.debug then 
            code.append("\tif("..predictibble.eval.." != "..name.."){")
            code.append('printf("expected %d and was %d at var ('..name..')\\n",'..predictibble.eval..','..name..');')
            code.append("}\\\n")
        end
        --code.append('printf("expected %d and was %d \\n",'..predictibble.eval..','..name..');')
        --code.append("\\\n")
    end






    private_key_obfuscate.fake_byte_set = function(props,randonizer,procedural_props,project_name,code, already_existed_integers,bytes_to_save,total_scope)
        local chosen_byte = private_key_obfuscate.get_randon_not_ajusted_byte(randonizer,bytes_to_save)
        if not chosen_byte then
            return
        end
        code.append(private_key_obfuscate.create_padding(total_scope).."key["..chosen_byte.index.."] = ")
        predictibble =  private_key_obfuscate.make_predicible_operation(randonizer,procedural_props,project_name, already_existed_integers,bytes_to_save)

        local fake_value = randonizer.generate_num(1,230)
        chosen_byte.ajusted = false
        chosen_byte.current_value = fake_value
        code.append(predictibble.code)
        if  predictibble.eval > 0 then
            code.append(" - ")
            code.append(predictibble.eval -fake_value)
        end

        if  predictibble.eval <= 0 then
            code.append(" + ")
            code.append(fake_value - predictibble.eval)
        end

        code.append(";")
        code.append("/*fake:")
        code.append(chosen_byte.byte)
        code.append("*/")
        code.append("\\\n")

        if props.debug then 
            code.append("\tif("..chosen_byte.byte.." != key["..chosen_byte.index.."]){")
            code.append('printf("expected %d and was %d at key['..chosen_byte.index..']\\n",'..chosen_byte.byte..',key['..chosen_byte.index..']);')
            code.append("}\\\n")
        end


    end




    private_key_obfuscate.integer_set = function(props,randonizer,procedural_props,project_name,code, already_existed_integers,bytes_to_save,total_scope)
        if  #already_existed_integers == 0 then
            return
        end
        local index = 1
        if #already_existed_integers > 1 then
            index = randonizer.generate_num(1,#already_existed_integers)
        end 
        local chosen_index_str =""..index
        local formmated_index = ""
        for j=1,#chosen_index_str do
            local current_char =private_key_obfuscate.sub(chosen_index_str,j,j)
            if current_char == "." then
                break
            end
            formmated_index = formmated_index.. current_char
        end
        
        local name = project_name.."_integer_"..formmated_index
        
        code.append(private_key_obfuscate.create_padding(total_scope)..name.." = ")
        local predictibble =  private_key_obfuscate.make_predicible_operation(randonizer,procedural_props,project_name, already_existed_integers,bytes_to_save)
        code.append(predictibble.code)
        code.append(";")
        code.append("/*set:")
        code.append(predictibble.eval)
        code.append("*/")
        code.append("\\\n")
        --code.append(predictibble.evalated_str)
        already_existed_integers[index] = predictibble.eval
        if props.debug then 
            code.append("\tif("..predictibble.eval.." != "..name.."){")
            code.append('printf("expected %d and was %d at var ('..name..')\\n",'..predictibble.eval..','..name..');')
            code.append("}\\\n")
        end
        --code.append('printf("expected %d and was %d \\n",'..predictibble.eval..','..name..');')
        --code.append("\\\n")
    end






    private_key_obfuscate.real_byte_sec = function(props,randonizer,procedural_props,project_name,code, already_existed_integers,bytes_to_save,total_scope)
        local chosen_byte = private_key_obfuscate.get_randon_not_ajusted_byte(randonizer,bytes_to_save)
        code.append(private_key_obfuscate.create_padding(total_scope).."key["..chosen_byte.index.."] = ")
        predictibble =  private_key_obfuscate.make_predicible_operation(randonizer,procedural_props,project_name, already_existed_integers,bytes_to_save)

        code.append(predictibble.code)
        if  predictibble.eval > 0 then
            code.append(" - ")
            code.append(predictibble.eval -chosen_byte.byte)
        end

        if  predictibble.eval <= 0 then
            code.append(" + ")
            code.append(chosen_byte.byte - predictibble.eval)
        end

        code.append(";")
        code.append("/*set:")
        code.append(chosen_byte.byte)
        code.append("*/")
        code.append("\\\n")

        if props.debug then 
            code.append("\tif("..chosen_byte.byte.." != key["..chosen_byte.index.."]){")
            code.append('printf("expected %d and was %d at key['..chosen_byte.index..']\\n",'..chosen_byte.byte..',key['..chosen_byte.index..']);')
            code.append("}\\\n")
        end

        chosen_byte.ajusted = true
        chosen_byte.current_value = chosen_byte.byte
    end





    private_key_obfuscate.create_bytes_to_save =function(key,starter_num)
        local bytes_to_save = {}
        for i=1,#key do 
            local byte_converted = private_key_obfuscate.byte(private_key_obfuscate.sub(key,i,i)) 

            if byte_converted < 0 then 
                print("Error: byte_converted < 0")
            end
            bytes_to_save[i] = {
                byte = byte_converted,
                index = i-1,--these its required because its a c array
                ajusted = false,
                current_value= starter_num
            }
        end 
        return bytes_to_save
    end 
    private_key_obfuscate.terminated= function(bytes_to_save)
        for i=1,#bytes_to_save do 
            if bytes_to_save[i].ajusted == false then 
                return false
            end 
        end 
        return true
    end 

    private_key_obfuscate.get_randon_byte = function(randonizer,bytes_to_save)
        local index = randonizer.generate_num(1,#bytes_to_save)
        return bytes_to_save[index]
    end

    private_key_obfuscate.get_randon_not_ajusted_byte = function(randonizer,bytes_to_save)

        local total_not_ajusted = {}
        for i=1,#bytes_to_save do 
            if bytes_to_save[i].ajusted == false then 
                total_not_ajusted[#total_not_ajusted + 1] = bytes_to_save[i]
            end 
        end

        if #total_not_ajusted == 0 then 
            return nil
        end
        if #total_not_ajusted == 1 then 
            return total_not_ajusted[1]
        end

        local index = randonizer.generate_num(1,#total_not_ajusted)
        return total_not_ajusted[index]

    end




    private_key_obfuscate.newCodeFormater = function()
        local added = {}
        local self_obj = {}
        self_obj.append = function(code)
            added[#added + 1] = code
        end
        self_obj.get_code = function()
            return private_key_obfuscate.concat(added)
        end
        return self_obj
    end 


    if string then 
    private_key_obfuscate.sub = string.sub
    private_key_obfuscate.byte = string.byte
    end
    if table then
    private_key_obfuscate.concat = table.concat
    end

    if pairs then
    private_key_obfuscate.pairs = pairs
    end
    if load then
    private_key_obfuscate.load = load
    end






    private_key_obfuscate.create_padding = function(size)
        local padding = "\t"
        for i=1,size do
            padding = padding.."\t"
        end
        return padding
    end
    private_key_obfuscate.parse_to_int_str = function(num)
        local int_str = ""..num
        local formmated = ""
        for i=1,#int_str do
            local current_char = private_key_obfuscate.sub(int_str,i,i)
            if current_char == "." then
                break
            end
            formmated = formmated..current_char
        end
        return formmated
    end






    private_key_obfuscate.make_predicible_operation = function(randonizer,procedural_props,project_name, already_existed_integers,bytes_to_save)
        local total_operations = randonizer.generate_num(
            procedural_props.min_operations_per_line,
            procedural_props.max_operations_per_line
        )
        local evalated_str = "return "
        local code = "("
        for i=1,total_operations do

            local operation_item = randonizer.choice({"byte","integer","random"})


            if operation_item == "byte" then 
                local chosen_byte = private_key_obfuscate.get_randon_byte(randonizer,bytes_to_save)
                code = code.." ".."key["..chosen_byte.index.."]"
                evalated_str = evalated_str.." "..private_key_obfuscate.parse_to_int_str(chosen_byte.current_value)
            
            elseif operation_item == "integer" and #already_existed_integers > 0 then 
                local chosen_index =1 
                if #already_existed_integers > 1 then
                    chosen_index = randonizer.generate_num(1,#already_existed_integers)
                end 
                local formmated_index = private_key_obfuscate.parse_to_int_str (chosen_index)
                local name = project_name.."_integer_"..formmated_index
                local value = already_existed_integers[chosen_index]
                code = code.." "..name
                evalated_str = evalated_str.." "..private_key_obfuscate.parse_to_int_str(value)
            else 
                local randon_int = randonizer.generate_num(1000,100000)
                code = code.." "..randon_int
                evalated_str = evalated_str.." "..private_key_obfuscate.parse_to_int_str(randon_int)
            end


            local operation = randonizer.choice({"+","-","*"})
            if i < total_operations then
                code = code .." "..operation 
                evalated_str = evalated_str.." "..operation
            end

        end 
        code = code..")"
        --print("evalated_str",evalated_str)
        return {code = code,eval = private_key_obfuscate.load(evalated_str)()}
    end 






    public_key_obfuscate.create_procedural_generation = function(props)
        local randonizer = private_key_obfuscate.newRandonizer(props.seed)

        local starter_num = randonizer.generate_num(1,100)
        local bytes_to_save = private_key_obfuscate.create_bytes_to_save(props.key,starter_num)
        local code  =private_key_obfuscate.newCodeFormater()

        local procedural_props = private_key_obfuscate.create_procedural_props(props)
        code.append("#ifndef "..props.name .. "_get_key_h\n")
        code.append("#define "..props.name .. "_get_key_h\n")
        code.append("#define "..props.name.."key_size "..#bytes_to_save.."\n")
        
        code.append("#define "..props.name.."_get_key(key) \\\n")

        code.append("\tfor(int i=0;i<"..#bytes_to_save..";i++){")
        code.append("key[i] = "..starter_num..";}\\\n")
        --set 0 to end 
        code.append("\tkey["..#bytes_to_save.."] = 0;\\\n")

        local created_integers = {}
        local total_scopes = 0
        while true do 

            if private_key_obfuscate.terminated(bytes_to_save) then 
                break
            end
            if total_scopes < procedural_props.max_scopes then
                local create_for = randonizer.generate_num(1,100)
                if create_for <= procedural_props.create_a_for * 100 then
                    private_key_obfuscate.create_for(props,randonizer,procedural_props,props.name,code,created_integers,bytes_to_save,total_scopes)
                    total_scopes = total_scopes + 1

                end                
                local create_if = randonizer.generate_num(1,100)
                if create_if <= procedural_props.create_a_if * 100 then
                    private_key_obfuscate.create_if(props,randonizer,procedural_props,props.name,code,created_integers,bytes_to_save,total_scopes)
                    total_scopes = total_scopes + 1
                end
            end



            local create_integer_choice = randonizer.generate_num(1,100)
            local create_integer_probability = procedural_props.create_a_integer
            if #created_integers >10 then
                create_integer_probability = procedural_props.create_a_integer_after10
            end
            if #created_integers >50 then
                create_integer_probability = procedural_props.create_a_integer_after50
            end
            
            --these stop the creation of integers
            if #created_integers >100 or total_scopes > 0 then
                create_integer_probability = -1
            end
            
            if create_integer_choice <= create_integer_probability * 100 then
            private_key_obfuscate.create_integer(props,randonizer,procedural_props,props.name,code,created_integers,bytes_to_save,total_scopes)
            end

            local set_real_byte = randonizer.generate_num(1,100)
            if set_real_byte <= procedural_props.real_byte_set * 100 then
                private_key_obfuscate.real_byte_sec(props,randonizer,procedural_props,props.name,code,created_integers,bytes_to_save,total_scopes)
            end
            
            local set_fake_byte = randonizer.generate_num(1,100)
            if set_fake_byte <= procedural_props.fake_byte_set * 100 then
                private_key_obfuscate.fake_byte_set(props,randonizer,procedural_props,props.name,code,created_integers,bytes_to_save,total_scopes)
            end

            if total_scopes > 0 then 
                local close_scope = randonizer.generate_num(1,100)
                if close_scope <= procedural_props.close_scopes * 100 then
                    total_scopes = total_scopes - 1
                    code.append(private_key_obfuscate.create_padding(total_scopes).."}\\\n")
                end
            end 

            local set_integer = randonizer.generate_num(1,100)
            if set_integer <= procedural_props.integer_set * 100 then
                private_key_obfuscate.integer_set(props,randonizer,procedural_props,props.name,code,created_integers,bytes_to_save,total_scopes)
            end
        end

        -- close all scopes
        for i=1,total_scopes do
            code.append("\t}\\\n")
        end
        
        code.append("\n#endif\n")
        return code.get_code()
    end 




    private_key_obfuscate.create_procedural_props = function(user_props)

        local defaut_props = {
            fake_byte_set = 0.5, --chance to set a unset byte a fake value
            create_a_integer = 0.33, --chance of create a interger  swap value
            create_a_integer_after10 = 0.10,
            create_a_integer_after50 = 0.05,
            make_a_usless_operation = 0.33,
            max_operations_per_line = 6,
            min_operations_per_line = 2,
            create_a_for =0.33,
            create_a_if = 0.33,
            max_scopes = 3,
            close_scopes = 0.66,
            integer_set = 0.33,
            fake_byte_set = 0.33,
            real_byte_set = 0.5,
        }
        if not user_props then
            return defaut_props
        end

        for key,value in pairs(defaut_props) do
            if user_props[key] then
                defaut_props[key] = user_props[key]
            end
        end
        return defaut_props

    end 



    private_key_obfuscate.flor = function(value)
        return value - (value % 1)
    end

    private_key_obfuscate.ajust = function(value,min,max)
        
        while value > max or value < min do
            if(value > max) then
                value = value / 3.9
            end
            if(value < min) then
                value = value * 3.5
            end
        end
        return private_key_obfuscate.flor(value)
    end

    private_key_obfuscate.rand_generate = function(value,seed)

        local TOTAL_LOOPS = 20
        local MIN_LIMIT = 1000
        local MAX_LIMIT = 100000
        local result = value
        
        for i=1,TOTAL_LOOPS do
            result = result * (seed / i + seed) 
            result = result * result
            result = private_key_obfuscate.ajust(result,MIN_LIMIT,MAX_LIMIT)
        end
        return private_key_obfuscate.ajust(result,MIN_LIMIT,MAX_LIMIT)
    end 

    private_key_obfuscate.newRandonizer = function(seed)
        local self_obj = {}
        local seed = seed
        local increment = 10
        self_obj.generate_num = function(min,max)
            if min == max then
                return min
            end
            
            increment = increment + 10
            local num = private_key_obfuscate.rand_generate(increment,seed)
            return private_key_obfuscate.ajust(num,min,max)
        end 
        self_obj.choice = function(itens)
            if #itens == 0 then
                return nil
            end
            if #itens == 1 then
                return itens[1]
            end
            local index = self_obj.generate_num(1,#itens)
            return itens[index]
        end
        return self_obj
    end


    return public_key_obfuscate

end 

key_obfuscate = key_obfuscate()