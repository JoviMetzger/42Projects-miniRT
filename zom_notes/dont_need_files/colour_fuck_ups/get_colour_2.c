/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_colour.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/02 15:45:05 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/15 16:28:12 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// Calculation of the diffuse light
static void	diffuse_light(t_colour_vars *colour, t_pixel *pix)
{
	colour->diff_fact = dot_product(colour->normal, pix->light_ray.vector);
	// printf("diff = %f | col norm = %f %f %f\n", colour->diff_fact, colour->normal.x, colour->normal.y, colour->normal.z);
	// printf("pix vec = %f %f %f\n", pix->light->ray.vector.x, pix->light->ray.vector.y, pix->light->ray.vector.z);
	

	////////////////////////////////////////////////////////////
	// colour->diff_fact = dot_product(colour->normal, colour->light_dir);
	if (colour->diff_fact < 0.0)
		colour->diff_fact = 0.0;
	// printf("diff here = %f\n", colour->diff_fact);
	// printf("ratio = %f\n", colour->curr_light->ratio);
	// exit(0);
	colour->diffuse.r = colour->curr_light->ratio * colour->diff_fact
		* colour->curr_light->colour.r;
	colour->diffuse.g = colour->curr_light->ratio * colour->diff_fact
		* colour->curr_light->colour.g;
	colour->diffuse.b = colour->curr_light->ratio * colour->diff_fact
		* colour->curr_light->colour.b;
}

// Calculation of the specular light
static void	specular_light(t_colour_vars *colour, t_ray ray, t_pixel *pix)
{
	colour->view_dir = normalize(minus(ray.place, colour->intersect_p));
	colour->ref_dir = normalize(ft_reflect(pix->light_ray.vector, colour->normal));
	colour->spec_fact = pow(dot_product(colour->ref_dir, colour->view_dir),
			colour->spec_power);
	if (colour->spec_fact < 0.0)
		colour->spec_fact = 0.0;
	colour->specular.r = colour->spec_intensity * colour->spec_fact
		* colour->curr_light->colour.r;
	colour->specular.g = colour->spec_intensity * colour->spec_fact
		* colour->curr_light->colour.g;
	colour->specular.b = colour->spec_intensity * colour->spec_fact
		* colour->curr_light->colour.b;
}

/*	This function add the light if no shadow (no intersection with object)	    
 *		- Calculate diffuse light contribution.
 *		- Calculate specular light contribution.
 *		- Accumulate light contributions. 
 *		  (newColour += diffuse_colour * base_colour / 255 + specular_colour)
 */
void	add_light(t_data *data, t_colour_vars *colour, t_ray ray, int i)
{
	diffuse_light(colour, data->pix[i]);
	specular_light(colour, ray, data->pix[i]);
	colour->result.r += colour->diffuse.r * colour->base.r / 255
		+ colour->specular.r;
	colour->result.g += colour->diffuse.g * colour->base.g / 255
		+ colour->specular.g;
	colour->result.b += colour->diffuse.b * colour->base.b / 255
		+ colour->specular.b;
}

/*	STEP 3. Compute a color for the closest intersection point.
 *
 *	This function uses the 'Phong reflection model' for each object.
 *	Including multiple light and creating shadows.
 *		- Initializing data->vars variables.
 *		- Initializing the base colour of the object.
 *		- Initializing the result of the colour with ambient light contribution.
 *		  (colour = ambient * base / 255)
 *		- Creating a light_direction.
 *		- Clamp final values to [0, 255]. 
 *		  This ensurs that the value is not less than 0 and not bigger than 255. 
 *		  So basiclly controls the overflow/underflow of RGB colour range.
 */
t_colour	get_colour(t_data *data, t_hit_data *obj_hit, t_objs *obj)
{
	int				j;

	j = -1;
	data->vars->intersect_p = plus(data->ray.place, mult_vecdub(data->ray.vector, obj_hit->t));
	data->vars->normal = obj->normal;
	data->vars->base = get_base_colour(obj, data->vars);
	data->vars->result.r = data->vars->ambient.r * data->vars->base.r / 255;
	data->vars->result.g = data->vars->ambient.g * data->vars->base.g / 255;
	data->vars->result.b = data->vars->ambient.b * data->vars->base.b / 255;
	// data->vars->curr_light = data->light[0]; // fix later
	// data->vars->light_dir = normalize(minus(data->vars->curr_light->place,
	// 	data->vars->intersect_p));
	data->vars->result.r = fmin(255, fmax(0, data->vars->result.r));
	data->vars->result.g = fmin(255, fmax(0, data->vars->result.g));
	data->vars->result.b = fmin(255, fmax(0, data->vars->result.b));
	return (data->vars->result);
}
