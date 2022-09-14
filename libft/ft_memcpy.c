/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:49:44 by amarzana          #+#    #+#             */
/*   Updated: 2022/04/16 11:23:06 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (src || dst)
	{
		while (i < n)
		{
			((char *)dst)[i] = ((const char *)src)[i];
			i++;
		}
		return (dst);
	}
	return (NULL);
}
