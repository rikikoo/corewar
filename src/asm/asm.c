/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 13:18:25 by vhallama          #+#    #+#             */
/*   Updated: 2022/04/25 15:11:32 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

int	main(int argc, char **argv)
{
	if (argc == 2 && !ft_strcmp(ft_strchr(argv[1], '\0') - 2, ".s"))
		assemble(argv[1]);
	else
		usage();
	return (0);
}
