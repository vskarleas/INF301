

PROGS=main acte1 acte2 acte3 acte3b acte4 acte5
CC=clang
CFLAGS=-g -Wall -Wextra -Wno-unused-parameter

all: $(PROGS)

tests_acte1: acte1
	@set -e; for f in `ls tests_acte1`; do ./acte1 tests_acte1/$$f; done; printf "\033[0;32mSuccès\033[0m sur l'acte I !\n";\

# 	for f in `ls tests/*.test`; do dot -Tsvg -o $$f.svg $$f.dot; tycat $$f.svg; done

tests_acte2: acte2
	@set -e; for f in `ls tests_acte2`; do ./acte2 tests_acte2/$$f; done; printf "\033[0;32mSuccès\033[0m sur l'acte II !\n"

tests_acte3: acte3
	@set -e; for f in `ls tests_acte3`; do ./acte3 tests_acte3/$$f; done; printf "\033[0;32mSuccès\033[0m sur l'acte III-A !\n"

tests_acte3b: acte3b
	@set -e; for f in `ls tests_acte3b`; do ./acte3b tests_acte3b/$$f; done; printf "\033[0;32mSuccès\033[0m sur l'acte III-B !\n"

tests_acte4: acte4
	set -e; for f in `ls tests_acte4`; do ./acte4 tests_acte4/$$f; done; printf "\033[0;32mSuccès\033[0m sur l'acte IV !\n"

OBJS= arbres.o arbresphylo.o listes.o common_tests.o file.o file_a.o
acte1: acte1.o $(OBJS)
acte2: acte2.o $(OBJS)
acte3: acte3.o $(OBJS)
acte3b: acte3b.o $(OBJS)
acte4: acte4.o $(OBJS)
acte5 : acte5.o $(OBJS) table_phylo.o

.PHONY: tests_acte1 tests_acte2 tests_acte3 tests_acte3b tests_acte4 

# Ici, on utilise l'"intelligence" de 'make' qui saura tout seul
# comment créer les .o à partir des .c
main: main.o arbresphylo.o arbres.o listes.o file.o file_a.o table_phylo.o

clean:
	rm -f $(PROGS) *.o
