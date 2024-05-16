### COMPILATION ###
CC := cc
CFLAGS := -Wall -Wextra -Werror -g3


### TEST FILES ###
## To be removed at the end ##
TEST_DIR := test/
define TEST_FILE :=
	$(addprefix $(SRC_DIR)/$(TEST_DIR)/, \
	)
endef
### END OF TEST FILE ###

### INCLUDES ###
PROJECT := minishell
PROJECT_DIR := ./

SRC_DIR := src
LEXER_DIR := lexer
ERROR_DIR := error
PROMPT_DIR := prompt
BUILTIN_DIR := builtin

define SRC_FILE := 
	$(addprefix $(SRC_DIR)/, \
		main.c \
		quote_utils.c\
		expand_strlen.c
	)
endef

define BUILTIN_FILE := 
	$(addprefix $(SRC_DIR)/$(BUILTIN_DIR_DIR)/, \
		ft_cd.c \
		ft_env.c\
		ft_echo.c \
		builtin_utils.c 
	)
endef

define PROMPT_FILE := 
	$(addprefix $(SRC_DIR)/$(PROMPT_DIR)/, \
		display.c \
)
endef

define LEXER_FILE :=
	$(addprefix $(SRC_DIR)/$(LEXER_DIR)/, \
		operator.c \
		unclosed_delimiter.c \
		first_pass.c \
		here_doc.c
	)
endef

define ERROR_FILE :=
	$(addprefix $(SRC_DIR)/$(ERROR_DIR)/, \
		error.c \
		unclosed_delimiter_error.c \
		syntax_error.c
	)
endef

SRC := $(SRC_FILE) $(LEXER_FILE)

### HEADER FILE ###
HEADER_DIR := -I ./includes/  -I./libft/includes/

# LIBFT
LIBFT := libft.a
FT_DIR := ./libft
FT := ft
FT_FLAG := -L$(FT_DIR) -l$(FT) -lreadline

## OBJECT FILE ###
OBJ_DIR := .obj
OBJ_LEXER := $(addprefix $(OBJ_DIR)/, $(notdir $(LEXER_FILE:%.c=%.o)))
OBJ_ERROR := $(addprefix $(OBJ_DIR)/, $(notdir $(ERROR_FILE:%.c=%.o)))
OBJ_TEST := $(addprefix $(OBJ_DIR)/, $(notdir $(TEST_FILE:%.c=%.o)))
OBJ_SRC := $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILE:%.c=%.o)))
OBJ_PROMPT := $(addprefix $(OBJ_DIR)/, $(notdir $(PROMPT_FILE:%.c=%.o)))
OBJ_BUILTIN := $(addprefix $(OBJ_DIR)/, $(notdir $(BUILTIN_FILE:%.c=%.o)))
OBJ := $(OBJ_LEXER) $(OBJ_ERROR) $(OBJ_TEST) $(OBJ_PROMPT) $(OBJ_SRC) $(OBJ_BUILTIN)

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

# COMPILING PROMPT FILE 
$(OBJ_DIR)/%.o : $(SRC_DIR)/$(PROMPT_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADER_DIR) -c $< -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/$(BUILTIN_DIR)/%.c
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
	rm -rf $(OBJ_DIR)
	make clean -C $(FT_DIR)

re : fclean all

norminette :
	norminette $(FT_DIR) $(SRC_DIR)/ $(HEADER_DIR)/
