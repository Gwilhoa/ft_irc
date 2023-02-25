NAME		:= ft_irc

CMD_LST		:= 
SRCS_LST	:= $(addprefix cmd/,$(CMD_LST)) main.cpp utils.cpp Server.cpp User.cpp Channel.cpp
SRCS_FILE	:= sources


INC_LST		:= ft_irc.hpp Server.hpp User.hpp Channel.hpp
INC_FILE	:= includes

CC			:= c++
FLAGS		:= -std=c++98
RM			:= rm -rf

OBJS_LST	:= $(SRCS_LST:.cpp=.o)
OBJS_FILE	:= .objects



SRCS		:= $(addprefix $(SRCS_FILE)/,$(SRCS_LST))
OBJS		:= $(addprefix $(OBJS_FILE)/,$(OBJS_LST))
INCS		:= $(addprefix $(INC_FILE)/,$(INC_LST))

all:		$(NAME)

$(OBJS_FILE)/%.o : $(SRCS_FILE)/%.cpp $(INCS) | $(OBJS_FILE)
				$(CC) $(FLAGS) -c $< -o $@ $(INC_FILE)


$(NAME) :	$(OBJS) Makefile $(INCS)
				$(CC) $(FLAGS) -o $(NAME) $(OBJS) -I$(INC_FILE)
clean	:
				$(RM) $(OBJS_FILE)
fclean	:	clean
				$(RM) $(NAME)
$(OBJS_FILE):
				mkdir $(OBJS_FILE)
				mkdir $(OBJS_FILE)/cmd

re		:	fclean all

.PHONY	:	all clean fclean re