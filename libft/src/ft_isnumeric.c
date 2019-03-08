/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semyonkomissarov <semyonkomissarov@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 19:03:32 by semyonkomis       #+#    #+#             */
/*   Updated: 2019/03/02 19:07:02 by semyonkomis      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isnumeric(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}
