/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:01:52 by vde-leus          #+#    #+#             */
/*   Updated: 2022/09/30 16:44:32 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*str_buffer;
static	size_t	len;

int	ft_find(char *str)
{
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (str[i] == '\n' || str[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

void	ft_str_add_char(char *dest, char c)
{
	size_t	i;

	i = 0;
	while (dest[i])
		i++;
	dest[i] = c;
}

void	ft_strcat(char *dest, char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
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

char	*ft_generate_data(int fd)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	str[BUFFER_SIZE] = '\0';
	read(fd, str, sizeof(char) * (BUFFER_SIZE));
	return (str);
}

t_list	*ft_create_elem(void *data)
{
	t_list	*elem1;

	elem1 = (t_list *)malloc(sizeof(t_list));
	elem1->element = data;
	elem1->next = NULL;
	return (elem1);
}

char	*ft_traitement_buffer()
{
	size_t	i;
	char	*resultat;

	i = 0;
	resultat = (char *)malloc((sizeof(char) * (len + 1)));
	ft_memset(resultat, '\0', (len + 1));
	while (str_buffer[i] != '\n' && i < len)
	{	
		resultat[i] = str_buffer[i];
		i++;
	}
	if (str_buffer[i] == '\n')
	{
		str_buffer = (str_buffer + i + 1);
		len = len - (i + 1);
		resultat [i] = '\n';
		return (resultat);
	}
	return (NULL);
}

t_list	*ft_generate_list(int *count, int fd)
{
	char	*str;
	t_list	*begin_list;
	t_list	*start;

	str = ft_generate_data(fd);
	begin_list = ft_create_elem(str);
	start = begin_list;
	while (ft_find(str) == 0)
	{
		str = ft_generate_data(fd);
		begin_list->next = ft_create_elem(str);
		begin_list = begin_list->next;
		*count = *count + 1;
	}
	return (start);
}

void	ft_vider_buffer(char *resultat)
{
	len = 0;
	while (*((char *)str_buffer + len) != '\n'
		&& *((char *)str_buffer + len) != '\0')
		ft_str_add_char(resultat, *((char *)str_buffer + len++));
	ft_str_add_char(resultat, *((char *)str_buffer + len++));
	str_buffer = str_buffer + len;
	len = BUFFER_SIZE - len;
}

char	*get_next_line(int fd)
{
	t_list	*start;
	char	*resultat;
	char	*str_buffer_intermediaire;
	int		count;
	size_t	k;

	count = 1;
	k = 0;
	if (str_buffer != NULL)
	{
		str_buffer_intermediaire = ft_traitement_buffer();
		if (str_buffer_intermediaire != NULL)
			return (str_buffer_intermediaire);
	}
	start = ft_generate_list(&count, fd);
	resultat = (char *)malloc(sizeof(char) * (BUFFER_SIZE * (count + 1) + 1));
	ft_memset(resultat, '\0', (BUFFER_SIZE * (count + 1) + 1));
	if (str_buffer != NULL)
	{
		while (k < len)
			ft_str_add_char(resultat, *((char *)str_buffer + k++));
	}
	while (start->next)
	{
		ft_strcat(resultat, start->element);
		start = start->next;
	}
	str_buffer = start->element;
	ft_vider_buffer(resultat);
	return (resultat);
}

int	main(void)
{
	char	*resultat;
	int		fd;

	fd = open("text.txt", O_RDONLY);
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
