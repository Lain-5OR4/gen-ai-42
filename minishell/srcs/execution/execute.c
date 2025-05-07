/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude            #+#  +:+       #+#        */
/*                                                #+#    #+#             */
/*   Created: 2025/05/07 12:00:00 by claude           #+#    #+#            */
/*   Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"));
}

int	execute_builtin(t_command *cmd, t_env **env)
{
	if (!ft_strcmp(cmd->cmd, "echo"))
		return (ft_echo(cmd));
	else if (!ft_strcmp(cmd->cmd, "cd"))
		return (ft_cd(cmd, env));
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd->cmd, "export"))
		return (ft_export(cmd, env));
	else if (!ft_strcmp(cmd->cmd, "unset"))
		return (ft_unset(cmd, env));
	else if (!ft_strcmp(cmd->cmd, "env"))
		return (ft_env(*env));
	else if (!ft_strcmp(cmd->cmd, "exit"))
		return (ft_exit(cmd));
	return (ERROR);
}

int	execute_external(t_command *cmd, t_env **env)
{
	char	*path;
	char	**env_array;
	pid_t	pid;
	int		status;

	path = find_command_path(cmd->cmd, *env);
	if (!path)
	{
		error_message(cmd->cmd, NULL, "command not found");
		return (127);
	}
	env_array = env_to_array(*env);
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, cmd->args, env_array) == -1)
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		free(path);
		free(env_array);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (EXIT_ERROR);
}

static int	execute_single_command(t_command *cmd, t_env **env)
{
	int	status;

	if (setup_redirections(cmd) != SUCCESS)
		return (ERROR);
	if (!cmd->cmd)
		return (SUCCESS);
	if (is_builtin(cmd->cmd))
		status = execute_builtin(cmd, env);
	else
		status = execute_external(cmd, env);
	return (status);
}

static int	execute_pipeline(t_command *commands, t_env **env)
{
	t_command	*current;
	pid_t		pid;
	int			status;
	int			last_status;

	current = commands;
	last_status = 0;
	while (current)
	{
		if (current->next)
			setup_pipes(current);
		pid = fork();
		if (pid == 0)
		{
			if (current->pipe_in != -1)
			{
				dup2(current->pipe_in, STDIN_FILENO);
				close(current->pipe_in);
			}
			if (current->pipe_out != -1)
			{
				dup2(current->pipe_out, STDOUT_FILENO);
				close(current->pipe_out);
			}
			status = execute_single_command(current, env);
			exit(status);
		}
		if (current->pipe_in != -1)
			close(current->pipe_in);
		if (current->pipe_out != -1)
			close(current->pipe_out);
		current = current->next;
	}
	while (wait(&status) > 0)
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
	return (last_status);
}

int	execute_commands(t_command *commands, t_env **env)
{
	t_command	*current;
	int			count;
	int			status;

	count = 0;
	current = commands;
	while (current && ++count)
		current = current->next;
	if (count == 1 && is_builtin(commands->cmd))
		status = execute_single_command(commands, env);
	else
		status = execute_pipeline(commands, env);
	g_shell.exit_status = status;
	return (status);
}