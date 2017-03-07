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