/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcub_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vspinell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:32:48 by vspinell          #+#    #+#             */
/*   Updated: 2021/04/11 15:32:50 by vspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBCUB_BONUS_H
# define LIBCUB_BONUS_H
# include "../libcub.h"

/*
**Minimap
*/

void			minimap_img(t_data *img, t_window *window, t_player *player,
					int min_fract);
void			mouse_rot(t_window *window);
void			player_movement_b(t_keys *keys, t_player *player, char **map);

#endif
