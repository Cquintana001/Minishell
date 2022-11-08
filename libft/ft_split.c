/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:21:43 by amarzana          #+#    #+#             */
/*   Updated: 2022/04/16 11:31:10 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_coincidences(char const *s, char c)
{
	int	coin;
	int	i;

	i = 0;
	coin = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			coin++;
		while (s[i] != c && s[i])
		i++;
	}
	return (coin);
}

char	**ft_split_job(char const *s, char c)
{
	int		len;
	int		i;
	int		start;
	int		coin;
	char	**str;

	coin = 0;
	i = -1;
	start = -1;
	len = ft_strlen(s);
	str = (char **) malloc(sizeof(char *) * (ft_coincidences(s, c) + 1));
	if (str == NULL || sizeof(str) == 0)
		return (NULL);
	while (++i <= len)
	{
		if (s[i] != c && start < 0)
			start = i;
		else if (start >= 0 && (s[i] == c || i == len))
		{
			str[coin++] = ft_substr(s, start, i - start);
			start = -1;
		}
	}
	str[coin] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	if (!s)
		return (NULL);
	return (ft_split_job(s, c));
}
