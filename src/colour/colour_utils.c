/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colour_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/02 15:45:05 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/16 16:13:44 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// TODO add funcs here when norming get_colour file

/*	This Function calculates the base colour of an object.
 *		- So if the object has a pattern (Checkerboard, texture),
 *		  it will first calculate that pattern and use it as a base colour,
 *		  before it applies the 'Phong reflection model'.
 *		- If the object is plain (has no pattern),
 *		  it will return the colour of the object as the base colour.	
 */
t_colour	get_base_colour(t_objs *obj, t_colour_vars *colour)
{
	t_colour	base;

	if (obj->what_pattern == 1 && obj->type == E_SPHERE)
		base = get_sphere_checkerboard(colour->normal);
	else
		base = obj->colour;
	return (base);
}

/*	Calculate the reflection direction using 
 *	the incident ray direction and surface normal.
 */
t_vec3	ft_reflect(t_vec3 incident, t_vec3 normal)
{
	return (minus(incident, mult_vecdub(normal, 2
				* dot_product(incident, normal))));
}
