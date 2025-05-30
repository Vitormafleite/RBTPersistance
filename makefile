# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iheaders

# Source and object files
SRCDIR = source
OBJDIR = obj
HEADERS = headers
SOURCES = $(wildcard $(SRCDIR)/*.cpp) main.cpp
OBJECTS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(notdir $(SOURCES)))

# Target binary
TARGET = rbtree

# Default rule
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each .cpp to .o in obj/
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/main.o: main.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create obj directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean rule
clean:
	rm -rf $(OBJDIR) $(TARGET)
