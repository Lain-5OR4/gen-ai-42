/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude            #+#  +:+       #+#        */
/*                                                #+#    #+#             */
/*   Created: 2025/05/07 12:00:00 by claude           #+#    #+#            */
/*   Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	g_shell;

static void	cleanup_shell(void)
{
	free_tokens(g_shell.tokens);
	free_commands(g_shell.commands);
	g_shell.tokens = NULL;
	g_shell.commands = NULL;
}

static void	run_shell(void)
{
	char	*input;

	while (!g_shell.should_exit)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (*input)
		{
			add_history(input);
			if (process_input(input) == SUCCESS)
			{
				if (g_shell.commands)
				{
					if (handle_heredoc(g_shell.commands) == SUCCESS)
						execute_commands(g_shell.commands, &g_shell.env);
				}
			}
		}
		free(input);
		cleanup_shell();
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	init_shell(envp);
	init_signals();
	run_shell();
	free_env(g_shell.env);
	return (g_shell.exit_status);
}