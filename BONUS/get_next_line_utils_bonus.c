/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 10:23:21 by vde-leus          #+#    #+#             */
/*   Updated: 2022/11/11 16:46:12 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*ft_generate_element(void)
{
	t_list	*element;
	size_t	i;

	i = 0;
	element = (t_list *)malloc(sizeof(t_list));
	if (!element)
		return (NULL);
	element->data = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!element->data)
		return (NULL);
	while (i <= BUFFER_SIZE)
		element->data[i++] = '\0';
	element->next = NULL;
	return (element);
}

t_fdlist	*ft_generate_fd_element(int fd)
{
	t_fdlist	*fd_element;

	fd_element = (t_fdlist *)malloc(sizeof(t_fdlist));
	if (fd < 0)
		return (NULL);
	fd_element->begin = ft_generate_element();
	fd_element->id_fd = fd;
	fd_element->next_fd = NULL;
	return (fd_element);
}

int	ft_fin_ligne(char *str)
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

size_t	ft_liste_size(t_list *liste)
{
	size_t	len;

	if (!liste)
		return (0);
	len = 0;
	while (liste)
	{
		len++;
		liste = liste->next;
	}
	return (len);
}

t_fdlist	*ft_recup_fd_list(t_fdlist **fd_liste, int fd)
{
	t_fdlist	*fd_element;
	t_fdlist	*fd_start;

	if (!fd_liste || !*fd_liste)
		return (NULL);
	fd_start = *fd_liste;
	while (fd_start)
	{
		if (fd_start->id_fd == fd)
			return (fd_start);
		fd_start = fd_start->next_fd;
	}
	fd_element = ft_generate_fd_element(fd);
	fd_start = *fd_liste;
	while (fd_start->next_fd)
		fd_start = fd_start->next_fd;
	fd_start->next_fd = fd_element;
	return (fd_element);
}
