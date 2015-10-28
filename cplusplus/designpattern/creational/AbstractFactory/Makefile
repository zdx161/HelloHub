all: AbstractFactoryTest

SRC = $(wildcard *.cpp)
obj = $(patsubst %.cpp, %.o, $(SRC))

#compile flags: CFLAGS CXXFLAGS
#preprocessor flags: CPPFLAGS
#CPPFLAGS = -D -I -U -o -Wall -Werror -M -MM
CXXFLAGS = -g -std=gnu++0x
LDFLAGS = -lstdc++

AbstractFactoryTest: $(obj)
	$(CC) $^ -o $@ $(LDFLAGS)
	@$(RM) $(obj)

#$(<) is better than $<
$(obj):%.o:%.cpp
	$(CC) $(CXXFLAGS) -c $(<) -o $@


.PHONY:clean

clean:
	@rm -rf $(obj) AbstractFactoryTest
