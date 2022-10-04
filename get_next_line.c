/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 11:19:30 by vde-leus          #+#    #+#             */
/*   Updated: 2022/10/04 15:43:21 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_generate_liste(t_list *buffer, int fd)
{
	t_list	*liste;
	t_list	*start;
	t_list	*next;

	start = ft_generate_element();
	liste = start;
	if ((buffer)->data[0] != '\0')
	{
		liste = buffer;
		(buffer)->next = start;
	}
	read(fd, start->data, BUFFER_SIZE);
	while (ft_endligne(start->data) == 0)
	{
		next = ft_generate_element();
		start->next = next;
		start = next;
		read(fd, start->data, BUFFER_SIZE);
	}
	return (liste);
}

t_list	*ft_generate_buffer(t_list *liste)
{
	t_list	*buffer;
	t_list	*last;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	buffer = ft_generate_element();
	last = liste;
	while (last->next)
		last = last->next;
	if (ft_endligne(last->data) == 0)
		return (buffer);
	while (last->data[i] != '\n')
		i++;
	i = i + 1;
	while (last->data[i])
	{
		buffer->data[j++] = last->data[i];
		last->data[i++] = '\0';
	}
	return (buffer);
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

char	*get_next_line(int fd)
{
	static t_list	*buffer;
	t_list			*liste;
	char			*resultat;
	size_t			i;

	i = 0;
	if (!buffer)
		buffer = ft_generate_element();
	//printf("Contenu du buffer : %s\n", buffer->data);
	if (ft_endligne(buffer->data) == 1)
	{
		resultat = ft_traitement_buffer(buffer);
		return (resultat);
	}
	liste = ft_generate_liste(buffer, fd);
	resultat = ft_strjoin(liste);
	//printf("le resultat doit etre : %s\n", resultat);
	while (resultat[i] && resultat[i] != '\n')
		i++;
	i = i + 1;
	while (resultat[i])
		resultat[i++] = '\0';
	buffer = ft_generate_buffer(liste);
	return (resultat);
}	

int	main(void)
{
	char	*resultat;
	int		fd;

	fd = open("text.txt", O_RDONLY);
	//fd = 0;
	resultat = get_next_line(fd);
	printf("LE RESULTAT : %s\n", resultat);
	resultat = get_next_line(fd);
	printf("LE RESULTAT : %s\n", resultat);
	resultat = get_next_line(fd);
	printf("LE RESULTAT : %s\n", resultat);
	resultat = get_next_line(fd);
	printf("LE RESULTAT : %s\n", resultat);
	resultat = get_next_line(fd);
	printf("LE RESULTAT : %s\n", resultat);
	resultat = get_next_line(fd);
	printf("LE RESULTAT : %s\n", resultat);
	resultat = get_next_line(fd);
	printf("LE RESULTAT : %s\n", resultat);
	resultat = get_next_line(fd);
	printf("LE RESULTAT : %s\n", resultat);
	resultat = get_next_line(fd);
	printf("LE RESULTAT : %s\n", resultat);
	resultat = get_next_line(fd);
	printf("LE RESULTAT : %s\n", resultat);
	resultat = get_next_line(fd);
	printf("LE RESULTAT : %s\n", resultat);

	return (0);
}

