/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude            #+#  +:+       #+#        */
/*                                                #+#    #+#             */
/*   Created: 2025/05/07 12:00:00 by claude           #+#    #+#            */
/*   Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_pwd_env(t_env **env)
{
	t_env	*pwd_node;
	t_env	*oldpwd_node;
	char	cwd[1024];

	pwd_node = get_env_node(*env, "PWD");
	oldpwd_node = get_env_node(*env, "OLDPWD");
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return ;
	if (oldpwd_node)
	{
		free(oldpwd_node->value);
		if (pwd_node && pwd_node->value)
			oldpwd_node->value = ft_strdup(pwd_node->value);
		else
			oldpwd_node->value = NULL;
	}
	if (pwd_node)
	{
		free(pwd_node->value);
		pwd_node->value = ft_strdup(cwd);
	}
}

int	ft_cd(t_command *cmd, t_env **env)
{
	char	*path;
	t_env	*home_node;

	if (!cmd->args[1])
	{
		home_node = get_env_node(*env, "HOME");
		if (!home_node || !home_node->value)
		{
			ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
			return (ERROR);
		}
		path = home_node->value;
	}
	else
		path = cmd->args[1];
	if (chdir(path) == -1)
	{
		error_message("cd", path, strerror(errno));
		return (ERROR);
	}
	update_pwd_env(env);
	return (SUCCESS);
}