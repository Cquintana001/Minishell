/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:07:07 by amarzana          #+#    #+#             */
/*   Updated: 2022/04/16 11:37:32 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (srclen);
	if (dstsize < dstlen)
		return (srclen + dstsize);
	else
	{
		while (src[i] && (dstlen + i) < dstsize)
		{
			dst[dstlen + i] = src[i];
			i++;
		}
		if ((dstlen + i) == dstsize && dstlen < dstsize)
			dst[dstlen + i - 1] = '\0';
		else
			dst[dstlen + i] = '\0';
	}
	return (dstlen + srclen);
}
