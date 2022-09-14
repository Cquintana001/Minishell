/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:54:05 by amarzana          #+#    #+#             */
/*   Updated: 2022/04/16 11:39:49 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*str;
	unsigned int	len;
	unsigned char	ch;

	ch = (unsigned char)c;
	str = (char *) s;
	len = ft_strlen(str);
	while (len)
	{
		if (str[len] == ch)
			return (&str[len]);
		len--;
	}
	if (str[len] == ch)
		return (&str[len]);
	return (0);
}
