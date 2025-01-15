#include <fcntl.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>


// int main(int argc, char const *argv[])
// {
// 	int fd = open("infile", O_WRONLY | O_CREAT | O_EXCL ,"0666");
// 	printf("%d\n", fd);

// 	return 0;
// }

// #include <stdio.h>

// extern char **environ;
// //int main(int argc, char *argv[], char *envp[])
// int	main(int argc, char *argv[])
// {
// 	int	idx = 0;

// 	(void)argc;
// 	(void)argv;
// 	while (environ[idx])
// 	{
// 		printf("environ[%d]: %s\n", idx, environ[idx]);
// 		idx++;
// 	}
// 	return (0);
// } 

#include <stdio.h>
#include <errno.h>

int	main(void)
{
	// perror("before error");
	errno = ENOMEM;
	// perror("errno = ENOMEM");
	// errno = EACCES;
	// perror("errno = EACCES");
	// errno = ENOENT;
	// perror("errno = ENOENT");
	// errno = ENOTDIR;
	// perror("errno = ENOTDIR");
	// errno = EFAULT;
	// perror("errno = EFAULT");
	// errno = EBADF;
	// perror("errno = EBADF");
	return (0);
}