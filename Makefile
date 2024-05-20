### COMPILATION ###
CC := cc
CFLAGS := -Wall -Wextra -Werror -g3


### INCLUDES ###
PROJECT := minishell
PROJECT_DIR := ./

SRC_DIR := src
PROMPT_DIR := prompt
PARSER_DIR := parser
ERROR_DIR := error
BUILTIN_DIR := builtin

define SRC_FILE := 
	$(addprefix $(SRC_DIR)/, \
		expand_strlen.c \
		quote_utils.c\
		main.c
	)
endef

define PROMPT_FILE := 
	$(addprefix $(SRC_DIR)/$(PROMPT_DIR)/, \
		display.c \
)
endef

define PARSER_FILE :=
	$(addprefix $(SRC_DIR)/$(PARSER_DIR)/, \
		operator.c \
		unclosed_delimiter.c \
		syntax_error.c \
		here_doc.c \
		token_utils.c \
		tokenizer.c \
		count_simple_command.c \
		split_to_simple_command.c \
		parse_input.c
	)
endef

define ERROR_FILE :=
	$(addprefix $(SRC_DIR)/$(ERROR_DIR)/, \
		error.c \
		unclosed_delimiter_error.c \
		print_syntax_error.c
)
endef

define BUILTIN_FILE := 
	$(addprefix $(SRC_DIR)/$(BUILTIN_DIR_DIR)/, \
		ft_cd.c \
		ft_env.c\
		ft_echo.c \
		ft_exit.c\
		ft_pwd.c\
		ft_export.c\
		ft_unset.c \
		builtin_utils.c 
	)
endef

### HEADER FILE ###
HEADER_DIR := -I./includes/  -I./libft/includes/

# LIBFT
FT_DIR := ./libft
LIBFT := $(FT_DIR)/libft.a
FT := ft
FT_FLAG := -L$(FT_DIR) -l$(FT)
LIB_FLAG := $(FT_FLAG) -lreadline

## OBJECT FILE ###
OBJ_DIR := .obj
OBJ_SRC := $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILE:%.c=%.o)))
OBJ_PROMPT := $(addprefix $(OBJ_DIR)/, $(notdir $(PROMPT_FILE:%.c=%.o)))
OBJ_PARSER := $(addprefix $(OBJ_DIR)/, $(notdir $(PARSER_FILE:%.c=%.o)))
OBJ_ERROR := $(addprefix $(OBJ_DIR)/, $(notdir $(ERROR_FILE:%.c=%.o)))
OBJ_BUILTIN := $(addprefix $(OBJ_DIR)/, $(notdir $(BUILTIN_FILE:%.c=%.o)))
OBJ := $(OBJ_SRC) $(OBJ_PROMPT) $(OBJ_PARSER) $(OBJ_ERROR) $(OBJ_BUILTIN)

.PHONY := bonus all clean fclean re

### RULES ###
all : $(PROJECT)

# PROJECT Compilation
$(PROJECT) : $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(HEADER_DIR) $(OBJ) -o $(PROJECT) $(LIB_FLAG)

$(LIBFT) : 
	make -C $(FT_DIR) --silent

# COMPILING SRC_FILE
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADER_DIR) -c $< -o $@

# COMPILING PROMPT FILE 
$(OBJ_DIR)/%.o : $(SRC_DIR)/$(PROMPT_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADER_DIR) -c $< -o $@

# COMPILING PARSER FILE 
$(OBJ_DIR)/%.o : $(SRC_DIR)/$(PARSER_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADER_DIR) -c $< -o $@

# CCOMPILING ERROR_FILE
$(OBJ_DIR)/%.o : $(SRC_DIR)/$(ERROR_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADER_DIR) -c $< -o $@

# COMPILING BUILTIN_FILE
$(OBJ_DIR)/%.o : $(SRC_DIR)/$(BUILTIN_DIR)/%.c
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
