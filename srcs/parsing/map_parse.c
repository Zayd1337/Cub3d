#include "../../includes/cube3d.h"

void	set_orientation(char o, t_ctrl *ctrl)
{
	if (o == 'N')
		ctrl->map->orientation = 0;
	if (o == 'S')
		ctrl->map->orientation = 1;
	if (o == 'E')
		ctrl->map->orientation = 2;
	if (o == 'W')
		ctrl->map->orientation = 3;
}

bool	correct_elems(t_ctrl *ctrl, char **map)
{
	int i;
	int j;
	bool orientation;

	orientation = false;
	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (ft_strchr("10 ", map[j][i]) == NULL)
			{
				if (ft_strchr("EWSN", map[j][i]) == NULL)
					return (printf ("Invalid character has been detected\n"), false);
				orientation = !orientation;//sense passer a true a la 1ere occurence
				if (orientation == false)//si c pas la 1ere fois...
					return (printf ("More than one orientation has been detected\n"), false);
				set_orientation(map[j][i], ctrl);
			}	
			i++;
		}
		j++;
	}
	return (true);
}

//closed/surrounded by walls
bool	check_walls(t_ctrl *ctrl, char **map, int i, int j)
{
	if (i == 0 || j == 0 || i == (int)ctrl->map->len_line - 1 || j == (int)ctrl->map->nb_line - 1)
		return (false);
	if (map[j][i - 1] == ' ')
		return (false);
	if (map[j][i + 1] == ' ')
		return (false);
	if (map[j - 1][i] == ' ')
		return (false);
	if (map[j + 1][i] == ' ')
		return (false);
	if (map[j - 1][i - 1] == ' ')
		return (false);
	if (map[j + 1][i + 1] == ' ')
		return (false);
	if (map[j - 1][i + 1] == ' ')
		return (false);
	if (map[j + 1][i - 1] == ' ')
		return (false);
	return (true);
}

bool	correct_walls(t_ctrl *ctrl, char **map)
{
	int i;
	int j;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == '0' && check_walls(ctrl, map, i, j) == false)
			{
				printf ("\nline %s is KO\n", map[j]);
				ft_putstr_fd("error: Map isn't correctly surrounded by walls\n", 1);
				return (false);
			}
			i++;
		}
		j++;
	}
	printf("\nwalls are OK\n");
	return (true);
}

bool	parse_map(t_ctrl *ctrl)
{
	if (correct_elems(ctrl, ctrl->map->map) == false)
		return (false);
	if (ctrl->map->orientation == -1)
		return (ft_putstr_fd("Missing orientation\n", 1), false);
	if (correct_walls(ctrl, ctrl->map->map) == false)
		return (false);
	return (true);
}