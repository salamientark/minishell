### COMPILATION ###
CC = cc
CFLAGS = -Wall -Wextra -Werror

### INCLUDES ###
PROJECT = minishell
PROJECT_DIR = ./

SRC_DIR = src
LEXER_DIR = lexer

LEXER_FILE = $(addprefix $(SRC_DIR)/$(LEXER_DIR)/, \
		unclosed_quote.c \
	)
SRC_FILE = $(addprefix $(SRC_DIR)/, \
		main.c \
)
SRC = $(SRC_FILE) $(LEXER_FILE)

### HEADER FILE ###
HEADER_DIR = includes

# LIBFT
FT_DIR = ./libft
FT = ft
FT_FLAG = -L$(FT_DIR) -l$(FT)

## OBJECT FILE ###
OBJ_DIR = .obj
OBJ_LEXER = $(addprefix $(OBJ_DIR)/, $(notdir $(LEXER_FILE:%.c=%.o)))
OBJ_SRC = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILE:%.c=%.o)))
OBJ = $(OBJ_SRC) $(OBJ_LEXER)

.PHONY=bonus all clean fclean

### RULES ###
all : $(PROJECT)

# PROJECT COmpilation
$(PROJECT) : $(OBJ)
	make -C $(FT_DIR)
	$(CC) $(CFLAGS) $(OBJ) -o $(PROJECT) $(FT_FLAG)

# COMPILING LEXER FILE 
$(OBJ_DIR)/%.o : $(SRC_DIR)/$(LEXER_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I ./$(HEADER_DIR) -c $< -o $@

# COMPILING SRC_FILE
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I ./$(HEADER_DIR) -c $< -o $@

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
