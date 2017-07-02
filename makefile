
# Target executable
TARGET=factory

# C++ Compiler
CXX=clang++

# C++ Compiler flags
CXXFLAGS=-O3 -std=c++14

# C Preprocessor flags
CPPFLAGS=-I/usr/include

# Libraries
LDLIBS=-lSDL2 -lSDL2_image

# Code Formatter
CF=clang-format

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

# Resource files
RESS=$(patsubst $(RESDIR)/%, $(BINDIR)/%, $(wildcard $(RESDIR)/*))

# Object files
OBJS=$(addprefix $(INTDIR)/, $(notdir $(SRCS:.cpp=.o)))


# Default make rule
$(BINDIR)/$(TARGET): $(OBJS) | $(BINDIR) $(RESS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDLIBS) -o $@ $^

# Generic make object rule
$(INTDIR)/%.o: $(SRCDIR)/%.cpp $(HDRS) | $(INTDIR)
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $(filter %.cpp, $<) -o $@

# Copy resource rule
$(BINDIR)/%: $(RESDIR)/% | $(BINDIR)
	cp $< $@

# Make directory rules
$(INTDIR):
	mkdir $(INTDIR)

$(BINDIR):
	mkdir $(BINDIR)



# Phony rules
.PHONY: clean format debug

clean:
	rm -rf $(INTDIR) $(BINDIR)

format:
	$(CF) -i $(SRCS) $(HDRS)
