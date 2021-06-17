# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/21 08:47:29 by dnakano           #+#    #+#              #
#    Updated: 2021/06/17 20:40:16 by dnakano          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra
LDFLAGS			=	-L$(LIBFTDIR) $(patsubst lib%,-l%,$(basename $(LIBFTNAME)))
LIBFTNAME		=	libft.a
LIBFTDIR		=	libft
LIBFT			=	$(LIBFTDIR)/$(LIBFTNAME)
SERVERSRCNAME	=	server.c
SERVERSRCDIR	=	./src/server
SERVERSRCS		=	$(addprefix $(SERVERSRCDIR)/,$(SERVERSRCNAME))
SERVEROBJS		=	$(SERVERSRCS:%.c=%.o)
SERVERHEADERS	=	libft/libft.h
SERVERNAME		=	server
SERVEROUTPUTDIR	=	.
SERVEROUTPUT	=	$(SERVEROUTPUTDIR)/$(SERVERNAME)
CLIENTSRCNAME	=	client.c
CLIENTSRCDIR	=	./src/client
CLIENTSRCS		=	$(addprefix $(CLIENTSRCDIR)/,$(CLIENTSRCNAME))
CLIENTOBJS		=	$(CLIENTSRCS:%.c=%.o)
CLIENTHEADERS	=	libft/libft.h
CLIENTNAME		=	client
CLIENTOUTPUTDIR	=	.
CLIENTOUTPUT	=	$(CLIENTOUTPUTDIR)/$(CLIENTNAME)
NAME			=	minitalk

.SUFFIXES:		.o .c

.PHONY:			all
all:			$(NAME)

$(SERVERNAME):	$(LIBFT) $(SERVEROBJS) $(SERVERHEADERS)
				$(CC) $(CFLAGS) $(SERVEROBJS) $(LDFLAGS) -o $(SERVEROUTPUT)

$(CLIENTNAME):	$(LIBFT) $(CLIENTOBJS) $(CLIENTHEADERS)
				$(CC) $(CFLAGS) $(CLIENTOBJS) $(LDFLAGS) -o $(CLIENTOUTPUT)

$(NAME):		$(SERVERNAME) $(CLIENTNAME)

# .PHONY:			bonus
# bonus:			$(LIBFT) $(BONUSOBJS) $(HEADERS)
# 				$(CC) $(CFLAGS) $(BONUSOBJS) $(LDFLAGS) -o $(OUTPUT)

$(LIBFT):
				make $(LIBFTNAME) -C $(LIBFTDIR)

%.o:%.c
				$(CC) $(CFLAGS) -c $< -o $@

.PHONY:			test
test:			$(NAME)
				cd test && ./test.sh

.PHONY:			testbonus
testbonus:		bonus
				cd test && ./test.sh bonus

.PHONY:			clean
clean:
				make fclean -C $(LIBFTDIR)
				rm -f $(SERVEROBJS) $(CLIENTOBJS)

.PHONY:			fclean
fclean:			clean
				make clean -C $(LIBFTDIR)
				rm -f $(OUTPUT)

.PHONY:			re
re:				fclean all
