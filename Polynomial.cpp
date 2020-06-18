#include "Polynomial.h"


using namespace std;


Polynomial::Polynomial(CustomArray<Monomial> src)
{
	soLuong_ = src.size();
	for (int i = 0; i < soLuong_; i++)
		poly_.push_back(src[i]);
}

Polynomial::Polynomial(const char *src)
{
	string str; // str dùng để lưu số, có thể là hệ số, có thể là số mũ
	soLuong_ = 0;
	string::size_type sizeStr;
	float heSo;
	int soMu;
	for (int i = 0; i < strlen(src); i++)
	{
		if (src[i] == '.' || src[i] == '+' || src[i] == '-' || (src[i] <= '9' && src[i] >= '0')) // nếu là . - + hay chữ số thì push vào
		{
			str.push_back(src[i]);
		}
		else if (src[i] == 'x') // nếu là src[i] = x thì chúng ta chuyển thành hệ số
		{
			heSo = stof(str, &sizeStr); // hàm chuyển str thanh hệ số
			str.clear();// sau đó ta clear str
		}
		else if (src[i] == ' ') // neu den dau ' ' thì chúng ta chuyển str thành số mũ
		{
			soMu = stof(str, &sizeStr);
			str.clear(); // sau đó lại clear str
			Monomial donThuc(heSo, soMu);
			poly_.push_back(donThuc);
			soLuong_++; // số lương tăng lên.
		}
		if (src[i + 1] == '\0')// vì trong chuổi mỗi đơn thức cách nhau dấu ' ' nhưng đến cuối chuổi ta không thể có ' ' nên phải kiểm tra có phải là cuối chuổi chưa
		{
			soMu = stof(str, &sizeStr);
			Monomial donThuc(heSo, soMu);
			poly_.push_back(donThuc);
			str.clear();
			soLuong_++; // số lượng tăng lên
		}
	}
}

Polynomial::Polynomial(const Polynomial & src) // hàm khởi tạo sao chép
{
	soLuong_ = src.soLuong_;
	for (int i = 0; i < soLuong_; i++)
	{
		poly_.push_back(src.poly_[i]);
	}
}

void Polynomial::pushBack(const Monomial & src)
{
	this->poly_.push_back(src);
	this->soLuong_++;
}

Polynomial & Polynomial::operator=(Polynomial & src)
{
	if (this != &src)
	{
		this->soLuong_ = src.soLuong_;
		this->poly_ = src.poly_;
	}
	return *this;
}

Monomial Polynomial::operator[](int i)
{
	return this->poly_[i];
}

void Polynomial::sortPoly()
{
	this->poly_.sort(giam);
	while ((*this)[0].getHeSo() == 0)
	{
		this->poly_.pop_front();
		this->soLuong_--;
	}
}

Polynomial& Polynomial::operator+(const Polynomial &src)
{
	Polynomial *result=new Polynomial; // kết quả
	for(int i=0;i<this->soLuong_;i++) // duyệt từng phần tử đa thức thứ nhất
		for (int j = 0;j < src.soLuong_;j++) //duyệt từng phần tử đa thức thứ 2
		{
			if (this->poly_[i].getSoMu() == src.poly_[j].getSoMu()) // tìm đơn thức có cùng số mũ 
			{
				result->pushBack( this->poly_[i] + src.poly_[j]);   // nếu có thì cộng 2 đơn thức và duyệt đến phần tử tiếp theo của đa thức thứ nhất
				break;
			}
		}
	// sau khi cộng các phần tử cùng số mũ, thì ta lại duyệt để push các phần tử khác số mũ của đa thức thứ nhất vào đa thức kết quả
	for (int i = 0;i < this->soLuong_;i++) //duyệt từng phần tử đa thức thứ nhất, kiểm tra xem nó có cùng số mũ với phần tử nào trong kết quả không, nếu không thì push vào
	{
		bool kiemTra = true;
		for (int j = 0;j < result->soLuong_;j++) // duyệt từng phần tử đa thức kết quả
		{
			if (this->poly_[i].getSoMu() == result->poly_[j].getSoMu()) kiemTra = false;
		}
		if (kiemTra == true) result->pushBack(this->poly_[i]);
	}
	// tương tự với  đa thức thứ 2 
	for (int i = 0;i < src.soLuong_;i++) 
	{
		bool kiemTra = true; 
		for (int j = 0;j < result->soLuong_;j++) 
		{
			if (src.poly_[i].getSoMu() == result->poly_[j].getSoMu()) kiemTra = false;
		}
		if (kiemTra == true) result->pushBack(src.poly_[i]);
	}
	// sắp xếp
	result->sortPoly();
	return *result;
}

