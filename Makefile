sources = main.c instructions.c registers.c stack.c
headers = main.h instructions.h registers.h stack.h
outfile = vm.out

ccf = -Wall

default:
	make build

build: $(sources)
	gcc $(sources) $(headers) -o $(outfile) $(ccf)

clean:
	rm -f $(outfile)
