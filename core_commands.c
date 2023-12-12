#include "shell.h"

/**
 * execute_user_command - forks a process and execute command
 * on the child process using execve
 * @myargv: synthetic commandarray for the program to run
 * @env: environment variables
 */
void execute_user_command(char *myargv[], char *env[])
{
	pid_t child_pid;
	int status;

	/*Check if the command exists in PATH*/
	if (access(myargv[0], X_OK) == -1)
	{
		perror("Command not found");
		return;
	}

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
	}
	else if (child_pid == 0)
	{
		/* Child process */
		if (execve(myargv[0], myargv, env) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		if (waitpid(child_pid, &status, 0) == -1)
		{
			perror("waitpid");
		}
	}
}

/**
 * handle_builtin_commands - executes the shell built-in commands
 * @commandarray: array of command arguments
 * @env: environment variables
 * Return: 1 if the command is a built-in, 0 otherwise
 */
int handle_builtin_commands(char *commandarray[], char *env[])
{
	if (_strcmp(commandarray[0], "exit") == 0)
	{
		exit_command(commandarray, env);
		return 1;
	}
	else if (_strcmp(commandarray[0], "env") == 0)
	{
		env_command(commandarray, env);
		return 1;
	}
	else if (_strcmp(commandarray[0], "cd") == 0)
	{
		cd_command(commandarray, env);
		return 1;
	}
	else if (_strcmp(commandarray[0], "alias") == 0)
	{
		alias_command(commandarray, env);
		return 1;
	}

	return 0;
}

/**
 * getusercommand - gets user command
 * Return: string
 */
char *getusercommand(void)
{
	char *buf = NULL;
	size_t bufsize = 0;
	size_t numchar;

	numchar = _getline(&buf, &bufsize, stdin);

	if (numchar == 0)
	{
		exit(-1);
	}

	if (buf[numchar - 1] == '\n')
		buf[numchar - 1] = '\0';

	return (buf);
}

/**
 * main - executes the shell commands
 * @argc: argument count
 * @argv: array of argument variables
 * @env: environment variables
 * Return: Always 0;
 */
int main(int argc, char *argv[], char *env[])
{
	executeshell(argc, argv, env);
	return 0;
}
