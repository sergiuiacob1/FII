all:
	flex lex.l
	yacc -d yacc.y
	gcc lex.yy.c y.tab.c utils.c -ll -ly 