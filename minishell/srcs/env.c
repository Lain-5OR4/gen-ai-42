/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude            #+#  +:+       #+#        */
/*                                                #+#    #+#             */
/*   Created: 2025/05/07 12:00:00 by claude           #+#    #+#            */
/*   Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*create_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	add_env_node(t_env **env, t_env *new_node)
{
	t_env	*current;

	if (!*env)
	{
		*env = new_node;
		return ;
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

t_env	*get_env_node(t_env *env, char *key)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	free_env(t_env *env)
{
	t_env	*current;
	t_env	*next;

	current = env;
	while (current)
	{
		next = current->next;
		free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

char	**env_to_array(t_env *env)
{
	t_env	*current;
	char	**env_array;
	int		size;
	int		i;
	char	*tmp;

	size = 0;
	current = env;
	while (current && ++size)
		current = current->next;
	env_array = (char **)malloc(sizeof(char *) * (size + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	current = env;
	while (current)
	{
		if (current->value)
		{
			tmp = ft_strjoin(current->key, "=");
			env_array[i] = ft_strjoin(tmp, current->value);
			free(tmp);
			i++;
		}
		current = current->next;
	}
	env_array[i] = NULL;
	return (env_array);
}