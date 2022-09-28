/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_champs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rikikyttala <rikikyttala@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:42:23 by rikikyttala       #+#    #+#             */
/*   Updated: 2022/09/28 23:01:13 by rikikyttala      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	add_unordered_champs(t_champ *champs, t_flags *flags)
{
	int		p;
	int		i;
	t_champ	unsorted[MAX_PLAYERS];

	p = -1;
	while (++p < flags->champ_count)
	{
		if (champs[p].playernbr < 0)
			unsorted[ft_abs(champs[p].playernbr) - 1] = champs[p];
	}
	p = 0;
	i = 0;
	while (++p <= flags->champ_count)
	{
		if (flags->used_nbrs[p - 1] == 0)
		{
			champs[p - 1] = unsorted[i];
			champs[p - 1].playernbr = p;
			i++;
		}
	}
}

static void	mark_unordered_champs(t_champ *champs, t_flags *flags)
{
	int	i;
	int	unordered_no;

	i = -1;
	unordered_no = -1;
	while (++i < flags->champ_count)
	{
		if (champs[i].playernbr < 1)
		{
			champs[i].playernbr = unordered_no;
			unordered_no--;
		}
	}
}

/*
** sorts champions according to -n flags given in the program arguments
**
** @champs: array of champions
** @champ_count: the total number of champions
*/
void	sort_champs(t_champ *champs, t_flags *flags)
{
	int		p;
	int		curr;
	t_champ	tmp;

	mark_unordered_champs(champs, flags);
	p = 1;
	while (p <= flags->champ_count)
	{
		curr = champs[p - 1].playernbr;
		if (curr > 0)
		{
			if (curr > flags->champ_count)
				print_error(-8, NULL, &champs[p - 1]);
			if (curr != p)
			{
				tmp = champs[curr - 1];
				champs[curr - 1] = champs[p - 1];
				champs[p - 1] = tmp;
				continue ;
			}
		}
		p++;
	}
	add_unordered_champs(champs, flags);
}
