#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>

#define BUFFER_SIZE 10000

typedef struct s_gnlque
{
	char *buf;
	int f;
	int r;
	int m;
} t_gnlque;

typedef struct s_gnl_node
{
	char c;
	struct s_gnl_node *next;
} t_gnl_node;

int producer(int fd, t_gnlque *q)
{
	int n;
    int i;


	printf("producer\n");
	if (q->r == q->f)
	{
		n = read(fd, &q->buf[q->r], BUFFER_SIZE);
	
		//for(int i = q->r; i < BUFFER_SIZE + 1; i++ )
		//{
		//	printf("%d", q->buf[i]);
		//}
		i = 0;
		// if (n == 0)
		// {	q->r = q->r - 1;}
		while (i < n)
		{
			printf("%d ", q->buf[q->r]);
		    q->r = (q->r + 1) % q->m;
			i++;
		}
		printf("\n");
	}
	else
		n = q->r - q->f;
	return (n);
}

void init_que(t_gnlque *q, char *buf)
{
	if (buf == NULL)
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	q->buf = buf;
	q->f = 0;
	q->r = 0;
	q->m = BUFFER_SIZE + 1;
}

void *consumer2(int read_size, t_gnlque *q, t_gnl_node *head)
{
	t_gnl_node	*new_lst;
	int			i;
    
    if (read_size == 0)
        return (head);
	i = 0;
	printf("consumer head\n");
	while (q->f != q->r && head->c != '\n' && i < read_size)
	{
		new_lst = (t_gnl_node *)malloc(sizeof(t_gnl_node));
		new_lst->c = q->buf[q->f];
		new_lst->next = head;
		head = new_lst;
		q->f = ((q->f + 1) % q->m);
		printf("%d ", head->c);
		i++;
	}
	printf("\n");
	return (head);
}

char    *create_str(t_gnl_node *head)
{
    int size;
    char    *str;
    t_gnl_node  *tmp;
	int	i;
    
    tmp = head;
	size = 0;
    while (tmp->next != NULL)
    {    
        size++;
        tmp = tmp->next;
    }
    printf("create str size: %d\n", size);
    str = malloc(sizeof(char) * (size + 1));
	i = 0;
    while (i < size)
    {
        str[size - (i + 1)] = head->c;
		i++;
		tmp = head;
		head = head->next;
		free(tmp);
    }
	str[i] = head->c;
	for (int i = 0; i < size + 1; i++ )
	{
		printf("%d ", str[i]);
	}
		printf("\n");
	free(head);
	return (str);
}

char	*dengling(char *result)
{
	free(result);
	result = NULL;
	return (result);
}

char *get_next_line(int fd)
{
	int read_size;
	static t_gnlque q;
	t_gnl_node *head;
	char    *result;
    int     eof;

	init_que(&q, q.buf);
	head = (t_gnl_node *)malloc(sizeof(t_gnl_node));
    head->c = '\0';
    head->next = NULL;
    eof = 0;
	while (head->c != '\n' && eof == 0)
	{
	    read_size = producer(fd, &q);
	    if (read_size == 0)
		    eof = 1;
	    head = consumer2(read_size, &q, head);
	    //printf("%d\n", head->c);
	}
	result = create_str(head);
	free(q.buf);
	q.buf = NULL;
	//if (*result == '\0')
	//	result = dengling(result);
	return (result);
}
