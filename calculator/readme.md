-steps to run this file<br>


$yacc -d calc.y<br>
$lex calc.l<br>
$gcc lex.yy.x y.tab.c -w<br>
$./a.out<br>
