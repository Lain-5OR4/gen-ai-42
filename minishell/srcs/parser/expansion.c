/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude            #+#  +:+       #+#        */
/*                                                #+#    #+#             */
/*   Created: 2025/05/07 12:00:00 by claude           #+#    #+#            */
/*   Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_var_name(char *str, int *i)
{
	int		start;
	int		len;
	char	*var_name;

	start = *i;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	else if (str[*i] >= '0' && str[*i] <= '9')
	{
		(*i)++;
		return (ft_strdup("0"));
	}
	while (str[*i] && (str[*i] == '_' || (str[*i] >= 'a' && str[*i] <= 'z')
			|| (str[*i] >= 'A' && str[*i] <= 'Z')
			|| (str[*i] >= '0' && str[*i] <= '9')))
		(*i)++;
	len = *i - start;
	if (len == 0)
		return (ft_strdup("$"));
	var_name = ft_substr(str, start, len);
	return (var_name);
}

static char	*replace_variable(char *str, int *i, t_env *env, int exit_status)
{
	char	*var_name;
	char	*var_value;
	char	*result;

	(*i)++;
	var_name = get_var_name(str + *i, i);
	if (ft_strcmp(var_name, "?") == 0)
	{
		free(var_name);
		return (ft_itoa(exit_status));
	}
	var_value = get_env_value(env, var_name);
	free(var_name);
	if (var_value)
		result = ft_strdup(var_value);
	else
		result = ft_strdup("");
	return (result);
}

char	*expand_variables(char *str, t_env *env, int exit_status)
{
	char	*result;
	int		i;
	int		j;
	char	*var_value;

	result = ft_calloc(1, 1);
	i = 0;
	while (str[i])
	{
		j = i;
		while (str[i] && str[i] != '$')
			i++;
		if (i > j)
		{
			var_value = ft_substr(str, j, i - j);
			result = ft_strjoin(result, var_value);
			free(var_value);
		}
		if (str[i] == '$')
		{
			var_value = replace_variable(str, &i, env, exit_status);
			result = ft_strjoin(result, var_value);
			free(var_value);
		}
	}
	return (result);
}

char	*process_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;
	char	quote;

	result = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				result[j++] = str[i++];
			if (str[i])
				i++;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}