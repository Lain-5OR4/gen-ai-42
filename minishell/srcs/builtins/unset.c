/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude            #+#  +:+       #+#        */
/*                                                #+#    #+#             */
/*   Created: 2025/05/07 12:00:00 by claude           #+#    #+#            */
/*   Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	remove_env_node(t_env **env, char *key)
{
	t_env	*current;
	t_env	*prev;

	if (!*env)
		return ;
	current = *env;
	prev = NULL;
	if (ft_strcmp(current->key, key) == 0)
	{
		*env = current->next;
		free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		return ;
	}
	while (current && ft_strcmp(current->key, key) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (current)
	{
		prev->next = current->next;
		free(current->key);
		if (current->value)
			free(current->value);
		free(current);
	}
}

int	ft_unset(t_command *cmd, t_env **env)
{
	int	i;
	int	status;

	status = SUCCESS;
	i = 1;
	while (cmd->args[i])
	{
		if (ft_strchr(cmd->args[i], '='))
		{
			error_message("unset", cmd->args[i], "not a valid identifier");
			status = ERROR;
		}
		else
			remove_env_node(env, cmd->args[i]);
		i++;
	}
	return (status);
}