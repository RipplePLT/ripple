.PHONY: default
default: gcc

gcc: lex yacc
	gcc lex.yy.c  y.tab.c -ly -ll

yacc:
	yacc ripple.y

lex:
	lex ripple.l

.PHONY: clean
clean:
	rm lex.yy.c a.out

.PHONY: all
all: clean default
