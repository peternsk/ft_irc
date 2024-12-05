

#--- BASIC ---#
NAME        = irc
CC          = c++
FLAGS       = -std=c++98 -Wall -Wextra -Werror -I./includes
RM          = rm -rf

#--- GROUP ---#
SRCS_DIR    = srcs
OBJS_DIR    = objs
CLASSES     = channel client operator server
UTILES        = main cmdUtils cmd channelManagerUtils channelManager

SRCS        = $(addsuffix .cpp, $(addprefix $(SRCS_DIR)/classes/, $(CLASSES))) \
              $(addsuffix .cpp, $(addprefix $(SRCS_DIR)/utiles/, $(UTILES)))

OBJS        = $(SRCS:$(SRCS_DIR)/%.cpp=$(OBJS_DIR)/%.o)

#--- COLOR ---#
BLACK       = \033[90;1m
RESET       = \033[0m

#--- TARGET ---#
all: ${NAME}

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.cpp
	@mkdir -p ${@D}
	@${CC} ${FLAGS} -c $< -o $@
	@echo "$(BLACK)Compiling: $< $(RESET)"

${NAME}: ${OBJS}
	@${CC} ${FLAGS} ${OBJS} -o ${NAME}
	@echo "$(BLACK)Compilation completed successfully!$(RESET)"

clean:
	@${RM} ${OBJS_DIR}
	@echo "$(BLACK)Cleanup completed successfully!$(RESET)"

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
