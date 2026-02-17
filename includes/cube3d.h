#ifndef CUB3D_H
#define CUB3D_H

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

typedef struct s_img
{
	//textures
	char *NO_t;
	char *SO_t;
	char *EA_t;
	char *WE_t;
	//couleurs
	int F_t[3];//RGB
	int C_t[3];//RGB

} t_img;

typedef	struct s_map
{


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
	char 			**map;
	t_img			*img;
	t_xy			*size;
	
} t_ctrl ;

int	ft_strcmp(const char *s1, const char *s2);

#endif