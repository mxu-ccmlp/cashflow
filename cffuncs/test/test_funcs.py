import datetime
import json
import cffuncs

def test2():
    print(cffuncs.__version__)
    print(cffuncs.calc_default(1,2,[3]))
    print(cffuncs.calc_dq(1,2,[3]))
    print(cffuncs.calc_prepayment(1,2,[3]))
if __name__ == '__main__':
    test2()