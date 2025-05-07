/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude            #+#  +:+       #+#        */
/*                                                #+#    #+#             */
/*   Created: 2025/05/07 12:00:00 by claude           #+#    #+#            */
/*   Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!(str[0] == '_' || (str[0] >= 'a' && str[0] <= 'z')
			|| (str[0] >= 'A' && str[0] <= 'Z')))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(str[i] == '_' || (str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= '0' && str[i] <= '9')))
			return (0);
		i++;
	}
	return (1);
}

static void	add_env_variable(t_env **env, char *arg)
{
	char	*equals;
	char	*key;
	char	*value;
	t_env	*node;

	equals = ft_strchr(arg, '=');
	if (equals)
	{
		key = ft_substr(arg, 0, equals - arg);
		value = ft_strdup(equals + 1);
		node = get_env_node(*env, key);
		if (node)
		{
			free(node->value);
			node->value = value;
		}
		else
			add_env_node(env, create_env_node(key, value));
		free(key);
	}
	else
	{
		node = get_env_node(*env, arg);
		if (!node)
			add_env_node(env, create_env_node(arg, NULL));
	}
}

static void	print_export(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(current->key, STDOUT_FILENO);
		if (current->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(current->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		current = current->next;
	}
}

int	ft_export(t_command *cmd, t_env **env)
{
	int	i;
	int	status;

	status = SUCCESS;
	if (!cmd->args[1])
	{
		print_export(*env);
		return (SUCCESS);
	}
	i = 1;
	while (cmd->args[i])
	{
		if (is_valid_identifier(cmd->args[i]))
			add_env_variable(env, cmd->args[i]);
		else
		{
			error_message("export", cmd->args[i], "not a valid identifier");
			status = ERROR;
		}
		i++;
	}
	return (status);
}