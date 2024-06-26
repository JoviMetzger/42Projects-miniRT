/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_coord.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 20:43:45 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/13 13:41:13 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../header/parser.h"

void	coord_light(t_data *data, double x, double y, double z)
{
	data->light[data->light_i]->place.x = x;
	data->light[data->light_i]->place.y = y;
	data->light[data->light_i]->place.z = z;
}

void	coord_camera(t_data *data, double x, double y, double z)
{
	data->camera.place.x = x;
	data->camera.place.y = y;
	data->camera.place.z = z;
}

void	coord_obj(t_data *data, double x, double y, double z)
{
	data->objs[data->objs_i]->center.x = x;
	data->objs[data->objs_i]->center.y = y;
	data->objs[data->objs_i]->center.z = z;
}
