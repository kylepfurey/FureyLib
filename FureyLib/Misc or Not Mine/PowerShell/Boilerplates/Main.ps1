# .ps1
# Program Main Entry Point Script

# Entry point of the program.
function Main {
	param ([Parameter(ValueFromRemainingArguments=$true)][string[]]$Arguments)
	$Arguments = $Arguments -split ' '
	Write-Output "Hello, Dinner!"

	# New code here

	return "Program exited with code " + (0) + "."
}

Main $args
