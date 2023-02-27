# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 10:50:27 by minjungk          #+#    #+#              #
#    Updated: 2023/03/02 03:44:49 by minjungk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_ON_ERROR:
.DEFAULT_GOAL := all

CFLAGS	+= -Wall -Wextra -Werror -MMD -MP -O2

ifdef DEBUG
CFLAGS	+= -O0 -g -Weverything -pedantic
endif

# **************************************************************************** #
# philo
# **************************************************************************** #
PHILO	= philo

PHILO_SRCS = \
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
