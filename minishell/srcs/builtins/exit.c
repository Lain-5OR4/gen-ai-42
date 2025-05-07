/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude            #+#  +:+       #+#        */
/*                                                #+#    #+#             */
/*   Created: 2025/05/07 12:00:00 by claude           #+#    #+#            */
/*   Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_command *cmd)
{
	int	status;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmd->args[1])
	{
		if (!is_numeric(cmd->args[1]))
		{
			error_message("exit", cmd->args[1], "numeric argument required");
			g_shell.exit_status = 255;
		}
		else if (cmd->args[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			return (ERROR);
		}
		else
			g_shell.exit_status = (unsigned char)ft_atoi(cmd->args[1]);
	}
	else
		g_shell.exit_status = g_shell.exit_status;
	status = g_shell.exit_status;
	g_shell.should_exit = 1;
	return (status);
}