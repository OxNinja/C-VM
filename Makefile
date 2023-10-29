sources = src/*
outfile = vm.out

cc = gcc
ccf = -Wall

default:
	make build

build: $(sources)
	$(cc) $(sources) -o $(outfile) $(ccf)

test: $(sources)
	$(cc) $(sources) -o $(outfile) $(ccf)
	ls -alh $(outfile)
	./$(outfile)

clean:
	rm -f $(outfile)
