/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:41:13 by vspinell          #+#    #+#             */
/*   Updated: 2021/04/11 15:41:25 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libcub.h"

void	clean_data(t_data *data)
{
	data->img = 0;
	data->addr = 0;
	data->bits_per_pixel = 0;
	data->line_length = 0;
	data->endian = 0;
}

void	clean_mouse_pos(t_mouse_pos *mouse_pos)
{
	mouse_pos->pos_x = 0;
	mouse_pos->pos_y = 0;
}

void	clean_mouse_click(t_mouse_ck *click)
{
	click->button = 0;
	click->pos_x = 0;
	click->pos_y = 0;
}

void	clean_keys(t_keys *keys)
{
	keys->w_key = 0;
	keys->a_key = 0;
	keys->s_key = 0;
	keys->d_key = 0;
	keys->left_arrow = 0;
	keys->right_arrow = 0;
	keys->esc = 0;
}

void	clean_window_struct(t_window *window)
{
	window->mlx = 0;
	window->mlx_win = 0;
	clean_data(window->curr_img);
	clean_mouse_click(window->click);
	clean_mouse_pos(window->mouse_pos);
	clean_keys(window->keys);
	window->close = 0;
}
