#include "shell.h"

/**
 * comp_env_with_val - check if val matches the name of an environment variable
 * @env: string in the form "name=value"
 * @val: this string is compared with name from the string "name=valuee"
 * Return: 0 is the strings match, 1 if they don't
 */

int comp_env_with_val(const char *env, const char *val)
{
	int i;

	for (i = 0;; i++)
	{
		if (env[i] != val[i])
		{
			if (env[i] == '=' && val[i] == '\0')
				return (0);
			else
				return (1);
		}
	}
}

/**
 * _getenv - return a pointer to the value of an environment variable
 * @name: name of the environment variable to search for its value
 * @env: environment variable
 * Return: pointer to the value of an environment variable searched
 *         NULL if not found
 */
char *_getenv(const char *name, char *env[])
{
	int i;

	for (i = 0; env[i] != NULL; i++)
	{
		if (comp_env_with_val(env[i], name) == 0)
		{
			return (env[i] + _str_len(name) + 1);
		}
	}
	return (NULL);
}

/**
 * _setenv - set the value of an environment variable
 * @name: name of env variable to set the value
 * @value: value to be set
 * @overwrite: if set to true, environment variable
 * Return: 0 on success, -1 on failure (with errno
 */

int _setenv(const char *name, const char *value, int overwrite)
{
	int i;
	extern char **environ;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (comp_env_with_val(environ[i], name) == 0)
		{
			if (overwrite)
			{
				int memsize = _str_len(value) + _str_len(name) + 2;
				environ[i] = realloc(environ[i], memsize);
				_strcpy(environ[i], name);
				_strcat(environ[i], "=");
				_strcat(environ[i], value);
			}
			return 0;
		}
	}

	/*Add a new environment variable*/
	int memsize = _str_len(value) + _str_len(name) + 2;
	char *new_env_var = malloc(memsize);
	if (new_env_var == NULL)
	{
		perror("malloc");
		return -1;
	}
	_strcpy(new_env_var, name);
	_strcat(new_env_var, "=");
	_strcat(new_env_var, value);

	/*Reallocate the environ array*/
	environ = realloc(environ, (i + 2) * sizeof(char *));
	if (environ == NULL)
	{
		perror("realloc");
		free(new_env_var);
		return -1;
	}

	environ[i] = new_env_var;
	environ[i + 1] = NULL;

	return 0;
}

/**
 * _unsetenv - unsets the value of an environment variable
 * @name: name of the environment variable to unset
 * Return: 0 in success, -1 on error (with errno set (not implemented yet))
 */
int _unsetenv(const char *name)
{
	extern char **environ;
	int i, j;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (comp_env_with_val(environ[i], name) == 0)
		{
			/*Free memory for the environment variable*/
			free(environ[i]);

			/*Shift remaining elements to fill the gap*/
			for (j = i; environ[j] != NULL; j++)
			{
				environ[j] = environ[j + 1];
			}

			return 0;
		}
	}

	/*Variable not found, nothing to unset*/
	return 0;
}
