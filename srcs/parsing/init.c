#include "../../includes/cube3d.h"

void init_textures_colors(t_map *map)
{
    // Floor
    map->color[0][0] = -1;
    map->color[0][1] = -1;
    map->color[0][2] = -1;
    // Ceiling
    map->color[1][0] = -1;
    map->color[1][1] = -1;
    map->color[1][2] = -1;
    // Textures
    map->textures[0] = NULL;
    map->textures[1] = NULL;
    map->textures[2] = NULL;
    map->textures[3] = NULL;
}

bool    init_map(t_ctrl *ctrl)
{
    ctrl->map = malloc(sizeof(t_map));
    if (!ctrl->map)
        return (false);
    ctrl->map->temp_map = NULL;
    ctrl->map->map_stock = NULL;
    ctrl->map->map = NULL;
    ctrl->map->nb_line = 0;
    ctrl->map->config_set = 0;
    init_textures_colors(ctrl->map);
    return (true);
}

void	init_struct(t_ctrl *ctrl)
{
    ctrl->map = NULL;
    ctrl->mlx = NULL;
    ctrl->win = NULL;
    ctrl->size = NULL;
	// ctrl->map->NO_t = NULL;
	// ctrl->map->SO_t = NULL;
	// ctrl->map->EA_t = NULL;
	// ctrl->map->WE_t = NULL;
}
