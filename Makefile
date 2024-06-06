### COMPILATION ###
CC := cc
CFLAGS := -Wall -Wextra -Werror -g3


### PROJECT NAME ###
PROJECT := minishell
PROJECT_DIR := ./

### SOURCE DIR ###
SRC_DIR := src
PROMPT_DIR	:= prompt
PARSER_DIR	:= parser
ERROR_DIR	:= error
BUILTIN_DIR := builtin
EXEC_DIR	:= exec
EXPAND_DIR := expand
BONUS_DIR := bonus

# *************************************************************************** #
#                             MANDATORY SOURCE FILE                           #
# *************************************************************************** #
define SRC_FILE := 
	$(addprefix $(SRC_DIR)/, \
		expand_strlen.c \
		quote_utils.c\
		main.c \
		init_minishell.c
	)
endef

define PROMPT_FILE := 
	$(addprefix $(SRC_DIR)/$(PROMPT_DIR)/, \
		display.c \
)
endef

define EXEC_FILE := 
	$(addprefix $(SRC_DIR)/$(PROMPT_DIR)/, \
		get_valid_path.c \
		split_path.c	\
		redirections.c	\
		exec_command.c	\
		free_all.c
)
endef

define PARSER_FILE :=
	$(addprefix $(SRC_DIR)/$(PARSER_DIR)/, \
		ft_token_add_back.c \
		ft_token_free_list.c \
		ft_token_get_head.c \
		ft_token_init_one.c \
		here_doc_count.c \
		here_doc_name.c \
		operator.c \
		unclosed_delimiter.c \
		syntax_error.c \
		here_doc.c \
		tokenize.c \
		alloc_simple_cmd.c \
		split_to_simple_command.c \
		parse_input.c
	)
endef

define ERROR_FILE :=
	$(addprefix $(SRC_DIR)/$(ERROR_DIR)/, \
		error.c \
		unclosed_delimiter_error.c \
		print_syntax_error.c \
		print_here_doc_warning.c
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

define EXPAND_FILE :=
	$(addprefix $(SRC_DIR)/$(EXPAND_DIR)/, \
		free_expand.c \
		is_expand.c \
		make_expand_tab.c \
		expanded_variable_len.c \
		expand_variable.c \
		var_expand_elem.c \
		perform_variable_expansion.c \
		word_split.c \
		perform_word_split.c \
		remove_quote.c
	)
endef

define MANDATORY_EXPAND_FILE :=
	$(addprefix $(SRC_DIR)/$(EXPAND_DIR)/, \
		expand.c
	)
endef

# *************************************************************************** #
#                               BONUS SOURCE FILE                             #
# *************************************************************************** #
define BONUS_EXPAND_FILE :=
	$(addprefix $(BONUS_DIR)/$(EXPAND_DIR)/, \
		simplify_pattern_bonus.c \
		pattern_match_bonus.c \
		perform_filename_expansion_bonus.c \
		expand_bonus.c
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
OBJ_EXEC := $(addprefix $(OBJ_DIR)/, $(notdir $(EXEC_FILE:%.c=%.o)))
OBJ_EXPAND := $(addprefix $(OBJ_DIR)/, $(notdir $(EXPAND_FILE:%.c=%.o)))
OBJ := $(OBJ_SRC) $(OBJ_PROMPT) $(OBJ_PARSER) $(OBJ_ERROR) $(OBJ_BUILTIN) \
		$(OBJ_EXPAND) $(OBJ_EXEC)

## MANDATORY OBJ FILE ##
OBJ_MANDATORY_EXPAND := $(addprefix $(OBJ_DIR)/, \
						$(notdir $(MANDATORY_EXPAND_FILE:%.c=%.o)))
OBJ_MANDATORY :=  $(OBJ) $(OBJ_MANDATORY_EXPAND)

## BONUS OBJ ##
OBJ_BONUS_EXPAND := $(addprefix $(OBJ_DIR)/, $(notdir $(BONUS_EXPAND_FILE:%.c=%.o)))
OBJ_BONUS := $(OBJ) $(OBJ_BONUS_EXPAND)

# *************************************************************************** #
#                                 BONUS OBJ FILE                              #
# *************************************************************************** #



.PHONY := bonus all clean fclean re

### RULES ###
all : $(PROJECT)

# PROJECT Compilation
$(PROJECT) : $(LIBFT) $(OBJ_MANDATORY)
	$(CC) $(CFLAGS) $(HEADER_DIR) $(OBJ_MANDATORY) -o $(PROJECT) $(LIB_FLAG)

# bonus compilation
bonus : $(LIBFT) $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(HEADER_DIR) $(OBJ_BONUS) -o $(PROJECT) $(LIB_FLAG)

$(LIBFT) : 
	make -C $(FT_DIR)

# *************************************************************************** #
#                                SRC COMPILE OBJ                              #
# *************************************************************************** #
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

# COMPILING EXEC_FILE
$(OBJ_DIR)/%.o : $(SRC_DIR)/$(EXEC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADER_DIR) -c $< -o $@

# COMPILING EXPAND_FILE
$(OBJ_DIR)/%.o : $(SRC_DIR)/$(EXPAND_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADER_DIR) -c $< -o $@

# *************************************************************************** #
#                                BONUS COMPILE OBJ                            #
# *************************************************************************** #
# COMPILING BONUS_EXPAND_FILE
$(OBJ_DIR)/%.o : $(BONUS_DIR)/$(EXPAND_DIR)/%.c
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
