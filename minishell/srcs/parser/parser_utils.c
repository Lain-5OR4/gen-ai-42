/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude            #+#  +:+       #+#        */
/*                                                #+#    #+#             */
/*   Created: 2025/05/07 12:00:00 by claude           #+#    #+#            */
/*   Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*create_command(void)
{
	t_command	*new_cmd;

	new_cmd = (t_command *)malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd->args = NULL;
	new_cmd->cmd = NULL;
	new_cmd->pipe_in = -1;
	new_cmd->pipe_out = -1;
	new_cmd->is_piped = 0;
	new_cmd->redirects = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	add_command(t_command **commands, t_command *new_cmd)
{
	t_command	*current;

	if (!*commands)
	{
		*commands = new_cmd;
		return ;
	}
	current = *commands;
	while (current->next)
		current = current->next;
	current->next = new_cmd;
}

t_redirect	*create_redirect(char *file, int type)
{
	t_redirect	*new_redirect;

	new_redirect = (t_redirect *)malloc(sizeof(t_redirect));
	if (!new_redirect)
		return (NULL);
	new_redirect->file = ft_strdup(file);
	new_redirect->type = type;
	new_redirect->fd = -1;
	new_redirect->next = NULL;
	return (new_redirect);
}

void	add_redirect(t_redirect **redirects, t_redirect *new_redirect)
{
	t_redirect	*current;

	if (!*redirects)
	{
		*redirects = new_redirect;
		return ;
	}
	current = *redirects;
	while (current->next)
		current = current->next;
	current->next = new_redirect;
}

void	free_commands(t_command *commands)
{
	t_command	*current;
	t_command	*next;
	t_redirect	*redirect;
	t_redirect	*next_redirect;
	int			i;

	current = commands;
	while (current)
	{
		next = current->next;
		if (current->args)
		{
			i = 0;
			while (current->args[i])
				free(current->args[i++]);
			free(current->args);
		}
		if (current->cmd)
			free(current->cmd);
		redirect = current->redirects;
		while (redirect)
		{
			next_redirect = redirect->next;
			free(redirect->file);
			free(redirect);
			redirect = next_redirect;
		}
		free(current);
		current = next;
	}
}