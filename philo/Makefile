# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 10:50:27 by minjungk          #+#    #+#              #
#    Updated: 2023/03/08 01:19:41 by minjungk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_ON_ERROR:
.DEFAULT_GOAL := all

CFLAGS	+= -Wall -Wextra -Werror -MMD -MP -O2
CPPFLAGS	+= -I ./util
CFLAGS	+= -g -pedantic
LDFLAGS	+= -pthread

ifdef DEBUG
CFLAGS	+= -O0 -g -Weverything -pedantic
endif

# **************************************************************************** #
# philo
# **************************************************************************** #
PHILO	= philo

PHILO_SRCS = \
	util/ft_calloc.c \
	util/ft_memcpy.c \
	util/time.c \
	initial.c \
	philo.c \
	philosopher.c \

PHILO_OBJS = $(PHILO_SRCS:.c=.o)
PHILO_DEPS = $(PHILO_SRCS:.c=.d)
-include $(PHILO_DEPS)

$(PHILO): $(PHILO_OBJS)

# **************************************************************************** #
# default
# **************************************************************************** #
all: $(PHILO)

clean:
	$(RM) $(PHILO_OBJS) $(PHILO_DEPS)

fclean: clean
	$(RM) $(PHILO)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re

# **************************************************************************** #
memcheck: $(PHILO)
	-valgrind --tool=memcheck \
		--leak-check=full \
		--track-origins=yes \
		./$(PHILO) $(args)

drd: $(PHILO)
	-valgrind --tool=drd \
		--trace-mutex=yes \
		--trace-semaphore=yes \
		--trace-fork-join=yes \
		--exclusive-threshold=10 \
		./$(PHILO) $(args)
