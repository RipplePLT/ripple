.PHONY: default
default:
	lex ripple.l
	gcc lex.yy.c

.PHONY: clean
clean:
	rm lex.yy.c a.out

.PHONY: all
all: clean default
