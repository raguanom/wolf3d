/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raguanom <raguanom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 15:17:51 by raguanom          #+#    #+#             */
/*   Updated: 2017/11/23 15:52:42 by raguanom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int             get_num_lines(char *file_name, int fd)
{
    int     num_lines;
    char    *line;

    num_lines = 0;
    while ((get_next_line(fd, &line)) > 0)
        num_lines++;
    return (num_lines);
}

int             get_num_points(char *file_name, char **str, char *line, int fd)
{
    int     num_points;
    int     i;

    while ((get_next_line(fd, &line)) > 0)
    {
        num_points = 0;
        str = ft_strsplit(line, ' ');
        i = -1;
        while (str[++i] != 0)
            num_points++;
    }
    ft_memdel(&line);
    i = -1;
    while (str[++i] != 0)
        ft_memdel(((void *)&str[i]));
    free(str);
    return (num_points);
}

t_wolf          *get_points_array(t_wolf *env)
{
    int         i;

    if (!(env->worldMap = (int**)malloc(sizeof(int*) * env->mapHeight)))
        return (NULL);
    i = 0;
    while (i < env->mapHeight)
    {
        if (!(env->worldMap[i] = (int*)malloc(sizeof(int) * map->mapWidth)))
            return (NULL);
        i++;
    }
    return (env);
}

void            get_points(t_wolf *env, int fd)
{
    char        **str;
    char        *line;
    int         i;
    int         j;
    int         k;

    i = 0;
    while (get_next_line(fd, &line) > 0)
    {
        str = ft_strsplit(line, ' ');
        k = -1;
        j = -1;
        while (str[++k] != 0)
            env->worldMap[i][++j] = ft_atoi(str[k]);
        k = -1;
        while (str[++k] != 0)
            ft_strdel(&str[k]);
        free(str);
        i++;
    }
}