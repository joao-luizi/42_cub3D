#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_config cfg;

	if (argc != 2)
		return (ft_putstr_fd("Error.\nIncorrect number of arguments.\n", 2), 1);
	if (!argv[1] || !argv[1][0])
		return (ft_putstr_fd("Error.\nEmpty file argument.\n", 2), 1);
	init_config(&cfg);
	cfg.normal_file_path = strtrim_dup(argv[1]);
	if (!cfg.normal_file_path)
		return (1);
	if (!load_configurations(&cfg))
		return (free_config(&cfg), 1);
	free_config(&cfg);
	return (0);
}