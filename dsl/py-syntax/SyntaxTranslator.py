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

    # result is a dictionary generated when visiting
    def get_result(self):
        return self.result


    # Visit a parse tree produced by PromiseParser#prog.
    def visitProg(self, ctx:PromiseParser.ProgContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#factdef.
    def visitFactdef(self, ctx:PromiseParser.FactdefContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#fact.
    def visitFact(self, ctx:PromiseParser.FactContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#pfact.
    def visitPfact(self, ctx:PromiseParser.PfactContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#locationFact.
    def visitLocationFact(self, ctx:PromiseParser.LocationFactContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#durationFact.
    def visitDurationFact(self, ctx:PromiseParser.DurationFactContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#laneChangeFact.
    def visitLaneChangeFact(self, ctx:PromiseParser.LaneChangeFactContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#laneGapFact.
    def visitLaneGapFact(self, ctx:PromiseParser.LaneGapFactContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#distanceToFact.
    def visitDistanceToFact(self, ctx:PromiseParser.DistanceToFactContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#equalToPred.
    def visitEqualToPred(self, ctx:PromiseParser.EqualToPredContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#lessThanPred.
    def visitLessThanPred(self, ctx:PromiseParser.LessThanPredContext):
        return self.visitChildren(ctx)
        

    # Visit a parse tree produced by PromiseParser#greaterThanPred.
    def visitGreaterThanPred(self, ctx:PromiseParser.GreaterThanPredContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#betweenPred.
    def visitBetweenPred(self, ctx:PromiseParser.BetweenPredContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#averageAlgo.
    def visitAverageAlgo(self, ctx:PromiseParser.AverageAlgoContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#varianceAlgo.
    def visitVarianceAlgo(self, ctx:PromiseParser.VarianceAlgoContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#collisionFact.
    def visitCollisionFact(self, ctx:PromiseParser.CollisionFactContext):
        return {'name' : 'collision'}


    # Visit a parse tree produced by PromiseParser#stopFact.
    def visitStopFact(self, ctx:PromiseParser.StopFactContext):
        return {'name' : 'stop'}


    # Visit a parse tree produced by PromiseParser#promisedef.
    def visitPromisedef(self, ctx:PromiseParser.PromisedefContext):
        self.result = ctx.promise().accept(self)


    # Visit a parse tree produced by PromiseParser#exist.
    def visitExist(self, ctx:PromiseParser.ExistContext):
        fact = self.visitChildren(ctx)
        return {'type' : 'exist', 'fact' : fact}


    # Visit a parse tree produced by PromiseParser#parens.
    def visitParens(self, ctx:PromiseParser.ParensContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#sequential.
    def visitSequential(self, ctx:PromiseParser.SequentialContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#concurrent.
    def visitConcurrent(self, ctx:PromiseParser.ConcurrentContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#optional.
    def visitOptional(self, ctx:PromiseParser.OptionalContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#until.
    def visitUntil(self, ctx:PromiseParser.UntilContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#notExist.
    def visitNotExist(self, ctx:PromiseParser.NotExistContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#daemon.
    def visitDaemon(self, ctx:PromiseParser.DaemonContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#factId.
    def visitFactId(self, ctx:PromiseParser.FactIdContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#closureFactId.
    def visitClosureFactId(self, ctx:PromiseParser.ClosureFactIdContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#factName.
    def visitFactName(self, ctx:PromiseParser.FactNameContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#closureFactName.
    def visitClosureFactName(self, ctx:PromiseParser.ClosureFactNameContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#param.
    def visitParam(self, ctx:PromiseParser.ParamContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#value.
    def visitValue(self, ctx:PromiseParser.ValueContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PromiseParser#unit.
    def visitUnit(self, ctx:PromiseParser.UnitContext):
        return self.visitChildren(ctx)


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
