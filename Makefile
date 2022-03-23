sources = main.c
outfile = vm.out

ccf = -Wall
ccf_test = -Wno-implicit-function-declaration

default:
	make test

test: $(sources)
	gcc $(sources) -o $(outfile) $(ccf_test)

build: $(sources)
	gcc $(sources) -o $(outfile) $(ccf)

clean:
	rm -f $(outfile)
