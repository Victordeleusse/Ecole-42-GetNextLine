/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-leus <vde-leus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:10:05 by vde-leus          #+#    #+#             */
/*   Updated: 2022/09/29 14:43:41 by vde-leus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// int	*ft_test_int(int i, size_t len, size_t *len_tot)
// {
// 	int	k;
// 	int	*resultat;

// 	k = 0;
// 	resultat = (int *)malloc(sizeof(int) * (len + 1));
// 	while (k < len)
// 		resultat[k++] = i++;
// 	resultat[k] = '0';
// 	*len_tot = len + 1;
// 	return (resultat);
// }


// int	main(void)
// {
// 	int		fd;
// 	size_t	len_tot;
// 	int		*resultat;

// 	/* create or open and write */

// 	resultat = ft_test_int(1, 9, &len_tot);
// 	printf("%d\n", len_tot);
// 	fd = open("my_file_test.txt", O_CREAT | O_WRONLY, 0700);
// 	if (fd == -1)
// 	{
// 		printf("Failed to create or open the file\n");
// 		exit(1);
// 	}
// 	write(fd, resultat, sizeof(int) * len_tot);
// 	close(fd);

// 	/* read */

// 	fd = open("my_file_test.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("Failed to open and read the file\n");
// 		exit(1);
// 	}
// 	read(fd, resultat, sizeof(int) * len_tot);
// 	printf("%d\n", read(fd, resultat, sizeof(int) * len_tot));
// 	close(fd);
// 	return (0);
// }


// char	*ft_test_char1(char c, size_t len, size_t *len_tot)
// {
// 	size_t	k;
// 	char	*str;

// 	k = 0;
// 	str = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!str)
// 		return (NULL);
// 	while (k < len)
// 	{
// 		str[k] = c;
// 		k++;
// 		c++;
// 	}
// 	str[2] = '\n';
// 	str[3] = '\n';
// 	str[k] = '\0';
// 	*len_tot = k + 1;
// 	return (str);
// }


// int	main(void)
// {
// 	int		fd;
// 	size_t	len_tot;
// 	char	*resultat;
// 	char	test[] = "oo";

// 	/* create or open and write */

// 	resultat = ft_test_char1('a', 10, &len_tot);
// 	//printf("%d\n", len_tot);
// 	//printf("%s\n", resultat);
// 	fd = open("my_file_test.txt", O_CREAT | O_WRONLY, 0700);
// 	if (fd == -1)
// 	{
// 		printf("Failed to create or open the file\n");
// 		exit(1);
// 	}
// 	write(fd, resultat, sizeof(char) * len_tot);
// 	close(fd);

// 	/* read */

// 	fd = open("my_file_test.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("Failed to open and read the file\n");
// 		exit(1);
// 	}
// 	read(fd, test, sizeof(char) * 2);
// 	printf("%s\n", test);
// 	//printf("%d\n", read(fd, resultat, sizeof(char) * 2));
// 	close(fd);
// 	return (0);
// }

// static int	var;

// void	ft_multi(void)
// {
// 	var++;
// }

// int	main(void)
// {
// 	ft_multi();
// 	ft_multi();
// 	ft_multi();
// 	var = var * 5;
// 	ft_multi();
// 	printf("%d\n", var);
// 	return (0);
// }

