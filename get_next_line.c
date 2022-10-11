/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:02:42 by vde-leus          #+#    #+#             */
/*   Updated: 2022/10/11 13:18:21 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_traitement(char *resultat, t_list **begin)
{
	size_t	j;
	size_t	i;

	j = 0;
	i = 0;
	while (resultat[j])
		j++;
	while ((*begin)->data[i] && (*begin)->data[i] != '\n')
	{	
		resultat[j++] = (*begin)->data[i];
		(*begin)->data[i++] = '\0';
	}
	resultat[j] = (*begin)->data[i];
	if ((*begin)->data[i] == '\n')
		(*begin)->data[i++] = '\0';
	if (resultat[j] == '\n')
		resultat[++j] = '\0';
	j = 0;
	while ((*begin)->data[i])
		(*begin)->data[j++] = (*begin)->data[i++];
	(*begin)->data[j] = '\0';
}

char	*get_next_line(int fd)
{
	static t_list	*begin;
	t_list			*liste;
	char			*resultat;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!begin)
		begin = ft_generate_element();
	liste = ft_generate_liste(&begin, fd);
	if (liste->data[0] == '\0')
	{
		free(liste->data);
		free(liste);
		begin = NULL;
		return (NULL);
	}
	resultat = ft_join(liste);
	ft_traitement(resultat, &begin);
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