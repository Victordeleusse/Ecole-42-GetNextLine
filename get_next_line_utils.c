/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 12:11:00 by vde-leus          #+#    #+#             */
/*   Updated: 2022/10/04 16:42:58 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(t_list *liste)
{
	t_list	*begin;
	char	*resultat;
	size_t	size_liste;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	begin = liste;
	if (!liste)
		return (NULL);
	size_liste = ft_sizelist(liste);
	resultat = (char *)malloc(sizeof(char) * (BUFFER_SIZE * size_liste + 1));
	if (!resultat)
		return (NULL);
	ft_memset(resultat, '\0', BUFFER_SIZE * size_liste + 1);
	while (begin)
	{
		while (begin->data[j])
			resultat[i++] = begin->data[j++];
		begin = begin->next;
		j = 0;
	}
	return (resultat);
}

int	ft_endligne(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_sizelist(t_list *begin_list)
{
	size_t	len_list;

	if (!begin_list)
		return (0);
	len_list = 0;
	while (begin_list)
	{
		len_list++;
		begin_list = begin_list->next;
	}
	return (len_list);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	if (!b)
		return (NULL);
	i = 0;
	while (i < len)
	{
		*(unsigned char *)(b + i) = (unsigned char)c;
		i++;
	}
	return (b);
}

t_list	*ft_generate_element(void)
{
	t_list	*element;

	element = (t_list *)malloc(sizeof(t_list));
	if (!element)
		return (NULL);
	element->data = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!element->data)
		return (NULL);
	ft_memset(element->data, '\0', BUFFER_SIZE + 1);
	element->next = NULL;
	return (element);
}
