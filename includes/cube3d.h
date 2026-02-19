#ifndef CUB3D_H
#define CUB3D_H

#define _GNU_SOURCE
#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "../libft/get_next_line_bonus.h"
#include "struct.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <X11/X.h>
# include <X11/keysym.h>
#include <stdbool.h>

# define WIN_WIDTH 960 
# define WIN_HEIGHT 720

typedef struct s_xy
{
	int x;
	int y;
} t_xy;

typedef struct s_temp_map
{
	char *row;
	struct s_temp_map *next;
} t_temp_map;

typedef struct s_map
{
	t_temp_map *temp_map;//ok
	char *map_stock;//used
	//vraie map
	char **map;
	//textures
	int	config_set;//<6 = pas fini d'allouer
	char *textures[4];//N, S, E, W,
	//couleurs RGB 
	int color[2][3];//F, C
	//dimensions
	int nb_line;
} t_map;

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bpp;
	int				x_len;
	int				endian;
}					t_data;

typedef struct s_ctrl
{
	void			*mlx;
	void			*win;
	t_map 			*map;
	t_xy			*size;
	
} t_ctrl ;


/*---------------MLX-----------------*/
/*mlx*/
int	end(t_ctrl *ctrl);

/*----------------PARSING----------------*/
/*init*/
void init_textures_colors(t_map *map);
void	init_struct(t_ctrl *ctrl);
bool    init_map(t_ctrl *ctrl);
/*parsing*/
bool	check_mapname(char *file_name);
bool	set_data(t_ctrl *ctrl, int argc, char **argv);
/*pre_map*/
bool	correct_texture(t_ctrl *ctrl, char *line);
bool	set_config(t_ctrl *ctrl, int fd);
/*temp_map_tools*/
bool	fill_temp_map(t_ctrl *ctrl, int fd);
bool	convert_in_tab(t_ctrl *ctrl);
t_temp_map	*add_node(char *line);
bool	putlast(t_temp_map **head, char *line);
void	free_list(t_temp_map **head);
int	chainlist_size(t_temp_map **head);
/*texture_color*/
bool set_texture(t_ctrl *ctrl, char **tabl);
bool	correct_RGB(t_ctrl *ctrl, char *line, int id);
int	set_color(t_ctrl *ctrl, char **tabl);

/*----------------RAYCASTING----------------*/

/*-------------UTILS----------------*/
void	free_tab(char **tab);
int	ft_strcmp(const char *s1, const char *s2);
int	count_elems(char **map, char c);
int	count_ocurr(char *str, char c);
char *remove_chars(char *line, char *to_rm);
bool	char_found(char *str, char *searched);
void	free_map(t_map *map);
void	free_all(t_ctrl *ctrl);
void	print_map_infos(t_ctrl *ctrl);
void	print_chain(t_temp_map **head);
void	free_chain(t_temp_map **head);

/*--------------------------------*/


#endif