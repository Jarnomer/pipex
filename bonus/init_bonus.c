/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:56:43 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/11 08:44:17 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	open_files(t_pipex *ppx)
{
	if (!ppx->hdoc)
	{
		ppx->infile = open(ppx->argv[1], O_RDONLY);
		ppx->outfile = open(ppx->argv[ppx->argc - 1],
				O_CREAT | O_WRONLY | O_TRUNC, PERMISSIONS);
	}
	else
	{
		read_heredoc(ppx);
		ppx->outfile = open(ppx->argv[ppx->argc - 1],
				O_CREAT | O_WRONLY | O_APPEND, PERMISSIONS);
	}
	if (ppx->infile == -1)
		error_logger(ppx->argv[1], ": ", strerror(errno));
	if (ppx->outfile == -1)
		error_logger(ppx->argv[ppx->argc - 1], ": ", strerror(errno));
}

static void	init_values(t_pipex *ppx)
{
	ppx->pipeout = -1;
	ppx->infile = -1;
	ppx->outfile = -1;
	ppx->idx = -1;
	ppx->stt = 2;
	ppx->cmds = ppx->argc - 4;
	if (!ft_strncmp("here_doc", ppx->argv[1], 9))
	{
		ppx->hdoc = true;
		ppx->cmds--;
		ppx->stt++;
	}
}

void	init_pipex(int argc, char **argv, char **envp, t_pipex *ppx)
{
	ppx->argc = argc;
	ppx->argv = argv;
	ppx->envp = envp;
	ppx->ecode = NOERROR;
	init_values(ppx);
	open_files(ppx);
	ppx->pids = ft_calloc(sizeof(ppx->pids), (ppx->cmds + 1));
	if (!ppx->pids)
		error_occured(ERR_MEM, MSG_MEM, ppx);
}
