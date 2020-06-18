#include "CustomArray.h"


template <typename T>
CustomArray<T>::CustomArray()    // khởi tạo mặc định
{
	lowerBound = NULL;
	begin = NULL;
	end = NULL;
	upperBound = NULL;
}

template<typename T>
CustomArray<T>::CustomArray(int n) // khởi tạo với kích thước N
{
	this->N = n;
	lowerBound = new T[3 * N];
	begin = &lowerBound[N];
	end = &lowerBound[2 * N];
	upperBound = &lowerBound[3 * N - 1];
	T *temp = begin;
	// gán giá trị mặc định là NULL
	while (temp != end) {
		//	delete temp;                                        
		temp = NULL;
		temp++;
	}
}

template<typename T>
CustomArray<T>::CustomArray(const CustomArray & ca)	  // khởi tạo sao chép
{
	this->N = ca.N;
	lowerBound = new T[3 * N];
	begin = &lowerBound[N];
	end = &lowerBound[2 * N];
	upperBound = &lowerBound[3 * N - 1];
	for (int i = 0; i < N; i++)
		this->begin[i] = ca.begin[i];
}

template<typename T>
CustomArray<T>::CustomArray(int n, T val)
{
	this->N = n;
	// Cấp phát và gán giá trị
	lowerBound = new T[3 * N];
	begin = &lowerBound[N];
	end = &lowerBound[2 * N];
	upperBound = &lowerBound[3 * N - 1];
	for (int i = 0; i < N; i++)
		this->begin[i] = val;
}

template<typename T>
void CustomArray<T>::xuat()
{
	int i = 0;
	T * t = begin;
	while (t != end) {
		cout << begin[i] << " ";
		i++;
		t++;
	}
}

template<typename T>
int CustomArray<T>::sizeLower()
{
	int sizeL = 0;
	T *countL = lowerBound;
	while (countL != begin) {
		sizeL++;
		countL++;
	}
	return sizeL;
}

template<typename T>
int CustomArray<T>::sizeBegin()
{
	int sizeB = 0;
	T *countB = begin;
	while (countB != end) {
		sizeB++;
		countB++;
	}
	return sizeB;
}

template<typename T>
int CustomArray<T>::sizeEnd()
{
	int sizeE = 0;
	T *countE = end;
	while (countE != upperBound) {
		sizeE++;
		countE++;
	}
	return sizeE + 1;
}

template<typename T>
CustomArray<T> & CustomArray<T>::operator=(CustomArray & carray)
{

	// Xóa các con trỏ cũ
	delete[] this->lowerBound;
	this->begin = this->end = this->upperBound = NULL;
	this->N = carray.N;
	// Cấp phát lại
	int sizeL = carray.sizeLower();
	int sizeB = carray.sizeBegin();
	int sizeE = carray.sizeEnd();
	lowerBound = new T[3 * N];
	begin = &lowerBound[sizeL];
	end = &lowerBound[sizeL + sizeB];
	upperBound = &lowerBound[3 * N - 1];
	// gán giá trị
	for (int i = 0; i < sizeB; i++)
		this->begin[i] = carray.begin[i];
	return *this;
}

template<typename T>
int CustomArray<T>::size()		// Lấy kích thước
{
	return end - begin;
}

template<typename T>
T* CustomArray<T>::getBegin()		// lấy con trỏ begin của CustomArray
{
	return this->begin;
}

template<typename T>
T * CustomArray<T>::getEnd()		// lấy con trỏ end của CustomArray
{
	return this->end;
}

template<typename T>
void CustomArray<T>::clear()	// Xóa tất cả phần tử trong array
{
	// clear 
	// Xóa
	delete[] lowerBound;
	begin = end = upperBound = NULL;
	// Cấp phát lại
	lowerBound = new T[3 * N];
	begin = &lowerBound[N];
	end = &lowerBound[2 * N];
	upperBound = &lowerBound[3 * N - 1];
}

