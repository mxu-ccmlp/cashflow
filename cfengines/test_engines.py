import cfengines
import cfengines.cfengine
import cffuncs
def test():
    print(cfengines.__version__)
    print(cffuncs.__version__)
    print(cffuncs.calc_default(1,1,[2]))
    print(cfengines.cfengine.calc_cashflow(1000, 0.05, 12,calc_default=cffuncs.calc_default,calc_prepay=cffuncs.calc_prepayment,calc_dq=cffuncs.calc_dq))
if __name__ == "__main__":
    test()