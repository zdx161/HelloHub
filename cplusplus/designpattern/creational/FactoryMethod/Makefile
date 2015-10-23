all: FactoryMethodTest
SRC = $(wildcard *.cpp)
obj = $(patsubst %.cpp, %.o, $(SRC))

CPPFLAGS = -g -std=gnu++0x
LDFLAGS = -lstdc++

FactoryMethodTest:$(obj)
	$(CC) $^ -o $@ $(LDFLAGS)

$(bin):%.o:%.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@


.PHONY: all clean test
clean:
	@rm -rf FactoryMethodTest $(obj)

test:
	@echo $(obj)