template<typename T>
bool CustomArray<T>::empty()	// Kiểm tra array có rỗng không  
{
	return (lowerBound == NULL);
}

template <typename T>
void CustomArray<T>::reSize(int newSize)
{
	// Đầu tiên tạo một mảng để lưu lại giá trị trong CustomArray
	// Vì kích thước của begin có thể thay đổi vì push, pull 
	// nên mảng phụ sẽ có kích thước bằng begin 
	int count = this->sizeBegin();		// số phần tử trong begin

										// Tạo mảng phụ
	T *temp = new T[count];
	for (int i = 0; i < count; i++)
		temp[i] = begin[i];

	// Xóa các con trỏ
	delete[] lowerBound;
	begin = end = upperBound = NULL;
	// Cấp phát lại với kích thước mới
	this->N = newSize;
	lowerBound = new T[3 * N];
	begin = &lowerBound[N];
	end = &lowerBound[2 * N];
	upperBound = &lowerBound[3 * N - 1];
	// Sao chép lại dữ liệu
	for (int i = 0; i < N; i++)
		this->begin[i] = temp[i];

}	// Điểu chỉnh kích thước mảng

template <typename T>
void CustomArray<T>::push_back(T value)
{
	// vì kích thước từng mảng con có thể thay đổi
	int sizeL = this->sizeLower();		// Kích thước mảng lowerBound
	int sizeB = this->sizeBegin();		// Kích thước mảng begin
	int sizeE = this->sizeEnd();		// Kích thước mảng end

										// Nếu begin chưa có phần tử nào
										//for (int i = 0; i < N; i++)
	if (begin == NULL)	// nếu trống thì thêm vào
	{
		// Cấp phát cho mảng với N = 1
		this->N = 1;
		lowerBound = new T[3 * N];
		begin = &lowerBound[N];
		end = &lowerBound[2 * N];
		upperBound = &lowerBound[3 * N - 1];
		*begin = value;
		return;
	}


	// Nếu end chưa trùng upperBound
	if (end != upperBound)
	{
		// Đưa end ra sau
		end = end + 1;
		sizeE -= 1;
		sizeB += 1;
		begin[sizeB - 1] = value;
		return;
	}
	// Nếu end trùng upperBound
	if (end == upperBound && lowerBound != begin)
	{
		// Cân chỉnh
		int l = sizeL - sizeE;
		int khoangCach;
		if (l == 0)
			khoangCach = 1;
		else
			khoangCach = (sizeL - sizeE + 1) / 2;	// tính khoảng cách để căn chỉnh
		sizeL -= khoangCach;
		sizeE += khoangCach;
		// sao chép dữ liệu
		T *temp = new T[sizeB];
		for (int i = 0; i < sizeB; i++)
			temp[i] = begin[i];
		// Đưa begin, end tới trước
		begin -= khoangCach;
		end -= khoangCach;
		for (int i = 0; i < sizeB; i++)
			begin[i] = temp[i];
		// Thêm phần tử
		end = end + 1;
		sizeE -= 1;
		sizeB += 1;
		begin[sizeB - 1] = value;
		return;
	}
	// Nếu phần dự trữ trái và phải đều hết
	if (end == upperBound && lowerBound == begin)
	{
		this->reSize(sizeB);
		// Thêm phần tử
		return push_back(value);
	}
}

