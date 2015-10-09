src = $(wildcard *.cpp)
object = $(patsubst %.cpp, %.o, $(src))

CPPFLAGS += -g
LDFLAGS += -lstdc++

singleton: $(object)
	$(CC) $^ -o $@ $(LDFLAGS)

$(object):%.o:%.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

.PHONY: clean test
test:
	@echo $(src)
	@echo $(object)

clean:
	@rm -rf $(object) singleton
