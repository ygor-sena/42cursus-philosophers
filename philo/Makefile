################################################################################
##                              42 PHILOSOPHERS                               ##
################################################################################

NAME			:= mandatory_philo

EXECUTABLE		:= philo

CC				:= cc
CYAN  			:= \33[1;36m
RESET 			:= \033[0m
LOG   			:= printf "[$(CYAN)INFO$(RESET)] %s\n"

################################################################################
##                                DIRECTORIES                                 ##
################################################################################

OBJ_DIR			:=	obj
INC_DIRS		:=	include
SRC_DIRS		:=	$(addprefix philo/, $(SRC_DIRS))
SRC_DIRS		+=	src

vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

HEADERS			:=	philo.h

SOURCES			:=	main.c \
					dinner.c \
					utils.c \
					init.c \
					manager.c \
					validation.c \
					actions.c

OBJS			:=	$(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

################################################################################
##                                 COMPILATION                                ##
################################################################################

CFLAGS			:=	-Wall -Werror -Wextra -g $(addprefix -I,$(INC_DIRS))

all:			$(NAME)

$(NAME):		$(EXECUTABLE)

$(EXECUTABLE):	$(OBJS)
	@$(LOG) "Linking objects to $@"
	$(CC) $^ -lrt -lpthread -o $@

$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	@$(LOG) "Compiling $@"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@$(LOG) "Creating objects directory"
	@mkdir $@

drd: $(NAME)
	valgrind --tool=drd ./$(EXECUTABLE) 5 800 200 200 5

hell: $(NAME)
	valgrind --tool=helgrind ./$(EXECUTABLE) 5 800 200 200 5

check: $(NAME)
	valgrind -q --leak-check=full --show-leak-kinds=all \
		--track-origins=yes ./$(EXECUTABLE) 5 800 200 200 5

clean:
	@$(RM) -r $(OBJS)
	@$(LOG) "Removing objects"
	@$(RM) -r $(OBJ_DIR)
	@$(LOG) "Removing objects directory"

fclean: clean
	@$(RM) -r $(EXECUTABLE)
	@$(LOG) "Removing $(EXECUTABLE)"

re: fclean all

.PHONY: all clean fclean re
