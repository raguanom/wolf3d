/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raguanom <raguanom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 15:01:11 by raguanom          #+#    #+#             */
/*   Updated: 2017/11/23 15:48:36 by raguanom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void        get_world(char *file_name, t_wolf *env)
{
    int     fd;
    char    **str;
    char    *line;

    line = NULL;
    str = NULL;
    fd = open(file_name, O_RDONLY);
    env->mapHeight = get_num_lines(file_name, fd);
    env->mapWidth = get_num_points(file_name, str, line, fd);
    env = get_points_array(env);
    //get_points(env, fd);
    close(fd);
}

static void        main_loop(t_wolf *env)
{
    while (1)
    {
        main_ray_casting(env);
        set_timing(env);
        events(env);
    }
}

static int      check_fd(char *file_name)
{
    int     fd;

    fd = open(file_name, O_RDONLY);
    if (-1 == fd)
    {
        ft_putstr("Check permissions for [");
        ft_putstr(file_name);
        ft_putstr("] Can only read file with ");
        ft_putendl("correct permmision.");
        exit(-1);
        return (1);
    }
    close(fd);
    return (0);
}

static void     die_usage(char *chr)
{
    ft_putstr("Usage: {");
    ft_putstr(chr);
    ft_putstr("} ");
    ft_putendl("--[file_name].fdf--");
    exit(-1);
}

static void     die_file_overflow(void)
{
    ft_putstr("Too many input files. ");
    ft_putstr("Please provide valid --[.fdf]-- file.\n");
    exit(-1);
}

int     main(int ac, char **av)
{
    t_wolf *env;

    env = NULL;
    if (ac == 2)
    {
        if (ft_strrchr(av[1], '.') == NULL)
            die_usage(av[0]);
        if (ft_strcmp(".wolf3d", ft_strrchr(av[1], '.')) != 0)
            die_usage(av[0]);
        else if (check_fd(av[1]))
            exit(-1);
        else
            main_loop(env);
    }
    else
    {
        if (ac > 2)
            die_file_overflow();
        else
            die_usage(av[0]);
    }
    return (0);
}