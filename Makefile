# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abutok <abutok@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/25 11:13:02 by abutok            #+#    #+#              #
#    Updated: 2018/02/23 14:13:28 by abutok           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
#	C compiler run and default error flags
GCC = gcc -Wall -Wextra -Werror
#	output flag for GCC compiler with preseted way to CLION project dir
OUT = -o $(NAME)
#	MLX flags
MLX = -lmlx -framework OpenGL -framework AppKit -framework OpenCL
#	fdf's sources
SRCDIR = ./srcs/
SRCFILES = cl.c fract_draw.c keyboardkeys.c mousekeys.c main.c
SRC = $(addprefix $(SRCDIR), $(SRCFILES))
#	fdf's objects
OBJDIR = ./objs/
OBJ = $(addprefix $(OBJDIR), $(SRCFILES:.c=.o))
#	fdf's headers
HDR = ./includes
#	libft
LIBFTLINK = -L ./libft -lft
LIBFTDIR = ./libft/
LIBFTHDR = ./libft/includes/
LIBFT = libft.a
LIBFTOBJDIR = ./libft/obj/
LIBFTSRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
			ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c \
			ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c \
			ft_strrchr.c  ft_strstr.c  ft_strnstr.c ft_strcmp.c ft_strncmp.c \
			ft_atoi.c ft_isalpha.c  ft_isdigit.c ft_isalnum.c ft_isascii.c \
			ft_isprint.c ft_toupper.c ft_tolower.c \
			ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c \
			ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c \
			ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c \
			ft_putchar.c  ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c \
			ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c\
			ft_swap.c ft_isupper.c ft_islower.c ft_sqrt.c ft_cshift.c get_next_line.c
LIBFTOBJ = $(addprefix $(LIBFTOBJDIR), $(LIBFTSRC:.c=.o))

.NOTPARALLEL = all fclean lclean clean lfclean re $(NAME) $(OBJDIR) $(LIBFT) $(LIBFTOBJDIR)

all: $(LIBFT) $(NAME)
#	fdf's rules
$(NAME): $(OBJDIR) $(OBJ)
	$(GCC) $(MLX) $(OBJ) $(OUT) $(LIBFTLINK) -I $(LIBFTHDR) -I $(HDR)

$(OBJDIR):
	@if [ ! -d "$(OBJDIR)" ]; then mkdir $(OBJDIR); fi

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(GCC) -c -I $(HDR) -I $(LIBFTHDR) $< -o $@

clean: lclean
	@if [ -d "$(OBJDIR)" ]; then rm -rf $(OBJDIR); fi

fclean: lfclean clean
	@if [ -f "$(NAME)" ]; then rm -rf $(NAME); fi

re: fclean all
#	libft's rules
$(LIBFT): $(LIBFTOBJDIR) $(LIBFTOBJ)
	@ar rc $(LIBFTDIR)$(LIBFT) $(LIBFTOBJ)
	@ranlib ./libft/libft.a

$(LIBFTOBJDIR):
	@if [ ! -d "$(LIBFTOBJDIR)" ]; then mkdir $(LIBFTOBJDIR); fi

$(LIBFTOBJDIR)%.o: $(LIBFTDIR)%.c
	$(GCC) -c -I $(LIBFTHDR) $< -o $@

lclean:
	@if [ -d "$(LIBFTOBJDIR)" ]; then rm -rf $(LIBFTOBJDIR); fi

lfclean: lclean
	@if [ -f "$(LIBFTDIR)$(LIBFT)" ]; then rm -rf $(LIBFTDIR)$(LIBFT); fi
