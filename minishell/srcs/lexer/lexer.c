/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude            #+#  +:+       #+#        */
/*                                                #+#    #+#             */
/*   Created: 2025/05/07 12:00:00 by claude           #+#    #+#            */
/*   Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_pipe(char *input, int *i, t_token **tokens)
{
	if (input[*i] == '|')
	{
		add_token(tokens, create_token("|", TOKEN_PIPE));
		(*i)++;
		return (1);
	}
	return (0);
}

static int	handle_redirect(char *input, int *i, t_token **tokens)
{
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			add_token(tokens, create_token("<<", TOKEN_HEREDOC));
			(*i) += 2;
		}
		else
		{
			add_token(tokens, create_token("<", TOKEN_REDIRECT_IN));
			(*i)++;
		}
		return (1);
	}
	else if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			add_token(tokens, create_token(">>", TOKEN_REDIRECT_APPEND));
			(*i) += 2;
		}
		else
		{
			add_token(tokens, create_token(">", TOKEN_REDIRECT_OUT));
			(*i)++;
		}
		return (1);
	}
	return (0);
}

static int	handle_quotes(char *input, int *i, int *j, char **word)
{
	char	quote;
	int		start;

	quote = input[*i];
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (!input[*i])
	{
		ft_putendl_fd("minishell: unclosed quote", STDERR_FILENO);
		free(*word);
		return (ERROR);
	}
	*j += *i - start;
	(*i)++;
	return (SUCCESS);
}

static int	handle_word(char *input, int *i, t_token **tokens)
{
	int		start;
	int		j;
	char	*word;

	start = *i;
	j = 0;
	while (input[*i + j] && !is_whitespace(input[*i + j])
		&& !is_special_char(input[*i + j]))
		j++;
	word = ft_substr(input, start, j);
	if (!word)
		return (ERROR);
	add_token(tokens, create_token(word, TOKEN_WORD));
	free(word);
	*i += j;
	return (SUCCESS);
}

static int	tokenize_input(char *input, t_token **tokens)
{
	int		i;
	int		status;

	i = 0;
	while (input[i])
	{
		if (is_whitespace(input[i]))
			i++;
		else if (handle_pipe(input, &i, tokens) || handle_redirect(input, &i, tokens))
			continue ;
		else
		{
			status = handle_word(input, &i, tokens);
			if (status != SUCCESS)
				return (status);
		}
	}
	return (SUCCESS);
}

int	lexer(char *input, t_token **tokens)
{
	*tokens = NULL;
	return (tokenize_input(input, tokens));
}