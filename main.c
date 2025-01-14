#include <mlx.h>
#include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <unistd.h>
#include <stdlib.h>
#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280
#define ON_KEYDOWN KeyPress
#define KEY_ESC XK_Escape
#define KEY_W XK_w
#define KEY_A XK_a
#define KEY_S XK_s
#define KEY_D XK_d

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;
typedef struct s_vars {
    void    *mlx;
    void    *win;
    t_data  img;
    int     color;
    int     img_width;
    int     img_height;
} t_vars;
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

int handle_movement(int keycode, t_vars *t_vars)
{
    if (keycode == KEY_W)
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

int close_window(int keycode, t_vars *vars)
{
    if (keycode != KEY_ESC)  // Not ESC key
        return (0);
    
    if (!vars || !vars->mlx)
        return (1);

    if (vars->img.img)
        mlx_destroy_image(vars->mlx, vars->img.img);
    if (vars->win)
        mlx_destroy_window(vars->mlx, vars->win);
    
    mlx_destroy_display(vars->mlx);
    free(vars->mlx);
    exit(0);
}


int main(void)
{
    t_vars  vars;
    char *path = "./test.xpm";
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 1920, 1080, "test");
    vars.img.img = mlx_new_image(vars.mlx, 1920, 1080);
    vars.img.img = mlx_xpm_file_to_image(vars.mlx, path, &vars.img_width, &vars.img_height);
    vars.img.img = mlx_xpm_file_to_image(vars.mlx, path, &vars.img_width, &vars.img_height);
    vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel,
                                    &vars.img.line_length, &vars.img.endian);
    vars.color = 0xFF0000;
    mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
    mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, vars.img_width, 0);
    mlx_hook(vars.win, ON_KEYDOWN, 1L<<0, close_window, &vars); // close_window
    mlx_loop(vars.mlx);
    return (0);
}

