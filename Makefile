
CFLAGS := -Wall -Wextra -pedantic -std=c11
CXXFLAGS := -Wall -Wextra -pedantic -std=c++11 -I./

all: test_toy parser css_parser

test_toy: test_toy.o
	$(CXX) -o $@ $<

parser: parser.o
	$(CXX) -o $@ $<

css_parser: css_parser.o
	$(CXX) -o $@ $<

.PHONY: clean
clean:
	rm *.o parser test_toy css_parser


