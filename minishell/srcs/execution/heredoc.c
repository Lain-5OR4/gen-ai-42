/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude            #+#  +:+       #+#        */
/*                                                #+#    #+#             */
/*   Created: 2025/05/07 12:00:00 by claude           #+#    #+#            */
/*   Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	create_temp_file(void)
{
	char	*filename;
	int		fd;
	int		i;

	i = 0;
	while (1)
	{
		filename = ft_strjoin("/tmp/minishell_heredoc_", ft_itoa(i));
		fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0600);
		free(filename);
		if (fd != -1)
			return (fd);
		if (errno != EEXIST)
			return (-1);
		i++;
	}
}

char	*get_heredoc_input(char *delimiter)
{
	char	*line;
	char	*content;
	char	*temp;

	content = ft_strdup("");
	g_shell.in_heredoc = 1;
	signal(SIGINT, sig_handler_heredoc);
	while (1)
	{
		line = readline("> ");
		if (!line || !g_shell.in_heredoc || !ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		temp = ft_strjoin(content, line);
		free(content);
		content = ft_strjoin(temp, "\n");
		free(temp);
		free(line);
	}
	g_shell.in_heredoc = 0;
	signal(SIGINT, sig_handler);
	return (content);
}

static int	process_heredoc(t_redirect *redirect)
{
	char	*content;
	int		fd;

	content = get_heredoc_input(redirect->file);
	if (!g_shell.in_heredoc && g_shell.exit_status == 130)
		return (ERROR);
	fd = create_temp_file();
	if (fd == -1)
	{
		free(content);
		return (ERROR);
	}
	write(fd, content, ft_strlen(content));
	free(content);
	close(fd);
	free(redirect->file);
	redirect->file = ft_strdup("/tmp/minishell_heredoc");
	redirect->type = TOKEN_REDIRECT_IN;
	return (SUCCESS);
}

int	handle_heredoc(t_command *commands)
{
	t_command	*current;
	t_redirect	*redirect;

	current = commands;
	while (current)
	{
		redirect = current->redirects;
		while (redirect)
		{
			if (redirect->type == TOKEN_HEREDOC)
			{
				if (process_heredoc(redirect) == ERROR)
					return (ERROR);
			}
			redirect = redirect->next;
		}
		current = current->next;
	}
	return (SUCCESS);
}