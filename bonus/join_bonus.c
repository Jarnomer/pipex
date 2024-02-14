/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:35:19 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/14 16:10:32 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	count_quotes(char *content, char c)
{
	int	cnt;
	int	i;

	i = 0;
	cnt = 0;
	while (content[i])
	{
		if (content[i] == c)
			cnt++;
		++i;
	}
	return (cnt);
}

static void	filter_quotes(char *content, char c, t_pipex *ppx)
{
	char	*temp;
	int		i;
	int		j;

	temp = ft_strdup(content);
	if (!temp)
		error_occured(ERR_MEM, MSG_MEM, ppx);
	i = ft_strlen(content) - 1;
	j = i - count_quotes(content, c);
	ft_bzero(content, i);
	while (i >= 0)
	{
		if (temp[i] != c)
			content[j--] = temp[i];
		i--;
	}
	free(temp);
}

static int	count_arguments(t_parse *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		lst = lst->next;
		++len;
	}
	return (len);
}

void	join_arguments(char c, t_pipex *ppx)
{
	t_parse	*temp;
	int		i;

	ppx->cmd = ft_calloc(sizeof(char *),
			count_arguments(ppx->args) + 1);
	if (!ppx->cmd)
		error_occured(ERR_MEM, MSG_MEM, ppx);
	temp = ppx->args;
	i = 0;
	while (temp)
	{
		if (ft_strchr(temp->content, c))
			filter_quotes(temp->content, c, ppx);
		ppx->cmd[i++] = temp->content;
		temp = temp->next;
	}
}
