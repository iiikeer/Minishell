/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:56:49 by elopez-u          #+#    #+#             */
/*   Updated: 2025/05/16 10:00:23 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>

extern int	g_status;

typedef struct s_node
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
	int		is_exec;
	pid_t	pid;
}	t_node;

typedef struct s_mini
{
	char		**env;
	char		*input;
	char		**tokens;
	int			nbr_nodes;
	t_node		**nodes;
}	t_mini;

// MAIN
void		mini_loop(t_mini *mini);

//SIGNALS
void		handle_signals(void);

// INITIALIZATION
void		init_mini(t_mini *mini);
char		**copy_env(char **env);
void		init_input(t_mini *mini);
char		*read_input(const char *hostname);
char		*spacer(char *line, int i, int j);
void		tokenizer(t_mini *mini, char *line);
void		expand_tokens(t_mini *mini);
void		validate_pipes_redir(t_mini *mini);
int			validate_redirections(char **tokens);
int			validate_pipes(char **tokens);
void		quotes_remover(char **tokens);

// NODES
void		create_nodes(t_mini *mini);
t_node		*new_node(t_mini *mini, char **tokens);
void		init_node(t_node *node);
char		**set_cmd(char **tokens, int count, int i, int j);
void		set_paths(t_node *node, char **env, int i);
int			set_in_out_file(t_node *node, char **tok, int in_fd, int out_fd);

// EXECUTION
void		execution(t_mini *mini);
void		execute_multiple_cmds(t_mini *mini);
void		execute_cmd(t_mini *mini, t_node *node);
int			execute_builtin(t_mini *mini, t_node *node);
int			ft_cd(t_node *node, char **env);
int			ft_pwd(void);
int			ft_env(t_node *node, char **env);
int			ft_exit(t_mini *mini, t_node *node, int exit_code);
int			ft_echo(t_node *node);
int			ft_unset(t_mini *mini, t_node *node, char **env);
int			ft_export(t_mini *mini, char **env);
void		execute_pipeline(t_mini *mini);

// UTILS
char		*hostname(void);
int			contains_any_char(char *s, char *c);
void		free_array(char **arr);
void		free_mini(t_mini *mini);
int			has_quotes(char	*token);
int			is_builtin(char *cmd);
void		open_quotes(char c, int *sq, int *dq);
void		print_minishell(void);
void		update_exit_status(t_mini *mini);
void		ft_error(t_mini *mini);
void		ft_error_tok(t_mini *mini);
char		*get_value(char *name, char **env);

// LIBFT
long int	ft_atol(const char *str);
int			ft_isalnum(int c);
int			ft_isspace(int c);
char		*ft_itoa(int nbr);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char const *s, char c);
char		*ft_strcat(char *dest, const char *src);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strdup(const char *s);
char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strndup(const char *s, size_t n);

#endif