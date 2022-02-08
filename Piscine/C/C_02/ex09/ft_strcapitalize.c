/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 20:03:59 by gneri             #+#    #+#             */
/*   Updated: 2020/11/04 11:08:30 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcapitalize(char *str)
{
	int i;
	int cont;

	i = 0;
	cont = 1;
	while (str[i])
	{
		if ((str[i] >= 'A' && str[i] <= 'Z') ||
				(str[i] >= 'a' && str[i] <= 'z') ||
				(str[i] >= '0' && str[i] <= '9'))
		{
			if (cont && (str[i] >= 'a' && str[i] <= 'z'))
				str[i] = str[i] - 32;
			else if (cont == 0 && (str[i] >= 'A' && str[i] <= 'Z'))
				str[i] = str[i] + 32;
			cont = 0;
		}
		else
			cont = 1;
		i++;
	}
	return (str);
}
