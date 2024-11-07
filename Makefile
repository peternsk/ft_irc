
CXX := g++
# CXXFLAGS := -std=c++98 -Wall -Wextra -g
CXXFLAGS := -Wall -Wextra -g


# Colors
COLOR_RESET := \033[0m
COLOR_CXX := \033[1;34m
COLOR_OK := \033[1;32m
COLOR_ERROR := \033[1;31m
COLOR_CLEAN := \033[1;36m
COLOR_RE := \033[1;35m
COLOR_MSG := \033[1;35m

# Source and output
SRCS := channelManager.cpp channel.cpp client.cpp cmdUtils.cpp cmd.cpp
OBJS := $(SRCS:.cpp=.o)
TARGET := ft_irc

# Program name
PROGRAM_NAME := ft_irc

# Custom message with fancy border
MESSAGE := "$(COLOR_MSG)╭───────────────────────────────╮\n│🌟 $(PROGRAM_NAME) Built Successfully 🌟│\n╰───────────────────────────────╯$(COLOR_RESET)"

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
	@echo -e "$(COLOR_CXX)Linking $@...$(COLOR_RESET)"
	@$(CXX) $(CXXFLAGS) -o $@ $(OBJS)
	@echo -e "$(COLOR_OK)Build succeeded!$(COLOR_RESET)"
	@echo $(MESSAGE)
# ./$(PROGRAM_NAME)
%.o: %.cpp
	@echo -e "$(COLOR_CXX)Compiling $<...$(COLOR_RESET)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo -e "$(COLOR_CLEAN)Cleaning object files and target...$(COLOR_RESET)"
	@rm -f $(OBJS)

fclean: clean
	@echo -e "$(COLOR_CLEAN)Cleaning all including target...$(COLOR_RESET)"
	@rm -f $(TARGET)

re: fclean
	@echo -e "$(COLOR_RE)Rebuilding the project...$(COLOR_RESET)"
	@$(MAKE) --no-print-directory all

# Help command to display available commands
help:
	@echo -e "$(COLOR_CXX)Available commands:$(COLOR_RESET)"
	@echo -e "  $(COLOR_CXX)make$(COLOR_RESET)       - Build the project"
	@echo -e "  $(COLOR_CXX)make clean$(COLOR_RESET) - Clean object files"
	@echo -e "  $(COLOR_CXX)make fclean$(COLOR_RESET) - Full clean (includes target)"
	@echo -e "  $(COLOR_CXX)make re$(COLOR_RESET)    - Rebuild the project"
	@echo -e "  $(COLOR_CXX)make help$(COLOR_RESET)  - Show this help message"

.PHONY: all clean fclean re help
