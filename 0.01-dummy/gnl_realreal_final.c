#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>

#define BUFFER_SIZE 3

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

    i = 0;
	if (q->r == q->f)
	{
	    //q->r++;//원래는 (r + 1) % m이 맞지만 생략함
        //이러허게 하면 r이랑 f가 3일때 오류가 발생하므로 수정함
        q->r = (q->r + 1) % q->m;
		n = read(fd, &q->buf[q->r], BUFFER_SIZE);
		//todo: if (n == 0)
		// 	q->r = q->r - 1;
		while (i < n - 1)
		{
		    q->r = (q->r + 1) % q->m;
			i++;
		}
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
	while (q->f != q->r && head->c != '\n' && i < read_size)
	{
		new_lst = (t_gnl_node *)malloc(sizeof(t_gnl_node));
		q->f = ((q->f + 1) % q->m);
		new_lst->c = q->buf[q->f];
		new_lst->next = head;
		head = new_lst;
		i++;
	}
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
    printf("size: %d\n", size);
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
	    printf("%d\n", (int)head->c);
	}
	result = create_str(head);
	//if (*result == '\0')
	//	result = dengling(result);
	return (result);
}
