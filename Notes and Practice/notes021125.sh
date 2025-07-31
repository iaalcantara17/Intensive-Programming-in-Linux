#!/bin/bash

func()
{
	echo "hello"
	echo "world"
}

x=$(func)

echo $x

head /etc/passwd




















# functions: act as a mini-script in bash
# accept parameters (based on position like $1, $2, etc.)
# accept command substitution

# within a function ${N} refers to the function parameters
# and outside the function ${N} refers to the shell parameters

#function my_function() 
#{
#	echo $1
#	echo $2
#}

#my_function

#function my_function() 
#{
#	local var=10
#	global_scope="this is in global scope"
#	echo $global_scope
#	return 100 # return in bash is used to return the exit status of a function
#
#	return
#
#	if [ 10 -le 11 ];
#		return
#	fi
#	echo "hello"
#}
#my_function

#output=$(my_function)
#echo $output

#my_function
#echo $global_scope
#echo $var

# another method to create a function

#myfunction()
#{
#
#}


























# case statements
# similar to switch statement in java
# executes based on a specific statement
# each statements ends with a pair of semicolon.

# Shell Parameters: the arguments passed as we invoke the script
# parameters are accessed based on their position like ${N}

#echo $0 # refers to name of the script
#echo $1 # refers to the first argument
#echo $2 # refers to the second argument

#echo $# # extract the length of parameters
#echo $* # extract all the elements except the program name
#echo $@ # extract all the elements except the program name

#for i
#do
#	echo $i
#	sleep 1
#done















# syntax:
# case value in
# 1) statement 1;;
# 2) statement 2;;
# *) default statement;;
# esac


#read var
#
#case $var in
#	1) echo "entered one";;
#	two) echo "entered two";;
#	3 | three) echo "entered three";;
#	*) echo "unknown value";;
#esac























# Arrays in Bash
# Two types of arrays
# 1. one-dimensional (indexed)
# 2. associative arrays

#pet=("a cat" dog "a snake")
#pet[100]="turtle"

# to declare use:
# 	declare -A arr_name

#declare -A shade
#shade[red]=apple
#shade[yellow]=banana
#shade[green]=grape

#echo ${shade[red]}

#for i in "${!shade[@]}"
#do
#	echo $i
#done

















#echo ${pet[0]} # extract element at index 0

# extract all elements using * and @
#echo ${pet[*]}
#echo ${pet[@]}

#echo ${pet:1:3} # extract from position 3 of length 3

#echo ${#pet[@]} # extracts the length
#echo ${!pet[@]} # extracts the index of the elements

#for i in one two three four
#do
#	echo $i
#done

# syntax for while
# 	 while [ expression ]
# 	 do
# 	 	statements
# 	 done

# continued pet example

## both * and @ combine all the words of all elements together and divide them into words based on special characters

# with double quotes for *, bash treats all the elements as a single string.

# with double quotes for @, bash treats each elements within a pair of quotes.

# "$pet[*]" => all elements as a single string
#"$pet[@]" => each element within a pair of quotes

#pet=("a cat" dog "a snake")
#pet[100]="turtle"

#for i in "${pet[@]}" # -> asterisks combines all of the words into one element and then separate them individually
#do
#	echo $i
#	sleep 2
#done

