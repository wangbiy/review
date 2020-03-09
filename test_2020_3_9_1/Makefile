ser=server
cli=client
.PHONY:all
all:$(ser) $(cli)
$(ser):server.cc
	g++ -o $@ $^ -std=c++11
$(cli):client.cc
	g++ -o $@ $^ -std=c++11
.PHONY:clean
clean:
	rm -f $(ser) $(cli)
