cc = g++ 
prom = xjl-server
deps = $(shell find ./ -maxdepth 1 -name "*.h")
src = $(shell find ./ -maxdepth 1 -name "*.cpp")
obj = $(src:%.cpp=%.o) 
lib = -levent
flags = -g -W -Wall -std=c++11
$(prom): $(obj)
	$(cc) $(obj) -o $(prom) $(lib) $(flags)

%.o: %.c $(deps)
	$(cc) -c $< -o $@ $(lib) $(flags)

clean:
	rm -rf $(obj) $(prom)

