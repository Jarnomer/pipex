/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 23:18:07 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/10 23:59:54 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	finish_heredoc(t_pipex *ppx)
{
	get_next_line(-1);
	free(ppx->temp);
	ppx->temp = NULL;
	free(ppx->lmtr);
	ppx->lmtr = NULL;
	close(ppx->pipe[WR_END]);
	close(ppx->pipe[RD_END]);
}

static void	prepare_heredoc(t_pipex *ppx)
{
	if (pipe(ppx->pipe) == -1)
		error_occured(ERR_PIPE, MSG_PIPE, ppx);
	ppx->lmtr = ft_strjoin(ppx->argv[2], "\n");
	if (!ppx->lmtr)
		error_occured(ERR_MEM, MSG_MEM, ppx);
	ppx->len = ft_strlen(ppx->lmtr);
	ft_putchar_fd('>', STDOUT_FILENO);
}

void	read_heredoc(t_pipex *ppx)
{
	prepare_heredoc(ppx);
	while (true)
	{
		ppx->temp = get_next_line(STDIN_FILENO);
		if (!ppx->temp)
			break ;
		if (!ft_strncmp(ppx->temp, ppx->lmtr, ppx->len))
			break ;
		ft_putstr_fd(ppx->temp, ppx->pipe[WR_END]);
		free(ppx->temp);
	}
	ppx->infile = dup(ppx->pipe[RD_END]);
	finish_heredoc(ppx);
}
