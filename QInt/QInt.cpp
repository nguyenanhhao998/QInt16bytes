#include "QInt.h"



QInt::QInt()
{
	for (int i = 0; i <= 3; i++)
	{
		arrayBits[i] = 0;
	}
}

QInt::~QInt()
{
}

//Hàm nhập
istream& operator>>(istream& in, QInt& Q)
{
	string X; //chuoi so thap phan
	cin >> X;
	Char_toQInt(X, Q);
	return in;
}
//Hàm xuất
ostream& operator<<(ostream& out, const QInt& Q)
{
	string ChuoiSo = QInt_toChar(Q);
	out << ChuoiSo;
	return out;
}
//Hàm chuyển từ chuỗi thập phân sang QInt
void Char_toQInt(string X, QInt& Q)
{
	int dau = 0;
	if (X[0] == '-')
	{
		//Nếu là số âm thì lấy phần chuỗi số sau dấu "-"
		dau = 1;
		X = &X[1];
	}
	//Chuyển chuỗi thập phân sang bit
	int i = 0;
	while (X != "")
	{
		auto len = X.length() - 1;
		int bit = (X[len] - 48) % 2;
		Q.SetBit(i, bit); //Gán giá trị bit tại vị trí thứ i
		X = Div2(X); //Chia chuỗi số cho 2
		i++;
	}
	//Nếu là số âm thì chuyển sang dạng bù 2
	if (dau == 1)//nếu là số âm
	{
		//bù 1
		for (int i = 0; i < 4; i++)
			Q.arrayBits[i] = ~Q.arrayBits[i];
		//bù 2
		for (int i = 0; i <= 127; i++)
		{
			int bit = Q.GetBit(i);
			if (bit == 0)
			{
				Q.SetBit(i, 1);
				break;
			}
			else Q.SetBit(i, 0);
		}
	}
}
//Hàm chuyển từ QInt sang chuỗi thập phân
string QInt_toChar(const QInt &Q)
{
	string ChuoiSo = "0";
	QInt Qi = Q;
	//Xét bit dấu
	int dau = Qi.GetBit(127); //lấy bit thứ 127: là bit dấu
	if (dau == 1) //Nếu là số âm thì đưa đưa về dạng X=-Not(bù2 -1)
	{
		//Trừ đi 1
		for (int i = 0; i <= 127; i++)
		{
			int bit = Qi.GetBit(i);
			if (bit == 1)
			{
				Qi.SetBit(i, 0);
				break;
			}
			else Qi.SetBit(i, 1);
		}
		//Lấy Not
		for (int i = 3; i >= 0; i--)
		{
			Qi.arrayBits[i] = ~Qi.arrayBits[i];
		}
	}
	for (int i = 126; i >= 0; i--)
	{
		int bit = Qi.GetBit(i);
		string B = { char(bit + 48) }; //Gán bit vào chuỗi string
		//Cập nhật chuỗi số: chuoiso = 2*chuoiso + bit
		ChuoiSo = congchuoiso(multiply2(ChuoiSo), B);
	}
	if (dau == 1) ChuoiSo = (char)('-') + ChuoiSo;
	return ChuoiSo;
}
//Hàm set bit: gán trị bit tại vị trí index
void QInt:: SetBit(int index, int bit)
{
	if (index > 127 || index < 0 || bit < 0 || bit>1) return;
	//Tìm vị trí phần tử trong arraybit (mỗi phần tử 4 byte) chứa bit (0 --> 3)
	int element = 3-index/32;
	//Tìm vị trí của bit trong trong phần tử (31-->0)
	int bit_element = index % 32;
	//Bật bit
	if (bit == 1)
	{
		arrayBits[element] = (1 << bit_element) | arrayBits[element];
	}
	else
	{
		arrayBits[element] = ~(1 << bit_element)&arrayBits[element];
	}

}
//Lấy giá trị bit tại vị trí index
int QInt::GetBit(int index) const
{
	//Tìm vị trí phần tử trong arraybit (mỗi phần tử 4 byte) chứa bit (0 --> 3)
	int element = 3 - index / 32;
	//Tìm vị trí của bit trong trong phần tử (31-->0)
	int bit_element = index % 32;
	//Lấy bit:
	return arrayBits[element] >> bit_element & 1;
}

