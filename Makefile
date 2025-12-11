NAME        = libftprintf.a

INCDIR      = includes
SRCDIR      = src

SRCS        = $(SRCDIR)/ft_printf.c \
              $(SRCDIR)/ft_printf_parse.c \
              $(SRCDIR)/ft_printf_utils.c \
              $(SRCDIR)/ft_printf_utils2.c \
              $(SRCDIR)/ft_printf_conv_csp.c \
              $(SRCDIR)/ft_printf_conv_diuxx.c

BSRCS       = $(SRCS)

OBJS        = $(SRCS:.c=.o)
BOBJS       = $(BSRCS:.c=.o)

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I $(INCDIR)
AR          = ar rcs
RM          = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus: fclean $(BOBJS)
	$(AR) $(NAME) $(BOBJS)

$(SRCDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(BOBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus