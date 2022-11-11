/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 10:41:12 by vde-leus          #+#    #+#             */
/*   Updated: 2022/11/11 18:41:38 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_generate_liste(t_list **begin, int fd)
{
	t_list	*liste;
	t_list	*suivant;

	if (!*begin)
		return (NULL);
	liste = *begin;
	if ((*begin)->data[0] != '\0')
	{	
		if (ft_fin_ligne((*begin)->data) == 1)
			return (liste);
		suivant = ft_generate_element();
		(*begin)->next = suivant;
		*begin = suivant;
	}
	while (read(fd, (*begin)->data, BUFFER_SIZE) > 0
		&& ft_fin_ligne((*begin)->data) == 0)
	{	
		suivant = ft_generate_element();
		(*begin)->next = suivant;
		(*begin) = suivant;
	}
	return (liste);
}

// t_list	*_my_lst(void)
// {
// 	static t_list	lst;

// 	return (&lst);
// }

/* Mise en place d'une garbage -> recuperation de toutes les adresses
des elements que je veux free. Une fois recupere sous la forme de liste 
ou autre -> ft_free_list.
*/

// void	*ft_malloc(int size, t_list **lst)
// {
// 	void	*output;

// 	output = malloc(size);
// 	lst_addback(lst, lstnew(&output);
// 	return (output);	
// }

char	*ft_join(t_list *liste)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*resultat;
	t_list	*suivant;

	len = ft_liste_size(liste);
	resultat = (char *)malloc(sizeof(char) * (len * BUFFER_SIZE + 1));
	if (!resultat)
		return (NULL);
	resultat[len * BUFFER_SIZE] = '\0';
	j = 0;
	while (liste->next)
	{
		i = 0;
		while (liste->data[i])
			resultat[j++] = liste->data[i++];
		free(liste->data);
		suivant = liste->next;
		free(liste);
		liste = suivant;
	}
	resultat[j] = '\0';
	return (resultat);
}

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

void	ft_clear(t_fdlist **fd_liste, t_fdlist *fd_element)
{
	t_fdlist	*start;

	start = *fd_liste;
	if (start->id_fd == fd_element->id_fd)
	{	
		*fd_liste = start->next_fd;
		free(start->begin->data);
		free(start->begin);
		free(start);
	}
	else
	{
		while (start->next_fd->id_fd != fd_element->id_fd)
			start = start->next_fd;
		start->next_fd = fd_element->next_fd;
		free(fd_element->begin->data);
		free(fd_element->begin);
		free(fd_element);
	}
}

char	*get_next_line(int fd)
{
	static t_fdlist	*fd_liste;
	t_fdlist		*fd_element;
	t_list			*liste;
	char			*resultat;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!fd_liste)
		fd_liste = ft_generate_fd_element(fd);
	fd_element = ft_recup_fd_list(&fd_liste, fd);
	liste = ft_generate_liste(&fd_element->begin, fd);
	resultat = ft_join(liste);
	ft_traitement(resultat, &fd_element->begin);
	if (resultat[0] == '\0')
	{
		ft_clear(&fd_liste, fd_element);
		free(resultat);
		return (NULL);
	}
	return (resultat);
}

// int	main(void)
// {
// 	char	*resultat;
// 	int		fd1;
// 	int		fd2;

// 	fd1 = open("text.txt", O_RDONLY);
// 	fd2 = open("text2.txt", O_RDONLY);
// 	//fd = 0;
// 	resultat = get_next_line(fd1);
// 	printf("LE RESULTAT venant de 1 : %s\n", resultat);
// 	free(resultat);
//	
// 	resultat = get_next_line(fd1);
// 	printf("LE RESULTAT venant de 1 : %s\n", resultat);
// 	free(resultat);
//	
// 	resultat = get_next_line(fd2);
// 	printf("LE RESULTAT venant de 2 : %s\n", resultat);
// 	free(resultat);
//	
// 	resultat = get_next_line(fd1);
// 	printf("LE RESULTAT  venant de 1: %s\n", resultat);
// 	free(resultat);
//	
// 	resultat = get_next_line(fd1);
// 	printf("LE RESULTAT  venant de 1: %s\n", resultat);
// 	free(resultat);
//	
// 	resultat = get_next_line(fd2);
// 	printf("LE RESULTAT  venant de 2: %s\n", resultat);
// 	free(resultat);
//	
// 	resultat = get_next_line(fd2);
// 	printf("LE RESULTAT  venant de 2: %s\n", resultat);
// 	free(resultat);
//	
// 	resultat = get_next_line(fd2);
// 	printf("LE RESULTAT  venant de 2: %s\n", resultat);
// 	free(resultat);
//	
// 	resultat = get_next_line(fd2);
// 	printf("LE RESULTAT  venant de 2: %s\n", resultat);
// 	free(resultat);
//	
// 	resultat = get_next_line(fd2);
// 	printf("LE RESULTAT  venant de 2: %s\n", resultat);
// 	free(resultat);
//	
// 	resultat = get_next_line(fd1);
// 	printf("LE RESULTAT  venant de 1: %s\n", resultat);
// 	free(resultat);
//	
// 	resultat = get_next_line(fd1);
// 	printf("LE RESULTAT  venant de 1: %s\n", resultat);
// 	free(resultat);
//	
// 	resultat = get_next_line(fd1);
// 	printf("LE RESULTAT  venant de 1: %s\n", resultat);
// 	free(resultat);
//	
// 	resultat = get_next_line(fd2);
// 	printf("LE RESULTAT  venant de 2: %s\n", resultat);
// 	free(resultat);
//	
// 	resultat = get_next_line(fd2);
// 	printf("LE RESULTAT  venant de 2: %s\n", resultat);
// 	free(resultat);
//	
// 	resultat = get_next_line(fd2);
// 	printf("LE RESULTAT  venant de 2: %s\n", resultat);
// 	free(resultat);
//	
// 	resultat = get_next_line(fd1);
// 	printf("LE RESULTAT  venant de 1: %s\n", resultat);
// 	free(resultat);
//	
// 	resultat = get_next_line(fd1);
// 	printf("LE RESULTAT  venant de 1: %s\n", resultat);
// 	free(resultat);
//	
// 	resultat = get_next_line(fd1);
// 	printf("LE RESULTAT  venant de 1: %s\n", resultat);
// 	free(resultat);
//	
// 	resultat = get_next_line(fd1);
// 	printf("LE RESULTAT  venant de 1: %s\n", resultat);
// 	free(resultat);

// 	return (0);
// }