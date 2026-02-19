#include "../../includes/cube3d.h"


//Alors la... j'ai total forget les listes chainees...

t_temp_map	*add_node(char *line)
{
	t_temp_map *new;

	if (!line)
		return (NULL);
	new = NULL;
	if ((new = malloc(sizeof(t_temp_map))) == NULL)
		return (NULL);
	new->row = remove_chars(line, "\n");
	new->next = NULL;
	// printf ("line = %s\n", new->row);
	return (new);
}

//ca peut echouer non?
bool	putlast(t_temp_map **head, char *line)
{
	t_temp_map *current;
	t_temp_map *new;

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
	return (true);
}

void	free_list(t_temp_map **head)
{
	t_temp_map	*next;
	t_temp_map	*current;
	int		size;

	if (!head | !*head)
		return ;
	size = chainlist_size(head);
	current = *head;
	while (size > 0)
	{
		next = current->next;
		free(current);
		current = next;
		size--;
	}
}

int	chainlist_size(t_temp_map **head)
{
	int		size;
	t_temp_map	*current;

	if (!head || !*head)
		return (0);
	current = *head;
	size = 1;
	while (current->next != *head)
	{
		current = current->next;
		size++;
	}
	return (size);
}

void	print_chain(t_temp_map **head)
{
	t_temp_map *current;

	current = *head;
	while (current != NULL)
	{
		printf ("| %s\n", current->row);
		current = current->next;
	}
}


bool	fill_temp_map(t_ctrl *ctrl, int fd)
{
	char *line;
	bool	end_map;
	
	ctrl->map->temp_map = add_node(ctrl->map->map_stock);//init ok
	if (!ctrl->map->temp_map)
		return (false);
	ctrl->map->nb_line++;
	end_map = false;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (end_map == false && !ft_strcmp(line, "\n"))//faut check si y a autre chose apres
		{
			end_map = true;
			free(line);
			continue ;
		}
		if (!end_map && putlast(&ctrl->map->temp_map, line) == false)
			return (free(line), false);
		else if (end_map && ft_strcmp(line, "\n"))
			return (free(line), ft_putstr_fd("There \
				is something after the map\n", 1), false);
		ctrl->map->nb_line++;
		free(line);
	}
	return (true);
}

bool	convert_in_tab(t_ctrl *ctrl)
{
	t_temp_map *current;
	int i;

	if (!ctrl->map || !ctrl->map->temp_map)
		return (false);
	ctrl->map->map = malloc(sizeof(char*) * (ctrl->map->nb_line + 1));
	if (!ctrl->map->map)
		return (false);
	current = ctrl->map->temp_map;
	i = 0;
	while (current)
	{
		ctrl->map->map[i++] = current->row;
		current->row = NULL;
		current = current->next;
	}
	ctrl->map->map[i] = NULL;
	if (ctrl->map->temp_map)
		free_chain(&ctrl->map->temp_map);
	return (true);
}
