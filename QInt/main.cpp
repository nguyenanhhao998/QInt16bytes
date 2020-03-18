#include "QInt.h"


void main()
{
	string Bits="111000111011100011110011010111001101110101011";
	QInt Q = QInt::Bin_to_dec(Bits);
	cout << Bits << " = " << Q << endl;
	system("pause");
}