/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhallama <vhallama@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:04:41 by vhallama          #+#    #+#             */
/*   Updated: 2022/05/03 12:07:07 by vhallama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "op.h"

void	null_comment(char *s)
{
	char	*p;

	p = ft_strchr(s, COMMENT_CHAR);
	if (p)
		*p = '\0';
}

void	skip_whitespace(char *s, size_t *i)
{
	while (s[*i] && (!ft_isprint(s[*i]) || s[*i] == ' '))
		(*i)++;
}