//Hàm chia chuỗi thập phân cho 2
string Div2(string S)
{
	string ChuoiKq;
	//Thuật toán trong stackoverlow
	int len = S.length();
	int add = 0;
	int flag=0; // Biến cờ để xác định có chữ số khác 0 đầu tiên (ví dụ 0005..)
	for (int i = 0; i < len; i++) // duyệt hết chuỗi
	{
		int kq = (S[i] - 48) / 2 + add;
		if ((S[i] - 48) % 2 == 1)
		{
			add = 5; //nextadd
		}
		else {
			add = 0;
		}
		if (kq != 0) flag = 1; // Phát hiện phần tử khác 0 đầu tiên
		if (flag) {
			ChuoiKq = ChuoiKq + char(kq + 48);
		}
	}
	return ChuoiKq;
}
string congchuoiso(string chuoi1, string chuoi2)
{
	string chuoikq = ""; //Chuỗi tổng
	int m = chuoi1.length() - 1;
	int n = chuoi2.length() - 1;
	int min;
	//Xác định chuỗi có dộ dài nhỏ hơn
	if (m < n) min = m;
	else min = n;
	int nho = 0; //Biến nhớ
	// Cộng phần giao nhau 2 chuỗi
	for (int i = 0; i <= min; i++)
	{
		char t = (chuoi1[m - i] - 48) + (chuoi2[n - i] - 48);
		char kq = t % 10 + nho;
		nho = t / 10;
		chuoikq = (char)(kq + 48) + chuoikq;
	}
	// Xử lí phần thừa còn lại của chuỗi 2 hoặc chuỗi 1
	if (m < n)
	{
		for (int i = n - min - 1; i >= 0; i--)
		{
			char t = chuoi2[i] - 48;
			char kq = t % 10 + nho;
			nho = t / 10;
			chuoikq = (char)(kq + 48) + chuoikq;
		}
	}
	else if (m > n)
	{
		for (int i = m - min - 1; i >= 0; i--)
		{
			char t = chuoi1[i] - 48;
			char kq = t % 10 + nho;
			nho = t / 10;
			chuoikq = (char)(kq + 48) + chuoikq;
		}
	}
	// Khi 2 chuỗi có độ dài bằng nhau
	else if (nho > 0) chuoikq = char(nho + 48) + chuoikq; //Nếu biến nhớ còn lớn hơn 0 thì thêm 1 chữ số vào đầu chuỗi
	return chuoikq;
}
string multiply2(string chuoiso)
{
	string chuoikq = ""; //chuỗi kết quả trả về
	int n = chuoiso.length() - 1;
	int nho = 0; //Biến nhớ
	for (int i = n; i >= 0; i--)
	{
		char t = (chuoiso[i] - 48) * 2;
		char kq = t % 10 + nho;
		nho = t / 10;
		chuoikq = char(kq + 48) + chuoikq; //cập nhật chuỗi kq

	}
	// nếu biến nhớ còn lớn hơn 0 thì thêm 1 chữ số có giá trị nhớ vào đầu chuỗi kq
	if (nho > 0) chuoikq = char(nho + 48) + chuoikq;
	return chuoikq;
}
//Toán tử dịch trái
QInt QInt::operator<<(int k)
{
	QInt Q2;
	if (k >= 128)
	{
		for (int i = 0; i <= 127; i++)
		{
			Q2.SetBit(i, 0);
		}
	}
	else
	{
		for (int i = k; i <= 127; i++)
		{
			int bit = this->GetBit(i - k);
			Q2.SetBit(i, bit);
		}
	}
	return Q2;
}
//Toán tử or |
QInt QInt::operator|(const QInt& Q2)
{
	QInt Qkq;
	for (int i = 0; i <= 3; i++)
	{
		Qkq.arrayBits[i] = this->arrayBits[i] | Q2.arrayBits[i];
	}
	return Qkq;
}

//Đổi từ nhị phân sang thập phân
QInt QInt::Bin_to_dec(string Bin)
{
	QInt Q;
	int len = Bin.length() - 1;
	//Nếu chiều dài của Bin lớn hơn 128 thì trả kết quả về 0;
	if (len > 127) return Q;
	else
	{
		for (int i = 0; i <= len; i++)
		{
			Q.SetBit(i,Bin[len-i] - 48); //Gán từng bit cho Q từ 0-->127
		}
	}
	return Q;
}