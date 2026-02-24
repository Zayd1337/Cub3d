#include "../../includes/cube3d.h"

bool	check_mapname(char *file_name)
{
	int	last;

	if (!file_name)
		return (1);
	last = ft_strlen(file_name) - 1;
	if (file_name[last] == 'b' && file_name[last - 1] == 'u' && file_name[last
		- 2] == 'c' && file_name[last - 3] == '.')
		return (true);
	return (false);
}

bool	set_map(t_ctrl *ctrl, int fd)
{
	if (fill_temp_map(ctrl, fd) == false)
		return (false);//free(ctrl->map->map_stock), 
	// free(ctrl->map->map_stock);
	if (convert_in_tab(ctrl) == false)
		return (false);
	return (true);
}

int	check_file(char *name)
{
	int		fd;
	char	c;

	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("error: File doesn't exist\n", 1), -1);
	if (read(fd, &c, 0) < 0)
		return (close(fd), ft_putstr_fd(name, 1), ft_putstr_fd(" is a folder\n",
				1), -1);
	return (fd);
}

bool	parse_data(t_ctrl *ctrl, int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		return (printf("error: Wrong number of arguments\n"), false);
	if (check_mapname(argv[1]) == false)
		return (ft_putstr_fd("error: Invalid map name\n", 1), false);
	if ((fd = check_file(argv[1])) == -1)
		return (printf("error: Invalid file\n"), false);
	if (init_map(ctrl, argv[1]) == false)
		return (close(fd), printf("map init failde\n"), false);
	if (set_config(ctrl, fd) == false)
		return (close(fd), printf("Invalid config\n"), false);
	if (set_map(ctrl, fd) == false)
		return (close(fd), false);
	if (parse_map(ctrl) == false)
		return (close(fd), false);
	print_map_infos(ctrl);
	return (close(fd), true);
}
