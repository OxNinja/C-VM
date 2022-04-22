sources = main.c
outfile = vm.out

ccf = -Wall

default:
	make build

build: $(sources)
	gcc $(sources) -o $(outfile) $(ccf)

clean:
	rm -f $(outfile)
