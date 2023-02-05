SRCDIR = src
OBJDIR = obj
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
TARGET = programa-principal
FLAGS = -g -Wall -Wextra
LIBS = -lglib-2.0
INCLUDE = -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -Iincludes

$(TARGET): $(OBJ)
	gcc $(FLAGS) $(INCLUDE) $(OBJ) -o $(TARGET) $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	gcc $(FLAGS) -c  $(INCLUDE) $< -o $@ $(LIBS)

clean:
	rm -rf $(OBJ)
	rm -rf $(TARGET)
