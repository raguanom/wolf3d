/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raguanom <raguanom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 13:07:30 by raguanom          #+#    #+#             */
/*   Updated: 2017/11/23 14:55:36 by raguanom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static SDL_Renderer     *init_ren(char *title)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *win = SDL_CreateWindow(title, 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Renderer *ren = SDL_CreateRenderer(win, 1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);
	SDL_RenderPresent(ren);
	return (ren);
}

void             init_raycaster(t_wolf *env, int x)
{
    env->cameraX = 2 * x / (double)env->width - 1;
    env->rayPosX = env->posX;
    env->rayPosY = env->posY;
    env->rayDirX = env->dirX + env->planeX * env->cameraX;
    env->rayDirY = env->dirY + env->planeY * env->cameraX;
    env->mapX = (int)env->rayPosX;
    env->mapY = (int)env->rayPosY;
    env->sideDistX = 0.0;
    env->sideDistY = 0.0;
    env->deltaDistX = sqrt(1 + (env->rayDirY * env->rayDirY) /
                        (env->rayDirX * env->rayDirY));
    env->deltaDistY = sqrt(1 + (env->rayDirX * env->rayDirX) /
                        (env->rayDirY * env->rayDirY));
    env->perpWallDist = 0.0;
    env->stepX = 0;
    env->stepY = 0;
    env->hit = 0;
    env->side = 0;
}

void                    init(t_wolf *env)
{
    env->posX = 2;
    env->posY = 2;
    env->dirX = -1;
    env->dirY = 0;
    env->planeX = 0;
    env->planeY = 0.66;
    env->MoveX = 0;
    env->MoveY = 0;
    env->aTime = 0;
    env->oldTime = 0;
    env->width = 640;
    env->height = 480;
    env->oldDirX = 0.0;
    env->oldPlaneX = 0.0;
    env->ren = init_ren("Wolf3D");
}