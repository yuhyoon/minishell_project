typedef struct s_cmd
{
	char	*exe_path;
	char	*name;
}t_cmd;

typedef struct s_builtin
{
	char	**name;
	char	*obj;
}t_builtin;

typedef struct s_redrct
{
	int		type; //input 0, output 1, heredoc 2, append 3
	char	*obj;
}t_redrct;
 
typedef struct s_env_var
{
	char	*name;
}t_env_var

typedef struct s_pipe
{
	int		pipe_pos;
	char	*left;
	char	*right;
}t_pipe;