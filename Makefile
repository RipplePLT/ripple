.PHONY: default
default: gcc

gcc: yacc lex 
	gcc lex.yy.c  y.tab.c -ly -ll

yacc:
	yacc -Wall ripple.y

lex:
	lex ripple.l

.PHONY: clean
clean:
	rm -rf lex.yy.c y.tab.h y.tab.c a.out

.PHONY: all
all: clean default
