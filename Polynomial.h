#pragma once
#include"CustomArray.h"
#include<fstream>

class Polynomial
{
private:
	int soLuong_;
	CustomArray<Monomial> poly_;
public:
	Polynomial() // phương thức khởi tạo mặc định
	{
		soLuong_ = 0;
	}
	Polynomial(CustomArray<Monomial> src); // phương thức khởi tạo từ một mảng đơn thức.
	Polynomial(const char *src); //phương thức khởi tạo từ một chuổi.
	Polynomial(const Polynomial &src);// phương thức khởi tạo sao chép
	void pushBack(const Monomial &src);// thêm một đơn thức vào
	Polynomial &operator=(Polynomial &src);// toán tử gán =
	Monomial operator[](int i); // trả về đơn thức ở vị trí i
	void sortPoly();
	Polynomial& operator+(const Polynomial &src); // cộng 2 đa thức
	Polynomial& operator+(float src); // cộng đa thức với một số thực
	Polynomial& operator-(const Polynomial &src); // trừ 2 đa thức
	Polynomial& operator-(float src); // trừ đa thức với một số thực       
	Polynomial& operator*(const Monomial &src); // nhân đa thức với đơn thức
	Polynomial& operator*(const Polynomial &src); // nhân 2 đa thức
	Polynomial& operator*(float src); // nhân đa thức với một số thực  
	Polynomial& operator/( Polynomial src); // toán tử chia lấy nguyên
	Polynomial& operator%(Polynomial src); // toán tử chia lấy dư
	Polynomial derivative(); // đạo hàm của đa thức
	Polynomial inf_integral(); //nguyên hàm của đa thức

	~Polynomial();// phương thức hủy
	void xuat();
	int getSoLuong(); // lấy số lượng

};

void docGhiFile(const char*input, const char*output); // đọc file và ghi file
