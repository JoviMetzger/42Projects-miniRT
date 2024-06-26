/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 15:30:59 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/22 21:59:31 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parser.h"

int	par_err(char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(msg, 2);
	return (0);
}

void	free_arr_error(char *msg, char **arr)
{
	free_array(arr);
	if (msg != NULL)
		error_msg(msg);
	else
		exit(EXIT_FAILURE);
}

void	free_close_parse_error(char *msg, char **ar, char *line, int file)
{
	close_protect(file);
	free_array(ar);
	free(line);
	error_msg(msg);
}

void	parse_error(char *msg, int file)
{
	close_protect(file);
	error_msg(msg);
}

void	error_msg(char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}
