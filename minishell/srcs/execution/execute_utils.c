/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude            #+#  +:+       #+#        */
/*                                                #+#    #+#             */
/*   Created: 2025/05/07 12:00:00 by claude           #+#    #+#            */
/*   Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(t_env *env, char *key)
{
	t_env	*node;

	node = get_env_node(env, key);
	if (node)
		return (node->value);
	return (NULL);
}

static char	**get_paths(t_env *env)
{
	char	*path_env;
	char	**paths;

	path_env = get_env_value(env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	return (paths);
}

char	*find_command_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*path;
	char	*full_path;
	int		i;

	if (!cmd || !*cmd)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	paths = get_paths(env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(path, cmd);
		free(path);
		if (access(full_path, X_OK) == 0)
		{
			i = 0;
			while (paths[i])
				free(paths[i++]);
			free(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return (NULL);
}

int	setup_redirections(t_command *cmd)
{
	t_redirect	*current;
	int			stdin_backup;
	int			stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	current = cmd->redirects;
	while (current)
	{
		if (current->type == TOKEN_REDIRECT_IN)
		{
			current->fd = open(current->file, O_RDONLY);
			if (current->fd == -1)
			{
				error_message("minishell", current->file, strerror(errno));
				return (ERROR);
			}
			dup2(current->fd, STDIN_FILENO);
		}
		else if (current->type == TOKEN_REDIRECT_OUT)
		{
			current->fd = open(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (current->fd == -1)
			{
				error_message("minishell", current->file, strerror(errno));
				return (ERROR);
			}
			dup2(current->fd, STDOUT_FILENO);
		}
		else if (current->type == TOKEN_REDIRECT_APPEND)
		{
			current->fd = open(current->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (current->fd == -1)
			{
				error_message("minishell", current->file, strerror(errno));
				return (ERROR);
			}
			dup2(current->fd, STDOUT_FILENO);
		}
		current = current->next;
	}
	return (SUCCESS);
}

int	setup_pipes(t_command *cmd)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return (ERROR);
	}
	cmd->pipe_out = pipe_fd[1];
	cmd->next->pipe_in = pipe_fd[0];
	cmd->is_piped = 1;
	cmd->next->is_piped = 1;
	return (SUCCESS);
}