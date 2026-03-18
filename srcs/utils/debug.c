/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 09:41:59 by jeazil            #+#    #+#             */
/*   Updated: 2026/03/18 09:42:29 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

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
	int	i;

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
	printf("RGB floor: %d\n", ctrl->map->color[0]);
	printf("RGB ceiling: %d\n", ctrl->map->color[1]);
	printf("config_set : %d\n", ctrl->map->textures_set);
	printf("config_set : %d\n", ctrl->map->colors_set);
	printf("config_set : %d\n", ctrl->map->map_set);
	printf("nb_line : %zu\n", ctrl->map->nb_line);
	printf("len_lime : %zu\n", ctrl->map->len_line);
	i = 0;
	while (ctrl->map->map && ctrl->map->map[i])
		printf("|%s|\n", ctrl->map->map[i++]);
}

void	print_error_bis(int error)
{
	if (error == CONFIG_MISSING)
		ft_putstr_fd("Error\nA config asset is missing\n", 1);
	else if (error == MAP_MISSING)
		ft_putstr_fd("Error\nMap is missing\n", 1);
	else if (error == MISSPLACED_ELEM)
		ft_putstr_fd("Error\nMissplaced element\n", 1);
	else if (error == INVALID_CHAR)
		ft_putstr_fd("Error\nInvalid char found\n", 1);
	else if (error == MULTIPLAYER)
		ft_putstr_fd("Error\nMore than one player detected\n", 1);
	else if (error == PLAYER_MISSING)
		ft_putstr_fd("Error\nPlayer is missing\n", 1);
	else if (error == STR_AFTER)
		ft_putstr_fd("Error\nString at the end of the file\n", 1);
	else if (error == INVALID_FILE_FORMAT)
		ft_putstr_fd("Error\nInvalid file format\n", 1);
	else if (error == INVALID_WALLS)
		ft_putstr_fd("Error\nInvalid walls\n", 1);
}

void	print_error(t_ctrl *ctrl)
{
	t_error	error;

	error = ctrl->error;
	if (error == MALLOC)
		ft_putstr_fd("Error\nMemory allocation failed\n", 1);
	else if (error == SUCCES)
		ft_putstr_fd("SUCCESS\n", 1);
	else if (error == INVALID_INPUT)
		ft_putstr_fd("Error\nInvalid input\n", 1);
	else if (error == INVALID_FILE)
		ft_putstr_fd("Error\nInvalid file\n", 1);
	else if (error == EMPTY_FILE)
		ft_putstr_fd("Error\nEmpty file\n", 1);
	else if (error == INVALID_CONFIG)
		ft_putstr_fd("Error\nA config asset is invalid\n", 1);
	print_error_bis(error);
}
