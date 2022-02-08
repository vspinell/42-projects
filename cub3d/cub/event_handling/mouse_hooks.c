/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:42:36 by vspinell          #+#    #+#             */
/*   Updated: 2021/04/11 15:42:37 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libcub.h"

int	mouse_click(int button, int pos_x, int pos_y, t_window *window)
{
	window->click->button = button;
	window->click->pos_x = pos_x;
	window->click->pos_y = pos_y;
	clean_mouse_click(window->click);
	return (0);
}

int	mouse_pos_mov(int x, int y, t_window *window)
{
	window->mouse_pos->pos_x = x;
	window->mouse_pos->pos_y = y;
	return (0);
}
