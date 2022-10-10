/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 11:19:30 by vde-leus          #+#    #+#             */
/*   Updated: 2022/10/10 13:45:30 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_generate_liste(t_list *buffer, int fd)
{
	t_list	*liste;
	t_list	*start;
	t_list	*next;

	start = ft_generate_element();
	printf("adresse de start : %p\n", start);
	liste = start;
	if ((buffer)->data[0] != '\0')
	{
		liste = buffer;
		(buffer)->next = start;
	}
	while (read(fd, start->data, BUFFER_SIZE) > 0)
	{	
		if (ft_endligne(start->data) == 0)
		{
			next = ft_generate_element();
			start->next = next;
			start = next;
		}
		else
			break ;
	}
	if (liste->data[0] == '\0')
		return (NULL);
	return (liste);
}

void	ft_generate_buffer(t_list *liste, t_list **buffer)
{
	t_list	*last;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	last = liste;
	while (last->next)
		last = last->next;
	if (ft_endligne(last->data) == 0)
		return ;
	while (last->data[i] != '\n')
		i++;
	i = i + 1;
	while (last->data[i])
	{
		(*buffer)->data[j++] = last->data[i];
		last->data[i++] = '\0';
	}
}

char	*ft_traitement_buffer(t_list *buffer)
{
	char	*resultat;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	resultat = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!resultat)
		return (NULL);
	ft_memset(resultat, '\0', BUFFER_SIZE + 1);
	while (buffer->data[i] != '\n')
	{
		resultat[i] = buffer->data[i];
		buffer->data[i++] = '\0';
	}
	resultat[i] = buffer->data[i];
	i++;
	resultat[i] = '\0';
	while (buffer->data[i])
	{
		buffer->data[j++] = buffer->data[i];
		buffer->data[i++] = '\0';
	}
	buffer->data[j] = '\0';
	return (resultat);
}

void	ft_clean_data(t_list *liste)
{
	t_list	*begin;
	t_list	*next;

	begin = liste;
	while (begin)
	{
		free(begin->data);
		next = begin->next;
		free(begin);
		begin = next;
	}
}

char	*get_next_line(int fd)
{
	static t_list	*buffer;
	t_list			*liste;
	char			*resultat;
	size_t			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = ft_generate_element();
	if (ft_endligne(buffer->data) == 1)
		return (ft_traitement_buffer(buffer));
	liste = ft_generate_liste(buffer, fd);
	if (liste == NULL)
		return (NULL);
	resultat = ft_strjoin(liste);
	while (resultat[i] && resultat[i] != '\n')
		i++;
	i = i + 1;
	while (resultat[i])
		resultat[i++] = '\0';
	ft_generate_buffer(liste, &buffer);
	ft_clean_data(liste);
	return (resultat);
}	

// int	main(void)
// {
// 	char	*resultat;
// 	int		fd;

// 	fd = open("text.txt", O_RDONLY);
// 	//fd = 0;
// 	resultat = get_next_line(fd);
// 	printf("LE RESULTAT : %s\n", resultat);
// 	resultat = get_next_line(fd);
// 	printf("LE RESULTAT : %s\n", resultat);
// 	resultat = get_next_line(fd);
// 	printf("LE RESULTAT : %s\n", resultat);
// 	resultat = get_next_line(fd);
// 	printf("LE RESULTAT : %s\n", resultat);
// 	resultat = get_next_line(fd);
// 	printf("LE RESULTAT : %s\n", resultat);
// 	resultat = get_next_line(fd);
// 	printf("LE RESULTAT : %s\n", resultat);
// 	resultat = get_next_line(fd);
// 	printf("LE RESULTAT : %s\n", resultat);
// 	resultat = get_next_line(fd);
// 	printf("LE RESULTAT : %s\n", resultat);
// 	resultat = get_next_line(fd);
// 	printf("LE RESULTAT : %s\n", resultat);
// 	resultat = get_next_line(fd);
// 	printf("LE RESULTAT : %s\n", resultat);
// 	resultat = get_next_line(fd);
// 	printf("LE RESULTAT : %s\n", resultat);

// 	return (0);
// }