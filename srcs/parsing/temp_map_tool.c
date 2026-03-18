/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_map_tool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeazil <jeazil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:42:06 by jeazil            #+#    #+#             */
/*   Updated: 2026/03/17 16:42:08 by jeazil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

t_temp_map	*add_node(char *line)
{
	t_temp_map	*new;

	if (!line)
		return (NULL);
	new = NULL;
	new = malloc(sizeof(t_temp_map));
	if (new == NULL)
		return (NULL);
	new->row = remove_chars(line, "\n");
	if (new->row == NULL)
		return (NULL);
	new->next = NULL;
	return (new);
}

bool	putlast(t_ctrl *ctrl, t_temp_map **head, char *line)
{
	t_temp_map	*current;
	t_temp_map	*new;
	size_t		len;

	if (!line)
		return (false);
	new = add_node(line);
	if (new == NULL)
		return (false);
	if (!*head)
	{
		*head = new;
		return (true);
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	len = ft_strlen(line);
	if (ctrl->map->len_line < len)
		ctrl->map->len_line = len;
	return (true);
}

int	reload_line(t_ctrl *ctrl, char *line, bool end_map)
{
	char	*temp;

	temp = remove_chars(line, "\n");
	if (!temp)
	{
		ctrl->error = MALLOC;
		return (ctrl->error);
	}
	if (!end_map && putlast(ctrl, &ctrl->map->temp_map, temp) == false)
	{
		ctrl->error = MALLOC;
		return (free(temp), ctrl->error);
	}
	if (end_map && ft_strcmp(line, "\n"))
	{
		ctrl->error = STR_AFTER;
		return (free(temp), ctrl->error);
	}
	ctrl->map->nb_line++;
	return (free(temp), SUCCES);
}

int	fill_temp_map(t_ctrl *ctrl, int fd)
{
	char	*line;
	bool	end_map;

	end_map = false;
	line = ctrl->map->map_stock;
	while (line != NULL)
	{
		if (end_map == false && !ft_strcmp(line, "\n"))
			end_map = true;
		else if (reload_line(ctrl, line, end_map) != SUCCES)
			return (ctrl->error);
		free(line);
		line = get_next_line(fd);
	}
	return (SUCCES);
}

int	convert_in_tab(t_ctrl *ctrl)
{
	t_temp_map	*current;
	int			i;

	if (!ctrl->map || !ctrl->map->temp_map)
		return (MALLOC);
	ctrl->map->map = ft_calloc((ctrl->map->nb_line + 1), sizeof(char *));
	if (!ctrl->map->map)
		return (MALLOC);
	current = ctrl->map->temp_map;
	i = 0;
	while (current)
	{
		ctrl->map->map[i] = set_len(current->row, ctrl->map->len_line);
		if (!ctrl->map->map[i++])
			return (MALLOC);
		current = current->next;
	}
	return (SUCCES);
}
