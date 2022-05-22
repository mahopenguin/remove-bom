CXX=clang++
CXXFLAGS=-std=c++20
EXEC=remove-bom
OBJ=remove-bom.o

$(EXEC): $(OBJ)
	$(CXX) -o $(EXEC) $(OBJ)

clean:
	rm -f $(EXEC) $(OBJ) *~
