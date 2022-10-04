/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:55:29 by vde-leus          #+#    #+#             */
/*   Updated: 2022/10/03 11:36:17 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_clean_list(t_list **begin_list)
{
	t_list	*next;

	while (*begin_list)
	{
		next = (*begin_list)->next;
		free((*begin_list)->element);
		free(*begin_list);
		*begin_list = next;
	}
}
