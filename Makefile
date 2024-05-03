### COMPILATION ###
CC = cc
CFLAGS = -Wall -Wextra -Werror

### INCLUDES ###
PROJECT = minishell
PROJECT_DIR = ./

SRC_DIR = src
SRC_FILE = 
			   
### HEADER FILE ###
HEADER_DIR = includes

# LIBFT
FT_DIR = ./libft
FT = ft
FT_FLAG = -L$(FT_DIR) -l$(FT)

## OBJECT FILE ###
OBJ_DIR = .obj
OBJ_SRC = $(addprefix $(OBJ_DIR)/, $(SRC_FILE:.c=.o))
OBJ_MANDATORY = $(addprefix $(OBJ_DIR)/, $(MANDATORY:.c=.o))
OBJ_BONUS = $(addprefix $(OBJ_DIR)/, $(BONUS:.c=.o))

.PHONY=bonus

### RULES ###
all : $(PROJECT)

bonus : $(OBJ_SRC) $(OBJ_BONUS)
	make -C $(FT_DIR)
	$(CC) -g3 $(CFLAGS) $(OBJ_SRC) $(OBJ_BONUS) -o $(PROJECT) $(FT_FLAG)

$(PROJECT) : $(OBJ_SRC) $(OBJ_MANDATORY)
	make -C $(FT_DIR)
	$(CC) -g3 $(CFLAGS) $(OBJ_SRC) $(OBJ_MANDATORY) -o $(PROJECT) $(FT_FLAG)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -g3 $(CFLAGS) -I ./$(HEADER_DIR)  -c $< -o $@

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