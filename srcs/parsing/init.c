#include "../../includes/cube3d.h"

bool    init_minilibx(t_ctrl *ctrl)
{
    ctrl->mlx = mlx_init();
    if (!ctrl->mlx)
        return (printf ("error malloc init 1\n"), false);
    ctrl->win = mlx_new_window(ctrl->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
    if (!ctrl->win)
        return (printf ("error malloc init 2\n"), false);
    return (true);
}

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
    ctrl->map->len_line = 0;
    ctrl->map->config_set = 0;
    ctrl->map->orientation = -1;
    init_textures_colors(ctrl->map);
    return (true);
}

void	init_struct(t_ctrl *ctrl)
{
    ctrl->map = NULL;
    ctrl->win = NULL;
    ctrl->mlx = NULL;
    ctrl->size = NULL;
    ctrl->img.NO.img = NULL;
    ctrl->img.SO.img = NULL;
    ctrl->img.EA.img = NULL;
    ctrl->img.WE.img = NULL;
}
