/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 09:35:29 by amarzana          #+#    #+#             */
/*   Updated: 2022/04/16 11:18:37 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_fillstr(char *str, long num, int neg, int len)
{
	if (num == 0)
		str[0] = '0';
	if (neg)
		str[0] = '-';
	str[len-- + neg] = '\0';
	while (num)
	{
		str[len + neg] = num % 10 + '0';
		len--;
		num = num / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	long	num;
	int		len;
	int		neg;
	char	*str;

	num = n;
	neg = 0;
	len = 0;
	if (num < 0)
	{
		neg = 1;
		num = -num;
	}
	while (n)
	{
		n = n / 10;
		len++;
	}
	if (num == 0)
		len = 1;
	str = (char *)malloc(sizeof(char) * (len + neg + 1));
	if (str == NULL)
		return (NULL);
	return (ft_fillstr(str, num, neg, len));
}
