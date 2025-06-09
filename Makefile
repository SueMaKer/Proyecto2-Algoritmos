# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
TARGET = $(BIN_DIR)/juego

# Reglas
all: $(TARGET)

# Vinculación final
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Compilación de cada .cpp a .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos intermedios
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Ejecutar el juego
run: all
	./$(TARGET)
