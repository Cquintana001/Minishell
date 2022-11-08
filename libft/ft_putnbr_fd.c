/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 09:54:29 by amarzana          #+#    #+#             */
/*   Updated: 2022/04/16 11:25:09 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	num;
	long	lnb;

	lnb = n;
	if (lnb < 0)
	{
		write(fd, "-", 1);
		lnb = -lnb;
	}
	if (lnb / 10)
		ft_putnbr_fd(lnb / 10, fd);
	num = lnb % 10 + '0';
	write(fd, &num, 1);
}
