/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-tkh <rben-tkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:12:05 by rben-tkh          #+#    #+#             */
/*   Updated: 2022/12/22 15:12:07 by rben-tkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	parsing(int ac, char **av, t_data *data, int len)
{
	char	*strfd;
	int		fd;

	data->mlx = 0;
	data->F_color = 0;
	data->C_color = 0;
	data->map = 0;
	if (ac != 2 || !av)
		return (write(2, "Error\nInvalid arguments\n", 24), -1);
	len = ft_strlen(av[1]);
	if (len < 5 || av[1][len - 1] != 'b' || av[1][len - 2] != 'u'
		|| av[1][len - 3] != 'c' || av[1][len - 4] != '.')
		return (write(2, "Error\nFile is not a .cub\n", 26), -1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (close(fd), write(2, "Error\n", 6), perror(av[1]), -1);
	strfd = init_strfd(fd);
	if (!strfd)
	{
		write(2, "Error\n", 6);
		return (perror(av[1]), free(strfd), close(fd), -1);
	}
	if (init_data(strfd, data, 0, 6) || check_path(data))
		return (close(fd), -1);
	return (close(fd), 0);
}

int	main(int argc, char **argv)
{
	t_data	img;

	img.NO_path = 0;
	img.SO_path = 0;
	img.WE_path = 0;
	img.EA_path = 0;
	if (parsing(argc, argv, &img, 0))
		return (ft_close(&img), -1);
	img.height = 720;
	img.length = 1480;
	img.X = find_x(img.map, &img);
	img.Y = find_y(img.map, &img);
	init_stuff(&img);
	img.key = 0;
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, img.length, img.height, "cub3D");
	img.north = new_pic(&img, 0, 0, 1);
	img.east = new_pic(&img, 0, 0, 2);
	img.west = new_pic(&img, 0, 0, 3);
	img.south = new_pic(&img, 0, 0, 4);
	mlx_hook(img.win, 2, 1L << 0, &press, &img);
	mlx_hook(img.win, 3, 1L << 1, &release, &img);
	mlx_hook(img.win, 17, 0, ft_close, &img);
	mlx_loop_hook(img.mlx, &ray, &img);
	return (mlx_loop(img.mlx), 0);
}
