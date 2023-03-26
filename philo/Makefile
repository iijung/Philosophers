# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 10:50:27 by minjungk          #+#    #+#              #
#    Updated: 2023/03/27 06:12:12 by minjungk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_ON_ERROR:
.DEFAULT_GOAL := all

CFLAGS		+= -Wall -Wextra -Werror -MMD -MP -O2
CFLAGS		+= -pedantic
CPPFLAGS	+= \
	-I ./util \
	-I ./time \
	-I ./shared \
	-I ./philosopher \

LDFLAGS		+= -pthread

ifdef DEBUG
CFLAGS		+= -O0 -g
endif

# **************************************************************************** #
# philo
# **************************************************************************** #
PHILO	= philo

PHILO_SRCS = \
	util/ft_atol.c \
	util/ft_calloc.c \
	util/ft_putstr_fd.c \
	time/ft_time.c \
	shared/ft_shared.c \
	philosopher/philosopher.c \
	philo.c \

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
	-valgrind --tool=drd -s \
		--trace-mutex=yes \
		--trace-semaphore=yes \
		--trace-fork-join=yes \
		--exclusive-threshold=10 \
		./$(PHILO) $(args)

helgrind: $(PHILO)
	-valgrind --tool=helgrind \
		./$(PHILO) $(args)
