/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude            #+#  +:+       #+#        */
/*                                                #+#    #+#             */
/*   Created: 2025/05/07 12:00:00 by claude           #+#    #+#            */
/*   Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	parse_env(char **envp, t_env **env)
{
	int		i;
	char	*key;
	char	*value;
	char	*equals;
	t_env	*new_node;

	i = 0;
	while (envp[i])
	{
		equals = ft_strchr(envp[i], '=');
		if (equals)
		{
			key = ft_substr(envp[i], 0, equals - envp[i]);
			value = ft_strdup(equals + 1);
			new_node = create_env_node(key, value);
			if (new_node)
				add_env_node(env, new_node);
			free(key);
			free(value);
		}
		i++;
	}
}

void	init_shell(char **envp)
{
	ft_memset(&g_shell, 0, sizeof(t_shell));
	g_shell.exit_status = 0;
	g_shell.should_exit = 0;
	g_shell.in_heredoc = 0;
	parse_env(envp, &g_shell.env);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_shell.exit_status = 130;
	}
}

void	sig_handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		g_shell.exit_status = 130;
		g_shell.in_heredoc = 0;
		close(STDIN_FILENO);
	}
}

void	init_signals(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}