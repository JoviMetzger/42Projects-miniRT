/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   triangle.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/08 18:00:14 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/21 18:37:04 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// Triangle

// Definition:
//  C is a vertex of our choice
//  V is a normal of the plane on which the triangle lies
//  V1 is a vector from vertex C to vertex C1 (V1=C1-C)
//  V2 is a vector from vertex C to vertex C2 (V2=C2-C)

// To hit a triangle we first hit a plane on which it lies, in the same manner as we hit a regular plane. 
// Then the two other triangle vertices give us a point to calculate two coefficients that tell us where 
// exactly we are on the triangle.

//    t = - X|V / D|V
//    P = C + V1*p + V2*q
// Solution:

//    P - C = V1*p + V2*q
//    [ Px-Cx ] = [ V1.x V2.x ] * [ p ]
//    [ Py-Cy ]   [ V1.y V2.y ]   [ q ]
// To calculate p and q we don't need the whole V1 and V2 vectors, we just need their x and y values 
// (or z are good as well). We yet have to calculate an inverse of the matrix in the above equation, 
// but this is a precalculation step.
// To determine whether the point P we hit actually lies within the triangle, we just have to ensure 
// that the scalar values p, q and their sum are within range [0,1].

// If we hit the triangle, we can use the p and q values to calculate (smooth) normals and to calculate 
// texture coordinates. Usually triangles build up bigger meshes, so we don't have to worry about flipping 
// the surface normal if we hit it from the back (like in case of a plane).

// A triangle for raytracing actually takes a little bit more space than for a regular scanline rendering 
// algorithm (e.g. OpenGL). That's because we have one more vector (V) and we have to keep original V1 and 
// V2 for rotations and scaling from frame to frame. We also have to calculate the inverse matrix per frame, 
// what takes additional time. What's more, we have to adapt a special hit test scheme for meshes, so that we 
// don't waste cycles on testing all triangles in a mesh. Perhaps a bounding volume hierarchy is a solution. 
// Nevertheless every additional thing takes up memory, and that's why triangles are not the most efficient 
// objects for raytracing, especially in complex scenes.

// does hit
bool		intersect_triangle(t_ray *ray, t_objs *tri, t_hit_data *hit_data)
{
	t_vec3	edge1;
	t_vec3	edge2;
	t_vec3	hit;
	float	dir;

	edge1 = minus(tri->point[1], tri->point[0]);
	edge2 = minus(tri->point[2], tri->point[0]);

	hit = cross_product(ray->vector, edge2);
	dir = dot_product(edge1, hit);

	
	if (dir > -EPSILON && dir < EPSILON)
		return (false);

	// f
	hit_data->a = 1.0 / dir;

	// s
	t_vec3 o_c = minus(ray->place, tri->point[0]);
	

	// check the scalar values (u q || b c) are in range 0-1
	// u
	hit_data->b = dot_product(o_c, hit);
	hit_data->b = hit_data->a * hit_data->b;
	if (hit_data->b < 0.0 || hit_data->b > 1.0)
		return (false);

	//q	
	t_vec3 c_c = cross_product(o_c, edge1); 

	// v
	hit_data->c = dot_product(ray->vector, c_c);
	hit_data->c = hit_data->a * hit_data->c;
	if (hit_data->c < 0.0 || hit_data->b + hit_data->c > 1.0)
		return (false);


	hit_data->t = dot_product(edge2, c_c);
	hit_data->t = hit_data->a * hit_data->t;
	if (hit_data->t < EPSILON)
		return (false);
	return (check_closest(hit_data));

}

// Clamp final values to [0, 255]
t_colour	get_tr_colour(t_data *data, t_hit_data *hit, t_ray ray, t_objs *obj)
{
	t_colour		result;
	t_colour_vars	vars;
	
	ft_bzero(&vars, sizeof(t_colour_vars));
	vars.inter_point = plus(ray.place, mult_vecdub(ray.vector, hit->t));
	get_colour(data, &vars, ray);

	// need for triangle
	// vars.normal = 
	
	vars.final_red = fmin(fmax(vars.final_red, obj->colour.r), 255);
	vars.final_green = fmin(fmax(vars.final_green, obj->colour.g), 255);
	vars.final_blue = fmin(fmax(vars.final_blue, obj->colour.b), 255);
	result.r = vars.final_red;
	result.g = vars.final_green;
	result.b = vars.final_blue;
	return (result);
}
