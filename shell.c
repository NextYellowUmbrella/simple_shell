#include "shell.h"

/**
 * shell_startup_script - displays welcome message to screen
 * Return: void;
 */
void shell_startup_script(void)
{
}

/**
 * eval_execute_command_loop - continuously asks
 * user for command and executes it
 * @argv: arguments passed to shell when it was opened
 * @env: environment variables of shell
 */
void eval_execute_command_loop(int argc __attribute__((unused)), char *argv[] __attribute__((unused)), char *env[])
{
	char *usercommand;
	char *commandarray[10];
	char *commandsep[10];
	int i;

	while (1)
	{
		displaycwd();
		usercommand = getusercommand();
		removecomment(usercommand);
		i = 0;

		if (*usercommand == '\0')
		{
			free(usercommand);
			continue;
		}

		tokenize_string(usercommand, commandsep, ';');

		while (commandsep[i] != NULL)
		{
			tokenize_string(commandsep[i], commandarray, ' ');
			remove_quotes(commandarray); /*Handle quotes*/

			if (handle_builtin_commands(commandarray, env) == 1)
			{
				i++;
				continue;
			}

			execute_user_command(commandarray, env);
			i++;
		}

		free(usercommand);
	}
}

/**
 * executeshell - activates command execution loop
 * @argc: argument count
 * @env: environment variables
 * Return: void;
 */
void executeshell(int argc __attribute__((unused)), char *argv[], char *env[])
{
	shell_startup_script();
	eval_execute_command_loop(argc, argv, env);
}
