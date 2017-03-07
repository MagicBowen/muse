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


