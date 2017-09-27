CXX		= g++

CXXFLAGS	= -Iinclude -MMD -MP -Wall -W -march=native -O2 -std=gnu++14

LDFLAGS		= -O2

LDLIBS		= -ldl

NAME		= summarizer

SRCS		= Summarizer.cpp

OBJS		= $(SRCS:.cpp=.o)

DEPS		= $(OBJS:.o=.d)


all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) -o $(NAME) $(LDFLAGS) $(OBJS) $(LDLIBS)

-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
