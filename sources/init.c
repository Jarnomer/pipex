/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:56:43 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/23 07:05:38 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static void	open_files(t_pipex *ppx)
{
	if (!ppx->is_hdoc)
	{
		ppx->infile = open(ppx->argv[1], O_RDONLY);
		ppx->outfile = open(ppx->argv[ppx->argc - 1],
				O_CREAT | O_WRONLY | O_TRUNC, PERMS);
	}
	else
	{
		read_heredoc(ppx);
		ppx->outfile = open(ppx->argv[ppx->argc - 1],
				O_CREAT | O_WRONLY | O_APPEND, PERMS);
	}
	if (ppx->infile == -1)
		error_logger(ppx->argv[1], ": ", strerror(errno));
	if (ppx->outfile == -1)
		error_logger(ppx->argv[ppx->argc - 1], ": ", strerror(errno));
}

static void	init_values(t_pipex *ppx)
{
	ppx->exitcode = NOERROR;
	ppx->inpipe = -1;
	ppx->infile = -1;
	ppx->outfile = -1;
	ppx->index = -1;
	ppx->start_pos = 2;
	ppx->cmd_count = ppx->argc - 4;
	if (!ft_strcmp("here_doc", ppx->argv[1]))
	{
		ppx->is_hdoc = true;
		ppx->cmd_count--;
		ppx->start_pos++;
	}
}

void	init_pipex(int argc, char **argv, char **envp, t_pipex *ppx)
{
	ft_bzero(ppx, sizeof(*ppx));
	ft_bzero(ppx->error, sizeof(ppx->error));
	ppx->argc = argc;
	ppx->argv = argv;
	ppx->envp = envp;
	init_values(ppx);
	open_files(ppx);
	ppx->pids = ft_calloc(sizeof(ppx->pids), (ppx->cmd_count + 1));
	if (!ppx->pids)
		error_occured(ERR_MEM, MSG_MEM, ppx);
}
