/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:53:13 by vde-leus          #+#    #+#             */
/*   Updated: 2022/10/11 12:52:49 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
