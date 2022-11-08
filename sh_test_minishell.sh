# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sh_test_minishell.sh                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/06 18:53:38 by dgerwig-          #+#    #+#              #
#    Updated: 2022/11/04 13:27:45 by caquinta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
RED="\033[0m\033[31m"
GREEN="\033[0m\033[32m"
YELLOW="\033[0m\033[33m"
BLUE="\033[0m\033[34m"
MAGENTA="\033[0m\033[35m"
CYAN="\033[0m\033[36m"
RESET="\033[0m"

TOTAL=0
CORRECT=0

FAILED=0       #print only failed tests: value FAILED=1

clear
printf "$MAGENTA\n"
printf "==========================================\n"
printf "            MINISHELL TESTER              \n"
printf "==========================================\n"
printf "$RESET\n"

	printf "⚠️  Select TYPE TEST --> all / simple / arg / echo / exit / retval / sign / dq / sq / env / exp / cd / pwd / relpath / envpath / redir / pipes / wild / and \n\n"
read -p "Enter command: " command
while [ "$command" != "all" ] && 
	[ "$command" != "simple" ] && 
	[ "$command" != "arg" ] && 
	[ "$command" != "echo" ] && 
	[ "$command" != "exit" ] && 
	[ "$command" != "retval" ] && 
	[ "$command" != "sign" ] && 
	[ "$command" != "dq" ] && 
	[ "$command" != "sq" ] && 
	[ "$command" != "env" ] &&
	[ "$command" != "exp" ] &&
	[ "$command" != "cd" ] && 
	[ "$command" != "pwd" ] && 
	[ "$command" != "relpath" ] && 
	[ "$command" != "envpath" ] && 
	[ "$command" != "redir" ] && 
	[ "$command" != "pipes" ] && 
	[ "$command" != "wild" ] &&
	[ "$command" != "and" ] 
do
	printf "\n‼️  WRONG USE. Use a valid TYPE TEST\n"
	printf "⚠️  Select TYPE TEST --> all / simple / arg / echo / exit / retval / sign / dq / sq / env / exp / cd / pwd / relpath / envpath / redir / pipes /wild / and \n\n"
	read -p "Enter command: " command
done
printf "\n"

exec_test_a()
{
	echo $@ | ./minishell | grep -iv "minishell $ " > test1
	echo $@ | /bin/bash > test2 
	test1="test1"
	test2="test2"
	compare_files "$@" 
}

exec_test_b()
{
	echo $@ | ./minishell | sed -n 'n;p' | rev | cut -c 17- | rev > test1
	echo $@ | /bin/bash | sed 's/$//' > test2 
	test1="test1"
	test2="test2"
	compare_files "$@" 
}

exec_test_c()
{
	echo $@ | ./minishell | grep -iv "$USER" | grep -iv "minishell" > test1
	echo $@ | /bin/bash > test2 
	test1="test1"
	test2="test2"
	compare_files "$@" 
}

exec_test_d()
{
	echo $@ | ./minishell | grep /Users > test1
	echo $@ | /bin/bash > test2 
	test1="test1"
	test2="test2"
	compare_files "$@" 
}

exec_test_e()
{
	echo $@ | ./minishell | grep "declare" | grep -v "SHLVL" | grep -v "_=" > test1
	echo $@ | /bin/bash | grep -v "OLDPWD" | grep -v "SHLVL" | grep -v "_=" > test2 
	test1="test1"
	test2="test2"
	compare_files "$@" 
}

exec_test_f()
{
	echo $@ | ./minishell | grep -iv "$USER" | grep -iv "minishell" > test1
	echo $@ | /bin/bash | grep -iv "minishell" > test2 
	test1="test1"
	test2="test2"
	compare_files "$@" 
}

exec_test_g()
{
	echo $@ | ./minishell | grep -iv "minishell $ " | grep -iv "test" > test1
	echo $@ | /bin/bash | grep -iv "test" > test2 
	test1="test1"
	test2="test2"
	compare_files "$@" 
}

exec_test_h()
{
	echo $@ | ./minishell | sed -n 'n;p' > test1
	echo $@ | /bin/bash > test2 
	test1="test1"
	test2="test2"
	compare_files "$@" 
}

exec_test_i()
{
	echo $@ | ./minishell | grep -iv "$USER" | grep -iv "minishell" | sed 's/> //g' > test1
	echo $@ | /bin/bash | grep -iv "minishell" > test2 
	test1="test1"
	test2="test2"
	compare_files "$@" 
}

