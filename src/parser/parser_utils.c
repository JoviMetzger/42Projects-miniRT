/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 15:20:47 by smclacke      #+#    #+#                 */
/*   Updated: 2024/08/17 18:15:50 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parser.h"

t_type	get_type(char *str)
{
	if (check_capital(str, 'A') == 1)
		return (E_AMBIENT);
	if (check_capital(str, 'L') == 1)
		return (E_LIGHT);
	if (check_capital(str, 'C') == 1)
		return (E_CAMERA);
	if (check_pl(str) == 1)
		return (E_PLANE);
	if (check_sp(str) == 1)
		return (E_SPHERE);
	if (check_cy(str) == 1)
		return (E_CYLINDER);
	if (check_tr(str) == 1)
		return (E_TRIANGLE);
	if (ft_strcmp(str, " ") == 0 || is_space(str))
		return (E_SPACE);
	if (hash_str(str))
		return (E_HASH);
	return (0);
}

void	*map_malloc(size_t size)
{
	void	*alloc;

	alloc = malloc(size);
	if (alloc == NULL)
		error_msg("malloc failure");
	return (alloc);
}

char	**rt_malloc(char **arr, int size, int file)
{
	arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!arr)
		parse_error("malloc failure", file);
	return (arr);
}

t_objs	**obj_malloc(t_data *data, char **arr, int size)
{
	data->objs_i = 0;
	data->objs = (t_objs **)malloc(sizeof(t_objs *) * (size + 1));
	if (!data->objs)
		free_arr_error("parser error", arr);
	return (data->objs);
}

t_objs	*object_malloc(t_data *data, char **arr)
{
	data->objs[data->objs_i] = (t_objs *)malloc(sizeof(t_objs));
	if (!data->objs[data->objs_i])
	{
		free_objects(data);
		free_arr_error("parser error", arr);
	}
	ft_bzero(data->objs[data->objs_i], sizeof(t_objs));
	return (data->objs[data->objs_i]);
}
