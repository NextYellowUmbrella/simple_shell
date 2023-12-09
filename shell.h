#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

/**
 * struct b_cmd - Short description
 * @command_name: First member
 * @func: Second member
 *
 * Description: Longer description
 */
typedef struct b_cmd
{
	char *command_name;
	int (*func)(char **, char **);
} command_object;

/**
 * struct alias_obj - Short description
 * @command: First member
 * @replacement: Second member
 *
 * Description: Longer description
 */
typedef struct alias_obj
{
	char *command;
	char *replacement;
} alias_t;

void executeshell(int argc __attribute__((unused)), char *argv[], char *env[]);
void shell_startup_script(void);
void eval_execute_command_loop(char *argv[], char *env[]);
void displaycwd(void);
char *getusercommand(void);
void removecomment(char *);
void tokenize_string(char *command, char *commandarray[], char sep);
size_t _getline(char **str, size_t *n, FILE *stream);
int handle_builtin_commands(char *commandarray[], char *env[]);
int (*get_fun(char *commandarray[]))(char *commandarray[], char **);
void execute_user_command(char *myprog, char *myargv[], char *env[]);
void convert_to_argv(char *command, char *commandarray[]);
char *resolve_path(char *, char *, char *);
int isonlydigit(char *);
int _str_len(const char *str);
int _atoi(char *s);
char *_strcpy(char *dest, const char *src);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, const char *src);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_getenv(const char *name, char *env[]);
int comp_env_with_val(const char *env, const char *val);
char *_getenv(const char *name, char *env[]);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
size_t print_to_fd(int fd, char *string);
size_t print_to_stdout(char *string);
size_t print_to_stderr(char *string);

int exit_command(char *commandarray[], char *env[] __attribute__((unused)));
int env_command(char *commandarray[] __attribute__((unused)), char *env[]);
int cd_command(char *commandarray[], char *env[]);
int alias_command(char *commandarray[], char *env[] __attribute__((unused)));

void displayaliases(alias_t aliases[]);
void updatealiases(char *str, alias_t aliases[]);

void remove_quotes(char *commandarray[]);
void remove_single_quotes(char *str);
void delete_char_at_index(char *str, int index);
int does_str_contain(char *, char);
void display_or_update_aliases(char *commandarray[], alias_t aliases[]);
int get_alias_index(alias_t aliases[], char *name);

#endif /* SHELL_H */
