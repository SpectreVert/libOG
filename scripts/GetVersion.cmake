function(GetVersion VersionFile Identifier)
	execute_process(
					COMMAND grep ${Identifier} ${VersionFile}
					COMMAND sed -e s/${Identifier}://g
					COMMAND tr -d '\n'
					OUTPUT_VARIABLE Out
					)
	set(SVERSION ${Out} PARENT_SCOPE)
endfunction()
