import os
import sys
import json
from antlr4 import *
from antlr4.InputStream import InputStream
from antlr4.error.ErrorListener import ErrorListener
from PromiseLexer import PromiseLexer
from PromiseParser import PromiseParser
from PromiseVisitor import PromiseVisitor



class SyntaxErrorListener( ErrorListener ):
    def syntaxError(self, recognizer, offendingSymbol, line, column, msg, e):
        error_msg = '{}:{}: syntax ERROR, {}'.format(line, column, msg)
        raise SyntaxError(error_msg)

    def reportAmbiguity(self, recognizer, dfa, startIndex, stopIndex, exact, ambigAlts, configs):
        error_msg = 'Ambiguity ERROR: {}'.format(configs)
        raise SyntaxError(error_msg)

    def reportAttemptingFullContext(self, recognizer, dfa, startIndex, stopIndex, conflictingAlts, configs):
        error_msg = 'Attempting full context ERROR: {}'.format(configs)
        raise SyntaxError(error_msg)

    def reportContextSensitivity(self, recognizer, dfa, startIndex, stopIndex, prediction, configs):
        error_msg = 'Context ERROR: {}'.format(configs)
        raise SyntaxError(error_msg)



class PromiseSyntaxVisitor( PromiseVisitor ):
    def __init__(self):
        self.factIdTable = []
        self.result = {}

    def get_result(self):
        return self.result

    def visitPromisedef(self, ctx):
        self.result = ctx.promise().accept(self)

    def visitCollisionFact(self, ctx):
        print('visitCollisionFact in PromiseSyntaxVisitor')
        return {'name' : 'collision'}

    def visitStopFact(self, ctx):
        print('visitStopFact in PromiseSyntaxVisitor')
        return {'name' : 'stop'}

    def visitExist(self, ctx):
        print('visitExist in PromiseSyntaxVisitor')
        fact = self.visitChildren(ctx)
        return {'type' : 'exist', 'fact' : fact}

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



def _parse(input):
    input_stream = InputStream(input)
    lexer = PromiseLexer(input_stream)
    token_stream = CommonTokenStream(lexer)
    parser = PromiseParser(token_stream)
    parser._listeners = [SyntaxErrorListener()]
    tree = parser.prog()
    visitor = PromiseSyntaxVisitor()
    visitor.visit(tree)
    return json.dumps(visitor.get_result())



def parse_to_json(input_str):
    if input_str.strip() == '': 
        return ''

    try:
        result = _parse(input_str)
        return result

    except Exception as e:
        print(str(e))
