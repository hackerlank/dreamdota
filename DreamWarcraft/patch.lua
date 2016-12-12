----------------------------------------------------------------------------------------
-- Starcraft II Universal Fixer
----------------------------------------------------------------------------------------

function main()
	print("Patching MPQ...")
	do_patch(fs.path("Resource.mpq"))
end

-- Do patch
-- mpq_path - Path of the mpq, type is fs.path
function do_patch(mpq_path)

	-- Try to open the mpq
	local mpq_handle = ar.stormlib_open_archive(mpq_path, 0, 0)

	if mpq_handle ~= 0 then
		-- *************************
		-- Process mpq
		-- Your code goes here...
		
		--ar.stormlib_set_hash_table_size(mpq_handle, 4096) --only need for sc2 ? 
		
		--script
		patch_mpq_by_dir(
			mpq_handle, 					-- MPQ handle
			"MPQContents",					-- Source directory
			"",					-- Path prefix
			true							-- To check contents
		)

		-- End process
		-- **************************

		-- Flush and close MPQ
		ar.stormlib_close_archive(mpq_handle)
	else
		print(string.format("Error. Cannot open \"%s\"", mpq_path:file_string()))
	end
end

------------------------------------------------------------------------------------------
-- Utility functions
------------------------------------------------------------------------------------------

-- Calculate MD5 value of a file
-- file_path - Path of a file, type must be fs.path
-- return md5 value(type is string), or nil if error occured
function md5_checksum_file(file_path)
	local content = load_file(file_path)
	return content and crypto.evp.digest("md5", content) or nil
end

-- Load contents of a file
-- file_path - Path of a file, type must be fs.path
-- return file content, or nil if error occured
function load_file(file_path)
	local f, e = io.open(file_path:file_string(), "rb")

	if f then
		local content = f:read("*a")
		f:close()
		return content
	else
		return nil, e
	end
end

-- Add file to MPQ. If check is true, it will first check whether the two files are
-- the same. Otherwise will directly add it to mpq
-- mpq_handle - Handle of the MPQ, HANDLE type
-- src_path - File path, fs.path type
-- path_in_mpq - Path string in MPQ, string type
-- check - Whether to check, boolean type
function check_and_add_file(mpq_handle, src_path, path_in_mpq, flags, check)
	local to_add = true
	local result = true
	
	--print("   ")
	--print("src_path = "..tostring(src_path))
	--print("path_in_mpq = "..path_in_mpq)

	if check then
		local success, fm_content = ar.stormlib_load_file(mpq_handle, path_in_mpq)
		if success and md5_checksum_file(src_path) == crypto.evp.digest("md5", fm_content) then
			to_add = false
		end
	end

	if to_add then
		result = ar.stormlib_add_or_replace_file(
			mpq_handle,
			src_path,
			path_in_mpq,
			flags
		)
		if result then
			print(string.format("Added %s", src_path:filename()))
		else
			print(string.format("Failed to add %s", src_path:filename()))
			--sys.system("pause")
		end
	else
		print(string.format("Skipped %s", src_path:filename()))
	end

	return result
end

-- Add files in a directory to another mpq, with dest path provided
-- mpq_handle - Destination MPQ handle, HANDLE type
-- src_dir - Source directory path, fs.path or string type
-- prefix_in_mpq - Path prefix in dest MPQ, string type
-- check - Check if the files are the same. true will check; false will not check
-- No return value
function patch_mpq_by_dir(mpq_handle, src_dir, prefix_in_mpq, check)
	local src = type(src_dir) == "string" and fs.path(src_dir) or src_dir

	print(string.format("Processing: %s", src:file_string()))

	-- Iterate over the directory
	for file in lfs.dir(src:file_string()) do
		local full_path = src / file
		-- Do with file and directory
		if lfs.attributes(full_path:file_string()).mode == "file"			-- Normal file
		then
			-- Add to MPQ
			check_and_add_file(
				mpq_handle,
				full_path,
				(prefix_in_mpq == "" and file or prefix_in_mpq .. "\\" .. file),
				bit.bor(MPQ_FILE_COMPRESS, MPQ_FILE_REPLACEEXISTING),
				check
			)
		elseif lfs.attributes(full_path:file_string()).mode == "directory"	-- Directory
		then
			if file ~= "." and file ~= ".." and file ~= ".svn" then
				-- Recursively do
				patch_mpq_by_dir(mpq_handle, full_path,
					(prefix_in_mpq == "" and file or prefix_in_mpq .. "\\" .. file), check
				)
			end
		end
	end
end

-- Entry point
main()