template <typename T>
void CustomArray<T>::push_front(T value)
{
	// vì kích thước từng mảng con có thể thay đổi
	int sizeL = this->sizeLower();		// Kích thước mảng lowerBound
	int sizeB = this->sizeBegin();		// Kích thước mảng begin
	int sizeE = this->sizeEnd();		// Kích thước mảng end
										// nếu lowerBound chưa trùng begin

	if (lowerBound != begin)
	{
		sizeL -= 1;
		sizeB += 1;
		begin -= 1;
		begin[0] = value;
		return;
	}
	// Nếu lowerBound trùng begin và end khác upper
	if (lowerBound == begin && end != upperBound)
	{
		// Cân chỉnh
		int khoangCach = (sizeL - sizeE) / 2;	// tính khoảng cách để căn chỉnh
		sizeL += khoangCach;
		sizeE -= khoangCach;
		// sao chép dữ liệu
		T *temp = new T[sizeB];
		for (int i = 0; i < sizeB; i++)
			temp[i] = begin[i];
		// Đưa begin, end ra sau
		begin += khoangCach;
		end += khoangCach;
		// Thêm phần tử
		begin = begin - 1;
		for (int i = 0; i < sizeB; i++)
			begin[i] = temp[i];
		sizeL -= 1;
		sizeB += 1;
		begin[0] = value;
		return;
	}
	// Nếu phần dự trữ trái phải đều hết
	if (lowerBound == begin && end == upperBound)
	{
		// Sao chép dữ liệu
		T *temp = new T[sizeB];
		for (int i = 0; i < sizeB; i++)
			temp[i] = begin[i];
		// Xóa lowerBound với end cũ
		delete[] lowerBound;
		begin = end = upperBound = NULL;
		// cấp phát lại 
		this->N++;
		lowerBound = new T[3 * N];
		begin = &lowerBound[N];
		end = &lowerBound[2 * N];
		upperBound = &lowerBound[3 * N - 1];
		// Đưa dữ liệu vào mảng mới
		for (int i = 0; i < sizeB; i++)
			begin[i] = temp[i];
		return;
	}
}

template <typename T>
T CustomArray<T>::pop_back()
{
	int sizeB = this->sizeBegin();
	T value = begin[sizeB - 1];
	end -= 1;
	return value;
}

template <typename T>
T CustomArray<T>::pop_front()
{
	int sizeB = this->sizeBegin();
	T value = begin[0];
	begin += 1;
	return value;
}
template<typename T>
void CustomArray<T>::insert(T * p, T value)
{
	int sizeL = this->sizeLower();		// Kích thước mảng lowerBound
	int sizeB = this->sizeBegin();		// Kích thước mảng begin
	int sizeE = this->sizeEnd();		// Kích thước mảng end
										// Tính vị trí con trỏ p
	int vitri = 0;
	T *t = begin;

	while (t != p) {
		vitri++;
		t++;
	}
	int center = this->sizeBegin() / 2;		// vị trí giữa của phần lưu trữ

											// nếu dự trữ phải còn và p ở nữa sau
	if (end != upperBound && vitri > center)
	{
		end += 1;
		// Dùng mảng phụ lưu dữ liệu sau p
		int sizeT = this->sizeBegin() - vitri;

		T *temp = new T[sizeT];
		for (int i = 0; i < sizeT; i++)
			temp[i] = begin[vitri + i];
		// chèn phần tử mới vào sau p
		begin[vitri] = value;
		for (int i = 0; i < sizeT; i++)
			begin[vitri + i + 1] = temp[i];
		return;
	}
	// Nếu dự trữ phải hết và p ở nửa sau
	if (end == upperBound && vitri > center)
	{
		// Căn chỉnh
		int khoangCach = (sizeL - sizeE) / 2;	// tính khoảng cách để căn chỉnh
		sizeL -= khoangCach;
		sizeE += khoangCach;
		// sao chép dữ liệu
		T *temp = new T[sizeB];
		for (int i = 0; i < sizeB; i++)
			temp[i] = begin[i];
		// Đưa begin, end tới trước
		begin -= khoangCach;
		end -= khoangCach;
		for (int i = 0; i < sizeB; i++)
			begin[i] = temp[i];
		// Chèn phần tử
		end += 1;
		// Dùng mảng phụ lưu dữ liệu sau p
		int sizeT = this->sizeBegin() - vitri;
		T *t = new T[sizeT];
		for (int i = 0; i < sizeT; i++)
			t[i] = begin[vitri + i];
		// chèn phần tử mới vào sau p
		begin[vitri] = value;
		for (int i = 0; i < sizeT; i++)
			begin[vitri + i + 1] = t[i];
		return;
	}
	// Nếu dự trữ trái còn và p ở nửa trước
	if (lowerBound != begin && vitri <= center)
	{
		// Tạo mảng phụ chứa dữ liệ
		T *temp = new T[vitri];
		for (int i = 0; i < vitri; i++)
			temp[i] = begin[i];
		begin -= 1;
		p -= 1;
		// Lấy dữ liệu
		for (int i = 0; i < vitri; i++)
			begin[i] = temp[i];
		begin[vitri] = value;
		return;
	}
	// Nếu dự trữ trái hết và p ở nửa trước
	if (lowerBound == begin && vitri <= center)
	{
		// Căn chỉnh
		int khoangCach = (sizeL - sizeE) / 2;	// tính khoảng cách để căn chỉnh
		sizeL += khoangCach;
		sizeE -= khoangCach;
		// sao chép dữ liệu
		T *temp = new T[sizeB];
		for (int i = 0; i < sizeB; i++)
			temp[i] = begin[i];
		// Đưa begin, end ra sau
		begin += khoangCach;
		end += khoangCach;
		for (int i = 0; i < sizeB; i++)
			begin[i] = temp[i];

		// Tạo mảng phụ
		T *t = new T[vitri];
		for (int i = 0; i < vitri; i++)
			t[i] = begin[i];
		// Đưa begin và p tới trước
		begin -= 1;
		p -= 1;
		for (int i = 0; i < vitri; i++)
			begin[i] = t[i];
		begin[vitri] = value;
		return;
	}

	// Nếu cả 2 phần dự trữ đều hết
	if (lowerBound == begin && end == upperBound)
	{
		this->reSize(sizeB);
		this->insert(p, value);
	}
}

