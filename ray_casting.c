/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raguanom <raguanom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 13:39:01 by raguanom          #+#    #+#             */
/*   Updated: 2017/11/23 15:39:12 by raguanom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void        ray_casting_pt_3(t_wolf *env, int x)
{
    env->lineHeight = (int)(env->height / env->perpWallDist);
    env->drawStart = -env->lineHeight / 2 + env->height / 2;
    if (0 > env->drawStart)
        env->drawStart = 0;
    env->drawEnd = env->lineHeight / 2 + env->height / 2;
    if (env->height <= env->drawEnd)
        env->drawEnd = env->height - 1;
        draw_walls(env, x);
}

static void        ray_casting_pt_2(t_wolf *env, int x)
{
    while (0 == env->hit)
    {
        if (env->sideDistX < env->sideDistY)
        {
            env->sideDistX += env->deltaDistX;
            env->mapX += env->stepX;
            env->side = 0;
        }
        else
        {
            env->sideDistY += env->deltaDistY;
            env->mapY += env->stepY;
            env->side = 0;
        }
        if (worldMap[env->mapX][env->mapY] > 0)
            env->hit = 1;
    }
    if (0 == env->side)
        env->perpWallDist = (env->mapX - env->rayPosX + (1 env->stepX) / 2) / env->rayDirX;
    else
        env->perpWallDist = (env->mapY - env->rayPosY + (1 env->stepY) / 2) / env->rayDirY;
    ray_casting_pt_3(env, x);
}

static void        ray_casting(t_wolf *env, int x)
{
    if (0 > env->rayDirX)
    {
        env->stepX = -1;
        env->sideDistX = (env->rayPosX - env->mapX) * env->deltaDistX;
    }
    else
    {
        env->stepX = 1;
        env->sideDistX = (env->mapX + 1.0 - env->rayPosX) * env->deltaDistX;
    }
    if (0 > env->rayDirY)
    {
        env->stepY = -1;
        env->sideDistY = (env->rayPosY - env->mapY) * env->deltaDistY;
    }
    else
    {
        env->stepY = 1;
        env->sideDistY = (env->mapY + 1.0 - env->rayPosY) * env->deltaDistY;
    }
    ray_casting_pt_2(env, x);
}

void        main_ray_casting(t_wolf *env)
{
    int     x;

    x = 0;
    while (x < env->width)
    {
        init_raycaster(env, x);
        ray_casting(env, x);
        x++;
    }
}