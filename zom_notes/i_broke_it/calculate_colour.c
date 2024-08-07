/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_colour.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:21 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/22 14:29:17 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/**
 * 	was attempting this for textures with planes but ... ya know
 * 
* 		// if (data->objs[i]->texture != NULL)
		// {
		// 	data->image = mlx_texture_to_image(data->mlx, data->objs[i]->texture);
		// 	// convert into colour some how...
		// 	if (!data->image)
		// 		return (ft_convert_rgb(0, 0, 0));
		// 	else
		// 		exit(EXIT_SUCCESS);
		// }
		// else
 * 
 */
// t_colour	texture_colour(t_data *data, t_objs *object)
// {
	// data->objs[data->objs_i]->text_img = mlx_texture_to_image(data->mlx, texture);
	// if (!data->objs[data->objs_i]->text_img)
	// 	return (printf("ret 2\n"), 0);
// }

// Calculate the reflection direction using the incident ray direction and surface normal
// Reflection direction = Incident direction - 2 * (Incident direction . Normal) * Normal
t_vec3	ft_reflect(t_vec3 incident, t_vec3 normal)
{
	return (minus(incident, mult_vecdub(normal, 2
			* dot_product(incident, normal))));
}

int32_t	ft_convert_rgb(int32_t r, int32_t g, int32_t b)
{
	int32_t	a;

	a = 0xFF;
	return (b << 8 | g << 16 | r << 24 | a);
}

static uint32_t	get_ret(t_hit_data *hit_data, t_colour colour)
{
	if (hit_data->closest_t != DBL_MAX)
		return (ft_convert_rgb(colour.r, colour.g, colour.b));
	else
		return (ft_convert_rgb(0, 0, 0)); // No intersection found, return black
}

/** lighting: 
 *	(https://learnopengl.com/Advanced-Lighting/Advanced-Lighting)
 *	(https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model)
 *	(https://en.wikipedia.org/wiki/Phong_reflection_model)
 *
 * 		@todo texture, colour, image... heh?
 */
uint32_t	ft_calculate_colour(t_data *data, t_hit_data *hit_data, t_ray ray)
{
	t_colour	colour;
	int			i;

	i = 0;
	hit_data->closest_t = DBL_MAX;
	while (i < data->objs_i)
	{
		if (data->objs[i]->type == E_PLANE)
		{
			if (intersect_plane(&ray, data->objs[i], hit_data))
				colour = get_old_colour(data, hit_data, ray, data->objs[i]);
		}
		// if (data->objs[i]->type == E_SPHERE)
		// {
		// 	if (intersect_sphere(&ray, data->objs[i], hit_data))
		// 		colour = get_old_colour(data, hit_data, ray, data->objs[i]);
		// 		// colour = get_sp_colour(data, hit_data, ray, data->objs[i]);
		// }
		// else if (data->objs[i]->type == E_CYLINDER)
		// {
		// 	if (intersect_cylinder(&ray, data->objs[i], hit_data))
		// 		colour = get_cy_colour(data, hit_data, ray, data->objs[i]);
		// }
		// else if (data->objs[i]->type == E_TRIANGLE)
		// {
		// 	if (intersect_triangle(&ray, data->objs[i], hit_data))
		// 		colour = get_tr_colour(data, hit_data, ray, data->objs[i]);
		// }
		i++;
	}
	return (get_ret(hit_data, colour));
}
