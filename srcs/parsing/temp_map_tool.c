#include "../../includes/cube3d.h"

t_temp_map	*add_node(char *line)
{
	t_temp_map	*new;

	if (!line)
		return (NULL);
	new = NULL;
	if ((new = malloc(sizeof(t_temp_map))) == NULL)
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
	if (ctrl->map->len_line < (len = ft_strlen(line)))
		ctrl->map->len_line = len;
	return (true);
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
		else
		{
			if (!end_map && putlast(ctrl, &ctrl->map->temp_map, line) == false)
				return (free(line), MALLOC);
			if (end_map && ft_strcmp(line, "\n"))
				return (free(line), STR_AFTER);
			ctrl->map->nb_line++;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (SUCCES);
}

char	*set_len(char *line, int len)
{
	char	*toret;
	int		i;

	if (len == 0)
		return (NULL);
	toret = malloc(sizeof(char) * (len + 1));
	if (!toret)
		return (NULL);
	i = 0;
	while (*line)
	{
		toret[i++] = *line;
		line++;
	}
	while (i < len)
		toret[i++] = ' ';
	toret[i] = '\0';
	return (toret);
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
