-steps to run this file


$yacc -d calc.y
$lex calc.l
$gcc lex.yy.x y.tab.c -w
$./a.out
