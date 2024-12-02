/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 22:09:53 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/10 20:40:25 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static char	*find_executable(t_pipex *ppx)
{
	int	i;

	i = 0;
	while (ppx->paths[i])
	{
		ppx->exec = ft_strjoin(ppx->paths[i++], ppx->temp);
		if (!ppx->exec)
			error_occured(ERR_MEM, MSG_MEM, ppx);
		else if (access(ppx->exec, F_OK) == 0)
			return (ppx->exec);
		free(ppx->exec);
	}
	return (NULL);
}

static char	**split_path_envp(t_pipex *ppx)
{
	int	i;

	i = 0;
	while (ppx->envp[i] != NULL
		&& !ft_strnstr(ppx->envp[i], "PATH=", 5))
		i++;
	if (ppx->envp[i] != NULL)
		return (ft_split(ppx->envp[i] + 5, ':'));
	ppx->error[NOPATH] = true;
	return (NULL);
}

char	*executable_path(t_pipex *ppx)
{
	if (!ppx->cmd || !*ppx->cmd)
		return (NULL);
	else if (ft_strchr(*ppx->cmd, '/'))
		return (ft_strdup(*ppx->cmd));
	ppx->paths = split_path_envp(ppx);
	if (!ppx->paths)
		return (NULL);
	ppx->temp = ft_strjoin("/", *ppx->cmd);
	if (!ppx->temp)
		error_occured(ERR_MEM, MSG_MEM, ppx);
	return (find_executable(ppx));
}
