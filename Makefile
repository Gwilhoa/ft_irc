NAME		:= ft_irc
SRCS_LST	:= main.cpp
SRCS_FILE	:= sources

OBJS_FILE	:= .objects
OBJS_LST	:= $(SRCS_LST:.cpp=.o)

INC_LST		:= 
INC_FILE	:= includes

CC			:= c++
FLAGS		:= -std=c++98 -Werror -Wall -Wextra
RM			:= rm -rf




SRCS		:= $(addprefix $(SRCS_FILE)/,$(SRCS_LST))
OBJS		:= $(addprefix $(OBJS_FILE)/,$(SRCS_LST))

all:		$(NAME)

$(OBJ_FILE)/%.o : $(SRCS_FILE)/%.cpp $(INC_LST)| $(OBJ_FILE)
				$(CC) $(FLAGS) -c $< -o $@ $(INC_FILE)


$(NAME) :	$(OBJS) Makefile $(INC_LST)
				$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(INC_FILE)
clean	:
				$(RM) $(OBJS_FILE)
fclean	:	clean
				$(RM) $(NAME)
$(OBJS_FILE):
				mkdir $(OBJS_FILE)

re		:	fclean all
