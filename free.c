/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 21:58:43 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/10 22:40:09 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_douple(char ***arr)
{
	int	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}

void	close_all_fds(t_pipex *ppx)
{
	if (!ppx)
		return ;
	if (ppx->pipe[WR_END] != -1)
		close(ppx->pipe[WR_END]);
	if (ppx->pipe[RD_END] != -1)
		close(ppx->pipe[RD_END]);
	if (ppx->pipeout != -1)
		close(ppx->pipeout);
	if (ppx->infile != -1)
		close(ppx->infile);
	if (ppx->outfile != -1)
		close(ppx->outfile);
}

void	self_destruct(t_pipex *ppx)
{
	if (!ppx)
		return ;
	if (ppx->cmd != NULL)
		free_douple(&ppx->cmd);
	if (ppx->paths != NULL)
		free_douple(&ppx->paths);
	free(ppx->exec);
	ppx->exec = NULL;
	free(ppx->temp);
	ppx->temp = NULL;
	free(ppx->pids);
	ppx->pids = NULL;
}