Polynomial & Polynomial::operator+(float src)
{
	Polynomial *result = new Polynomial(*this); // kết quả
	Monomial temp(src, 0);
	result->pushBack(temp);
	return *result;
}

Polynomial & Polynomial::operator-(const Polynomial & src)
{
	Polynomial *result = new Polynomial; // kết quả
	for (int i = 0;i < this->soLuong_;i++) // duyệt từng phần tử đa thức thứ nhất
		for (int j = 0;j < src.soLuong_;j++) //duyệt từng phần tử đa thức thứ 2
		{
			if (this->poly_[i].getSoMu() == src.poly_[j].getSoMu()) // tìm đơn thức có cùng số mũ 
			{
				result->pushBack(this->poly_[i] - src.poly_[j]);   // nếu có thì trừ 2 đơn thức và duyệt đến phần tử tiếp theo của đa thức thứ nhất
				break;
			}
		}
	// sau khi trừ các phần tử cùng số mũ, thì ta lại duyệt để push các phần tử khác số mũ của đa thức thứ nhất vào đa thức kết quả
	for (int i = 0;i < this->soLuong_;i++) //duyệt từng phần tử đa thức thứ nhất, kiểm tra xem nó có cùng số mũ với phần tử nào trong kết quả không, nếu không thì push vào
	{
		bool kiemTra = true;
		for (int j = 0;j < result->soLuong_;j++) // duyệt từng phần tử đa thức kết quả
		{
			if (this->poly_[i].getSoMu() == result->poly_[j].getSoMu()) kiemTra = false;
		}
		if (kiemTra == true) result->pushBack(this->poly_[i]);
	}
	// tương tự với  đa thức thứ 2 nhưng lưu ý có thêm dấu trừ trước hệ số
	for (int i = 0;i < src.soLuong_;i++)
	{
		bool kiemTra = true;
		for (int j = 0;j < result->soLuong_;j++)
		{
			if (src.poly_[i].getSoMu() == result->poly_[j].getSoMu()) kiemTra = false;
		}
		if (kiemTra == true)
		{
			result->pushBack(-src.poly_[i]);
		}
	}
	// sắp xếp
	result->sortPoly();
	return *result;
}

Polynomial & Polynomial::operator-(float src)
{
	Polynomial *result = new Polynomial(*this); // kết quả
	Monomial temp(-src, 0); // khởi tạo đơn thức có số mũ =0 và hệ số = src rồi push vào
	result->pushBack(temp);
	return *result;
}

Polynomial & Polynomial::operator*(const Monomial & src)
{
	Polynomial *result=new Polynomial;
	for (int i = 0;i < this->soLuong_;i++)
	{
		result->pushBack((*this)[i] * src); // duyệt từng đơn thức trong đa thức rồi nhân với đơn thức src
	}
	return *result;
}

Polynomial & Polynomial::operator*(const Polynomial & src)
{
	Polynomial *result = new Polynomial;
	for (int i = 0;i < src.soLuong_;i++)
	{
		Polynomial temp = (*this) * src.poly_[i];
		(*result) = (*result) + temp;
	}
	return *result;
}

Polynomial & Polynomial::operator*(float src)
{
	Polynomial *result = new Polynomial;
	for (int i = 0;i < this->soLuong_;i++)
	{
		result->pushBack((*this)[i] * src);
	}
	return *result;
}

Polynomial & Polynomial::operator/( Polynomial  src)
{
	Polynomial surplus = (*this); // số dư
	Polynomial *result = new Polynomial; // kết quả
	while (surplus[0].getSoMu() >= src[0].getSoMu()) // trong khi số mũ >= thì chia
	{
		Monomial temp = surplus[0] / src[0]; // đơn thức kết quả khi chia 2 đơn thức đầu (lớn nhất) cho nhau
		result->pushBack(temp); // đẩy đơn thức kết quả vào trong đa thức kết quả
		surplus = surplus - (src * temp); // số dư = số dư - src*đơn thức temp
	}
	return *result;
}

Polynomial & Polynomial::operator%(Polynomial src)
{
	Polynomial *result=new Polynomial; // kết quả (số dư)
	*result = (*this) - ((*this) / src)*src;  //biết a/b=c (+d) , suy ra số dư d = a -c*b
	result->sortPoly(); // sắp xếp để bỏ đi cái phần tử có hệ số bằng không, ví dụ 0x^3
	return *result;
}

Polynomial Polynomial::derivative()
{
	Polynomial res;
	res.soLuong_ = soLuong_;
	for (int i = 0; i < soLuong_; i++)
	{
		res.poly_.push_back(poly_[i].derivative());
	}
	return res;
}

