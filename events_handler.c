/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raguanom <raguanom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 14:21:58 by raguanom          #+#    #+#             */
/*   Updated: 2017/11/23 15:52:03 by raguanom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void    set_timing(t_wolf *env)
{
    env->oldTime = env->aTime;
    env->aTime = SDL_GetTicks();
    env->frameTime = (env->aTime - env->oldTime) / 1000.0;
    SDL_RenderPresent(env->ren);
}

void    events(t_wolf *env)
{
    env->moveSpeed = env->frameTime * 30.0;
    env->rotSpeed = env->frameTime * 6.0;
    while (SDL_PollEvent(&env->event))
    {
        env->MoveX = env->posX + env->dirX * env->moveSpeed;
        env->MoveY = env->posY + env->dirY * env->moveSpeed;
        if (env->event.type == SDL_KEYDOWN)
        {
            if (env->event.key.keysym.sym == SDLK_UP)
                move_forward(env);
            if (env->event.key.keysym.sym == SDLK_DOWN)
                move_backward(env);
            if (env->event.key.keysym.sym == SDLK_RIGHT)
                rotate_right(env);
            if (env->event.key.keysym.sym == SDLK_LEFT)
                rotate_left(env);
            if (env->event.key.keysym.sym == SDLK_ESCAPE)
                exit(-1);
        }
    }
}