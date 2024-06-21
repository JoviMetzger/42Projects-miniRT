/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   do_calcs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/16 16:14:41 by smclacke      #+#    #+#                 */
/*   Updated: 2024/06/21 15:30:17 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// colour->light_dir = normalize(minus(colour->curr_light->place,
    //          colour->intersect_p));
    // shadow_ray.place = plus(colour->intersect_p, mult_vecdub(colour->normal,
    //          EPSILON));
    // shadow_ray.vector = colour->light_dir;
    // printf("inter_p = %f %f %f\n", inter_p.x, inter_p.y, inter_p.z);
    // printf("light_dir = %f %f %f\n", light_dir.x, light_dir.y, light_dir.z);
    // printf("place = %f %f %f\n", shadow_ray.place.x, shadow_ray.place.y, shadow_ray.place.z);

static t_ray	init_light_ray(t_data *data, int i)
{
	t_vec3  inter_p = plus(data->pix[i]->ray.place,
		mult_vecdub(data->pix[i]->ray.vector, data->pix[i]->hit_t));

	t_vec3  light_dir = normalize(minus(data->light[0]->place, inter_p));

	data->pix[i]->shadow_ray.place = data->light[0]->place;
	data->pix[i]->shadow_ray.vector = light_dir;

	return (data->pix[i]->shadow_ray);
}

bool   shadow_calc(t_data *data, t_ray ray, int i)
{
    bool		 in_shadow = false;
    int			 obj_i = 0;
    t_hit_data 	 hit_2;

	hit_2.closest_t = DBL_MAX;

    while (obj_i < data->objs_i)
    {
        if (intersect_sphere(&ray, data->objs[obj_i], &hit_2))
		{
			if (hit_2.closest_t == data->pix[i]->hit_t)
				in_shadow = true;
		}
        else if (intersect_cylinder(&ray, data->objs[obj_i], &hit_2))
		{
			if (hit_2.closest_t == data->pix[i]->hit_t)
				in_shadow = true;
		}
        else if (intersect_triangle(&ray, data->objs[obj_i], &hit_2))
		{
			if (hit_2.closest_t == data->pix[i]->hit_t)
				in_shadow = true;
		}
        else if (intersect_plane(&ray, data->objs[obj_i], &hit_2))
		{
			if (hit_2.closest_t == data->pix[i]->hit_t)
				in_shadow = true;
		}
        obj_i++;
    }
    // exit(0);
    if (in_shadow)
		return (true);
	return (false);
}

void	do_calcs(t_data *data)
{
	t_hit_data	hit;

	data->i = 0;
	while (data->i < data->total_pix)
	{
		data->ray = ft_create_ray(data, data->pix[data->i]->x,
				data->pix[data->i]->y);
		data->pix[data->i]->shadow_ray = init_light_ray(data, data->i);
		ft_calculate_colour(data, &hit, data->i);
		data->mouse.mou_y = data->pix[data->i]->y;
		data->mouse.mou_x = data->pix[data->i]->x;
		data->pix[data->i]->hit_t = hit.t;
		data->i++;
	}
	// data->i = 0;
	// while (data->i < data->total_pix)
	// {
	// 	if (data->pix[data->i]->hit_b == true)
	// 	{
	// 			data->pix[data->i]->colour = data->pix[data->i]->light;
	// 	}
	// 	data->i++;
	// }
}




//////////////////// trying to get shadow ray..


// static void get_ret(t_data *data, t_hit_data *hit, t_objs *obj, int i)
// {
//     if (hit->closest_t != DBL_MAX)
//     {
//         data->pix[data->i]->hit_t = hit->t;
//         data->pix[i]->hit_b = true;
//         data->pix[i]->colour = get_ambient(data, obj);
//         shadow_calc(data, i);
//         // data->pix[i]->light = get_light(data, data->ray, obj);
//     }
//     else
//         data->pix[i]->colour = data->pix[i]->black;
// }



// colour->light_dir = normalize(minus(colour->curr_light->place,
    //          colour->intersect_p));
    // shadow_ray.place = plus(colour->intersect_p, mult_vecdub(colour->normal,
    //          EPSILON));
    // shadow_ray.vector = colour->light_dir;
// void    shadow_calc(t_data *data, int i)
// {
//     t_hit_data  hit_2;
//     t_ray   shadow_ray;
//     t_vec3  inter_p = plus(data->pix[i]->ray.place,
//         mult_vecdub(data->pix[i]->ray.vector, data->pix[i]->hit_t));
//     // printf("shadow t = %f\n", data->pix[i]->hit_t);
//     t_vec3  light_dir = normalize(minus(data->light[0]->place, inter_p));
//     // shadow_ray.place = plus(inter_p, mult_vecdub(data->pix[i]->obj->normal, EPSILON));
//     shadow_ray.place = data->light[0]->place;
//     shadow_ray.vector = light_dir;
//     // printf("inter_p = %f %f %f\n", inter_p.x, inter_p.y, inter_p.z);
//     // printf("light_dir = %f %f %f\n", light_dir.x, light_dir.y, light_dir.z);
//     // printf("place = %f %f %f\n", shadow_ray.place.x, shadow_ray.place.y, shadow_ray.place.z);
//     bool in_shadow = false;
//     int obj_i = 0;
//     while (obj_i < data->objs_i)
//     {
//         if (intersect_sphere(&shadow_ray, data->objs[obj_i], &hit_2)
//             || intersect_cylinder(&shadow_ray, data->objs[obj_i], &hit_2)
//             || intersect_triangle(&shadow_ray, data->objs[obj_i], &hit_2)
//             || intersect_plane(&shadow_ray, data->objs[obj_i], &hit_2))
//             {
//                 // puts("intersect");
//                 // printf("shadow hit = %f\n", hit_2.t);
//                 in_shadow = true;
//                 break ;
//             }
//                 // return (true);
//         // else
//         //  return (false);
//         obj_i++;
//     }
//     // exit(0);
//     if (!in_shadow)
//     {
//         data->pix[i]->colour = get_light(data, data->ray, data->pix[i]->obj);
//     }
// }



// void    do_calcs(t_data *data)
// {
//     t_hit_data  hit;
//     data->i = 0;
//     while (data->i < data->total_pix)
//     {
//         data->ray = ft_create_ray(data, data->pix[data->i]->x,
//                 data->pix[data->i]->y);
//         ft_calculate_colour(data, &hit, data->i);
//         // data->pix[data->i]->hit_t = hit.t;
//         // shadow_calc(data, data->i);
//         data->mouse.mou_y = data->pix[data->i]->y;
//         data->mouse.mou_x = data->pix[data->i]->x;
//         // printf("og t = %f\n", hit.t);
//         // printf("og pix t = %f\n", data->pix[data->i]->hit_t);
//         // data->pix[data->i]->ray.place = data->ray.place;
//         // data->pix[data->i]->ray.vector = data->ray.vector;
//         data->i++;
//     }
//     // data->i = 0;
//     // while (data->i < data->total_pix)
//     // {
//     //  if (data->pix[data->i]->hit_b == true)
//     //  {
//     //      if (shadow_calc(data, data->i))
//     //      {
//     //          // puts("light?");
//     //          data->pix[data->i]->colour = data->pix[data->i]->light;
//     //      }
//     //      else
//     //          data->pix[data->i]->colour = data->pix[data->i]->ambient;
//     //  }
//     //  data->i++;
//     // }
// }
