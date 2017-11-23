/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raguanom <raguanom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 14:00:59 by raguanom          #+#    #+#             */
/*   Updated: 2017/11/23 15:49:22 by raguanom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static void	swap(int *n1, int *n2)
{
	int temp;

	temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}


//draw function:
void draw_line(SDL_Renderer *ren, int x1, int y1, int x2, int y2)
{
	double	slope;
	double	offset;
	int		iterate;
	int		*a;
	int		*b;

	slope = 0;
	offset = 0;
	if (abs(x1 - x2) >= abs(y1 - y2))
	{
		a = &x1;
		b = &y1;
	}
	else
	{
		swap(&x1, &y1);
		swap(&x2, &y2);
		a = &y1;
		b = &x1;
	}
		iterate = -1 + (2 * (x1 < x2));
		slope = ((double)abs(y1 - y2) / (double)abs(x1 - x2)) * (-1 + (2 * (y1 < y2)));
		while (x1 != x2)
		{
			if (offset >= 0.49999 || offset <= -0.5)
			{
				offset -= -1 + (2 * (y1 < y2));
				y1 += -1 + (2 * (y1 < y2));
			}
			SDL_RenderDrawPoint(ren, *a, *b);
			x1 += iterate;
			offset += slope;
		}
}

static void        choos_wall_colors(t_wolf *env, int x)
{
    if (0 == env->side)
    {
        if (0 > env->stepX)
            SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
        else
            SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
    }
    else
    {
        if (0 > env->stepY)
            SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
        else
            SDL_SetRenderDrawColor(ren, 255, 255, 0, 255);
    }
}

void        draw_walls(t_wolf *env, int x)
{
    int     i;

    i = 0;
    if (i < env->drawStart + 1)
    {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        draw_line(ren, x, i, x, env->drawStart);
        i++;
    }
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    choos_wall_colors(env, x);
    draw_line(ren, x, env->drawStart + 2, x, env->drawEnd);
    if (i >= env->drawEnd && i < env->height)
    {
        SDL_SetRenderDrawColor(ren, 210, 180, 140, 255);
        draw_line(ren, x, i, x, h);
        i++;
    }
}