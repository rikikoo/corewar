/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:53:32 by vhallama          #+#    #+#             */
/*   Updated: 2022/05/02 16:13:34 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"

int	char_in_label_chars(char s)
{
	size_t	i;

	i = 0;
	while (LABEL_CHARS[i])
	{
		if (s == LABEL_CHARS[i])
			return (1);
		i++;
	}
	return (0);
}
