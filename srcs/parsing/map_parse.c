#include "../../includes/cube3d.h"

void	set_player(char o, t_ctrl *ctrl, int i, int j)
{
	if (o == 'N')
		ctrl->map->orientation = 0;
	if (o == 'S')
		ctrl->map->orientation = 1;
	if (o == 'E')
		ctrl->map->orientation = 2;
	if (o == 'W')
		ctrl->map->orientation = 3;
	ctrl->player.x = (float)i;
	ctrl->player.y = (float)j;
}

int	correct_elems(t_ctrl *ctrl, char **map)
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
				return ((ctrl->error = INVALID_CHAR), ctrl->error);
			if (ft_strchr("EWSN", map[j][i]))
			{
				if (++player > 1)
					return ((ctrl->error = MULTIPLAYER), ctrl->error);
				set_player(map[j][i], ctrl, i, j);
			}
		}
	}
	if (player == 0)
		return ((ctrl->error = PLAYER_MISSING), ctrl->error);
	return (SUCCES);
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

int	correct_walls(t_ctrl *ctrl, char **map)
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
				return ((ctrl->error = INVALID_WALLS), ctrl->error);
			i++;
		}
		j++;
	}
	return (SUCCES);
}

int	parse_map(t_ctrl *ctrl)
{
	if (correct_elems(ctrl, ctrl->map->map) != SUCCES)
		return (ctrl->error);
	if (correct_walls(ctrl, ctrl->map->map) != SUCCES)
		return (ctrl->error);
	return (SUCCES);
}