/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 21:58:43 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/14 15:55:06 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_parser(t_parse **lst)
{
	t_parse	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
	free(*lst);
	*lst = NULL;
}

static void	free_single(char **str)
{
	if (!str || !*str)
		return ;
	free(*str);
	*str = NULL;
}

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
	if (ppx->args != NULL)
		free_parser(&ppx->args);
	if (ppx->exec != NULL)
		free_single(&ppx->exec);
	if (ppx->temp != NULL)
		free_single(&ppx->temp);
	if (ppx->pids != NULL)
	{
		free(ppx->pids);
		ppx->pids = NULL;
	}
}
