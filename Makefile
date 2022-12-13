# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yujelee <yujelee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 16:22:38 by minsukan            #+#    #+#              #
#    Updated: 2022/11/04 16:10:28 by yujelee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL = all

NAME		=	minishell
CFLAGS		=	-Wall -Werror -Wextra -MMD -MP
CPPFLAGS	=	-I./include -I./libft -I$(HOME)/.brew/opt/readline/include
LDFLAGS		=	-L./libft -L$(HOME)/.brew/opt/readline/lib
LDLIBS		=	-lft -lreadline
RM			=	rm -rf

OUTDIR		=	out/

LIBFT		=	./libft/libft.a

MAIN = main.c

ifdef bonus
	MAIN = main_bonus.c
endif

SRCS		= 	$(MAIN)							\
				parse_line.c					\
				replace_space.c					\
				replace_op.c					\
				expand_env.c					\
				expand_env_utils.c				\
				manage_symbol.c					\
				manage_envlst.c					\
				manage_error.c					\
				manage_env.c					\
				manage_mem.c					\
				manage_signal.c					\
				symbolize.c						\
				preprocess_line.c				\
				check_cmd.c						\
				validate.c						\
				validate_utils.c				\
				manage_info.c					\
				expand_filename.c				\
				delete_quote.c					\
				execute.c						\
				token_tree/and_or.c				\
				token_tree/brace_group.c		\
				token_tree/make_parse_tree.c	\
				token_tree/pipeline.c			\
				token_tree/utils.c				\
				execute_pipe_line.c				\
				execute_pipe_line_utils.c		\
				execute_pipe_line_io.c			\
				execute_pipe_line_io_utils.c	\
				execute_single_commend.c		\
				fork_heredoc.c					\
				replace_wild_card.c				\
				make_env.c						\
				built_in/ft_cd.c				\
				built_in/ft_cd_utils.c			\
				built_in/ft_echo.c				\
				built_in/ft_env.c				\
				built_in/ft_exit.c				\
				built_in/ft_export.c			\
				built_in/ft_pwd.c				\
				built_in/ft_unset.c				\
				built_in/ft_pipe_export.c						

OBJS		=	$(addprefix $(OUTDIR),$(SRCS:%.c=%.o))
DEPS		=	$(addprefix $(OUTDIR),$(SRCS:%.c=%.d))
-include $(DEPS)

$(OUTDIR)%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

bonus : 
	$(MAKE) bonus=1 

all		:
	$(MAKE) -C $(dir $(LIBFT))
	$(MAKE) $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(OBJS) : $(LIBFT)

$(LIBFT) : 
	@$(MAKE) -C $(dir $(LIBFT))

clean	:
	@$(RM) $(OUTDIR)
	@$(MAKE) -C $(dir $(LIBFT)) clean

fclean	: clean
	@$(RM) $(NAME) $(LIBFT)

re		: fclean
	$(MAKE) all

.PHONY	: all clean fclean re $(dir $(LIBFT)) bonus
