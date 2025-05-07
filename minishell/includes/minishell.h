/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claude            #+#  +:+       #+#        */
/*                                                #+#    #+#             */
/*   Created: 2025/05/07 12:00:00 by claude           #+#    #+#            */
/*   Updated: 2025/05/07 12:00:00 by claude          ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SUCCESS 0
# define ERROR 1
# define SYNTAX_ERROR 2
# define EXIT_ERROR 130

/* トークンタイプ */
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC,
	TOKEN_NEWLINE
}	t_token_type;

/* レキサーのトークン構造体 */
typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

/* リダイレクション構造体 */
typedef struct s_redirect
{
	char				*file;
	int					type;
	int					fd;
	struct s_redirect	*next;
}	t_redirect;

/* コマンド構造体 */
typedef struct s_command
{
	char				**args;
	char				*cmd;
	int					pipe_in;
	int					pipe_out;
	int					is_piped;
	t_redirect			*redirects;
	struct s_command	*next;
}	t_command;

/* 環境変数構造体 */
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* シェル構造体 - グローバル状態 */
typedef struct s_shell
{
	t_env		*env;
	t_command	*commands;
	t_token		*tokens;
	int			exit_status;
	int			in_heredoc;
	int			should_exit;
}	t_shell;

extern t_shell	g_shell;

/* 初期化関数 */
void		init_shell(char **envp);
void		init_signals(void);

/* シグナルハンドラ */
void		sig_handler(int signum);
void		sig_handler_heredoc(int signum);

/* 環境変数操作 */
t_env		*create_env_node(char *key, char *value);
void		add_env_node(t_env **env, t_env *new_node);
t_env		*get_env_node(t_env *env, char *key);
void		free_env(t_env *env);
char		**env_to_array(t_env *env);

/* 入力処理と構文解析 */
int			process_input(char *input);
int			lexer(char *input, t_token **tokens);
int			parser(t_token *tokens, t_command **commands);

/* レキサーユーティリティ */
t_token		*create_token(char *value, t_token_type type);
void		add_token(t_token **tokens, t_token *new_token);
void		free_tokens(t_token *tokens);
int			is_special_char(char c);
int			is_whitespace(char c);

/* パーサーユーティリティ */
t_command	*create_command(void);
void		add_command(t_command **commands, t_command *new_cmd);
void		free_commands(t_command *commands);
t_redirect	*create_redirect(char *file, int type);
void		add_redirect(t_redirect **redirects, t_redirect *new_redirect);

/* 拡張と引用符処理 */
char		*expand_variables(char *str, t_env *env, int exit_status);
char		*process_quotes(char *str);

/* コマンド実行 */
int			execute_commands(t_command *commands, t_env **env);
int			execute_builtin(t_command *cmd, t_env **env);
int			execute_external(t_command *cmd, t_env **env);
int			setup_redirections(t_command *cmd);
int			setup_pipes(t_command *cmd);

/* ビルトインコマンド */
int			ft_echo(t_command *cmd);
int			ft_cd(t_command *cmd, t_env **env);
int			ft_pwd(void);
int			ft_export(t_command *cmd, t_env **env);
int			ft_unset(t_command *cmd, t_env **env);
int			ft_env(t_env *env);
int			ft_exit(t_command *cmd);

/* パス処理 */
char		*find_command_path(char *cmd, t_env *env);
char		*get_env_value(t_env *env, char *key);

/* ヘアドキュメント */
int			handle_heredoc(t_command *commands);
char		*get_heredoc_input(char *delimiter);

/* ユーティリティ関数 */
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_strlen(const char *s);
char		**ft_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		error_message(char *cmd, char *arg, char *message);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memset(void *b, int c, size_t len);

#endif