#include<iostream>
#include"brass.h"
using std::cout;
using std::endl;
using std::string;

typedef std::ios_base::fmtflags format;
typedef std::streamsize precis;
format setFormat();
void restore(format f, precis p);
Brass::Brass(const string& s, long an, double bal)
{
	fullName = s;
	acctNum = an;
	balance = bal;
}
void Brass::Deposit(double amt)
{
	if (amt < 0)
		cout << "Negative deposit not allowed; deposit is cancelled." << endl;
	else
		balance += amt;
}
void Brass::Wthdraw(double amt)
{
	format initialSate = setFormat();
	precis prec = cout.precision(2);
	if (amt < 0)
		cout << "Withdrawal amout must be positive; withdrawal canceled.\n";
	else if (amt <= balance)
		balance -= amt;
	else
		cout << "Withdrawal amout of $" << amt << " exceeds your balance." << endl << "Withdrawal canceled." << endl;
	restore(initialSate, prec);
}
double Brass::Balance() const
{
	return balance;
}
void Brass::ViewAcct() const
{
	format initialSate = setFormat();
	precis prec = cout.precision(2);
	cout << "Client:" << fullName << endl;
	cout << "Account Number: " << acctNum << endl;
	cout << "Balance: $" << balance << endl;
	restore(initialSate, prec);
}
BrassPlus::BrassPlus(const string& s, long an, double bal, double m1, double r):Brass(s,an,bal)
{
	maxLoan = m1;
	owesBank = 0.0;
	rate = r;
}
BrassPlus::BrassPlus(const Brass& ba, double m1, double r) :Brass(ba)
{
	maxLoan = m1;
	owesBank = 0.0;
	rate = r;
}
void BrassPlus::ViewAcct() const
{
	format initialSate = setFormat();
	precis prec = cout.precision(2);
	Brass::ViewAcct();
	cout << "Maximum loan: $" << maxLoan << endl;
	cout << "Owed to bank: $" << owesBank << endl;
	cout.precision(3);
	cout << "Loan Rate: " << 100 * rate << "%" << endl;
	restore(initialSate, prec);
}
void BrassPlus::Withdraw(double amt)
{
	format initialSate = setFormat();
	precis prec = cout.precision(2);
	double bal = Balance();
	if (amt <= bal)
		Brass::Wthdraw(amt);
	else if (amt <= bal + maxLoan - owesBank)
	{
		double advance = amt - bal;
		owesBank += advance * (1.0 + rate);
		cout << "Bank advance: $" << advance << endl;
		cout << "Finance charge: $" << advance * rate << endl;
		Deposit(advance);
		Brass::Wthdraw(amt);
	}
	else
		cout << "Credit limit exceeded.Transaction cancelled." << endl;
	restore(initialSate, prec);
}
format setFormat()
{
	return cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
}
void restore(format f, precis p)
{
	cout.setf(f, std::ios_base::floatfield);
	cout.precision(p);
}
