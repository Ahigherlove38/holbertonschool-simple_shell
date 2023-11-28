#include "main.h"
/**
 * tokenize_path - tokenizes PATH variable into an array of tokens
 * @path_string: the full path string
 *
 * Returns: array of pointers to path tokens
 */

char **tokenize_path(char *path_string)
{
	char **path_tokens; /*  array of pointers to store path tokens */
	int token_index = 0;
	char *token; /* temporary token storage */

	/* allocate memory for the buffer */
	path_tokens = (char **)malloc(sizeof(char *) * 1024);
	if (path_tokens == NULL)
	{
		perror("Error in memory allocation");
		exit(EXIT_FAILURE);
	}

	/* tokenize path string */
	token = strtok(path_string, ":");
	while (token != NULL)
	{
		path_token[token_index] = token;
		token = strtok(NULL, ":");
		token_index++;
	}
	path_tokens[token_index] = NULL; /* marking end of buffer */
	
	return (path_tokens);
}

/**
 * get_full_path - gets the  full path fo a given command
 * @command: the command for which the full path is needed
 *
 * Returns: full path or NULL on error
 */
char *get_full_path(char *command)
{
	char *path_env, *copied_path;
	char full_path[1024];
	char *path_token;
	struct stat file_info;

	/* get the value of the PATH environment variable */
	path_env = getenv("PATH");
	if (path_env == NULL)
	{
		perror("getenv");
		return (NULL);
	}

	/* duplicate the environment variable for tokenization */
	copied_path = strdup(path_env);
	if (copied_path == NULL)
	{
		perror("strdup");
		return (NULL);
	}

	/* tokenize the PATH variable to search for the command */
	path_token =strtok(copied_path, ":");
	while (path_token)
	{
		/* construct full path */
		snprintf(full_path, sizeof(full_path), "%s/%s", path_token, command);

		/* check if path is valid */
		if (stat(full_path, &file_info) == 0)
		{
			free(copied_path);
			return (strdup(full_path);
		}
		path_token = strtok(NULL, ":"); /* get next token */
	}

	free(copied_path);
	return (NULL);
}

/**
 * print_envirionment - prints the current environment variables
 */

void print_environment(void)
{
	char **env_variable = environ; /* pointer to environment variables */

	while (*env_variable != NULL)
	{
		printf("%s\n", *env_variable);
		env_variable++;
	}
}
