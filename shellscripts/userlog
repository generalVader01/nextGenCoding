#!/bin/bash

# userlog.sh: A script to retrive useful information

LOG_FILE=/var/log/auth.log # The log file to be read
USER=$1 
SUCCESS_OR_FAILURE=$2
ISLOCAL=$3 
SUCCESS="-s" 
FAILURE="-f"
SHOW_HELP="--help" 
SHOW_ALL="--all" 

# This function shows how to run the script 
 
show_script_usage () {
	echo "Usage: ./userlog.sh <user> <success or failure> 
for addtiional information, type: ./userlog.sh --help" 1>&2
	exit 10
}       

# Basic help menu - Provides additional information 

show_help () {
        echo "This is a help menu.

To show all logged activity in the file with the user, the first argument should be the user name
Example: ./userlog.sh john 

The program can also accept a 2nd argument, which specifies if the the program will display only failures, successes, or both 

The second argument accepts three different commands: 

-s, --success: Prints out authentication successes associated with the user
-f, --failure: Prints out authentication failures  associated with the user
-a, --all: Prints out all logging associated with the user

Example: ./userlog.sh john -s : Prints out authentication successes associated with the user 
Example: ./userlog.sh john -f : Prints out authentication failures associated with the user
Example: ./userlog.sh john -a : Prints out all logging activitiy associated with the user 

And so on and so forth. 

Possible application of this program: 

1) Find all activity associated with the root account (./userlog.sh root --all)
2) Find all failed attempts to switch over to the root account, with a given user (./userlog.sh john -f | grep root)
3) Find all successful attempts to switch users (EX: ./userlog.sh john -s | grep "Successful su") 
4) Find all attempts by a user with no sudo powers to invoke sudo (EX: ./userlog.sh john -a | grep "NOT in sudoers")
5) Output all logging of a user to a file (EX: ./userlog.sh john -a > john.txt)
And much more ... 
"

exit 10

}

# This function will show all successes associated with a user regarding authentication 

success() {

# Iterates through standard input, and scans each line of input for required input
while read -r line
do 
        if grep -q $USER <<<$line
	then

                read -r line 
		# Reads line of text
                PROMPT=$line 
		# Sets the aforementioned text equal to the PROMPT 
		read -r line 

		# If line contains the phase "uthentication failure", then do NOT echo that line
                if [[ "$PROMPT" != *"uthentication failure"* ]]  
		then
                        echo $PROMPT 
		fi 
        fi 

done < "$LOG_FILE" # Content of the log file is loaded 

exit 10 # Terminates 

}

# Failure - This function outputes all authentication failures associated with a user

failure() {

while read -r line
do
        if grep -q $USER <<<$line
        then

                read -r line
                PROMPT=$line
                read -r line
		# If processed line contains the string "uthentication failure", DO print it
                if [[ "$PROMPT" == *"uthentication failure"* ]] 
		then
                        echo $PROMPT
                fi

		if [[ "$PROMPT" == *"user NOT in"* ]]
                then
                        echo $PROMPT
                fi
		if [[ "$PROMPT" == *"FAILED"* ]]
                then
                        echo $PROMPT
                fi
        fi

done < "$LOG_FILE"

exit 10

}

# Shows all logging associated with the user

show_all() {

while read -r line
do
        if grep -q $USER <<<$line
        then

                read -r line
                PROMPT=$line
                read -r line
		echo $PROMPT
        fi

done < "$LOG_FILE" 

exit 10 # terminates program 

}

# A variety of ways to invoke the help menu 

if [ "$1" == "$SHOW_HELP" ] || [ "$1" == "$SHOW_HELP2" ] || [ "$1" == "$SHOW_HELP3" ] || [ "$1" == "-help" ] 
then
	show_help
fi

if [ $# -gt 2 ] 
then 
	echo "Error! Too many arguments. Run the program with either one or two arguments" 1>&2
	show_script_usage
fi

if [ $# -eq 0 ] 
then
        echo "Run the program with either one or two arguments" 1>&2
        show_script_usage
fi

# If the only argument is the user, defaults to printing out all logging information 

if [ $# -eq 1 ] 
then
	show_all
fi

# Checks if the user exists anywhere in the log file

if ! grep -q $1 $LOG_FILE 
then
        echo "No entry in log "$LOG_FILE" for user "$USER"" 1>&2
        exit 0
fi

# Shows all logged activity of the user
 
if [ "$2"  != "-s" ] && [ "$2" != "-f" ] && [ "$2" != "-a" ] && [ "$2" != "--all" ] && [ "$2" != "--success" ] && [ "$2" != "--failure" ] 
then
	echo "Bad input! Try running the program's second argument with one of the approved arguments, as listed in the help menu" 1>&2
	show_help 
fi

# If second argument is -s, call success function

if [ "$2" == "-s" ] 
then
	success

# If second argument is -f, call failure function
elif [ "$2" == "-f" ]
then
	failure

# Calls all logging data regarding a user 

elif [ "$2" == "-a" ] || [ "$2" == "--all" ] 
then
	show_all 
fi
 
exit 10  # Terminate program 
