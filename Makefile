#CXX = g++
CXXFLAGS = -Wall -std=c++17 -O2
TARGET = test

SRC = test.cpp RapidSight.cpp Pathfinder.cpp LightAssault.cpp
OBJ = $(SRC:.cpp=.o)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f *.o $(TARGET)
