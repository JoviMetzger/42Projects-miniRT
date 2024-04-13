/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pos_tri.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/13 17:57:51 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/13 17:58:09 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// can of triangle heheh
static bool	intersect_cylinder(t_ray *ray, t_objs *cylinder, t_obj_data *obj_data)
{
	t_vec3	ray_og = ray->place;
	t_vec3	ray_dir = ray->vector;
	double	radius = cylinder->diameter / 2;
	double	height_half = cylinder->height / 2;

	t_vec3	oc = minus(ray_og, cylinder->center);
	// t_vec3	oc = minus(cyl_dir, cyl_pos);



	// calculation of coefficients for quadratic equation
// ------------- og almost working ------------/
	// obj_data->a = dot_product(ray_dir, ray_dir) - pow(dot_product(ray_dir, cylinder->vector), 2);
	// obj_data->b = 2.0 * dot_product(oc, cylinder->vector) - dot_product(oc, ray_dir) * dot_product(ray_dir, cylinder->vector);
	// obj_data->c = dot_product(cross_product(oc, cylinder->vector), cross_product(oc, cylinder->vector)) - (radius * radius);
// ------------- og almost working ------------/

/**
 *bool	cylinder_intersect(t_cylinder *cy, t_ray *ray, t_hit *inter)
{
	double		t;
	t_vec3		co;
	t_equation	equation;

	equation.t1 = -1;
	equation.t2 = -1;
	co = vec3_sub(ray->origin, cy->cap1);
	equation.a = vec3_dot(ray->direction, ray->direction) - \
		pow(vec3_dot(ray->direction, cy->normal), 2);
	equation.b = 2 * (vec3_dot(ray->direction, co) - \
		(vec3_dot(ray->direction, cy->normal) * vec3_dot(co, cy->normal)));
	equation.c = vec3_dot(co, co) - pow(vec3_dot(co, cy->normal), 2) - \
		pow(cy->radius, 2);
	solve(&equation);
	if (equation.t1 <= 0 && equation.t2 <= 0)
		return (false);
	t = verify_intersections(cy, ray, &equation, inter);
	if (t > 0.0f)
	{
		inter->t = t;
		inter->color = cy->color;
		return (true);
	}
	return (false);
}
 * 
 */
	// ------------- test 2 ------------/
	obj_data->a = dot_product(ray_dir, ray_dir) - pow(dot_product(ray_dir, cylinder->vector), 2); // cyl->normal
	obj_data->b = 2.0 * (dot_product(ray_dir, oc) - (dot_product(ray_dir, cylinder->vector) * dot_product(oc, cylinder->vector)));
	obj_data->c = dot_product(oc, oc) - pow(dot_product(oc, cylinder->vector), 2) - radius * radius; // pow(radius, 2);
	// ------------- test 2 ------------/


	// discriminant, solve the quadratic equation
	obj_data->d = obj_data->b * obj_data->b - 4 * obj_data->a * obj_data->c;


	// check for intersection
	if (obj_data->d < 0)
		return (false); // no intersection

	// calcuate roots of quadratic equation
	obj_data->root1 = (-obj_data->b - sqrt(obj_data->d)) / (2.0 * obj_data->a);
	obj_data->root2 = (-obj_data->b + sqrt(obj_data->d)) / (2.0 * obj_data->a);


	//check if intersection point is within the cpaped ends of the cylinder
	//cylinder formulia = ray_ogirin (Y) + t * ray_direction (Y) 
	double t1 = ray_og.y + obj_data->root1 * ray_dir.y;
	double t2 = ray_og.y + obj_data->root2 * ray_dir.y;
	
	// set roots.. if not within caps, set to infinity (oder?)
	if (t1 < (cylinder->vector.y - height_half) || t1 > (cylinder->vector.y + height_half))
		obj_data->root1 = INFINITY;
	if (t2 < (cylinder->vector.y - height_half) || t2 > (cylinder->vector.y + height_half))
		obj_data->root2 = INFINITY;

	obj_data->t = fmin(obj_data->root1, obj_data->root2); // returns the smaller double
	if (obj_data->t > 0)
		return (true); // intersection found
	return (false); // no intersection
}