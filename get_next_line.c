// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   get_next_line.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mnoskov <marvin@42.fr>                     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2018/05/11 15:54:16 by mnoskov           #+#    #+#             */
// /*   Updated: 2018/05/11 15:54:20 by mnoskov          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */


#include "get_next_line.h"

int				i_nl(char **str)
{
	int 		index;

	index = 0;
	while ((*str)[index] && (*str)[index] != '\n')
		index++;
	return (index);
}

int				is_written(char **mem, char **line)
{
	int 		index;
	char 		*trash;

	index = i_nl(mem);
	trash = *mem;
	if ((*mem)[0] == '\n')										
	{		
		*line = ft_strdup("\0");													
		*mem = ft_strsub(*mem, index + 1, ft_strlen(*mem) - index);	
			free(trash);
			return (1);											
	}															
	else															
		*line = ft_strsub(*mem, 0, index);
	*mem = ft_strsub(*mem, index + 1, ft_strlen(*mem) - index);
	free(trash);
	return (ft_strlen(*line) > 0 ? 1 : 0);
}

int				get_next_line(const int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	static char *mem[400];
	char 		*trash;
	int			bytes;

	if (read(fd, buff, 0) < 0)
		return (-1);
	if(!mem[fd])
		mem[fd] = ft_strdup("\0");
	while ((bytes = read(fd, buff, BUFF_SIZE))> 0)
	{	

		buff[bytes] = '\0';
		trash = mem[fd];
		mem[fd] = ft_strjoin(trash, buff);
		free(trash);
		if (mem[fd] && ft_strchr(mem[fd], '\n'))
			break; 
	}
	if (mem[fd][0] == '\0')
		return (0);
	bytes = is_written(&mem[fd], line);
	return (bytes);
}

// int		main(int argc, char **argv)
// {
// 	int fd;
// 	int fd1;

// 	char *line;
	
// 	fd = open("/Users/mnoskov/Projects/get_next_line/a", O_RDONLY);
// 	fd1 = open("/Users/mnoskov/Projects/get_next_line/b", O_RDONLY);

// 	if(get_next_line(fd, &line))
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 	}
// 	if(get_next_line(fd, &line))
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 	}
// 	while(get_next_line(fd1, &line))
// 	{
// 		printf("%s\n", line);
// 		free (line);
// 	}
// 	system ("leaks a.out");
// }

