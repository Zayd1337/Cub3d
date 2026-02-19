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
		return (false);
	if (convert_in_tab(ctrl) == false)//transforme en tab et free la liste chainee d'avant
		return (false);
	// print_map_infos(ctrl);
	return (true);
}

int	check_file(char *name)
{
	int fd;
	char c;

	if (check_mapname(name) == false)
		return (ft_putstr_fd("error: Invalid map name\n", 1), -1);
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("error: File doesn't exist\n", 1), -1);
	if (read(fd, &c, 0) < 0)//verif si dossier
		return (close(fd), ft_putstr_fd(name, 1), ft_putstr_fd(" is a folder\n", 1), -1);
	return (fd);
}

void	print_map_infos(t_ctrl *ctrl)
{
	printf ("-------PRINT INFOS-------\n");
	if (!ctrl->map)
		return ;

	printf("SO : %s\n", ctrl->map->textures[0]);
    printf("NO : %s\n", ctrl->map->textures[1]);
    printf("EA : %s\n", ctrl->map->textures[2]);
    printf("WE : %s\n", ctrl->map->textures[3]);

	printf("F : [%d][%d][%d]\n", ctrl->map->color[0][0],\
		 ctrl->map->color[0][1], ctrl->map->color[0][2]);
	printf("F : [%d][%d][%d]\n", ctrl->map->color[1][0],\
		 ctrl->map->color[1][1], ctrl->map->color[1][2]);

	printf("config_set : %d\n", ctrl->map->config_set);
	printf("nb_line : %d\n", ctrl->map->nb_line);

	int i = 0;
	while (ctrl->map->map[i])
	{
		printf("| %s\n", ctrl->map->map[i]);
		i++;
	}
}

//dispatchers du parsing de l'input
bool	set_data(t_ctrl *ctrl, int argc, char **argv)
{
	int fd;

	if (argc != 2)
		return (printf("error: Wrong number of arguments\n"), false);
	printf ("%s\n", argv[1]);
	if ((fd = check_file(argv[1])) == -1)
		return (printf("error: Invalid file\n"), false);
	if (init_map(ctrl) == false)
		return (printf("map init failde\n"), false);
	if (set_config(ctrl, fd) == false)
		return (printf("Invalid config\n"), false);
	if (set_map(ctrl, fd) == false)
		return (false);
	// if (parse_map(ctrl) == false)
	// 	return (false);
	close(fd);
	return (true);
}
