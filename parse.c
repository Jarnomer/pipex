/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:28:30 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/14 16:15:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	append_argument(t_parse **lst, t_parse *new)
{
	t_parse	*temp;

	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

static char	*find_breakpoint(char *argv, char c)
{
	int	q;

	q = 0;
	while (*argv && *argv != ' ')
	{
		if (*argv == c)
			q++;
		argv++;
	}
	if (*argv && q == 1)
	{
		while (q != 0)
		{
			if (*argv == c)
				q--;
			argv++;
		}
	}
	return (argv);
}

static char	*find_startpoint(char *argv)
{
	while (*argv && *argv == ' ')
		argv++;
	return (argv);
}

static void	format_arguments(char *argv, char c, t_pipex *ppx)
{
	t_parse	*new;
	char	*temp;

	while (*argv)
	{
		argv = find_startpoint(argv);
		if (!*argv)
			error_occured(ERR_CMD, MSG_CMD, ppx);
		temp = find_breakpoint(argv, c);
		new = ft_calloc(1, sizeof(t_parse));
		if (!new)
			error_occured(ERR_MEM, MSG_MEM, ppx);
		new->content = ft_substr(argv, 0, temp - argv);
		if (!new->content)
			error_occured(ERR_MEM, MSG_MEM, ppx);
		append_argument(&ppx->args, new);
		argv = temp;
	}
	join_arguments(c, ppx);
}

void	parse_argument(char *argv, t_pipex *ppx)
{
	if (ft_strchr(argv, '\'') && ft_strchr(argv, '\"')
		&& (ft_strchr(argv, '\'') > ft_strchr(argv, '\"')))
		format_arguments(argv, '\"', ppx);
	else if (ft_strchr(argv, '\'') && ft_strchr(argv, '\"'))
		format_arguments(argv, '\'', ppx);
	else if (ft_strchr(argv, '\"'))
		format_arguments(argv, '\"', ppx);
	else if (ft_strchr(argv, '\''))
		format_arguments(argv, '\'', ppx);
	else
		format_arguments(argv, ' ', ppx);
}
