grammar Promise;

prog:   (def)* expr;

def:   ID ':' fact END;

fact   :   sfact
       |   pfact
       ;

pfact  : pfdef 'predicate that' pred ;

pfdef  :  'distance to vehicle ' INT
       |  'duration'
       |  'lane change'
       |  'lane gap'
       ;

pred   : 'equal to' param
       | 'less than' param
       | 'greater than' param
       | 'between' param 'and' param
       ;

sfact  : 'collision'
       | 'stop'
       ;  

expr   :   expr '&&' expr  # con
       |   expr '||' expr  # opt
       |   expr '->' expr  # seq
       |   expr '-|' expr  # until
       |   expr '-<' expr  # daemon
       |   '!' ID          # notExist
       |   ID              # exist
       |   sfact           # simpleFact  
       |   '(' expr ')'    # parens
       ;   

param  :   value unit* ;

value  :   INT | FLOAT ; 

unit   :   'm'
       |   's'
       |   'km/h' 
       ;        

NOT    :   '!'  ;
CON    :   '&&' ;
OPT    :   '||' ;
SEQ    :   '->' ;
UNTIL  :   '-|' ;
DAEMON :   '-<' ;
ID     :   [A-Za-z]+ [0-9]* ;
INT    :   [0-9]+ ;
FLOAT  :   [0-9]+ '.' [0-9]+ ;  
END    :   '.' ;       
WS     :   [ \t\r\n]+ -> skip ;