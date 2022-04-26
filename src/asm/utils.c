/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:42:08 by vhallama          #+#    #+#             */
/*   Updated: 2022/04/26 18:40:48 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include <stdio.h>
#include <errno.h>

void	usage(void)
{
	ft_printf("Usage: ./asm champion_file.s\n");
	ft_printf("		champion_file.s - from assembly to byte code\n");
}

void	parser_error_exit(char *s, int row, int col)
{
	if (errno == 0)
	{
		ft_putstr_fd("Error [", 2);
		ft_putnbr_fd(row, 2);
		ft_putstr_fd(":", 2);
		ft_putnbr_fd(col, 2);
		ft_putstr_fd("]: ", 2);
		ft_putendl_fd(s, 2);
	}
	else
		perror(s);
	exit(1);
}

void	error_exit(char *s)
{
	if (errno == 0)
		ft_putendl_fd(s, 2);
	else
		perror(s);
	exit(1);
}

void	*malloc_safe(size_t size)
{
	void	*mem;

	mem = (void *)malloc(size);
	if (mem == NULL)
		error_exit("Error: malloc");
	bzero(mem, size);
	return (mem);
}
