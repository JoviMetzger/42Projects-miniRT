/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_funcs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 14:57:01 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/30 15:18:26 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/parser.h"

int	is_valid(int c)
{
	if (!is_dash(c) && !is_num(c) && !is_dot(c)
		&& !ft_isspace(c) && !is_comma(c))
		return (0);
	return (1);
}

int	is_num(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\0')
		return (c);
	return (0);
}

int	is_comma(int c)
{
	return (c == ',');
}

int	is_dot(int c)
{
	return (c == '.');
}
