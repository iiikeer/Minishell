/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multiple_cmds.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iullibar <iullibar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:30:49 by iullibar          #+#    #+#             */
/*   Updated: 2025/05/12 11:42:51 by iullibar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	cmd_execution(t_mini *mini, t_node *node)
{
	if (!is_builtin(node->full_cmd[0]) && node->is_exec)
	{
		if (node->full_path == NULL || node->full_cmd == NULL)
		{
			printf("%s: command not found\n", node->full_cmd[0]);
			free_mini(mini);
			exit(127);
		}
		if (execve(node->full_path, node->full_cmd, mini->env) == -1)
		{
			printf("%s: command not found\n", node->full_cmd[0]);
			free_mini(mini);
			exit (127);
		}
	}
	else if (is_builtin(node->full_cmd[0]) && node->is_exec)
	{
		execute_builtin(mini, node);
		exit (g_status);
	}
}

static void	cmd_prepare(t_mini *min, t_node *node, int aux[2], int pipefd[2])
{
	if (node->infile != STDIN_FILENO)
	{
		if (dup2(node->infile, STDIN_FILENO) == -1)
			ft_error(min);
		close(node->infile);
	}
	else if (aux[1] != -1)
	{
		if (dup2(aux[1], STDIN_FILENO) == -1)
			ft_error(min);
		close(aux[1]);
	}
	if (node->outfile != STDOUT_FILENO)
	{
		if (dup2(node->outfile, STDOUT_FILENO) == -1)
			ft_error(min);
		close(node->outfile);
	}
	else if (aux[0] < min->nbr_nodes - 1)
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	cmd_execution(min, node);
}

void	execute_multiple_cmds(t_mini *mini)
{
	int	aux[2];
	int	pipefd[2];

	aux[0] = -1;
	aux[1] = -1;
	while (mini->nodes[++aux[0]])
	{
		if (pipe(pipefd) == -1)
			return ;
		mini->nodes[aux[0]]->pid = fork();
		if (mini->nodes[aux[0]]->pid == -1)
			return ;
		else if (mini->nodes[aux[0]]->pid == 0)
			cmd_prepare(mini, mini->nodes[aux[0]], aux, pipefd);
		else
		{
			close(pipefd[1]);
			if (aux[1] != -1)
				close(aux[1]);
			aux[1] = pipefd[0];
		}
	}
	aux[0] = -1;
	while (++aux[0] < mini->nbr_nodes)
		waitpid(mini->nodes[aux[0]]->pid, &g_status, 0);
}
