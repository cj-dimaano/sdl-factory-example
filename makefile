
# Target executable
TARGET=factory

# Code Compiler
CC=clang++

# Code Formatter
CF=clang-format

# Compiler options
OPTS=-Weverything -O3 -I/usr/include

# Libraries
LIBS=-lSDL2 -lSDL2_image

# Source directory
SRCDIR=src

# Resource directory
RESDIR=res

# Intermediate directory
INTDIR=obj

# Output directory
BINDIR=bin

# Source files
SRCS=$(wildcard $(SRCDIR)/*.cpp)

# Header files
HDRS=$(wildcard $(SRCDIR)/*.h)

# Object files
OBJS=$(addprefix $(INTDIR)/, $(notdir $(SRCS:.cpp=.o)))

# Generic make object rule
$(INTDIR)/%.o: $(SRCDIR)/%.cpp $(HDRS)
	mkdir -p $(INTDIR) && $(CC) -c -o $@ $< $(OPTS)

# Default make rule
$(BINDIR)/$(TARGET): $(OBJS)
	mkdir -p $(BINDIR) && $(CC) -o $@ $^ $(OPTS) $(LIBS) && cp $(RESDIR)/* $(BINDIR)


.PHONY: clean format

clean:
	rm -rf $(INTDIR) $(BINDIR)

format:
	$(CF) -i $(SRCS) $(HDRS)