Polynomial Polynomial::inf_integral()
{
	Polynomial res;
	res.soLuong_ = soLuong_;
	for (int i = 0; i < soLuong_; i++)
	{
		res.poly_.push_back(poly_[i].inf_integral());
	}
	return res;
}
void docGhiFile(const char * input, const char * output)
{
	ifstream rFile;
	rFile.open(input);
	if (rFile.is_open())
	{
		ofstream wFile; // mở file để viết
		wFile.open(output);
		char temp[255]; //temp lưu từng dòng của file
		string cauLenh; //câu lệnh dùng để biết mục đích của dòng trong file là gì
		Polynomial res; // khởi tạo đa thức kết quả
		while (!rFile.eof())
		{
			rFile.getline(temp, 255); // lấy từng dòng ghi vào temp
			for (int i = 0; i < 3; i++)
				cauLenh.push_back(temp[i]); // lấy 3 kí tự đầu của temp
			if (cauLenh == "add" || cauLenh == "sub" || cauLenh == "mul" || cauLenh == "div" 
				|| cauLenh == "mod") // nếu là toán tử 2 ngôi thì sẽ thực hiện
			{
				char bieuThuc1[100], bieuThuc2[100]; // vì là toán tử 2 ngôi nên phải có 2 đa thức được tạo ra
				int i = 0; // biến đếm cho temp
				int doDai1 = 0, doDai2 = 0; // độ dài cho biểu thức 1 và biểu thức 2;
				while (temp[i] != ',') // biểu thức đầu sẽ lấy từ sau dấu '(' đến trước dấu ','
				{
					if (temp[i] == '.' || temp[i] == '+' || temp[i] == '-' || temp[i] == ' ' || temp[i] == 'x'
						|| temp[i] == '^' || (temp[i] >= '0' && temp[i] <= '9'))
						bieuThuc1[doDai1++] = temp[i]; // nếu là  '+' '-' 'x' '^' ' ' và các chữ số thì sẽ lấy
					i++; // biến đếm tăng lên 1
				}
				bieuThuc1[doDai1] = '\0'; // gán NULL vô cuối cùng của biểu thức 1
				while (temp[i] != ')') // biểu thức 2 từ sau ',' đến trước ')'
				{
					if (temp[i] == '.' || temp[i] == '+' || temp[i] == '-' || temp[i] == ' ' || temp[i] == 'x'
						|| temp[i] == '^' || (temp[i] >= '0' && temp[i] <= '9'))
						bieuThuc2[doDai2++] = temp[i]; // giống như biểu thức 1
					i++; // biến đếm tăng lên 1
				}
				bieuThuc2[doDai2] = '\0'; // gán NULL vào cuối cùng của biểu thức 2
				Polynomial daThuc1(bieuThuc1), daThuc2(bieuThuc2); // khởi tạo 2 đa thức từ biểu thức 1 và 2 ở trên
				
				if (cauLenh == "add") res = daThuc1 + daThuc2; // trường hợp +
				else if (cauLenh == "sub") res = daThuc1 - daThuc2; // trường hợp -
				else if (cauLenh == "mul") res = daThuc1 * daThuc2; // trường hợp *
				else if (cauLenh == "div") res = daThuc1 / daThuc2; // trường hợp /
				else res = daThuc1 % daThuc2; // trường hợp còn lại là %
			}
			else if (cauLenh == "der" || cauLenh == "inf")
			{
				char bieuThuc[100];
				int doDai = 0;
				for (int i = 0; i < strlen(temp); i++)
				{
					if (temp[i] == '.' || temp[i] == '+' || temp[i] == '-' || temp[i] == ' ' || temp[i] == 'x'
						|| temp[i] == '^' || (temp[i] >= '0' && temp[i] <= '9'))
						bieuThuc[doDai++] = temp[i]; // giống như biểu thức 1
				}
				bieuThuc[doDai] = '\0';
				Polynomial daThuc(bieuThuc);
				if (cauLenh == "der")
				{
					Polynomial kq = daThuc.derivative();
					res = kq;
				}
				else 
				{
					Polynomial kq = daThuc.inf_integral();
					res = kq;
				}
			}
			
			if (wFile.is_open())
			{
				for (int i = 0; i < res.getSoLuong(); i++)
				{
					float heSo = res[i].getHeSo();
					int soMu = res[i].getSoMu();
					if (heSo > 0)
						wFile << "+" << heSo << "x^" << soMu << " ";
					else if (heSo < 0)
						wFile << heSo << "x^" << soMu << " ";
				}
				wFile << endl;
			}
			
			cauLenh.clear();
		}
		wFile.close();
	}
	rFile.close();
}

Polynomial::~Polynomial()
{
}

void Polynomial::xuat() // hàm để test
{
	poly_.xuat();
}

int Polynomial::getSoLuong()
{
	return soLuong_;
}
