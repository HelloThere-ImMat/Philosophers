/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdorr <mdorr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:17:08 by mdorr             #+#    #+#             */
/*   Updated: 2023/07/10 14:57:12 by mdorr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/philo.h"

static bool	is_inbounds(long nb, int c)
{
	return (nb * 10 < LONG_MAX - c);
}

static int	skip_and_check_sign(char **str)
{
	while (**str == ASCII_SPACE || **str == ASCII_TAB)
		++*str;
	if (**str == '-')
	{
		printf("%s %s\n", NEGATIVE_ARG, *str);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	check_nbr(char *str)
{
	long	nb;
	char	*arg;

	nb = 0;
	arg = str;
	if (skip_and_check_sign(&str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (ft_isdigit(*str) != 0)
	{
		if (is_inbounds(nb, *str - ASCII_ZERO) == false)
		{
			printf("%s %s\n", OUT_OF_BOUNDS_ARG, arg);
			return (EXIT_FAILURE);
		}
		nb = nb * 10 + (*str - ASCII_ZERO);
		str++;
	}
	if (*str != ASCII_NULL)
	{
		printf("%s %s\n", NON_DIGIT_ARG, str);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	check_arg_values(int argc, char **argv)
{
	size_t	i;
	int		ret_val;

	i = 1;
	ret_val = 0;
	while (i < (size_t)argc)
	{
		ret_val += check_nbr(argv[i]);
		i++;
	}
	return (ret_val);
}

int	check_arg(int argc, char **argv)
{
	int	ret_val;

	ret_val = EXIT_FAILURE;
	if (argc < ARG_MIN_NBR)
		printf("%s, %s\n", NOT_ENOUGH_ARGS, ARG_INSTRUCTION);
	else if (argc > ARG_MAX_NBR)
		printf("%s, %s\n", TOO_MANY_ARGS, ARG_INSTRUCTION);
	else if (check_arg_values(argc, argv) == EXIT_SUCCESS)
		ret_val = EXIT_SUCCESS;
	return (ret_val);
}