exec_test_j()
{
	echo $@ | ./minishell | grep -iv "$USER" | grep -iv "minishell" > test/test1
	echo $@ | /bin/bash > test/test2 
	test1="test/test1"
	test2="test/test2"
	compare_files "$@" 
}

exec_test_signals()
{
#	echo $@ | ./minishell
	./minishell
	pid= ps u | grep ./minishell | grep -v Users | grep -v grep | awk '{print $2}' 
	echo $@ | kill -2 pid 
	}

compare_files()
{
	if [ ! -d ./test/ ] ; then
		mkdir ./test
	fi
	if (cmp -s  "$test1" "$test2") ; then
		if [ $FAILED -eq 1 ]; then
		CORRECT=$(( $CORRECT + 1 ))
		else
		CORRECT=$(( $CORRECT + 1 ))
		printf $CYAN"Test nº: %.3d \t$RESET" "$(($TOTAL + 1))" 
		printf $BOLDGREEN"✅ Right! $GREEN %s $RESET\n" "$@"
		printf $YELLOW"minishell output: \n$BLUE"
		echo $@ | ./minishell
		printf $YELLOW"bash output: \n$BLUE"
		echo $@ | /bin/bash
		printf $YELLOW"\nTEST minishell output: \n%.40s\n$(cat -e test1)\n%.40s$RESET\n" "=========================================" "========================================="
		printf $GREEN"TEST bash output: \n%.40s\n$(cat -e test2)\n%.40s$RESET\n" "=========================================" "========================================="
		printf "$RESET\n"
		fi
	else
		printf $CYAN"Test nº: %.3d \t$RESET" "$(($TOTAL + 1))" 
		printf $BOLDRED"❌ Error! %s %s$RESET\n" "$@"
		printf $YELLOW"minishell output: \n$BLUE"
		echo $@ | ./minishell
		printf $YELLOW"bash output: \n$BLUE"
		echo $@ | /bin/bash
		printf "$RESET"
		printf $YELLOW"\nTEST minishell output: \n%.40s\n$(cat -e test1)\n%.40s$RESET\n" "=========================================" "========================================="
		printf $GREEN"TEST bash output: \n%.40s\n$(cat -e test2)\n%.40s$RESET\n" "=========================================" "========================================="
		printf $RED"TEST diff minishell vs bash output: \n%.40s\n$(diff test1 test2)\n%.40s$RESET\n\n" "=========================================" "========================================="
	rm -rf test/* test* tests hello hola lol ls test/test1 test/test2 *outfi* 
	fi
	TOTAL=$(($TOTAL + 1))
}

print_result()
{
	if [ $CORRECT -eq $TOTAL ]; then
		printf "\n$BOLDGREEN"
	else
		printf "\n$BOLDRED"
	fi
	printf "%s: %d/%d passed tests (%0.2f%%)\n\n$RESET" "$command" "$CORRECT" "$TOTAL" "$(($CORRECT * 100 / $TOTAL))"
}

# SIMPLE
if [ "$command" = "simple" ] || [ "$command" = "all" ] ; then
	printf "$CYAN\n"
	printf "******************************************\n"
	printf "         TYPE TEST: simple\n"
	printf "******************************************\n"
	printf "$RESET\n"
	exec_test_h "./minishell"
	exec_test_g "/bin/ls"
	exec_test_g "/bin/fake"
	exec_test_d "\"\""  
	exec_test_d ""         					#empty
	exec_test_d "      "					#spaces
	exec_test_d "					"		#tabs
	print_result
fi

# ARGUMENTS 
if [ "$command" = "arg" ] || [ "$command" = "all" ] ; then
	printf "$CYAN\n"
	printf "******************************************\n"
	printf "         TYPE TEST: arguments\n"
	printf "******************************************\n"
	printf "$RESET\n"
	exec_test_g "/bin/ls | grep Makefile"
	exec_test_g "/bin/ls | grep 'Makefile'"
	exec_test_g "/bin/ls | grep "Makefile""
	print_result
fi

#ECHO
if [ "$command" = "echo" ] || [ "$command" = "all" ] ; then
	printf "$CYAN\n"
	printf "******************************************\n"
	printf "         TYPE TEST: echo\n"
	printf "******************************************\n"
	printf "$RESET\n"
	exec_test_c "echo "
	exec_test_c "ECHO "
	exec_test_c "echo -n"
	exec_test_c "ECHO -n"
	exec_test_c "echo test arg1" 
	exec_test_c "ECHO test arg1" 
	exec_test_c "echo test arg1 arg2" 
	exec_test_c "echo test arg1 arg2 arg3" 
	exec_test_c "echo test      arg"
	exec_test_d "echo \$PATH"
	exec_test_c "echo checking if spaces      work properly"
	exec_test_c "echo \"checking if spaces       work properly\""
	exec_test_c "echo 'checking if spaces   work properly'"
	exec_test_c "echo \$FAKE"
	exec_test_c "echo '\$FAKE'"
	exec_test_c "echo \"\$FAKE\""
	exec_test_c "echo \$FAKE''"
	exec_test_c "echo \$FAKE\"\""
	exec_test_d "echo \$PWD"
	exec_test_d "echo \$PWD \$PWD"
	exec_test_d "echo \$PWD\$PWD"
	exec_test_d "echo \$PWD\$PWD42"
	exec_test_d "echo \$PWD\$PWD 42"
	exec_test_d "echo    \$PWD   "
	exec_test_d "echo \"   \$PWD   \""
	exec_test_d "echo \"\$PWD\""
	exec_test_d "echo \"\$USER \$PWD\""
	exec_test_d "echo \"'\$PWD'\""
	exec_test_c "echo \"'hello'\""
	exec_test_d "echo \"\"\$PWD\"\""
	exec_test_c "echo \"\"hello\"\""
	exec_test_d "echo \"\"\"\$PWD\"\"\""
	exec_test_c "echo \"\"hello\"\""
	exec_test_c "echo '\"\$PWD\"'"
	exec_test_c "echo '\"hello\"'"
	exec_test_d "echo ''\$PWD''"
	exec_test_c "echo ''hello''"
	exec_test_c "echo \$ PWD"
	exec_test_c "echo '\$P'\"W'D'\""
	exec_test_c "echo \"\$~\""
	exec_test_c "hola echo hello"
	exec_test_c "echo \" \$\""
	exec_test_c "echo \"\$\""
	exec_test_c "echo \"\$\"\"\""
	exec_test_c "echo \"\$\"xx\"\""
	exec_test_c "echo xx\"\$\"\"\""
	exec_test_c "echo \$"
	exec_test_c "echo \$=\$"
	exec_test_c "echo \$+\$"
	exec_test_c "echo \$=\$=\$"
	exec_test_c "echo \$+\$+\$"
	exec_test_c "echo \$=\$=\$=\$"
	exec_test_c "echo \$+\$+\$+\$"
	exec_test_c "echo \$=\$ \$=\$"
	exec_test_c "echo \$+\$ \$+\$"
	exec_test_c "echo \$ hello"
	exec_test_c "echo \"\"\$"
	exec_test_c "echo \$?"
	exec_test_b "echo -n test"
	exec_test_b "echo -nn test"
	exec_test_b "echo -nnnnn -nnnnn test"
	exec_test_c "echo -nnnnnx -nnnnn test"
	exec_test_b "echo -nnnnn -nnnnnx test"
	exec_test_b "echo -n test -n"
	exec_test_b "echo -n test hello"
	exec_test_b "echo -nnnnnnn -nnnnn -nnnnnnn test hello -n"
	exec_test_b "echo '-n' test"
	exec_test_b "echo \"-n\" test"
	exec_test_c "echo '-n -n' test"
	exec_test_c "echo \"-n -n\" test"
	exec_test_b "echo '-n' -n test"
	exec_test_b "echo \"-n\" -n test"
	exec_test_b "echo \"-n\" test"
	exec_test_c "echo \"'-n'\" test"
	exec_test_c "echo '\"-n\"' test"
	print_result
fi

# EXIT
if [ "$command" = "exit" ] || [ "$command" = "all" ] ; then
	printf "$CYAN\n"
	printf "******************************************\n"
	printf "         TYPE TEST: exit\n"
	printf "******************************************\n"
	printf "$RESET\n"
	exec_test_d "exit 42"
	exec_test_d "EXIT 42"
	exec_test_d "exit 42 42"
	exec_test_d "exit 42 -42"
	exec_test_d "exit 4244353254"
	exec_test_d "exit wrong"
	exec_test_d "exit "
	exec_test_d "exit echo hello"
	exec_test_d "exit not a number"
	exec_test_d "exit 42"
	exec_test_d "exit 0"
	exec_test_d "exit .42"
	exec_test_d "exit +42"
	exec_test_d "exit + 42"
	exec_test_d "exit + 42 42"
 	exec_test_d "exit ++42"
	exec_test_d "exit -42"
	exec_test_d "exit - 42"
	exec_test_d "exit -"
	exec_test_d "exit --42"
	exec_test_d "exit 43 a"
	exec_test_d "exit a 44"
	exec_test_d "exit 43b"
	exec_test_d "exit b44"
	exec_test_d "exit 9223372036854775807"
	exec_test_d "exit 9223372036854775808"
	exec_test_d "exit -9223372036854775808"
	exec_test_d "exit -9223372036854775809"
	exec_test_d "exit 42 alpha"
	exec_test_d "exit beta 24"
	exec_test_d "exit '42'"
	exec_test_d "exit '+42'"
	exec_test_d "exit \"42\""
	exec_test_d "exit \"+42\""
	exec_test_d "exit 42'42'\"42\""
	exec_test_d "exit +42'42'\"42\""
	exec_test_d "exit exit"
	exec_test_c "exit | echo no"
	print_result
fi

# RETURN VALUE OF A PROCESS
if [ "$command" = "retval" ] || [ "$command" = "all" ] ; then
	printf "$CYAN\n"
	printf "**************************************************\n"
	printf "         TYPE TEST: return value of a process\n"
	printf "**************************************************\n"
	printf "$RESET\n"
	exec_test_c "/bin/fake \n \$?"
	exec_test_c "/bin/fake \n expr \$? + \$?"
	print_result
fi

# SIGNALS
if [ "$command" = "sign" ] || [ "$command" = "all" ] ; then
	printf "$CYAN\n"
	printf "******************************************\n"
	printf "         TYPE TEST: signals\n"
	printf "******************************************\n"
	printf "$RESET\n"
#	exec_test_signals ""
	print_result
fi

# DOUBLE QUOTES
if [ "$command" = "dq" ] || [ "$command" = "all" ] ; then
	printf "$CYAN\n"
	printf "******************************************\n"
	printf "         TYPE TEST: double quotes\n"
	printf "******************************************\n"
	printf "$RESET\n"
	exec_test_c "echo \"hello"
	exec_test_c "echo \"hello\""
	exec_test_c "echo \"hello      spaces\""
	exec_test_c "echo \"hello	tab\""
	exec_test_c "echo \"cat lol.c | cat >lol.c\""
	exec_test_c "echo \"\""
	exec_test_d "\"pwd\""
	exec_test_c "\"$\""
	exec_test_g "echo \"$USER\""
	exec_test_g "echo \"'$USER'\""
	exec_test_g "echo '\"$USER\"'"
	exec_test_c "cat \"     hello       \""
	print_result
fi

# SIMPLE QUOTES
if [ "$command" = "sq" ] || [ "$command" = "all" ] ; then
	printf "$CYAN\n"
	printf "******************************************\n"
	printf "         TYPE TEST: simple quotes\n"
	printf "******************************************\n"
	printf "$RESET\n"
	exec_test_c "echo 'hello"
	exec_test_c "echo 'hello'"
	exec_test_c "echo 'hello      spaces'"
	exec_test_c "echo 'hello	tab'"
	exec_test_c "echo 'cat lol.c | cat >lol.c'"
	exec_test_c "echo ''"
	exec_test_d "'pwd'"
	exec_test_g "echo '$USER'"
	exec_test_g "echo \"'$USER'\""
	exec_test_g "echo '\"$USER\"'"
	exec_test_c "cat '     hello      '"
	print_result
fi

# ENV 
if [ "$command" = "env" ] || [ "$command" = "all" ] ; then
	printf "$CYAN\n"
	printf "******************************************\n"
	printf "         TYPE TEST: env\n"
	printf "******************************************\n"
	printf "$RESET\n"
	exec_test_d "env | grep PATH"
	exec_test_d "ENV | grep PATH"
	exec_test_c "echo \$"
	exec_test_d "echo \$PWD"
	exec_test_c "echo '\$PWD'"
	exec_test_c "echo \$'PWD'"
	exec_test_d "echo \"\$PWD\""
	exec_test_c "echo \$\"PWD\""
	exec_test_c "echo \"\$\"PWD"
	exec_test_c "echo \" \$\"PWD"
	exec_test_c "echo \$''"
	exec_test_c "echo \$\"\""
	exec_test_c "echo \$' '"
	exec_test_c "echo \$\" \""
	exec_test_c "echo \$'?'"
	exec_test_c "echo \$\"? \""
	exec_test_c "echo \$'? '"
	exec_test_c "echo \$\"? \""
	print_result
fi

# EXPORT / UNSET
if [ "$command" = "exp" ] || [ "$command" = "all" ] ; then
	printf "$CYAN\n"
	printf "******************************************\n"
	printf "         TYPE TEST: export / unset\n"
	printf "******************************************\n"
	printf "$RESET\n"
	exec_test_e "export"
	exec_test_d "export NEW=new"
	exec_test_d "export TEST=hello"
	exec_test_d "export arg=GOODBYE"
	exec_test_d "export abc=GOODBYE"
	exec_test_d "export ORIGINALPATH=\$PATH"
	exec_test_d "export PATH=\$PATH:new_dir"
	exec_test_d "export TEST=hello world"
	exec_test_c "echo \$TEST"
	exec_test_d "export TEST=\"hello\""
	exec_test_d "export TEST='hello'"
	exec_test_d "export TEST=\"he'llo\""
	exec_test_d "export TEST='he\"llo'"
	exec_test_d "export _TEST=_hello"
	exec_test_d "export 5TEST=5hello"
	exec_test_d "export TEST5=hello5"
	exec_test_d "export TE_ST=he_ll]o"
	exec_test_d "export TEST=he_ll]o"
	exec_test_d "export TEST_EMPTY="
	exec_test_d "export TEST1=hello"
	exec_test_d "export TEST"
	exec_test_d "export =hello"
	exec_test_d "export  =hello"
	exec_test_d "export CHEVRON1=\"<\""
	exec_test_d "export CHEVRON2=\">\""
	exec_test_d "export ="
	exec_test_d "export '='"
	exec_test_d "export \"=\""
	exec_test_d "export \"\$\""
	exec_test_d "export TEST=\"\""
	exec_test_d "export TEST=\"''\""
	exec_test_d "export TEST=''"
	exec_test_d "export TEST='\"\"'"
	exec_test_d "export TESTWEIRDCASE=\"\$\""
	exec_test_c "unset"
	exec_test_c "unset NEW"
	exec_test_c "unset NEW_FAKE"
	exec_test_c "unset PPID"
	exec_test_c "unset CLICOLOR"
	exec_test_c "unset __CF_USER_TEXT_ENCODING"
	exec_test_d "EXPORT NEW=new"
	exec_test_c "UNSET NEW"
	print_result
fi

# CD
if [ "$command" = "cd" ] || [ "$command" = "all" ] ; then
	printf "$CYAN\n"
	printf "******************************************\n"
	printf "         TYPE TEST: cd\n"
	printf "******************************************\n"
	printf "$RESET\n"
	exec_test_a "cd"
	exec_test_a "CD"
	exec_test_a "cd .a"
	exec_test_a "cd /Users"
	exec_test_a "cd /"
	exec_test_a "cd //"
	exec_test_a "cd /////"
	exec_test_a "cd ./././"
	exec_test_a "cd ../../../"
	exec_test_a "cd ?"
	exec_test_a "cd +"
	exec_test_a "cd _"
	exec_test_a "cd $"
	exec_test_a "cd $?"
	exec_test_a "cd '..'"
	exec_test_a "cd \"..\""
	exec_test_a "cd /var/log"
	exec_test_a "cd '/var/log'"
	exec_test_a "cd \"/var/log\""
	exec_test_a "CD /var/log"
	exec_test_a "cd inc"
	exec_test_a "cd ../minishell/src"
	exec_test_a "cd ../minishell/libft/src"
	exec_test_a "cd ."
	exec_test_a "cd .."
	exec_test_a "cd wrong_path"
	print_result
fi

# PWD 
if [ "$command" = "pwd" ] || [ "$command" = "all" ] ; then
	printf "$CYAN\n"
	printf "******************************************\n"
	printf "         TYPE TEST: pwd\n"
	printf "******************************************\n"
	printf "$RESET\n"
	exec_test_d "pwd"
	exec_test_d "PWD"
	print_result
fi

# RELATIVE PATH
if [ "$command" = "relpath" ] || [ "$command" = "all" ] ; then
	printf "$CYAN\n"
	printf "******************************************\n"
	printf "         TYPE TEST: relative path\n"
	printf "******************************************\n"
	printf "$RESET\n"
	exec_test_a "cd ../../../../../../../../bin/ls "
	exec_test_a "../../../../../../../../bin/ls "
	print_result
fi

# ENVIRONMENT PATH
if [ "$command" = "envpath" ] || [ "$command" = "all" ] ; then
	printf "$CYAN\n"
	printf "******************************************\n"
	printf "         TYPE TEST: environment path\n"
	printf "******************************************\n"
	printf "$RESET\n"
	exec_test_g "ls"
	exec_test_d "unset PATH"
	exec_test_g "export PATH=$PATH:new_dir"
	print_result
fi

# REDIRECTION
if [ "$command" = "redir" ] || [ "$command" = "all" ] ; then
	printf "$CYAN\n"
	printf "******************************************\n"
	printf "         TYPE TEST: redir\n"
	printf "******************************************\n"
	printf "$RESET\n"
	exec_test_c "echo test > ls | cat ls"
	exec_test_c "echo test > ls >> ls >> ls | echo test >> ls | cat ls"
	exec_test_c "> lol echo test lol | cat lol"
	exec_test_c ">lol echo > tests>lol>tests>>lol>tests mdr >lol tests >tests | cat tests"
	exec_test_f "cat < notes_03_minishell.mkd"         
	exec_test_f "cat < notes_03_minishell.mkd > test3"         
	exec_test_i "cat << here"
	exec_test_i "cat <<here"
	exec_test_j "ls > outfile"
	exec_test_j "ls >> outfile"
	exec_test_j "ls >> > outfile"
	exec_test_j "ls >>> outfile"
	exec_test_j "ls >"
	exec_test_j "cat >"
	exec_test_j "cat <"
	exec_test_j "> outfile ls"
	exec_test_d "ls <|outfile"
	exec_test_j "ls > \"outfile danger\""            
	exec_test_j "ls > \'outfile danger\'"          
	exec_test_j "ls >| outfile | cat -e outfile"
	exec_test_j "ls > | outfile | cat -e outfile"
	exec_test_f "ls >| outfile | cat -e outfile"
	exec_test_f "ls > | outfile | cat -e outfile"
	exec_test_f "ls > outfile | echo bla1 "
	exec_test_f "ls > outfile | exit "
	exec_test_f "ls > outfile | | exit"
	exec_test_f "ls > 'outfile\"danger '"       
	exec_test_f "ls > 'outfile \" danger '"       
	exec_test_f "ls > \"outfile'danger \" "      
	exec_test_f "ls > \"outfile ' danger \" "      
	exec_test_f "ls > \"outfi|<le ' da>nger \" "   
	exec_test_f "ls >outfile >outfile2 >>outfile3 <infile1 <<here1 <infile2 m*  >>outfile4 | cat -e >outfile5 <<here2"
	print_result
fi

# PIPES
if [ "$command" = "pipes" ] || [ "$command" = "all" ] ; then
	printf "$CYAN\n"
	printf "******************************************\n"
	printf "         TYPE TEST: pipes\n"
	printf "******************************************\n"
	printf "$RESET\n"
	exec_test_g "echo \"\" | ls"
	exec_test_d "env | grep PATH"
	exec_test_d "ENV | grep PATH"
	exec_test_d "env | env | grep PATH"
	exec_test_d "| echo hello"
	exec_test_d "echo > |"
	exec_test_d "ls | cat -e >"
	exec_test_c "cat Makefile | head -c 100 | wc"
	exec_test_c "echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat"
	exec_test_f "ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls"
	print_result
fi

# WILDCARD 
if [ "$command" = "wild" ] || [ "$command" = "all" ] ; then
	printf "$CYAN\n"
	printf "******************************************\n"
	printf "         TYPE TEST: wildcard\n"
	printf "******************************************\n"
	printf "$RESET\n"
	exec_test_g "ls val*"
	exec_test_g "ls *supp"
	exec_test_g "ls *fi*"
	exec_test_g "ls va*upp"
 	print_result
fi

# && and || 
if [ "$command" = "and" ] || [ "$command" = "all" ] ; then
	printf "$CYAN\n"
	printf "******************************************\n"
	printf "         TYPE TEST: && and ||\n"
	printf "******************************************\n"
	printf "$RESET\n"
	exec_test_g "echo hello && echo world"
	print_result
fi

rm -rf test test1 test2 test3 tests hello hola lol ls test/test1 test/test2 *outfi* 
