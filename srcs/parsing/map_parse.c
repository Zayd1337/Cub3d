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
	int	i;
	int	j;
	int	player;

	player = 0;
	j = -1;
	while (map[++j])
	{
		i = -1;
		while (map[j][++i])
		{
			if (!ft_strchr("10 EWSN", map[j][i]))
				return (ft_putstr_fd("Error\nInvalid char in map\n", 2), false);
			if (ft_strchr("EWSN", map[j][i]))
			{
				if (++player > 1)
					return (ft_putstr_fd("Error\nMultiplayer is not allowed\n",
							1), false);
				set_orientation(map[j][i], ctrl);
			}
		}
	}
	if (player == 0)
		return (ft_putstr_fd("Error\nNo spawn point detected\n", 1), false);
	return (true);
}

// closed/surrounded by walls
bool	check_walls(t_ctrl *ctrl, char **map, int i, int j)
{
	if (i == 0 || j == 0 || i == (int)ctrl->map->len_line - 1
		|| j == (int)ctrl->map->nb_line - 1)
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
	int	i;
	int	j;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (ft_strchr("0NSEW", map[j][i]) && check_walls(ctrl, map, i,
					j) == false)
				return (ft_putstr_fd("Error\nMap isn't correctly enclosed\n",
						1), false);
			i++;
		}
		j++;
	}
	return (true);
}

bool	parse_map(t_ctrl *ctrl)
{
	if (correct_elems(ctrl, ctrl->map->map) == false)
		return (false);
	if (ctrl->map->orientation == -1)
		return (ft_putstr_fd("Missing player\n", 1), false);
	if (correct_walls(ctrl, ctrl->map->map) == false)
		return (false);
	return (true);
}