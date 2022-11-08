/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzana <amarzana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 10:54:42 by amarzana          #+#    #+#             */
/*   Updated: 2022/04/16 11:12:39 by amarzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	sign;
	int	i;
	int	num;

	sign = 1;
	i = 0;
	num = 0;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}	
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			break ;
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * sign);
}
