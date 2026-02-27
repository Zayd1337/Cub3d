#include "../../includes/cube3d.h"

void	free_tab(char **tab)
{
	int	j;

	j = 0;
	while (tab[j])
	{
		free(tab[j]);
		j++;
	}
	free(tab);
}

void	free_chain(t_temp_map **head)
{
	t_temp_map	*next;
	t_temp_map	*current;

	if (!head | !*head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		if (current->row)
			free(current->row);
		free(current);
		current = next;
	}
}

void	free_map(t_map *map)
{
	int	i;

	if (map->name)
		free(map->name);
	if (map->map)
		free_tab(map->map);
	if (map->temp_map)
		free_chain(&map->temp_map);
	i = -1;
	while (++i < 4)
	{
		if (map->textures[i])
			free(map->textures[i]);
	}
	free(map);
}

void	clean_img(t_ctrl *ctrl)
{
	if (ctrl->img.NO.img)
		mlx_destroy_image(ctrl->mlx, ctrl->img.NO.img);
	if (ctrl->img.SO.img)
		mlx_destroy_image(ctrl->mlx, ctrl->img.SO.img);
	if (ctrl->img.EA.img)
		mlx_destroy_image(ctrl->mlx, ctrl->img.EA.img);
	if (ctrl->img.WE.img)
		mlx_destroy_image(ctrl->mlx, ctrl->img.WE.img);
	if (ctrl->img.F_C.img)
		mlx_destroy_image(ctrl->mlx, ctrl->img.F_C.img);
	if (ctrl->img.minimap.img)
		mlx_destroy_image(ctrl->mlx, ctrl->img.minimap.img);
	if (ctrl->img.to_print.img)
		mlx_destroy_image(ctrl->mlx, ctrl->img.to_print.img);
}

void	free_all(t_ctrl *ctrl)
{
	clean_img(ctrl);
	if (ctrl->win)
		mlx_destroy_window(ctrl->mlx, ctrl->win);
	if (ctrl->mlx)
	{
		mlx_destroy_display(ctrl->mlx);
		free(ctrl->mlx);
	}
	if (ctrl->map)
		free_map(ctrl->map);
}