/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:40:08 by vhallama          #+#    #+#             */
/*   Updated: 2022/04/25 16:42:00 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	free_commands(t_commands *commands)
{
	free(commands->name);
	free(commands->comment);
	free(commands->statements);
	free(commands);
}
