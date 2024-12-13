import cffuncs
def calc_cashflow(principal, rate, term, calc_prepay=cffuncs.calc_prepayment,calc_default=cffuncs.calc_default,calc_dq=cffuncs.calc_dq):
    """Calculate the cashflow for a loan."""
    # Calculate the monthly payment
    monthly_rate = rate / 12
    monthly_payment = principal * (monthly_rate / (1 - (1 + monthly_rate) ** -term))
    # Initialize the cashflow
    cashflow = []
    balance = principal
    # Calculate the cashflow for each month
    for i in range(term):
        interest = balance * monthly_rate
        principal = monthly_payment - interest
        balance -= principal
        # Calculate the default and prepayment amounts
        defaultamt = calc_default(i, int(principal), [rate])
        prepayment = calc_prepay(i, int(principal), [rate])
        # Calculate the DQ amount
        dqamt = calc_dq(i, int(principal), [rate])
        cashflow.append({'month': i, 'interest': interest, 'principal': principal, 'balance': balance, 'default': defaultamt, 'prepayment': prepayment, 'dq': dqamt})
        balance += dqamt
    return cashflow