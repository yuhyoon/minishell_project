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
	char	type;
	int		parts;
	char	*obj;
}t_redrct;
 
typedef struct s_env_var
{
	char	*name;
}t_env_var;

typedef struct s_pipe
{
	int		pipe_pos;
	char	*left;
	char	*right;
}t_pipe;