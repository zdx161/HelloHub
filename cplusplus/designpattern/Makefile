
SRC = $(wildcard *.cpp)
BIN = $(patsubst %.cpp, %, $(SRC))
OBJ = $(patsubst %.cpp, %.o, $(SRC))

CPPFLAGS += -g -std=gnu++0x
LDFLAGS += -lstdc++

$(BIN):%:%.o
	$(CC) $< -o $@ $(LDFLAGS)

$(OBJ):%.o:%.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@


.PHONY: clean test
test:
	@echo $(CPPFLAGS) $(CC)

clean:
	@rm -rf $(OBJ) $(BIN)
