#!/bin/sh
# ***** SUMMARY *****
# Ensures that input is only of alphabetical or numeric characters

# ***** CHANGELOG *****
# 1.0: Base program made.

validateAlphaNum()
{
	# Destroys unacceptable characters
	compressed="$(echo $1 | sed -e 's/[^[:alnum:]]//g')"

	if [ "$compressed" != "$input" ] ; then
		return 1
	else
		return 0
	fi
}

# sample usage of this function in a script

echo -n "Enter input: "
read input

if ! validateAlphaNum "$input" ; then
	echo "Your input must only contain letters and numbers" >&2
	exit
else
	echo "Input is valid."
fi

exit 0
