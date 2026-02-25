#include "../../includes/cube3d.h"

int check_mapname(char *file_name)
{
    int len;

    if (!file_name)
        return (INVALID_FILE);
    len = ft_strlen(file_name);
	if (len < 5)
        return (ft_putstr_fd("Error\nMap name too short\n", 2), INVALID_FILE);
    if (ft_strncmp(file_name + (len - 4), ".cub", 4) == 0)
        return (SUCCES);
    return (ft_putstr_fd("Error\nInvalid map extension\n", 2), INVALID_FILE);
}

//c les maillons les plus loins du main qui maj ctrl->error
int	set_map(t_ctrl *ctrl, int fd)
{
	if ((ctrl->error = fill_temp_map(ctrl, fd)) != SUCCES)
		return (ctrl->error);
	if ((ctrl->error = convert_in_tab(ctrl)) != SUCCES)
		return (ctrl->error);
	return (SUCCES);
}

// bool	is_valid_file(char *path)
// {
// 	int	fd;

// 	if (!path || ft_strlen(path) < 5 || 
// 	    ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 4) != 0)
// 		return (false);
// 	fd = open(path, O_RDONLY);
// 	if (fd < 0)
// 		return (false);
// 	if (read(fd, NULL, 0) < 0) 
// 	{
// 		close(fd);
// 		return (false);
// 	}
// 	close(fd);
// 	return (true);
// }

int	check_file(char *name)
{
	int		fd;
	char	c;

	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (INVALID_FILE);
	if (read(fd, &c, 0) < 0)
		return (close(fd), INVALID_FILE);
	return (fd);
}

int	texture_file_exist(t_ctrl *ctrl)
{
	int i;
	int fd;

	i = 0;
	while (i < 4)
	{
		if ((fd = check_file(ctrl->map->textures[i])) == -1)
		{
			free(ctrl->map->map_stock);
			ctrl->error = INVALID_FILE;
			return (ctrl->error);
		}
		close(fd);//proteger?
		i++;
	}
	return (SUCCES);
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
	else if (error == CONFIG_MISSING)
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

int	parse_data(t_ctrl *ctrl, int argc, char **argv)
{
	int	fd; 
	//ici les fonctions auront deja set ctrl->error
	if (argc != 2)
		return (printf("nb args\n"), (ctrl->error = INVALID_INPUT), ctrl->error);
	if (check_mapname(argv[1]) != SUCCES)
		return (printf("map name\n"), ctrl->error);
	if ((fd = check_file(argv[1])) == INVALID_FILE)
		return (printf("bad file\n"), (ctrl->error = INVALID_FILE), ctrl->error);
	if (init_map(ctrl, argv[1]) != SUCCES)
		return (printf("init map\n"), close(fd), ctrl->error);
	if (set_config(ctrl, fd) != SUCCES)
		return (printf("set_config\n"), close(fd), ctrl->error);
	if (texture_file_exist(ctrl) != SUCCES)
		return (printf("texture file\n"), close(fd), ctrl->error);
	if (set_map(ctrl, fd) != SUCCES)
		return (printf("set map\n"), close(fd), ctrl->error);
	if (parse_map(ctrl) != SUCCES)
		return (printf("parse\n"), close(fd), ctrl->error);
	print_map_infos(ctrl);
	return (printf("succes\n"), close(fd), SUCCES);
}
