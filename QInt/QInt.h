#ifndef __QInt_H__
#define __QInt_H__

#include <iostream>
#include <string>
using namespace std;

class QInt
{
private:
	int arrayBits[4];
	// Qui ước đánh số thứ tự bit từ phải sang trái (127 <--- 0)
	// Mỗi phần tử có 32 bit (31 <-- 0)
public:
	QInt();
	~QInt();
public:

	//Đổi từ nhị phân sang thập phân
	static QInt Bin_to_dec(string Bin);

	//Toán tử dịch trái
	QInt operator<<(int);

	//Toán tử or |
	QInt operator|(const QInt&);

public:
	//Set bit: gán giá trị bit tại vị trí index
	void SetBit(int index, int bit);
	//Lấy giá trị bit tại vị trí index
	int GetBit(int index) const;

	//Toán tử nhập
	friend istream& operator>>(istream&, QInt&);
	//Toán tử xuất
	friend ostream& operator<<(ostream&, const QInt&);

	//Hàm chuyển từ chuỗi thập phân sang QInt
	friend void Char_toQInt(string X, QInt& Q);
	//Hàm chuyển từ QInt sang chuỗi thập phân
	friend string QInt_toChar(const QInt &Q);
	
};

   /*Các hàm xử lí chuỗi số thập phân*/

//Hàm chia chuỗi số thập phân cho 2
string Div2(string S);
//Hàm nhân chuỗi số thập phần không âm cho 2
string multiply2(string chuoiso);
//Hàm cộng 2 chuỗi số thập phân không âm
string congchuoiso(string chuoi1, string chuoi2);

#endif
