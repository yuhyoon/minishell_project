// #include <unistd.h>
// #include <stdio.h>
// #include <sys/wait.h>
// #include <errno.h>

// int main(int argc, char const *argv[])
// {
// 	/* code */
// 	int id1 = fork();
// 	int id2 = fork();

// 	if (id1 == 0)
// 	{
// 		if (id2 == 0)
// 			printf("id1 %d Process Y %d\n", id1, id2);
// 		else
// 			printf("id1 %d Process X %d\n", id1, id2);
// 	}
// 	else
// 	{
// 		if (id2 == 0)
// 			printf("id1 %d Process Z %d\n", id1, id2);
// 		else
// 			printf("id1 %d Parent!!!!!!!!!!! %d\n",  id1, id2);
// 	}
// 	while (wait(NULL) != -1 || errno != ECHILD)
// 	{
// 		printf("Waited for a child to finish \n");
// 	}
// 	return 0;
// }


int main(int argc, char const *argv[])
{
	int fd[2];

	if (pipe(fd) == -1)
	{
		printf("Error pipe");
		return 1;
	}
	int id = fork();
	if (id == 0){
		close(fd[0]);
		int x;
		printf("Enter a Number : ");
		scanf("%d\n", &x);
		open()
		if (write(fd[0], &x, sizeof(int)) == -1)
		{
			printf("An error ocurred with WRITing to the pipe");
			return 2;
		}
		close(fd[1]);

	}else{

		int y;
		printf("Written Number : %d\n ", y);

	}
	return 0;
}
