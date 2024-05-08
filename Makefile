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
SRC_FILE = src/lexer/unclosed_quote.c \
	src/main.c

# define SRC_FILE :=
# 	$(addprefix $(SRC_DIR)/, \
# 		$(addprefix $(LEXER_DIR)/, \
# 			unclosed_quote.c 
# 		)
# 	)
# 	main.c
# 
# endef

### HEADER FILE ###
HEADER_DIR = includes

# LIBFT
FT_DIR = ./libft
FT = ft
FT_FLAG = -L$(FT_DIR) -l$(FT)

## OBJECT FILE ###
OBJ_DIR = .obj
# OBJ_SRC = $(addprefix $(OBJ_DIR)/, $(notdir $(patsubst(%.c, %.o, $(SRC_FILE)))))
OBJ_SRC = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILE:%.c=%.o)))
# OBJ_SRC = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILE:%.c=%.o)))

.PHONY=bonus

### RULES ###
all : $(PROJECT)

$(PROJECT) : $(OBJ_SRC)
	make -C $(FT_DIR)
	$(CC) -g3 $(CFLAGS) $(OBJ_SRC) $(OBJ_MANDATORY) -o $(PROJECT) $(FT_FLAG)


$(OBJ_DIR)/%.o : $(SRC_DIR)/$(LEXER_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I ./$(HEADER_DIR) -c $< -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I ./$(HEADER_DIR) -c $< -o $@

# $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
# 	@mkdir -p $(@D)
# 	$(CC) -g3 $(CFLAGS) -I ./$(HEADER_DIR)  -c $< -o $@

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
