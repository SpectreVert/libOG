function(GetVersion VersionFile)
	execute_process(
					COMMAND grep MAJOR ${VersionFile}
					COMMAND sed -e s/MAJOR://g
					COMMAND tr -d '\n'
					OUTPUT_VARIABLE Out
					)
	set(MAJOR ${Out} PARENT_SCOPE)
	execute_process(
					COMMAND grep MINOR ${VersionFile}
					COMMAND sed -e s/MINOR://g
					COMMAND tr -d '\n'
					OUTPUT_VARIABLE Out
					)
	set(MINOR ${Out} PARENT_SCOPE)
	execute_process(
					COMMAND grep PATCH ${VersionFile}
					COMMAND sed -e s/PATCH://g
					COMMAND tr -d '\n'
					OUTPUT_VARIABLE Out
					)
	set(PATCH ${Out} PARENT_SCOPE)
endfunction()
