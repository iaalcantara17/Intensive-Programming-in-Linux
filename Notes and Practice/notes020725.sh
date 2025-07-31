#!/bin/bash

# Arithmetic Expansion:
# 	allows to perform arithmetic operations like +, -, %, / ** etc
# 	we use $((expression))
#
# 	ex: echo 1+1 -> 1+1
# 	ex: echo $((1+1)) -> 2
#
# Filename expansion:
# 	Bash scans all words/text for certain characters like *, ?,
# 	If the text contain these characters, then it's regarded as a pattern
# 	And replaces all the filenames matching the pattern.
