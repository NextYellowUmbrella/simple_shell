# Simple Shell

## Project Overview

The objective of this project is to create a simple shell called hsh that mimics the basic functionality of the standard Unix shell sh. The shell should be able to execute commands from both interactive and non-interactive modes.

# Requirements

## General Requirements

<img src="https://intranet.alxswe.com/brand_alx/share_image_2019.jpg" width="300" height="100" />

- Compile using gcc with options -Wall -Werror -Wextra -pedantic -std=gnu89 on Ubuntu 20.04 LTS.
- Follow Betty style guidelines.
- No memory leaks.
- Maximum of 5 functions per file.
- Include-guard all header files.
- Minimize system calls.
- Include a README with project description.

# Output Requirements:

- Exact output and error output as `sh` except for program name.

# Allowed Functions and System Calls:

`access, chdir, close, closedir, execve, exit, _exit, fflush, fork, free,
getcwd, getline, getpid, isatty, kill, malloc, open, opendir, perror,
read, readdir, signal, stat, lstat, fstat, strtok, wait, waitpid,
wait3, wait4, write`

# Testing

- Interactive Mode:
  - Run `./hsh` and enter commands separated by `($)`.
  - Exit the shell using the exit command.
- Non-Interactive Mode:
  - Pipe commands to ./hsh using echo "command" | ./hsh.
  - Input commands from a file using cat file | ./hsh.

# Implementation

The shell can be implemented in multiple C files, each responsible for specific functionalities. A main function can be used to handle command parsing and execution.

# Additional Considerations

- Handle error conditions appropriately.
- Support command arguments and redirection.
- Consider implementing built-in commands for common tasks.
- Evaluate performance and optimize as needed.

## Usage

In order to run this program,

Clone This Repo;

`git clone https://github.com/NextYellowUmbrella/simple_shell.git`

Compile it with;

`gcc 4.8.4 -Wall -Werror -Wextra -pedantic *.c -o hsh.`

You can then run it by invoking `./hsh` in that same directory.

How to use it
In order to use this shell, in a terminal, first run the program:
`prompt$ ./hsh`
It wil then display a simple prompt and wait for commands.
`$`
A command will be of the type `$` command

To invoke **hsh**, compile all .c files in the repository and run the resulting executable.

hsh can be invoked both interactively and non-interactively. If hsh is invoked with standard input not connected to a terminal, it reads and executes received commands in order.

Example:

```
$ echo "echo 'hello'" | ./hsh
'hello'
$
```

If hsh is invoked with standard input connected to a terminal (determined by isatty(3)), an interactive shell is opened. When executing interactively, hsh displays the prompt $ when it is ready to read a command.

Example:

```
$./hsh
$
```

Alternatively, if command line arguments are supplied upon invocation, hsh treats the first argument as a file from which to read commands. The supplied file should contain one command per line. hsh runs each of the commands contained in the file in order before exiting.

Example:

```
$ cat test
echo 'hello'
$ ./hsh test
'hello'
$
```

## Environment

Upon invocation, `hsh` receives and copies the environment of the parent process in which it was executed. This environment is an array of name-value strings describing variables in the format `NAME=VALUE`. A few key environmental variables are:

### HOME

The home directory of the current user and the default directory argument for the cd builtin command.

```
$ echo "echo $HOME" | ./hsh
/home/paxxchal
```

### PWD

The current working directory as set by the cd command.

```
$ echo "echo $PWD" | ./hsh
/home/paxxchal/simple_shell
```

### OLDPWD

The previous working directory as set by the cd command.

```
$ echo "echo $OLDPWD" | ./hsh

```

### PATH

A colon-separated list of directories in which the shell looks for commands. A null directory name in the path (represented by any of two adjacent colons, an initial colon, or a trailing colon) indicates the current directory.

```
$ echo "echo $PATH" | ./hsh
/home/projects/.cargo/bin:/home/projects/.local/bin:/home/projects/.rbenv/plugins/ruby-build/bin:/home/projects/.rbenv/shims:/home/projects/.rbenv/bin:/home/projects/.nvm/versions/node/v10.15.3/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/projects/.cargo/bin:/home/projects/workflow:/home/projects/.local/bin
```

## hsh Builtin Commands

### cd

- Usage: `cd [DIRECTORY]`
- Changes the current directory of the process to `DIRECTORY`.
- If no argument is given, the command is interpreted as `cd $HOME`.
- If the argument `-` is given, the command is interpreted as `cd $OLDPWD` and the pathname of the new working directory is printed to standard output.
- If the argument, `--` is given, the command is interpreted as `cd $OLDPWD` but the pathname of the new working directory is not printed.
- The environment variables `PWD` and `OLDPWD` are updated after a change of directory.

Example:

```
$ ./hsh
$ pwd
/home/simple_shell
$ cd ../
$ pwd
/home
$ cd -
$ pwd
/home/simple_shell
```

### alias

- Usage: `alias [NAME[='VALUE'] ...]`
- Handles aliases.
- `alias`: Prints a list of all aliases, one per line, in the form `NAME='VALUE'`.
- `alias NAME [NAME2 ...]`: Prints the aliases NAME, NAME2, etc. one per line, in the form `NAME='VALUE'`.
- `alias NAME='VALUE' [...]`: Defines an alias for each NAME whose `VALUE` is given. If name is already an alias, its value is replaced with `VALUE`.

Example:

```
$ ./hsh
$ alias show=ls
$ show
AUTHORS            builtins_help_2.c  errors.c         linkedlist.c        shell.h       test
README.md          env_builtins.c     getline.c        locate.c            hsh
alias_builtins.c   environ.c          helper.c         shell.c              split.c
builtin.c          err_msgs1.c        helpers_2.c      man_1_simple_shell  str_funcs1.c
builtins_help_1.c  err_msgs2.c        input_helpers.c  proc_file_comm.c    str_funcs2.c
```

### exit

- Usage: exit [STATUS]
- Exits the shell.
- The STATUS argument is the integer used to exit the shell.
- If no argument is given, the command is interpreted as exit 0.

Example:

```
$ ./hsh
$ exit
```

### env

- Usage: env
- Prints the current environment.

Example:

```
$ ./hsh
$ env
NVM_DIR=/home/projects/.nvm
...
```

### setenv

- Usage: setenv [VARIABLE] [VALUE]
- Initializes a new environment variable, or modifies an existing one.
- Upon failure, prints a message to stderr.

Example:

```
$ ./hsh
$ setenv NAME Poppy
$ echo $NAME
Poppy
```

### unsetenv

- Usage: `unsetenv [VARIABLE]`
- Removes an environmental variable.
- Upon failure, prints a message to `stderr`.

Example:

```
$ ./hsh
$ setenv NAME Poppy
$ unsetenv NAME
$ echo $NAME
$
```

**Thank you for going through our shell documentation.**

## AUTHORS

NNAMANI PASCHAL
Abdurahman almehdi Ibrahem
