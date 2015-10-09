src = $(wildcard *.cpp)
object = $(patsubst %.cpp, %.o, $(src))

CPPFLAGS += -g
LDFLAGS += -lstdc++

newplace: $(object)
	$(CC) $^ -o $@ $(LDFLAGS)

$(object):%.o:%.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

.PHONY:clean
clean:
	@rm -rf $(object) newplace
