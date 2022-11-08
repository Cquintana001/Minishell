/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokens_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caquinta <caquinta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:12:27 by caquinta          #+#    #+#             */
/*   Updated: 2022/10/29 11:17:26 by caquinta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_assign(int check, char a, char **quote, char *c)
{
	if (a != **quote && check == 0)
	{
		check = 1;
		*c = **quote;
		(*quote)++;
	}
	else if (a != **quote && check == 1)
	{
		check = 0;
		(*quote)++;
	}
	return (check);
}

void	count_assign(char **aux, char **quote, int *x, char a)
{
	**aux = a;
	(*quote)++;
	(*aux)++;
	(*x)++;
}

int	check_char(char *str)
{
	if (*str == *(str + 1))
		return (2);
	return (1);
}
