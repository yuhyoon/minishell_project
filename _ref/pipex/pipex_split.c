/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 10:36:35 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/07/26 13:01:00 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex_quote(char *str_dup)
{
	int		len;
	int		i;

	len = ft_strlen(str_dup);
	i = 0;
	while (i < len && str_dup[i] != '\0')
	{
		if (ft_strspn(str_dup + i, "\'\""))
		{
			str_dup[i] = '\0';
			i++;
			i += ft_strcspn(str_dup + i, "\'\"");
			str_dup[i] = '\0';
		}
		if (str_dup[i] == ' ')
			str_dup[i] = '\0';
		i++;
	}
	return (i);
}

int	pipex_get_size(char *s, int len)
{
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (i < len)
	{
		if (s[i] != '\0')
		{
			cnt++;
			while (i < len && s[i] != '\0')
				i++;
		}
		if (i >= len)
			break ;
		i++;
	}
	return (cnt);
}

char	**pipex_splited(char *s_dup, int w, char **abs)
{
	int		cnt;
	int		index_jump;

	cnt = 0;
	while (cnt < w)
	{
		while (*s_dup == '\0')
			s_dup++;
		abs[cnt] = ft_strdup(s_dup);
		index_jump = ft_strlen(abs[cnt]);
		s_dup = s_dup + index_jump;
		cnt++;
	}
	abs[cnt] = NULL;
	return (abs);
}

char	**pipex_split(char *s)
{
	int		s_len;
	char	*s_dup;
	int		w;
	char	**abs;

	s_len = ft_strlen(s);
	s_dup = ft_strdup(s);
	if (s_len < pipex_quote(s_dup))
	{
		free(s_dup);
		s_dup = NULL;
		return (NULL);
	}
	w = pipex_get_size(s_dup, s_len);
	abs = (char **)malloc(sizeof(char *) * (w + 1));
	if (!abs)
		return (0);
	pipex_splited(s_dup, w, abs);
	free(s_dup);
	return (abs);
}
