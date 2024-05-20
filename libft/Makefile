### COMPILATION ###
CC = cc
CFLAGS = -Wall -Wextra -Werror

### INCLUDES ###
PROJECT = libft.a
PROJECT_DIR = ./

### SOURCE FILES ###
SRC_DIR = ./src
SRC_FILE = ft_isascii.c ft_isalnum.c ft_isalpha.c ft_isdigit.c ft_isprint.c \
			ft_toupper.c ft_tolower.c ft_bzero.c ft_memset.c ft_memmove.c \
			ft_memcpy.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_strchr.c \
			ft_strrchr.c ft_strncmp.c ft_strncpy.c ft_strlcpy.c ft_strlcat.c \
			ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
			ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
			ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
			ft_putendl_fd.c ft_putnbr_fd.c ft_isnumber.c ft_strcmp.c \
			get_next_line_utils.c get_next_line.c \
			flags.c print_c.c print_i.c print_p.c print_s.c print_u.c \
			print_x.c print_xup.c printf_utils.c ft_printf_opt.c ft_printf.c \
			ft_strcat.c ft_strncat.c ft_strlcat.c \
			ft_strndup.c

BONUS_FILE = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			 ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
			 ft_lstmap.c

### HEADER FILE ###
HEADER_DIR = ../includes
HEADER_FILE = libft.h
## OBJECT FILE ###
OBJ_DIR = .obj

OBJ_FILE = $(addprefix $(SRC_DIR)/, $(addprefix $(OBJ_DIR)/, $(SRC_FILE:.c=.o))) \
			$(addprefix $(SRC_DIR)/, $(addprefix $(OBJ_DIR)/, $(GNL_FILE:.c=.o)))
BONUS_OBJ = $(addprefix, $(OBJ_DIR)/, $(BONUS_FILE:.c=.o))


### RULES ###
all : $(PROJECT)

$(PROJECT) : $(OBJ_FILE)
	ar rc $(PROJECT) $(OBJ_FILE)

$(SRC_DIR)/$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@

bonus : $(BONUS_OBJ)
	ar rc $(PROJECT) $(BONUS_OBJ)

fclean : clean
	rm -f $(PROJECT)

#Suppresion des fichiers objet
clean :
	rm -f $(OBJ_FILE)
	@rm -df $(OBJ_DIR)

re : fclean all
