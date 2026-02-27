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

# define WIN_WIDTH 1280 
# define WIN_HEIGHT 720

#define	SPEED 1 //la vitesse du joueur

typedef enum e_error
{
	SUCCES = 0,
	MALLOC = -2,
	INVALID_INPUT = 1,//debut seulement

	INVALID_FILE = -1,//obligatoirement -1 

	//config
	EMPTY_FILE = 2,
	INVALID_CONFIG = 12,//!!! ni 1 ni 0
	CONFIG_MISSING = 3,
	MAP_MISSING = 4,
	MISSPLACED_ELEM = 5,

	//parsemap
	INVALID_CHAR = 6,
	MULTIPLAYER = 7,
	PLAYER_MISSING = 8,
	INVALID_WALLS = 11,
	STR_AFTER = 9,

	//mlx
	INVALID_FILE_FORMAT = 10
}t_error;

typedef struct s_xy
{
	int x;
	int y;
} t_xy;

typedef struct s_coor//pour le player et les rayons
{
	double x;
	double y;
} t_coor;

typedef struct s_temp_map//parsing only
{
	char *row;
	struct s_temp_map *next;
} t_temp_map;

typedef struct s_map
{
	//infos utiles
	char *name;

	char **map;
	char *textures[4];//N, S, E, W
	int color[2];//F, C
	size_t nb_line;
	size_t	len_line;
	int	orientation;//NO=0 SO=1 EA=2 WE=3

	//parsing
	int textures_set;//<4 = pas fini d'allouer
	int	colors_set;//<2 = pas fini d'allouer
	bool map_set;//== 0 = pas fini d'allouer
	t_temp_map *temp_map;//ok
	char *map_stock;//used
} t_map;

typedef struct s_data//mlx img
{
	t_xy			img_dim;//en unite de map
	void			*img;
	char			*addr;
	int				bpp;
	int				x_len;
	int				endian;
}					t_data;

typedef struct s_images
{
	//static
	t_data	NO;
	t_data	SO;
	t_data	EA;
	t_data	WE;
	t_data	F_C;
	t_data	minimap;
	//je sais pas encore quoi faire de dimension...
	t_xy	dimension;//toutes les images doivent avoir la mm
	
	//dynamique
	t_data	to_print;
	
} t_images;

typedef struct s_player
{
	t_xy	map_c;//coordonnees dans les unites de la map
	t_coor	precis;//coordonnees en pixels
}t_player ;

typedef struct s_ctrl
{
	void			*mlx;
	void			*win;
	t_map 			*map; 
	t_images		img;
	int				tile_size;//en pixels
	t_player		player;
	bool			key_press[6];//wasd<-->
	// int			moving;
	
	t_error			error;
} t_ctrl ;


/*---------------MLX-----------------*/
/*mlx*/
int	end(t_ctrl *ctrl);
int	keypress(int keysym, t_ctrl *ctrl);
int	keyrelease(int keysym, t_ctrl *ctrl);
int	move(t_ctrl *ctrl);
bool	set_img(t_ctrl *ctrl);

/*----------------PARSING----------------*/
/*init*/
int    init_minilibx(t_ctrl *ctrl);
void init_textures_colors(t_map *map);
void	init_struct(t_ctrl *ctrl);
int    init_map(t_ctrl *ctrl, char *name);
/*map_parse*/
int	parse_map(t_ctrl *ctrl);
/*parsing*/
void	print_error(t_ctrl *ctrl);
int	check_file(char *name);
int	check_mapname(char *file_name);
int	parse_data(t_ctrl *ctrl, int argc, char **argv);
/*pre_map*/
bool	map_found(t_ctrl *ctrl, char *line);
int	correct_texture(t_ctrl *ctrl, char *line);
int	set_config(t_ctrl *ctrl, int fd);
int	error_config(t_ctrl *ctrl);
/*temp_map_tools*/
int	fill_temp_map(t_ctrl *ctrl, int fd);
int	convert_in_tab(t_ctrl *ctrl);
t_temp_map	*add_node(char *line);
bool	putlast(t_ctrl *ctrl, t_temp_map **head, char *line);
/*texture_color*/
int set_texture(t_ctrl *ctrl, char **tabl);
bool	correct_RGB(t_ctrl *ctrl, char **tabl, int id);
int	set_color(t_ctrl *ctrl, char **tabl);

/*----------------RAYCASTING----------------*/
void	my_mlx_pixel_put(t_data *data, t_xy p, t_xy win_s, int color);
int	convert_rgb(int r, int g, int b);
/*render*/
int	prepare_minimap(t_ctrl *ctrl);
int	prepare_static(t_ctrl *ctrl);
int	render(t_ctrl *ctrl);

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
char	**split_tab(char const *s, char *rm);

/*--------------------------------*/


#endif