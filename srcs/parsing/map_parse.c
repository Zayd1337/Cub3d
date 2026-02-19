// #include "../../includes/cube3d.h"

// //The map must be composed of only 6 possible characters: 0 for an empty space,
// //1 for a wall, and N,S,E or W for the player’s start position and spawning
// //orientation

// bool	correct_elems(char **map)
// {
// 	int i;
// 	int j;
// 	bool ori;

// 	ori = false;
// 	j = 0;
// 	while (map[j])
// 	{
// 		i = 0;
// 		while (map[j][i])
// 		{
// 			if (ft_strchr("10 ", map[j][i]) == NULL)//si autre
// 			{
// 				if (ft_strchr("EWSN", map[j][i]) == NULL)
// 					return (false);
// 				ori = !ori;//sense passer a true a la 1ere occurence
// 				if (ori == false)//si c pas la 1ere fois...
// 					return (false);
// 			}	
// 			i++;
// 		}
// 		j++;
// 	}
// 	return (true);
// }

// void	check_walls(t_ctrl *ctrl, char **map, int i, int j)
// {
// 	//back tracking

// }

// //closed/surrounded by walls

// bool	correct_walls(t_ctrl *ctrl, char **map)
// {
// 	if ()
// }

// bool	parse_map(t_ctrl *ctrl)
// {
// 	if (correct_elems(ctrl->map->map) == false)
// 		return (false);
// 	if (correct_walls(ctrl->map->map) == false)
// 		return (false);
// 	return (true);
// }