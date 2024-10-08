/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_colour.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:21 by smclacke      #+#    #+#                 */
/*   Updated: 2024/08/17 18:23:24 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/*	This function checks which object is closer to the camera, 
 *	other wise objects will overlap and won't be dispalyed realistic.
 *		- Calculates the colour of the nearest object.
 *		- If no intersection is found, colour is set to black.
 */
static void	get_ret(t_data *data, t_hit_data *hit, t_objs *obj, int i)
{
	data->pix[i]->obj = obj;
	if (hit->closest_t != DBL_MAX)
	{
		data->pix[i]->hit_b = true;
		data->pix[i]->hit_t = obj->obj_t;
		data->pix[i]->obj->obj_t = obj->obj_t;
		data->pix[i]->ambient = get_ambient(data, obj);
		data->pix[i]->light = get_light(data, data->ray, obj);
		data->pix[i]->colour = data->pix[i]->light;
	}
	else
		data->pix[i]->colour = data->pix[i]->black;
}

/*	This function applies necessary information to the object.
 *		- data->mouse.mouse_map[data->mouse.mou_y][data->mouse.mou_x] = i; 
 *		  is for the mouse_map, so that we can select object.
 */
static t_objs	*update_obj(t_data *data, int i)
{
	data->objs[i]->i_am = i;
	data->mouse.mouse_map[data->mouse.mou_y][data->mouse.mou_x] = i;
	return (data->objs[i]);
}

/*	STEP 2. Determine which objects the ray intersects
 *	
 *	This function applies colour to each hit object.
 *		- It loops through all the objects and checks 
 *		  if it has an intersect point (if a obj gets hit).
 *			- If it does have a hit point it executs update_obj();
 *			  (Becuse the function was too long)
 */
void	ft_calculate_colour(t_data *data, t_hit_data *hit, int pix_index)
{
	int		i;
	t_objs	*tmp_obj;

	i = 0;
	hit->closest_t = DBL_MAX;
	while (i < data->objs_i)
	{
		if (data->objs[i]->type == E_SPHERE
			&& sphere(&data->ray, data->objs[i], hit))
			tmp_obj = update_obj(data, i);
		else if (data->objs[i]->type == E_PLANE
			&& plane(&data->ray, data->objs[i], hit))
			tmp_obj = update_obj(data, i);
		else if (data->objs[i]->type == E_CYLINDER
			&& cylinder(&data->ray, data->objs[i], hit))
			tmp_obj = update_obj(data, i);
		else if (data->objs[i]->type == E_TRIANGLE
			&& triangle(&data->ray, data->objs[i], hit))
			tmp_obj = update_obj(data, i);
		i++;
	}
	get_ret(data, hit, tmp_obj, pix_index);
}
