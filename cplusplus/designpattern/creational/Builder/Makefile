all: Builder
src = $(wildcard *.cpp)
obj = $(patsubst %.cpp, %.o, $(src))

CPPFLAGS = -D_DEBUG
CXXFLAGS = -g -std=gnu++0x
LDFLAGS = -lstdc++

Builder:$(obj)
	$(CC) $+ -o $@ $(LDFLAGS)
	$(RM) $(obj)

$(obj):%.o:%.cpp
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c $(<) -o $@

.PHONY: all clean

clean:
	@rm -f Builder $(obj)