template<typename T>
void CustomArray<T>::erase(T * p)
{
	int sizeL = this->sizeLower();		// Kích thước mảng lowerBound
	int sizeB = this->sizeBegin();		// Kích thước mảng begin
	int sizeE = this->sizeEnd();		// Kích thước mảng end
	int vitri = 0;
	T *t = begin;

	while (t != p) {
		vitri++;
		t++;
	}
	int center = this->sizeBegin() / 2;
	// Nếu p ở nữa sau
	if (vitri > center)
	{
		// Tạo mảng phụ
		int sizeT = sizeB - vitri;
		T *temp = new T[sizeT];
		for (int i = 0; i < sizeT; i++)
			temp[i] = begin[vitri + i];
		//  Xóa
		for (int i = 0; i < sizeT; i++)
			begin[vitri + i - 1] = temp[i];
		end -= 1;
		return;
	}
	// Nếu p ở nữa trước
	if (vitri <= center)
	{
		// dời tới trước
		// Tạo mảng phụ
		T *temp = new T[vitri];
		for (int i = 0; i < vitri; i++)
			temp[i] = begin[i];
		// Xóa
		begin += 1;
		for (int i = 0; i < vitri; i++)
			begin[i] = temp[i];
		return;
	}
}

template<typename T>
void swapT(T & a, T & b)
{
	T t = a;
	a = b;
	b = t;
}

template<typename T>
void CustomArray<T>::sort(bool(*option)(T, T)) //seletion sort
{
	int size = this->sizeBegin();
	for (int i = 0; i < size - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < size; j++)
			if (option(begin[min], begin[j]))
				min = j;
		swapT(begin[i], begin[min]);
	}
}

template<typename T>
CustomArray<T>::~CustomArray()
{
	delete[] lowerBound;
	begin = end = upperBound = lowerBound = NULL;
}

template<typename T>
T CustomArray<T>::operator[](int i) const
{
	return this->begin[i];
}

template class CustomArray<int>;
template class CustomArray<Monomial>;
template class CustomArray<string>;