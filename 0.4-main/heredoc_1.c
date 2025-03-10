/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 00:32:55 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/04 23:10:46 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
// #include <stdlib.h>
// #include "analysis.h"

// void    close_fd(int fd)
// {
// 	if (close(fd) == -1)
// 		exit(EXIT_FAILURE);
// }

// void    handle_heredoc_child(int write_fd, char *delimeter)
// {
// 	char *line;

// 	close_fd(write_fd - 1);
// 	printf("close : %d\n", write_fd - 1);
// 	printf("write_fd : %d\n", write_fd);
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line || ft_strncmp(line, delimeter, ft_strlen(line)) == 0)
// 		{
// 			free(line);
// 			break;
// 		}
// 		write(write_fd, line, ft_strlen(line));
// 		write(write_fd, "\n", 1);
// 		free(line);
// 	}
// 	close_fd(write_fd);
// 	exit(0);
// }

// void    create_heredoc_pipe(int *read_fd, int *write_fd)
// {
// 	int fd[2];

// 	if (pipe(fd) == -1)
// 		exit(EXIT_FAILURE);
// 	*read_fd = fd[0];
// 	*write_fd = fd[1];
// }

// void    handle_heredoc_parent(t_redrct *rdrct, int read_fd, int write_fd)
// {
// 	int status;

// 	close_fd(write_fd);
// 	rdrct->fd = read_fd;
// 	printf("??? : %d\n", rdrct->fd);
// 	if (wait(&status) == -1)
// 		exit(EXIT_FAILURE);
// 	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
// 		exit(EXIT_FAILURE);
// }

// void	f_heredoc(t_redrct *rdrct)
// {
// 	pid_t pid;
// 	int	read_fd;
// 	int	write_fd;

// 	create_heredoc_pipe(&read_fd, &write_fd);
// 	pid = fork();
// 	if (pid == -1)
// 		exit(EXIT_FAILURE);
// 	if (pid == 0)
// 		handle_heredoc_child(write_fd, rdrct->obj);
// 	else
// 		handle_heredoc_parent(rdrct, read_fd, write_fd);
// }
