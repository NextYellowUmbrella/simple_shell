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

		/*Pass the full path of the command to execute_user_command*/
		char *full_path_command = _get_full_path(commandarray[0], env);
		if (full_path_command != NULL)
		{
			commandarray[0] = full_path_command;
			execute_user_command(commandarray, env);
			free(full_path_command);
		}
		else
		{
			/*Handle error: command not found in PATH*/
			fprintf(stderr, "Command not found: %s\n", commandarray[0]);
		}

		i++;
	}

	free(usercommand);
}

/**
 * _get_full_path - gets the full path
 * of the command from PATH
 * @command: command argument passed to shell when it was opened
 * @env: environment variables of shell
 */
char *_get_full_path(const char *command, char *env[])
{
	char *path = _getenv("PATH", env);
	char *token, *full_path;

	if (path == NULL)
	{
		return NULL;
	}

	token = strtok(path, ":");
	while (token != NULL)
	{
		full_path = (char *)malloc(strlen(token) + strlen(command) + 2);
		if (full_path == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		strcpy(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, command);

		if (access(full_path, X_OK) == 0)
		{
			return full_path;
		}

		free(full_path);
		token = strtok(NULL, ":");
	}

	return NULL; /*Command not found in PATH*/
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
