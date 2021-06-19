# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dnakano <dnakano@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/21 08:47:29 by dnakano           #+#    #+#              #
#    Updated: 2021/06/19 15:04:04 by dnakano          ###   ########.fr        #
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
CLIENTSRCNAME	=	client.c minisend.c
CLIENTSRCDIR	=	./src/client
CLIENTSRCS		=	$(addprefix $(CLIENTSRCDIR)/,$(CLIENTSRCNAME))
CLIENTOBJS		=	$(CLIENTSRCS:%.c=%.o)
CLIENTHEADERS	=	libft/libft.h src/client/minitalk_client.h
CLIENTNAME		=	client
CLIENTOUTPUTDIR	=	.
CLIENTOUTPUT	=	$(CLIENTOUTPUTDIR)/$(CLIENTNAME)
BONUSSERVERSRCNAME	=	server_bonus.c
BONUSSERVERSRCDIR	=	./src/server
BONUSSERVERSRCS		=	$(addprefix $(BONUSSERVERSRCDIR)/,$(BONUSSERVERSRCNAME))
BONUSSERVEROBJS		=	$(BONUSSERVERSRCS:%.c=%.o)
BONUSSERVERHEADERS	=	libft/libft.h
BONUSSERVERNAME		=	server
BONUSSERVEROUTPUTDIR	=	.
BONUSSERVEROUTPUT	=	$(BONUSSERVEROUTPUTDIR)/$(BONUSSERVERNAME)
BONUSCLIENTSRCNAME	=	client_bonus.c minisend_bonus.c
BONUSCLIENTSRCDIR	=	./src/client
BONUSCLIENTSRCS		=	$(addprefix $(BONUSCLIENTSRCDIR)/,$(BONUSCLIENTSRCNAME))
BONUSCLIENTOBJS		=	$(BONUSCLIENTSRCS:%.c=%.o)
BONUSCLIENTHEADERS	=	libft/libft.h src/client/minitalk_client_bonus.h
BONUSCLIENTNAME		=	client
BONUSCLIENTOUTPUTDIR	=	.
BONUSCLIENTOUTPUT	=	$(BONUSCLIENTOUTPUTDIR)/$(BONUSCLIENTNAME)
NAME			=	minitalk

.SUFFIXES:		.o .c

.PHONY:			all
all:			$(NAME)

$(SERVERNAME):	$(LIBFT) $(SERVEROBJS) $(SERVERHEADERS)
				$(CC) $(CFLAGS) $(SERVEROBJS) $(LDFLAGS) -o $(SERVEROUTPUT)

$(CLIENTNAME):	$(LIBFT) $(CLIENTOBJS) $(CLIENTHEADERS)
				$(CC) $(CFLAGS) $(CLIENTOBJS) $(LDFLAGS) -o $(CLIENTOUTPUT)

$(NAME):		$(SERVERNAME) $(CLIENTNAME)

bonus_server:	$(LIBFT) $(BONUSSERVEROBJS) $(BONUSSERVERHEADERS)
				$(CC) $(CFLAGS) $(BONUSSERVEROBJS) $(LDFLAGS) -o $(BONUSSERVEROUTPUT)

bonus_client:	$(LIBFT) $(BONUSCLIENTOBJS) $(BONUSCLIENTHEADERS)
				$(CC) $(CFLAGS) $(BONUSCLIENTOBJS) $(LDFLAGS) -o $(BONUSCLIENTOUTPUT)

bonus:			bonus_server bonus_client

$(LIBFT):
				make $(LIBFTNAME) -C $(LIBFTDIR)

%.o:%.c
				$(CC) $(CFLAGS) -c $< -o $@

.PHONY:			test
test:			$(NAME)
				cd test && ./test.sh

.PHONY:			testbonus
testbonus:		bonus
				cd test && ./test.sh

.PHONY:			clean
clean:
				make fclean -C $(LIBFTDIR)
				rm -f $(SERVEROBJS) $(CLIENTOBJS) $(BONUSSERVEROBJS) $(BONUSCLIENTOBJS)

.PHONY:			fclean
fclean:			clean
				make clean -C $(LIBFTDIR)
				rm -f $(SERVEROUTPUT) $(CLIENTOUTPUT)

.PHONY:			re
re:				fclean all
