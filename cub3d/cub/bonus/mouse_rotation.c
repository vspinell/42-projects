/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:37:26 by vspinell          #+#    #+#             */
/*   Updated: 2021/04/11 15:37:28 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libcub.h"

void	mouse_rot(t_window *window)
{
	int	left_quarter;
	int	right_quarter;

	left_quarter = window->game->res_w_nu / 4;
	right_quarter = window->game->res_w_nu - left_quarter;
	if (window->mouse_pos->pos_x > right_quarter)
		decrement_degree(&window->plr->tilt, R_VEL / 4,
						window->plr->plane);
	if (window->mouse_pos->pos_x < left_quarter)
		increment_degree(&window->plr->tilt, R_VEL / 4,
						window->plr->plane);
}
