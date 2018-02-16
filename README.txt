*****************************
Simple UNIX Shell
Author: Ibrahim Thai
*****************************


**********************************
Program Description & How it Works
**********************************
This program is a simple UNIX Shell that I implemented that deals with simple commands like the Linux Terminal. It allows you to run other programs as well as creating unique programs that I also invented.

My program starts off very simple as you simply input "make" in order to create an executable file for this program:

run: make

Once the executable file is made, you compile it.

run: ./msh

you will get the following output:

ithai@shell: 

The text above is when the program starts and you're in my Shell program.

This Shell is very simple, and it follows a straightforward process. Like any commands on a normal Linux Terminal, you can easily execute it once you enter it on the Command Line. The general protocol behind my Shell is the "forking". Whatever command you put on my Shell, it will fork the process. Forking is when you create a child process, and you're able to work on that process without having the parent process to interfere. Suppose you want to input a command on my Shell:

ithai@shell: ls

The command "ls" displays all files in the directory. So in my program, I would fork it to create a child. Once the child is successfully made, I would execute the command using the execvp() function in the child process.

When the command includes an ampersand "&" at the end, the parent does not wait for the child to finish, but continues processing. This can be seen by the fact that the "ithai@shell: " would print out before the print out of the child command. For example:

Command "ls" without "&"
=========================
ithai@shell: ls
Brief Report.txt  desktop.ini  lex.c	 lex.yy.o  msh	       my_shell.o   output.txt
CON		  hello.txt    lex.yy.c  Makefile  my_shell.c  numbers.txt

Command "ls" with "&"
=========================
ithai@shell: ls &
ithai@shell: Brief Report.txt  desktop.ini  lex.c	 lex.yy.o  msh	       my_shell.o   output.txt
CON		  hello.txt    lex.yy.c  Makefile  my_shell.c  numbers.txt

This shows that the parent did NOT wait for the child, and returned immediately.
NOTE: You can still input any command. The child output is simply there.


-------------------
My Special Command
-------------------
My unique command is called "puns". Once you input "puns" on the command line, you're given a list of puns that you can read and enjoy. 








