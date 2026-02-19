#include "../../includes/cube3d.h"

void	free_tab(char **tab)
{
	int j;

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
	int i;

	if (map->map_stock)
		free(map->map_stock);
	if (map->map)
		free_tab(map->map);
	i = 0;
	while (i < 4)
	{
		if (map->textures[i])
			free (map->textures[i]);
		i++;
	}
	// free(map->temp_map);
	// if (map->temp_map)
	// 	free_chain(&map->temp_map);
	free(map);
}

void	free_all(t_ctrl *ctrl)
{
	if (ctrl->map)
		free_map(ctrl->map);
}