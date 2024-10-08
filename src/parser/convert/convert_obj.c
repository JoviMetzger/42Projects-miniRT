/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_obj.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/12 23:42:49 by smclacke      #+#    #+#                 */
/*   Updated: 2024/08/17 17:59:15 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/parser.h"

static int	tri_coords(char **elem_str, t_data *data)
{
	data->objs[data->objs_i]->point_flag = 0;
	if (!is_coord(elem_str[1], 0, 0))
		return (par_err("invalid: Triangle: coordinate"));
	if (!convert_coord(data, elem_str[1]))
		return (par_err("invalid: Triangle: coordinate"));
	data->objs[data->objs_i]->point_flag = 1;
	if (!is_coord(elem_str[2], 0, 0))
		return (par_err("invalid: Triangle: coordinate"));
	if (!convert_coord(data, elem_str[2]))
		return (par_err("invalid: Triangle: coordinate"));
	data->objs[data->objs_i]->point_flag = 2;
	if (!is_coord(elem_str[3], 0, 0))
		return (par_err("invalid: Triangle: coordinate"));
	if (!convert_coord(data, elem_str[3]))
		return (par_err("invalid: Triangle: coordinate"));
	return (1);
}

// /**
//  * #Identifier   #Coordinates: point1  point2  point3    #R,G,B
// */
int	sort_tr(char **elem_str, t_data *data)
{
	if (!tri_coords(elem_str, data))
		return (0);
	if (!convert_rgb(data, elem_str[4]))
		return (par_err("invalid: Triangle: RGB | [0-255]"));
	vec_obj(data, 0, 0, 1);
	data->objs[data->objs_i]->normal
		= data->objs[data->objs_i]->vector;
	data->objs[data->objs_i]->edge[0]
		= minus(data->objs[data->objs_i]->point[1],
			data->objs[data->objs_i]->point[0]);
	data->objs[data->objs_i]->edge[1]
		= minus(data->objs[data->objs_i]->point[2],
			data->objs[data->objs_i]->point[0]);
	return (1);
}

// /**
//  * #Identifier     #Coordinates        #3D vector      #R,G,B
//  * pl              0.0,0.0,-10.0       0.0,1.0,0.0     0,0,225
// */
int	sort_pl(char **elem_str, t_data *data)
{
	if (!is_coord(elem_str[1], 0, 0))
		return (par_err("invalid: Plane: coordinate"));
	if (!convert_coord(data, elem_str[1]))
		return (par_err("invalid: Plane: coordinate"));
	if (!is_coord(elem_str[2], 0, 0))
		return (par_err("invalid: Plane: 3D vector"));
	if (!convert_vector(data, elem_str[2]))
		return (par_err("invalid: Plane: 3D vector"));
	if (!is_rgb(elem_str[3], 0, 0))
		return (par_err("invalid: Plane: RGB | [0-255]"));
	if (!convert_rgb(data, elem_str[3]))
		return (par_err("invalid: Plane: RGB | [0-255]"));
	data->objs[data->objs_i]->normal = data->objs[data->objs_i]->vector;
	return (1);
}

/**
 * #Identifier     #Coordinates        #Diameter       #R,G,B
 * sp              0.0,0.0,20.6        12.6            10,0,255
*/
int	sort_sp(char **elem_str, t_data *data)
{
	if (!is_coord(elem_str[1], 0, 0))
		return (par_err("invalid: Sphere: coordinate"));
	if (!convert_coord(data, elem_str[1]))
		return (par_err("invalid: Sphere: coordinate"));
	if (!convert_double(data, elem_str[2], 1))
		return (par_err("invalid: Sphere: diameter"));
	if (!is_rgb(elem_str[3], 0, 0))
		return (par_err("invalid: Sphere: RGB | [0-255]"));
	if (!convert_rgb(data, elem_str[3]))
		return (par_err("invalid: Sphere: RGB | [0-255]"));
	return (1);
}

// /**
//  * #Identifier  #Coordinates     #3D vector    #Diameter   #Height  #R,G,B
//  * cy           50.0,0.0,20.6    0.0,0.0,1.0   14.2        21.42    10,0,255
// */
int	sort_cy(char **elem_str, t_data *data)
{
	if (!is_coord(elem_str[1], 0, 0))
		return (par_err("invalid: Cylinder: coordinate"));
	if (!convert_coord(data, elem_str[1]))
		return (par_err("invalid: Cylinder: coordinate"));
	if (!is_coord(elem_str[2], 0, 0))
		return (par_err("invalid: Cylinder: 3D vector"));
	if (!convert_vector(data, elem_str[2]))
		return (par_err("invalid: Cylinder: 3D vector"));
	if (!convert_double(data, elem_str[3], 1))
		return (par_err("invalid: Cylinder: diameter"));
	if (!convert_double(data, elem_str[4], 2))
		return (par_err("invalid: Cylinder: height"));
	if (!is_rgb(elem_str[5], 0, 0))
		return (par_err("invalid: Cylinder: RGB | [0-255]"));
	if (!convert_rgb(data, elem_str[5]))
		return (par_err("invalid: Cylinder: RGB | [0-255]"));
	cyl_cals(data);
	data->objs[data->objs_i]->normal
		= data->objs[data->objs_i]->vector;
	return (1);
}
