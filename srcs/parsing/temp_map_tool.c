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
	new->row = line;
	new->next = NULL;
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