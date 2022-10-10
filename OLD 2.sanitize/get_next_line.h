/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:20:09 by vde-leus          #+#    #+#             */
/*   Updated: 2022/10/10 13:38:34 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_list
{
	char			*data;
	struct s_list	*next;
}t_list;

void	*ft_memset(void *b, int c, size_t len);
char	*ft_strjoin(t_list *liste);
int		ft_endligne(char *str);
size_t	ft_sizelist(t_list *begin_list);
t_list	*ft_generate_element(void);

t_list	*ft_generate_liste(t_list *buffer, int fd);
void	ft_generate_buffer(t_list *liste, t_list **buffer);
char	*ft_traitement_buffer(t_list *buffer);
void	ft_clean_data(t_list *liste);
char	*get_next_line(int fd);

#endif
