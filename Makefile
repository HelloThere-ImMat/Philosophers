##########
### CC ###
##########

CC		=	gcc

#############
### FLAGS ###
#############

CFLAGS	=	-Wall -Werror -Wextra -g

ifeq ($(debug), true)
	CFLAGS	+= -fsanitize=undefined,thread
endif

#############
### NAMES ###
#############

NAME	=	philo
B_NAME	=	philo_bonus

############
### SRCS ###
############

SRCS	+=	philo.c
SRCS	+=	check_arg.c
SRCS	+=	lib_utils.c
SRCS	+=	diner.c
SRCS	+=	manager.c
SRCS	+=	init_philo.c
SRCS	+=	init.c
SRCS	+=	time.c
SRCS	+=	forks.c
SRCS	+=	eat.c
SRCS	+=	stop_or_print.c

##################
### BONUS SRCS ###
##################



##############
### HEADER ###
##############

HEADER	=	philo.h

##################
#### INCLUDES ####
##################

INCLUDES	+= -I includes/

###############
### OBJECTS ###
###############

OBJS		=	$(SRCS:.c=.o)

###############
#### LINKS ####
###############

LINKS		= -pthread

#############
### PATHS ###
#############

#SRCS_DIR	= srcs/
#SRCS_PATH	+= $(addprefix $(SRCS_DIR), $(SRCS))
SRCS_PATH	+= srcs/
SRCS_PATH	+= srcs/arg/
SRCS_PATH	+= srcs/diner/
SRCS_PATH	+= srcs/init/

vpath %.c ${SRCS_PATH}

B_SRCS_DIR	= srcs_bonus/
B_SRCS_PATH	= $(addprefix $(SRCS_B_DIR), $(B_SRCS))

HEADER_DIR	= header/
HEADER_PATH	= $(addprefix $(HEADER_DIR), $(HEADER))

OBJS_DIR	=	objs/
OBJS_PATH	=	$(addprefix $(OBJS_DIR), $(OBJS))

#############
### RULES ###
#############

all:		$(NAME)

$(NAME): $(MAKEFILE) $(HEADER_PATH) $(OBJS_PATH)
	$(CC) $(CFLAGS) $(OBJS_PATH) -o $@ $(LINKS)

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c
		@mkdir -p $(OBJS_DIR)
		${CC} $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -rf ${OBJS_DIR}

fclean:	clean
	@$(RM) -f ${NAME}

re:			fclean all

.PHONY:	all clean fclean re
