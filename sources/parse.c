/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2024/03/02 12:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	advance_parser(char *str, int i, int amount, t_parse *parser)
{
	if (str == NULL)
	{
		parser->quoted = false;
		parser->meta = 0;
	}
	else
	{
		parser->quoted = true;
		parser->meta = str[i];
	}
	return (amount);
}

int	handle_meta(char *str, t_parse *parser)
{
	if (str[0] == '\\' && str[1])
		return (2);
	if ((str[0] == '\'' || str[0] == '\"') && !parser->quoted)
		return (advance_parser(str, 0, 1, parser));
	if (parser->quoted && str[0] == parser->meta)
		return (advance_parser(NULL, 0, 1, parser));
	return (1);
}

int	is_delimiter(char c, t_parse *parser)
{
	if (parser->quoted)
		return (0);
	return (c == ' ' || c == '\t');
}

static int	count_tokens(char *cmd, t_parse *parser)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (cmd[i])
	{
		while (cmd[i] && is_delimiter(cmd[i], parser))
			i++;
		if (cmd[i])
			count++;
		while (cmd[i] && !is_delimiter(cmd[i], parser))
			i += handle_meta(&cmd[i], parser);
	}
	return (count);
}

void	parse_command(char *cmd, t_pipex *ppx)
{
	t_parse	parser;
	int		count;
	int		i;

	ft_bzero(&parser, sizeof(t_parse));
	count = count_tokens(cmd, &parser);
	ppx->cmd = ft_calloc(count + 1, sizeof(char *));
	if (!ppx->cmd)
		error_occured(ERR_MEM, MSG_MEM, ppx);
	i = 0;
	while (i < count)
	{
		ppx->cmd[i] = extract_token(&cmd, &parser);
		if (!ppx->cmd[i])
			error_occured(ERR_MEM, MSG_MEM, ppx);
		i++;
	}
}
