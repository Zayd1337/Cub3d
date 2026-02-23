#include "../../includes/cube3d.h"

bool	check_mapname(char *file_name)
{
	int	last;

	if (!file_name)
		return (1);
	last = ft_strlen(file_name) - 1;
	if (file_name[last] == 'b' && file_name[last - 1] == 'u'
		&& file_name[last - 2] == 'c' && file_name[last - 3] == '.')
		return (true);
	return (false);
}

bool	set_map(t_ctrl *ctrl, int fd)
{
	if (fill_temp_map(ctrl, fd) == false)//creer une liste chainee contenant les lignes de la map
		return (free(ctrl->map->map_stock), false);
	free(ctrl->map->map_stock);
	if (convert_in_tab(ctrl) == false)//transforme en tab et free la liste chainee d'avant
		return (false);
	return (true);
}

int	check_file(char *name)
{
	int fd;
	char c;

	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("error: File doesn't exist\n", 1), -1);
	if (read(fd, &c, 0) < 0)//verif si dossier
		return (close(fd), ft_putstr_fd(name, 1), ft_putstr_fd(" is a folder\n", 1), -1);
	return (fd);
}

//dispatchers du parsing de l'input
bool	parse_data(t_ctrl *ctrl, int argc, char **argv)
{
	int fd;

	if (argc != 2)
		return (printf("error: Wrong number of arguments\n"), false);
	printf ("%s\n", argv[1]);
	if (check_mapname(argv[1]) == false)
		return (ft_putstr_fd("error: Invalid map name\n", 1), -1);
	if ((fd = check_file(argv[1])) == -1)
		return (printf("error: Invalid file\n"), false);
	if (init_map(ctrl) == false)
		return (close(fd), printf("map init failde\n"), false);
	if (set_config(ctrl, fd) == false)
		return (close(fd), printf("Invalid config\n"), false);
	if (set_map(ctrl, fd) == false)
		return (close(fd), false);
	print_map_infos(ctrl);
	if (parse_map(ctrl) == false)
		return (close(fd), false);
	return (close(fd), true);
}
