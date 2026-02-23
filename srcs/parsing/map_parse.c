#include "../../includes/cube3d.h"

//The map must be composed of only 6 possible characters: 0 for an empty space,
//1 for a wall, and N,S,E or W for the player’s start position and spawning
//orientationentation

// bool	clean_line(char *line, char *ok)
// {
// 	int i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (ft_strchr(ok, line[i]) == NULL)
// 			return (false);
// 		i++;
// 	}
// 	return (true);
// }

bool	correct_elems(char **map)
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
			if (ft_strchr("10 ", map[j][i]) == NULL)//si autre
			{
				// printf ("special char : %c\n", map[j][i]);
				if (ft_strchr("EWSN", map[j][i]) == NULL)
					return (printf ("Invalid character has been detected\n"), false);
				orientation = !orientation;//sense passer a true a la 1ere occurence
				// printf ("ori : %d\n", orientation);
				if (orientation == false)//si c pas la 1ere fois...
					return (printf ("More than one orientation has been detected\n"), false);
			}	
			i++;
		}
		j++;
	}
	return (true);
}

// bool	check_walls(t_ctrl *ctrl, char **map, int i, int j)
// {
// 	int j;
// 	int i;

// 	j = 0;
// 	while (map[j])
// 	{
// 		i = 0;
// 		while(map[j][i])
// 		{
// 			if ((!map[j][i - 1] || map[j][i - 1] == ' ') && map[j][i] != '1')
// 				return (false);
// 			if ((!map[j][i + 1] || map[j][i + 1] == ' ') && map[j][i] != '1')
// 				return (false);
// 			if ((!map[j - 1][i] || map[j - 1][i] == ' ') && map[j][i] != '1')
// 				return (false);
// 			if ((!map[j + 1][i] || map[j + 1][i] == ' ') && map[j][i] != '1')
// 				return (false);
// 			i++;
// 		}
// 		j++;
// 	}
// 	return (true);
// }

//closed/surrounded by walls

bool	check_walls(t_ctrl *ctrl, char **map, int i, int j)
{
	//tout le tours de la map
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
	if (correct_elems(ctrl->map->map) == false)
		return (false);
	if (correct_walls(ctrl, ctrl->map->map) == false)
		return (false);
	return (true);
}