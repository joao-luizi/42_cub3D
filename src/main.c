/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:52:51 by joaomigu          #+#    #+#             */
/*   Updated: 2025/05/14 17:52:52 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_config	cfg;
	t_app_state	st;

	if (argc != 2)
		return (ft_putstr_fd("Error.\nIncorrect number of arguments.\n", 2), 1);
	if (!argv[1] || !argv[1][0])
		return (ft_putstr_fd("Error.\nEmpty file argument.\n", 2), 1);
	init_config(&cfg);
	cfg.normal_file_path = strtrim_dup(argv[1]);
	if (!cfg.normal_file_path)
		return (1);
	if (!load_configurations(&cfg))
		return (free_config(&cfg, true), 1);
	init_state(&st);
	if (!check_configurations(&cfg, &st))
	{
		free_config(&cfg, true);
		return (free_state(&st), 1);
	}
	free_config(&cfg, false);
	init_window(&st);
	free_state(&st);
	return (0);
}
