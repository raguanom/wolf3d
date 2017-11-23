/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_and_rot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raguanom <raguanom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 14:27:16 by raguanom          #+#    #+#             */
/*   Updated: 2017/11/23 14:59:29 by raguanom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void    move_forward(t_wolf *env)
{
    if (env->mapWorld[(int)env->MoveX][(int)env->posY] == 0)
        env->posX += env->dirX * env->moveSpeed;
    if (env->mapWorld[(int)env->posX][(int)env->MoveY] == 0)
        env->posX += env->dirX * env->moveSpeed;
}

void    move_backward(t_wolf *env)
{
    if (env->mapWorld[(int)env->MoveX][(int)env->posY] == 0)
        env->posX -= env->dirX * env->moveSpeed;
    if (env->mapWorld[(int)env->posX][(int)env->MoveY] == 0)
        env->posX -= env->dirX * env->moveSpeed;
}

void    rotate_right(t_wolf *env)
{
    env->oldDirX = env->dirX;
    env->dirX = env->dirX * cos(-env->rotSpeed) - env->dirY * sin(-env->rotSpeed);
    env->dirY = env->oldDirX * sin(-env->rotSpeed) + env->dirY * cos(-env->rotSpeed);
    env->oldPlaneX = env->planeX;
    env->planeX = env->planeX * cos(-env->rotSpeed) - env->planeY * sin(-env->rotSpeed);
    env->planeY = env->oldPlaneX * sin(-env->rotSpeed) + env->planeY * cos(-env->rotSpeed);
}

void    rotate_left(t_wolf *env)
{
    env->oldDirX = env->dirX;
    env->dirX = env->dirX * cos(env->rotSpeed) - env->dirY * sin(env->rotSpeed);
    env->dirY = env->oldDirX * sin(env->rotSpeed) + env->dirY * cos(env->rotSpeed);
    env->oldPlaneX = env->planeX;
    env->planeX = env->planeX * cos(env->rotSpeed) - env->planeY * sin(env->rotSpeed);
    env->planeY = env->oldPlaneX * sin(env->rotSpeed) + env->planeY * cos(env->rotSpeed);
}