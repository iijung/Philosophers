# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/02 03:35:23 by minjungk          #+#    #+#              #
#    Updated: 2023/03/02 03:46:27 by minjungk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_ON_ERROR:
.DEFAULT_GOAL := all

PHILO		= philo
$(PHILO):
	$(MAKE) -C $(PHILO)

PHILO_BONUS	= philo_bonus
$(PHILO_BONUS):
	$(MAKE) -C $(PHILO_BONUS)

# **************************************************************************** #
# default
# **************************************************************************** #
all: $(PHILO)

bonus: $(PHILO_BONUS)

clean:
	$(MAKE) -C $(PHILO) clean
	$(MAKE) -C $(PHILO_BONUS) clean

fclean: clean
	$(MAKE) -C $(PHILO) fclean
	$(MAKE) -C $(PHILO_BONUS) fclean

re: fclean
	$(MAKE) -C $(PHILO) all
	$(MAKE) -C $(PHILO_BONUS) all

.PHONY: all clean fclean re bonus $(PHILO) $(PHILO_BONUS)
