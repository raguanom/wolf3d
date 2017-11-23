/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raguanom <raguanom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 10:02:09 by raguanom          #+#    #+#             */
/*   Updated: 2017/11/23 15:52:19 by raguanom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <sdl.h>
# include <stdio.h>
# include <math.h>

# include "./libft/libft.h"

/*
**  Ray struct:
*/
typedef struct      s_wolf
{
    SDL_Renderer    *ren;
    SDL_Event       event;
    int             width;
    int             height;
    int             **mapWorld;
    int             mapWidth;
    int             mapHeight;
    double          posX;
    double          posY;
    double          dirX;
    double          dirY;
    double          oldDirX;
    double          planeX;
    double          planeY;
    double          oldPlaneX;
    double          aTime;
    double          oldTime;
    double          frameTime;
    double          moveSpeed;
    double          rotSpeed;
    double          cameraX;
    double          rayPosX;
    double          rayPosY;
    double          rayDirX;
    double          rayDirY;
    int             mapX;
    int             mapY;
    double          MoveX;
    double          MoveY;
    double          sideDistX;
    double          sideDistY;
    double          deltaDistX;
    double          deltaDistY;
    double          perpWallDist;
    int             hit;
    int             side;
    int             stepX;
    int             stepY;
    int             lineHeight;
    int             drawStart;
    int             drawEnd;
}                   t_wolf;

/*
**  Functions:
*/
//pos of player, direction of player, camera plane, movement, fps, screen creation:
void            init(t_wolf *env);
//SDL_Renderer    *ren_init(char *title);
void            draw_linedraw_line(SDL_Renderer *ren, int x1, int y1, int x2, int y2);
void            game_loop(t_wolf *e);
void        get_world(char *file_name, t_wolf *env);
void             init_raycaster(t_wolf *env, int x);
void    set_timing(t_wolf *env);
void    events(t_wolf *env);
void        main_ray_casting(t_wolf *env);
t_wolf          *get_points_array(t_wolf *env);
int             get_num_points(char *file_name, char **str, char *line, int fd);
int             get_num_lines(char *file_name, int fd);
void    rotate_left(t_wolf *env);
void    rotate_right(t_wolf *env);
void    move_backward(t_wolf *env);
void    move_forward(t_wolf *env);

#endif