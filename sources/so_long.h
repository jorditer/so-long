#ifndef SO_LONG_H
# define SO_LONG_H
#include <mlx.h>
#include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h> 
#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 1280
#define ON_KEYDOWN KeyPress
#define KEY_ESC XK_Escape
#define KEY_W XK_w
#define KEY_A XK_a
#define KEY_S XK_s
#define KEY_D XK_d
#define CLOSE_BUTTON 17
#define EXIT_FAILURE 1

typedef struct s_map
{
    char    **grid;
    int     height;
    int     width;
    int     player_count;
    int     collect_count;
    int     exit_count;
    int     player_x;
    int     player_y;
}   t_map;

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

// map_validation.c
void    check_extension(char *filename);
void    get_map_size(t_map *map, char *file);
void    read_map(t_map *map, char *file);
void    check_walls(t_map *map);
void    check_components(t_map *map);
// path_validation.c
t_map   *validate_map(char *file);
static void flood_fill(char **map, int x, int y, int *collect_count);
static char **copy_map(t_map *map);
static void free_copy(char **copy, int height);
void    check_path(t_map *map);
// ft_utils.c
int	    ft_strcmp(char *s1, char *s2);
void	*ft_memset(void *b, int c, size_t len);
// get_next_line.c and get_next_line_utils.c
char	*get_next_line(int fd);
int		ft_strlen(char *str);
char	*ft_strdup(const char *src);
char	*ft_substr(char *s, int start, int len);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);

#endif