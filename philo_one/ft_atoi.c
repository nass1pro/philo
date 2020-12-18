/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahaddac <nahaddac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 11:45:20 by nahaddac          #+#    #+#             */
/*   Updated: 2020/12/18 10:49:35 by nahaddac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int		ft_fneg(const char *str)
{
	int			i;
	int			f;
	int			n;

	n = 1;
	i = 0;
	f = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r' ||
			str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	while (str[i] == '-' || str[i] == '+')
		i++;
	return (i);
}

static int		ft_neg(const char *str)
{
	int			i;
	int			f;
	int			n;

	n = 1;
	i = 0;
	f = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r' ||
			str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-' || str[i] == '+')
		{
			f += 1;
			if (f > 1)
				return (0);
			if (str[i] == '-')
				n = -1;
		}
		i++;
	}
	return (n);
}

int				ft_atoi(const char *str)
{
	int			i;
	int			n;
	long int	nb;

	i = 0;
	n = ft_neg(str);
	nb = 0;
	if (n == 0)
		return (0);
	if (ft_fneg(str) < 0)
		return (0);
	i = ft_fneg(str);
	while (str[i] >= 48 && str[i] <= 57)
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
		if (nb * n > 2147483647)
			return (-1);
		if (nb * n < -2147483648)
			return (0);
	}
	return (nb * n);
}
