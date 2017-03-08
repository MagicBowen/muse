# Generated from Promise.g4 by ANTLR 4.6
from antlr4 import *
if __name__ is not None and "." in __name__:
    from .PromiseParser import PromiseParser
else:
    from PromiseParser import PromiseParser

# This class defines a complete listener for a parse tree produced by PromiseParser.
class PromiseListener(ParseTreeListener):

    # Enter a parse tree produced by PromiseParser#prog.
    def enterProg(self, ctx:PromiseParser.ProgContext):
        pass

    # Exit a parse tree produced by PromiseParser#prog.
    def exitProg(self, ctx:PromiseParser.ProgContext):
        pass


    # Enter a parse tree produced by PromiseParser#factdef.
    def enterFactdef(self, ctx:PromiseParser.FactdefContext):
        pass

    # Exit a parse tree produced by PromiseParser#factdef.
    def exitFactdef(self, ctx:PromiseParser.FactdefContext):
        pass


    # Enter a parse tree produced by PromiseParser#fact.
    def enterFact(self, ctx:PromiseParser.FactContext):
        pass

    # Exit a parse tree produced by PromiseParser#fact.
    def exitFact(self, ctx:PromiseParser.FactContext):
        pass


    # Enter a parse tree produced by PromiseParser#pfact.
    def enterPfact(self, ctx:PromiseParser.PfactContext):
        pass

    # Exit a parse tree produced by PromiseParser#pfact.
    def exitPfact(self, ctx:PromiseParser.PfactContext):
        pass


    # Enter a parse tree produced by PromiseParser#locationFact.
    def enterLocationFact(self, ctx:PromiseParser.LocationFactContext):
        pass

    # Exit a parse tree produced by PromiseParser#locationFact.
    def exitLocationFact(self, ctx:PromiseParser.LocationFactContext):
        pass


    # Enter a parse tree produced by PromiseParser#durationFact.
    def enterDurationFact(self, ctx:PromiseParser.DurationFactContext):
        pass

    # Exit a parse tree produced by PromiseParser#durationFact.
    def exitDurationFact(self, ctx:PromiseParser.DurationFactContext):
        pass


    # Enter a parse tree produced by PromiseParser#laneChangeFact.
    def enterLaneChangeFact(self, ctx:PromiseParser.LaneChangeFactContext):
        pass

    # Exit a parse tree produced by PromiseParser#laneChangeFact.
    def exitLaneChangeFact(self, ctx:PromiseParser.LaneChangeFactContext):
        pass


    # Enter a parse tree produced by PromiseParser#laneGapFact.
    def enterLaneGapFact(self, ctx:PromiseParser.LaneGapFactContext):
        pass

    # Exit a parse tree produced by PromiseParser#laneGapFact.
    def exitLaneGapFact(self, ctx:PromiseParser.LaneGapFactContext):
        pass


    # Enter a parse tree produced by PromiseParser#distanceToFact.
    def enterDistanceToFact(self, ctx:PromiseParser.DistanceToFactContext):
        pass

    # Exit a parse tree produced by PromiseParser#distanceToFact.
    def exitDistanceToFact(self, ctx:PromiseParser.DistanceToFactContext):
        pass


    # Enter a parse tree produced by PromiseParser#equalToPred.
    def enterEqualToPred(self, ctx:PromiseParser.EqualToPredContext):
        pass

    # Exit a parse tree produced by PromiseParser#equalToPred.
    def exitEqualToPred(self, ctx:PromiseParser.EqualToPredContext):
        pass


    # Enter a parse tree produced by PromiseParser#lessThanPred.
    def enterLessThanPred(self, ctx:PromiseParser.LessThanPredContext):
        pass

    # Exit a parse tree produced by PromiseParser#lessThanPred.
    def exitLessThanPred(self, ctx:PromiseParser.LessThanPredContext):
        pass


    # Enter a parse tree produced by PromiseParser#greaterThanPred.
    def enterGreaterThanPred(self, ctx:PromiseParser.GreaterThanPredContext):
        pass

    # Exit a parse tree produced by PromiseParser#greaterThanPred.
    def exitGreaterThanPred(self, ctx:PromiseParser.GreaterThanPredContext):
        pass


    # Enter a parse tree produced by PromiseParser#betweenPred.
    def enterBetweenPred(self, ctx:PromiseParser.BetweenPredContext):
        pass

    # Exit a parse tree produced by PromiseParser#betweenPred.
    def exitBetweenPred(self, ctx:PromiseParser.BetweenPredContext):
        pass


    # Enter a parse tree produced by PromiseParser#averageAlgo.
    def enterAverageAlgo(self, ctx:PromiseParser.AverageAlgoContext):
        pass

    # Exit a parse tree produced by PromiseParser#averageAlgo.
    def exitAverageAlgo(self, ctx:PromiseParser.AverageAlgoContext):
        pass


    # Enter a parse tree produced by PromiseParser#varianceAlgo.
    def enterVarianceAlgo(self, ctx:PromiseParser.VarianceAlgoContext):
        pass

    # Exit a parse tree produced by PromiseParser#varianceAlgo.
    def exitVarianceAlgo(self, ctx:PromiseParser.VarianceAlgoContext):
        pass


    # Enter a parse tree produced by PromiseParser#collisionFact.
    def enterCollisionFact(self, ctx:PromiseParser.CollisionFactContext):
        pass

    # Exit a parse tree produced by PromiseParser#collisionFact.
    def exitCollisionFact(self, ctx:PromiseParser.CollisionFactContext):
        pass


    # Enter a parse tree produced by PromiseParser#stopFact.
    def enterStopFact(self, ctx:PromiseParser.StopFactContext):
        pass

    # Exit a parse tree produced by PromiseParser#stopFact.
    def exitStopFact(self, ctx:PromiseParser.StopFactContext):
        pass


    # Enter a parse tree produced by PromiseParser#promisedef.
    def enterPromisedef(self, ctx:PromiseParser.PromisedefContext):
        pass

    # Exit a parse tree produced by PromiseParser#promisedef.
    def exitPromisedef(self, ctx:PromiseParser.PromisedefContext):
        pass


    # Enter a parse tree produced by PromiseParser#exist.
    def enterExist(self, ctx:PromiseParser.ExistContext):
        pass

    # Exit a parse tree produced by PromiseParser#exist.
    def exitExist(self, ctx:PromiseParser.ExistContext):
        pass


    # Enter a parse tree produced by PromiseParser#parens.
    def enterParens(self, ctx:PromiseParser.ParensContext):
        pass

    # Exit a parse tree produced by PromiseParser#parens.
    def exitParens(self, ctx:PromiseParser.ParensContext):
        pass


    # Enter a parse tree produced by PromiseParser#sequential.
    def enterSequential(self, ctx:PromiseParser.SequentialContext):
        pass

    # Exit a parse tree produced by PromiseParser#sequential.
    def exitSequential(self, ctx:PromiseParser.SequentialContext):
        pass


    # Enter a parse tree produced by PromiseParser#concurrent.
    def enterConcurrent(self, ctx:PromiseParser.ConcurrentContext):
        pass

    # Exit a parse tree produced by PromiseParser#concurrent.
    def exitConcurrent(self, ctx:PromiseParser.ConcurrentContext):
        pass


    # Enter a parse tree produced by PromiseParser#optional.
    def enterOptional(self, ctx:PromiseParser.OptionalContext):
        pass

    # Exit a parse tree produced by PromiseParser#optional.
    def exitOptional(self, ctx:PromiseParser.OptionalContext):
        pass


    # Enter a parse tree produced by PromiseParser#until.
    def enterUntil(self, ctx:PromiseParser.UntilContext):
        pass

    # Exit a parse tree produced by PromiseParser#until.
    def exitUntil(self, ctx:PromiseParser.UntilContext):
        pass


    # Enter a parse tree produced by PromiseParser#notExist.
    def enterNotExist(self, ctx:PromiseParser.NotExistContext):
        pass

    # Exit a parse tree produced by PromiseParser#notExist.
    def exitNotExist(self, ctx:PromiseParser.NotExistContext):
        pass


    # Enter a parse tree produced by PromiseParser#daemon.
    def enterDaemon(self, ctx:PromiseParser.DaemonContext):
        pass

    # Exit a parse tree produced by PromiseParser#daemon.
    def exitDaemon(self, ctx:PromiseParser.DaemonContext):
        pass


    # Enter a parse tree produced by PromiseParser#factId.
    def enterFactId(self, ctx:PromiseParser.FactIdContext):
        pass

    # Exit a parse tree produced by PromiseParser#factId.
    def exitFactId(self, ctx:PromiseParser.FactIdContext):
        pass


    # Enter a parse tree produced by PromiseParser#closureFactId.
    def enterClosureFactId(self, ctx:PromiseParser.ClosureFactIdContext):
        pass

    # Exit a parse tree produced by PromiseParser#closureFactId.
    def exitClosureFactId(self, ctx:PromiseParser.ClosureFactIdContext):
        pass


    # Enter a parse tree produced by PromiseParser#factName.
    def enterFactName(self, ctx:PromiseParser.FactNameContext):
        pass

    # Exit a parse tree produced by PromiseParser#factName.
    def exitFactName(self, ctx:PromiseParser.FactNameContext):
        pass


    # Enter a parse tree produced by PromiseParser#closureFactName.
    def enterClosureFactName(self, ctx:PromiseParser.ClosureFactNameContext):
        pass

    # Exit a parse tree produced by PromiseParser#closureFactName.
    def exitClosureFactName(self, ctx:PromiseParser.ClosureFactNameContext):
        pass


    # Enter a parse tree produced by PromiseParser#param.
    def enterParam(self, ctx:PromiseParser.ParamContext):
        pass

    # Exit a parse tree produced by PromiseParser#param.
    def exitParam(self, ctx:PromiseParser.ParamContext):
        pass


    # Enter a parse tree produced by PromiseParser#value.
    def enterValue(self, ctx:PromiseParser.ValueContext):
        pass

    # Exit a parse tree produced by PromiseParser#value.
    def exitValue(self, ctx:PromiseParser.ValueContext):
        pass


    # Enter a parse tree produced by PromiseParser#unit.
    def enterUnit(self, ctx:PromiseParser.UnitContext):
        pass

    # Exit a parse tree produced by PromiseParser#unit.
    def exitUnit(self, ctx:PromiseParser.UnitContext):
        pass


