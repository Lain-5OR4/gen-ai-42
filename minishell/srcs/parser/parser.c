/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude            #+#  +:+       #+#        */
/*                                                #+#    #+#             */
/*   Created: 2025/05/07 12:00:00 by claude           #+#    #+#            */
/*   Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_args(t_token *tokens, int pipe_boundary)
{
	t_token	*current;
	int		count;

	current = tokens;
	count = 0;
	while (current && (current->type != TOKEN_PIPE || !pipe_boundary))
	{
		if (current->type == TOKEN_WORD)
		{
			count++;
			current = current->next;
		}
		else if (current->type == TOKEN_REDIRECT_IN
			|| current->type == TOKEN_REDIRECT_OUT
			|| current->type == TOKEN_REDIRECT_APPEND
			|| current->type == TOKEN_HEREDOC)
		{
			current = current->next;
			if (current)
				current = current->next;
		}
		else
			current = current->next;
	}
	return (count);
}

static char	**create_args_array(t_token *tokens, int pipe_boundary)
{
	t_token	*current;
	char	**args;
	int		count;
	int		i;

	count = count_args(tokens, pipe_boundary);
	args = (char **)malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	current = tokens;
	i = 0;
	while (current && (current->type != TOKEN_PIPE || !pipe_boundary))
	{
		if (current->type == TOKEN_WORD)
		{
			args[i++] = ft_strdup(current->value);
			current = current->next;
		}
		else if (current->type == TOKEN_REDIRECT_IN
			|| current->type == TOKEN_REDIRECT_OUT
			|| current->type == TOKEN_REDIRECT_APPEND
			|| current->type == TOKEN_HEREDOC)
		{
			current = current->next;
			if (current)
				current = current->next;
		}
		else
			current = current->next;
	}
	args[i] = NULL;
	return (args);
}

static int	handle_redirections(t_token *tokens, t_command *cmd, int pipe_boundary)
{
	t_token	*current;
	t_token	*file_token;

	current = tokens;
	while (current && (current->type != TOKEN_PIPE || !pipe_boundary))
	{
		if (current->type == TOKEN_REDIRECT_IN
			|| current->type == TOKEN_REDIRECT_OUT
			|| current->type == TOKEN_REDIRECT_APPEND
			|| current->type == TOKEN_HEREDOC)
		{
			file_token = current->next;
			if (file_token && file_token->type == TOKEN_WORD)
			{
				add_redirect(&cmd->redirects,
					create_redirect(file_token->value, current->type));
				current = file_token->next;
			}
			else
				current = current->next;
		}
		else
			current = current->next;
	}
	return (SUCCESS);
}

static t_token	*parse_command(t_token *tokens, t_command **commands)
{
	t_command	*new_cmd;
	t_token		*current;

	new_cmd = create_command();
	if (!new_cmd)
		return (NULL);
	new_cmd->args = create_args_array(tokens, 1);
	if (new_cmd->args && new_cmd->args[0])
		new_cmd->cmd = ft_strdup(new_cmd->args[0]);
	handle_redirections(tokens, new_cmd, 1);
	add_command(commands, new_cmd);
	current = tokens;
	while (current && current->type != TOKEN_PIPE)
		current = current->next;
	if (current && current->type == TOKEN_PIPE)
		return (current->next);
	return (NULL);
}

int	parser(t_token *tokens, t_command **commands)
{
	t_token	*current;

	*commands = NULL;
	current = tokens;
	while (current)
		current = parse_command(current, commands);
	return (SUCCESS);
}