
all: test_toy parser

%o: %cpp
	$(CXX) -I./ -o $@ $<

test_toy: test_toy.o
	$(CXX) -o $@ $<

parser: parser.o
	$(CXX) -o $@ $<




