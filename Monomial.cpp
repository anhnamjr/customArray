#include "Monomial.h"



Monomial::Monomial()
{
	this->heSo_ = this->soMu_ = 0; // khởi tạo hệ số và số mũ bằng 0
}

Monomial::Monomial(float heSo, int soMu) // heSo va soMu là 2 giá trị truyền vào để khởi tạo
{
	this->heSo_ = heSo;
	this->soMu_ = soMu;
}

Monomial::Monomial(const Monomial & src) //tham biến truyền vào chỉ lấy giá trị, ko được thay đổi nên ta để const; src là source (nguồn)
{
	this->heSo_ = src.heSo_;
	this->soMu_ = src.soMu_;
}

Monomial & Monomial::operator=(const Monomial & src)
{
	if (this != &src) // tránh gán bằng chính nó, dẫn đến đệ quy
	{
		this->heSo_ = src.heSo_;
		this->soMu_ = src.soMu_;
	}
	return *this;
}

Monomial Monomial::operator*(const Monomial & src)
{
	Monomial result; // tạo một đơn thức kết quả
	// nhân 2 đơn thức là nhân hệ số, cộng số mũ
	result.heSo_ = this->heSo_ * src.heSo_;
	result.soMu_ = this->soMu_ + src.soMu_;
	return result;
}

Monomial Monomial::operator*(float src)
{
	return Monomial(this->heSo_*src, this->soMu_); // nhân hệ số với số thực đó
}

Monomial Monomial::operator/(const Monomial & src)
{
	Monomial result; // tạo một đơn thức kết quả
	// chia 2 đơn thức là chia hệ số, trừ số mũ
	result.heSo_ = this->heSo_ / src.heSo_;
	result.soMu_ = this->soMu_ - src.soMu_;
	return result;
}

Monomial Monomial::derivative()
{
	// đạo hàm: hệ số = hệ số * số mũ , sau đó số mũ = số mũ -1
	Monomial result;
	if (this->heSo_ == 0 || this->soMu_ == 0) return result; // trả về đơn thức mặc định có hệ số = số mũ =0
	result.heSo_ = this->heSo_ * this->soMu_;
	result.soMu_ = this->soMu_ - 1;
	return result;
}

Monomial Monomial::inf_integral()
{
	// Nguyên hàm : số mũ tăng 1, sau đó hệ số /= số mũ
	Monomial result;
	result.soMu_ = this->soMu_ + 1;
	result.heSo_ = this->heSo_ / (this->soMu_ + 1);
	return result;
}

int Monomial::getSoMu()
{
	return this->soMu_;
}

float Monomial::getHeSo()
{
	return this->heSo_;
}

Monomial Monomial::operator+(const Monomial & src)
{
	Monomial result; // kết quả
	result.soMu_ = this->soMu_;
	result.heSo_ = this->heSo_+src.heSo_; // cộng 2 đơn thức cùng số mũ thì ta cộng hệ số
	return result;
}

Monomial Monomial::operator-(const Monomial & src)
{
	Monomial result; // kết quả
	result.soMu_ = this->soMu_;
	result.heSo_ = this->heSo_ - src.heSo_; // trừ 2 đơn thức cùng số mũ thì ta trừ hệ số
	return result;
}

Monomial Monomial::operator-()
{
	Monomial result(*this);
	result.heSo_ = -result.heSo_; // lấy đơn thức âm, vd a=3x^6 thì -a = -3x^6
	return result;
}


Monomial::~Monomial()
{
}

bool Monomial::operator>(const Monomial & src)
{
	if (this->soMu_ == src.soMu_) // nếu số mũ bằng nhau thì
	{
		return (this->heSo_ > src.heSo_); // nếu hệ số vế trái lớn hơn thì return true
	}
	else return (this->soMu_ > src.soMu_); // nếu số mũ khác nhau thì đơn thức nào có số mũ lớn hơn thì lớn hơn
}

bool Monomial::operator>=(const Monomial & src)
{
	if (this->soMu_ == src.soMu_) // nếu số mũ bằng nhau thì
	{
		return (this->heSo_ >= src.heSo_); // nếu hệ số vế trái lớn hơn hoặc bằng thì return true
	}
	else return (this->soMu_ > src.soMu_); // nếu số mũ khác nhau thì đơn thức nào có số mũ lớn hơn thì lớn hơn

}

bool Monomial::operator!=(const Monomial & src)
{
	// nếu hệ số khác nhau, hoặc số mũ khác nhau thì 2 đơn thức khác nhau
	if (this->heSo_ != src.heSo_ || this->soMu_ != src.soMu_)
		return true; 
	else return false;
}

bool Monomial::operator==(const Monomial & src)
{
	return !(*this != src); // không bằng thì khác 
}

bool Monomial::operator<(const Monomial & src)
{
	if (this->soMu_ == src.soMu_) // nếu số mũ bằng nhau thì
	{
		return (this->heSo_ < src.heSo_); // nếu hệ số vế trái lớn hơn thì return true
	}
	else return (this->soMu_ < src.soMu_); // nếu số mũ khác nhau thì đơn thức nào có số mũ bé hơn thì bé hơn
}

ostream & operator<<(ostream & os, const Monomial & src) // hàm xuất
{
	os << src.heSo_ << "x^" << src.soMu_;
	return os;
}
