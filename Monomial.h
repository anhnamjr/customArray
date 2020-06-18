#pragma once
#include <iostream>

using namespace std;

class Monomial // lớp đơn thức
{
private:
	// thuộc tính class có dấu "_"  ở cuối để phân biệt với biến bình thường
	float heSo_; // hệ số
	int soMu_; // số mũ
public:
	Monomial();// phương thức khởi tạo mặc định 
	Monomial(float heSo, int soMu); //Khởi tạo từ hệ số và số mũ truyền vào
	Monomial(const Monomial &src); // Phương thức khởi tạo sao chép
	~Monomial(); // phương thức hủy
	Monomial &operator=(const Monomial &src); // toán tử gán bằng
	Monomial operator*(const Monomial &src); // toán tử nhân
	Monomial operator*(float src);// nhân đơn thức với một số thực
	Monomial operator/(const Monomial &src); // toán tử chia
	Monomial derivative(); // tính đạo hàm của đơn thức
	Monomial inf_integral();// Tính nguyên hàm của đơn thức
	int getSoMu();
	float getHeSo();
	Monomial operator+(const Monomial &src); // cộng 2 đơn thức có cùng số mũ
	Monomial operator-(const Monomial &src); // cộng 2 đơn thức có cùng số mũ
	Monomial operator-(); // lấy âm (đơn thức + lại = 0 )
	bool operator>(const Monomial &src); // toán tử so sánh 
	bool operator>=(const Monomial &src); 
	bool operator!=(const Monomial &src);
	bool operator==(const Monomial &src);
	bool operator<(const Monomial &src);
	friend ostream& operator<<(ostream &os, const Monomial &src); // xuất đơn thức để test
};

