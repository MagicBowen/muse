grammar Promise;

prog:   (factdef)* promisedef;

factdef  :   ID ':' fact END;

fact     :   sfact
         |   pfact
         ;

pfact    : pfname 'predicate that' algo? pred ;

pfname   :  'location'                    # locationFact
         |  'duration'                    # durationFact
         |  'lane change'                 # laneChangeFact
         |  'lane gap'                    # laneGapFact
         |  'distance to vehicle' INT     # distanceToFact
         ;

pred     : 'equal to' param               # equalToPred
         | 'less than' param              # lessThanPred
         | 'greater than' param           # greaterThanPred
         | 'between' param 'and' param    # betweenPred
         ;

algo     : 'average'                      # averageAlgo
         | 'variance'                     # varianceAlgo
         ;

sfact    : 'collision'                    # collisionFact
         | 'stop'                         # stopFact
         ;

promisedef  : 'promise' ':' promise END;  

promise  :   promise '&&' promise         # concurrent
         |   promise '||' promise         # optional
         |   promise '->' promise         # sequential
         |   promise '-|' promise         # until
         |   promise '-<' promise         # daemon
         |   '!' basepromise              # notExist
         |   basepromise                  # exist 
         |   '(' promise ')'              # parens
         ;         

basepromise : ID                          # factId
            | '[' ID ']'                  # closureFactId
            | sfact                       # factName
            | '[' sfact ']'               # closureFactName
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