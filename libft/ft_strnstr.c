/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 10:11:38 by amarzana          #+#    #+#             */
/*   Updated: 2022/04/16 11:39:12 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	in;
	size_t	ih;

	ih = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[ih] && ih < len)
	{
		in = 0;
		while (haystack[ih + in] == needle[in] && (in + ih) < len)
		{
			if (needle[in + 1] == '\0')
				return ((char *)&haystack[ih]);
			in++;
		}
		ih++;
	}
	return (0);
}
