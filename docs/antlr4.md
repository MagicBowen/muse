# antlr4 for promise

## antlr

### prepare

- Install Java (version 1.6 or higher).
- make sure you java install ok

~~~
$ java -version
$ javac -version
~~~

- download antlr4

~~~
$ cd /usr/local/lib
$ curl -O http://www.antlr.org/download/antlr-4.5.3-complete.jar
~~~

- modify you bashrc file, add following:

~~~
export CLASSPATH=".:/usr/local/lib/antlr-4.5.3-complete.jar:$CLASSPATH"

alias antlr4='java -Xmx500M -cp "/usr/local/lib/antlr-4.5.3-complete.jar:$CLASSPATH" org.antlr.v4.Tool'

alias grun='java org.antlr.v4.gui.TestRig'
~~~

- make sure antlr4 installed ok

~~~
$ java org.antlr.v4.Tool
ANTLR Parser Generator Version 4.5.3
-o ___ specify output directory where all output is generated
-lib ___ specify location of .tokens files
...
~~~

### test antlr4

In a temporary directory, put the following grammar inside file Hello.g4: Hello.g4

~~~
// Define a grammar called Hello
grammar Hello;
r  : 'hello' ID ;         // match keyword hello followed by an identifier
ID : [a-z]+ ;             // match lower-case identifiers
WS : [ \t\r\n]+ -> skip ; // skip spaces, tabs, newlines
~~~

Then run ANTLR the tool on it:

~~~
$ cd /tmp
$ antlr4 Hello.g4
$ javac Hello*.java
~~~

Now test it:

~~~
$ grun Hello r -tree
hello parrt
^D
(r hello parrt)
(That ^D means EOF on unix; it's ^Z in Windows.) The -tree option prints the parse tree in LISP notation.
It's nicer to look at parse trees visually.
$ grun Hello r -gui
hello parrt
^D
~~~

![](pics/hello-parrt.png.png)

## python

### prepare

- install python3

- download python3 runtime for antlr4:
  [antlr4-python3-runtime](https://pypi.python.org/pypi/antlr4-python3-runtime/)

- also you can install the runtime by pip

~~~
$ pip3 install antlr4-python3-runtime
~~~

### generate

~~~
$ cd muse/dsl
$ antlr4 -visitor -Dlanguage=Python3 Promise.g4 -o ./py-check
~~~

### check syntax

In dsl/py-check folder, already exists two python files for promise syntax check.

~~~python
# PromiseSyntaxVisitor.py

from PromiseVisitor import PromiseVisitor
from PromiseParser import PromiseParser

class PromiseSyntaxVisitor(PromiseVisitor):
    def __init__(self):
        self.factIdTable = []

    def visitFactdef(self, ctx):
        id = ctx.ID().getText()
        if id in self.factIdTable:
            raise SyntaxError("Error: duplicate fact id {0}".format(id))
        else:
            self.factIdTable.append(id)
        return 0

    def visitFactId(self, ctx):
        return self.__checkFactIdDefined(ctx)

    def visitClosureFactId(self, ctx):
        return self.__checkFactIdDefined(ctx)

    def __checkFactIdDefined(self, ctx):
        id = ctx.ID().getText()
        if id not in self.factIdTable:
            raise SyntaxError("Error: undefined fact id {0}".format(id))
        return 0
~~~

~~~python
# SyntaxChecker.py

import os
import sys
from antlr4 import *
from antlr4.InputStream import InputStream
from PromiseLexer import PromiseLexer
from PromiseParser import PromiseParser
from PromiseSyntaxVisitor import PromiseSyntaxVisitor

def main():
    input_stream = FileStream(sys.argv[1])
    lexer = PromiseLexer(input_stream)
    token_stream = CommonTokenStream(lexer)
    parser = PromiseParser(token_stream)
    tree = parser.prog()

    visitor = PromiseSyntaxVisitor()
    visitor.visit(tree)

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: python {0} <syntax file>".format(os.path.basename(__file__)))
        sys.exit(1)

    main()
    print('parse ok!')
~~~

### test

~~~
cd py-check
$ python3 SyntaxChecker.py ../expr.txt
parse ok!
~~~


## cpp

### prepare

- download cpp runtime for antlr4:
  [antlr4-cpp-runtime](http://www.soft-gems.net/index.php/tools/49-the-antlr4-c-target-is-here)

### generate

~~~
$ cd muse/dsl
$ antlr4 -visitor -Dlanguage=Cpp Promise.g4 -o ./cpp-syntax
~~~

### test

~~~
$ mkdir build
$ cd build
cmake ../cpp-syntax
make
~~~

