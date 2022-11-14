/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:53:33 by vde-leus          #+#    #+#             */
/*   Updated: 2022/10/10 17:11:25 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	char			*data;
	struct s_list	*next;
}t_list;

t_list	*ft_generate_element(void);
int		ft_fin_ligne(char *str);
size_t	ft_liste_size(t_list *liste);
t_list	*ft_generate_liste(t_list **begin, int fd);
char	*ft_join(t_list *liste);
void	ft_traitement(char *resultat, t_list **begin);
char	*get_next_line(int fd);

#endif