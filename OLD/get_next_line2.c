/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:27:04 by vde-leus          #+#    #+#             */
/*   Updated: 2022/10/03 23:47:15 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	long	i;

	if (dst < src)
	{
		i = 0;
		while ((size_t)i < len)
		{
			*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
			i++;
		}
		return (dst);
	}
	else
	{
		i = len - 1;
		while (i >= 0)
		{
			*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
			i--;
		}
		return (dst);
	}
}

t_list	*ft_generate_list(int fd, t_list *buffer)
{
	t_list	*start;
	t_list	*liste;
	t_list	*next;

	start = ft_generate_element();
	liste = start;
	if (buffer->data[0] != '\0')
	{
		liste = buffer;
		liste->next = start;
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
	t_list	*start;
	size_t	i;
	size_t	j;

	buffer = ft_generate_element();
	i = 0;
	j = 0;
	start = liste;
	while (start->data)
		start = start->next;
	if (ft_endligne(start->data) == 1)
	{
		while ((start->data)[i] != '\n')
			i++;
		i++;
		while ((start->data)[i])
		{
			buffer->data[j++] = (start->data)[i];
			(start->data)[i++] = '\0';
		}
	}
	return (buffer);
}

char	*ft_intermediaire(t_list *buffer)
{
	char	*resultat;
	size_t	i;

	i = 0;
	resultat = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	ft_memset(resultat, '\0', BUFFER_SIZE + 1);
	while ((buffer->data)[i] != '\n')
	{
		resultat[i] = (buffer->data)[i];
		i++;
	}
	resultat[i] = (buffer->data)[i];
	i++;
	ft_memmove(buffer->data, buffer->data + i, BUFFER_SIZE + 1 - i);
	return (resultat);
}

char	*get_next_line(int fd)
{
	static t_list	*buffer;
	t_list			*liste;
	char			*resultat;
	size_t			size;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = ft_generate_element();
	if (ft_endligne(buffer->data) == 1)
	{
		resultat = ft_intermediaire(buffer);
		return (resultat);
	}
	liste = ft_generate_list(fd, buffer);
	size = ft_sizelist(liste);
	buffer = ft_generate_buffer(liste);
	resultat = (char *)malloc(sizeof(char) * (BUFFER_SIZE * (size + 1)));
	ft_memset(resultat, '\0', BUFFER_SIZE * (size + 1));
	while (liste->data)
	{
		ft_strjoin(resultat, liste->data);
		liste = liste->next;
	}
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

	return (0);
}

