/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jordi <jordi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:24:05 by jordi             #+#    #+#             */
/*   Updated: 2025/02/14 17:15:16 by jordi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// typedef struct s_vars {
//     void    *mlx;
//     void    *win;
//     t_data  img_1;
//     t_data  img_C;
//     t_data  img_E;
//     t_data  img_P;
//     t_data  img_0;
//     int     color;
//     int     img_width;
//     int     img_height;
// } t_vars;
// For setting the player position for each keypress
// int key_handler(int keycode, t_vars *vars)
// {
//     if (keycode == KEY_W)
//         vars->player.pos.x += 1;
//     else if (keycode == KEY_A)
//         vars->player.pos.x -= 1;
//     else if (keycode == KEY_S)
//         vars->player.pos.y -= 1;
//     else if (keycode == KEY_D)
//         vars->player.pos.y += 1;
//     return (0);
// }

int handle_close(t_vars *vars)
{
    if (vars->img.img)
        mlx_destroy_image(vars->mlx, vars->img.img);
    if (vars->win)
        mlx_destroy_window(vars->mlx, vars->win);
    if (vars->mlx)
    {
        mlx_destroy_display(vars->mlx);
        free(vars->mlx);
    }
    exit(0);
    return (0);
}
int handle_keypress(int keycode, t_vars *t_vars)
{
    if (keycode == KEY_ESC)
        handle_close(t_vars);
    else if (keycode == KEY_W)
        printf("W\n");
    else if (keycode == KEY_A)
        printf("A\n");
    else if (keycode == KEY_S)
        printf("S\n");
    else if (keycode == KEY_D)
        printf("D\n");
    return (0);
}

void ft_put_pixel(t_data *data, int x, int y, int color)
{
    char *pixel;
    
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
    {
        pixel = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
        *(unsigned int *)pixel = color;
    }
}


int main(int argc, char **argv)
{
    t_vars  vars;
    t_map *map;


    char *path = "./test.xpm";

	check_args(argc, argv);
    map = validate_map(argv[1]);
    vars.mlx = mlx_init();
    if (!vars.mlx)
        return (EXIT_FAILURE);
    vars.win = mlx_new_window(vars.mlx, 1920, 1080, "test");
    if (!vars.win)
    {
        mlx_destroy_display(vars.mlx);
        free(vars.mlx);
        return (EXIT_FAILURE);
    }
    // vars.img.img = mlx_new_image(vars.mlx, 1920, 1080);
    vars.img.img = mlx_xpm_file_to_image(vars.mlx, path, &vars.img_width, &vars.img_height);
    if (!vars.img.img)
    {
        mlx_destroy_window(vars.mlx, vars.win);
        mlx_destroy_display(vars.mlx);
        free(vars.mlx);
        return (EXIT_FAILURE);
    }
    // vars.img.img = mlx_xpm_file_to_image(vars.mlx, path, &vars.img_width, &vars.img_height);
    vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel,
                                    &vars.img.line_length, &vars.img.endian);
    vars.color = 0xFF0000;
    mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
    mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, vars.img_width, 0);
    mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, vars.img_width * 2, 0);
    // mlx_hook(vars.win, ON_KEYDOWN, 1L<<0, handle_keypress, &vars); // close_window
    mlx_key_hook(vars.win, handle_keypress, &vars);
    mlx_hook(vars.win, CLOSE_BUTTON, 0L, handle_close, &vars);  // 17 is the X button event
    mlx_loop(vars.mlx);
    return (0);
}

