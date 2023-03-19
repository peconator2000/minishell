NAME = 			minishell

NAME_SRCS =		ft_cmd_list.c \
				ft_inits.c   	\
				ft_main.c ft_utils.c

HEADER	= 		minishell.h

SRC_SIGNAL = 	signals/ft_signals.c\
				signals/ft_signals_utils.c

SRC_WORKPIPE =	work_pipe/ft_executer.c \
				work_pipe/ft_pipe_utils.c \
				work_pipe/ft_pipex.c

SRC_REDIRECTS = redirects/ft_redirects_type.c \
				redirects/ft_redirects_utils.c \
				redirects/ft_redirects.c        

SRC_BUILTINS = 	builtins/ft_cd.c   \
				builtins/ft_cd_utils.c \
				builtins/ft_echo.c  \
				builtins/ft_export.c \
				builtins/ft_export_utils.c \
				builtins/ft_pwd.c     \
				builtins/ft_unset.c    \
				builtins/ft_builtin_handler.c \
				builtins/ft_env.c

SRC_PARSER =	parser/ft_argument_edit.c \
				parser/ft_argument_pars.c  \
				parser/ft_dollar_check.c    \
				parser/ft_dollar_pars.c      \
				parser/ft_dollar_utils.c      \
				parser/ft_env_list.c           \
				parser/ft_envp_pars.c           \
				parser/ft_find_path.c 			 \
				parser/ft_main_pars.c             \
				parser/ft_pars_utils.c             \
				parser/ft_pattern_pars.c            \
				parser/ft_quotes_pars.c              \
				parser/ft_redirect_pars.c             \
				parser/ft_var.c 					   \
				parser/ft_mega_utils.c

SRC_LIBA =		lib_utils/ft_intstr.c  \
				lib_utils/ft_isallnum.c \
				lib_utils/ft_memcpy.c    \
				lib_utils/ft_memset.c     \
				lib_utils/ft_pipe_split.c  \
				lib_utils/ft_putstr_fd.c    \
				lib_utils/ft_split.c         \
				lib_utils/ft_strcmp.c          \
				lib_utils/ft_strdup.c           \
				lib_utils/ft_strjoin.c           \
				lib_utils/ft_strlen.c             \
				lib_utils/ft_strncmp.c             \
				lib_utils/ft_strnstr.c              \
				lib_utils/ft_substr.c                \
				lib_utils/ft_itoa.c

			#redirects.c 

OBJS = 			$(NAME_SRCS:.c=.o) \
				$(SRC_PARSER:.c=.o) \
				$(SRC_SIGNAL:.c=.o)  \
				$(SRC_WORKPIPE:.c=.o) \
				$(SRC_BUILTINS:.c=.o)  \
				$(SRC_REDIRECTS:.c=.o)

FLAGS = 		-Wall -Wextra -L/Users/$(USER)/.brew/Cellar/readline/8.1.2/lib/ -I/Users/$(USER)/.brew/Cellar/readline/8.1.2/include 

all : 			$(NAME)

$(NAME) : 		$(HEADER) $(OBJS) Makefile
				@gcc $(FLAGS) $(OBJS) $(SRC_LIBA) -o $(NAME) -lreadline
				@printf "minishell was build ✅\n"

clean :
				@rm -rf $(OBJS)
				@printf "ALL is in trash 🗑\n"

fclean : 		clean
				@rm -f $(NAME)

re :
				@$(MAKE) fclean
				@$(MAKE) all

.PHONY : 		all clean fclean re bonus rebonus
