#include "../includes/cube3d.h"

void	print_chain(t_temp_map **head)
{
	t_temp_map	*current;

	current = *head;
	while (current != NULL)
	{
		printf("|%s|\n", current->row);
		current = current->next;
	}
}

void	print_map_infos(t_ctrl *ctrl)
{
	printf("-------PRINT INFOS-------\n");
	if (!ctrl->map)
		return ;
	if (ctrl->map->textures[0])
		printf("SO : %s\n", ctrl->map->textures[0]);
	if (ctrl->map->textures[1])
		printf("NO : %s\n", ctrl->map->textures[1]);
	if (ctrl->map->textures[2])
		printf("EA : %s\n", ctrl->map->textures[2]);
	if (ctrl->map->textures[3])
		printf("WE : %s\n", ctrl->map->textures[3]);

	printf("F : [%d][%d][%d]\n", ctrl->map->color[0][0], ctrl->map->color[0][1],
		ctrl->map->color[0][2]);
	printf("F : [%d][%d][%d]\n", ctrl->map->color[1][0], ctrl->map->color[1][1],
		ctrl->map->color[1][2]);

	printf("config_set : %d\n", ctrl->map->config_set);
	printf("nb_line : %zu\n", ctrl->map->nb_line);
	printf("len_lime : %zu\n", ctrl->map->len_line);

	int i = 0;
	while (ctrl->map->map && ctrl->map->map[i])
	{
		printf("|%s|\n", ctrl->map->map[i]);
		i++;
	}
}