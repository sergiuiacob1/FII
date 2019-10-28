all:
	flex angryc.l
	yacc -dy angryc.y
	g++ lex.yy.c y.tab.c utils.cpp -ll -ly 