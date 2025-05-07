/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude            #+#  +:+       #+#        */
/*                                                #+#    #+#             */
/*   Created: 2025/05/07 12:00:00 by claude           #+#    #+#            */
/*   Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("minishell: pwd");
		return (ERROR);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (SUCCESS);
}