### COMPILATION ###
CC := cc
CFLAGS := -Wall -Wextra -Werror -g3


### TEST FILES ###
## To be removed at the end ##
TEST_DIR := test/
define TEST_FILE :=
	$(addprefix $(SRC_DIR)/$(TEST_DIR)/, \
		test_lexer.c
	)
endef
### END OF TEST FILE ###

### INCLUDES ###
PROJECT := minishell
PROJECT_DIR := ./

SRC_DIR := src
LEXER_DIR := lexer
ERROR_DIR := error

define SRC_FILE := 
	$(addprefix $(SRC_DIR)/, \
		main.c \
)
endef

define LEXER_FILE :=
	$(addprefix $(SRC_DIR)/$(LEXER_DIR)/, \
		unclosed_quote.c \
		ft_shell_types.c \
		ft_delimiter.c \
		split_input.c \
	)
endef

define ERROR_FILE :=
	$(addprefix $(SRC_DIR)/$(ERROR_DIR)/, \
		error.c \
		syntax_error.c
)
endef

SRC := $(SRC_FILE) $(LEXER_FILE)

### HEADER FILE ###
HEADER_DIR := -I./includes/  -I./libft/includes/

# LIBFT
LIBFT := libft/libft.a
FT_DIR := ./libft
FT := ft
FT_FLAG := -L$(FT_DIR) -l$(FT)

## OBJECT FILE ###
OBJ_DIR := .obj
OBJ_LEXER := $(addprefix $(OBJ_DIR)/, $(notdir $(LEXER_FILE:%.c=%.o)))
OBJ_ERROR := $(addprefix $(OBJ_DIR)/, $(notdir $(ERROR_FILE:%.c=%.o)))
OBJ_TEST := $(addprefix $(OBJ_DIR)/, $(notdir $(TEST_FILE:%.c=%.o)))
OBJ_SRC := $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILE:%.c=%.o)))
OBJ := $(OBJ_LEXER) $(OBJ_ERROR) $(OBJ_TEST) $(OBJ_SRC)

.PHONY := bonus all clean fclean

### RULES ###
all : $(PROJECT)

# PROJECT COmpilation
$(PROJECT) : $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(HEADER_DIR) $(OBJ) -o $(PROJECT) $(FT_FLAG)
# 	$(CC) $(CFLAGS) -I $(HEADER_DIR) $(OBJ) -o $(PROJECT) $(FT_FLAG)

$(LIBFT) : 
	make -C $(FT_DIR)

# COMPILING LEXER FILE 
$(OBJ_DIR)/%.o : $(SRC_DIR)/$(LEXER_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADER_DIR) -c $< -o $@

# COMPILING ERROR FILE 
$(OBJ_DIR)/%.o : $(SRC_DIR)/$(ERROR_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADER_DIR) -c $< -o $@

# COMPILING TEST FILE 
$(OBJ_DIR)/%.o : $(SRC_DIR)/$(TEST_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADER_DIR) -c $< -o $@

# COMPILING SRC_FILE
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADER_DIR) -c $< -o $@

fclean : clean
	rm -f $(PROJECT)
	make fclean -C $(FT_DIR)

#Suppresion des fichiers objet
clean :
	rm -f $(OBJ_DIR)/*.o
	@rm -df $(OBJ_DIR)/
	make clean -C $(FT_DIR)

re : fclean all

norminette :
	norminette $(FT_DIR) $(SRC_DIR)/ $(HEADER_DIR)/
