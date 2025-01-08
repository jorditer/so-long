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
} t_vars;
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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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
// x & y maximum x and y location to print to
void draw_square(t_data *img, int x, int y, int size, int color)
{
    int i, j;

    // Loop through each row of the square
    for (i = y; i < y + size; i++)
    {
        // Loop through each column of the square
        for (j = x; j < x + size; j++)
        {
            // Draw each pixel of the square
            ft_put_pixel(img, j, i, color);
        }
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

int change_colors(t_vars *vars)
{
    if (vars->color == 0xFF0000)
        vars->color == 0x00FF00;
    else if (vars->color == 0x00FF00)
        vars->color == 0x0000FF;
    else
        (vars->color == 0xFF0000);
}

int main(void)
{
    t_vars  vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 1920, 1080, "test");
    vars.img.img = mlx_new_image(vars.mlx, 1920, 1080);
    vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel,
                                    &vars.img.line_length, &vars.img.endian);
    int color = 0xFF0000;
    draw_square(&vars.img, 300, 300, 500, color);
    mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
    mlx_hook(vars.win, ON_KEYDOWN, 1L<<0, close_window, &vars); // close_window
    mlx_key_hook(vars.win, handle_movement, &vars);
    mlx_loop_hook(vars.mlx, change_colors, &vars);
    mlx_loop(vars.mlx);
    return (0);
}
// int mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct_ptr)(), void *param);

