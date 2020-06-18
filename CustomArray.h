#pragma once
#include <string>
#include <conio.h>
#include "Monomial.h"
using namespace std;

template <typename T>
class CustomArray
{
	int N;			// Kích thước phần lưu trữ
	T *lowerBound;	// trỏ đến phần tử đầu tiên của phần dự trữ bên trái
	T *begin;		// trỏ đến phần tử đầu tiên của phần lưu trữ
	T *end;			// trỏ đến phần tử đầu tiên của phần dự trữ bên phải
	T *upperBound;	// trỏ đến phần tử cuối cùng của phần dự trữ bên phải
public:
	CustomArray();						// Khởi tạo mặc định
	CustomArray(int n);					// Khởi tạo với kích thước N
	CustomArray(const CustomArray &ca); // Khởi tạo sao chép
	CustomArray(int n, T val);			// Khởi tạo với kích thước N và giá trị mặc định val
	void xuat(); // hàm xuất để test
	int sizeLower();	//	lấy size lowerBound                                                                   
	int sizeBegin();	//	lấy size begin                                                                        
	int sizeEnd();		//	lấy size upperBound                                                                  
	CustomArray& operator=(CustomArray& carray);	// Toán tử gán bằng
	int size();		// Lấy kích thước
	T* getBegin();	// lấy con trỏ begin của CustomArray
	T* getEnd();	// lấy con trỏ end của CustomArray
	void clear();	// Xóa tất cả phần tử trong array
	bool empty();	// Kiểm tra array có rỗng không                              
	void reSize(int newSize);	// Điều chỉnh kích thước mảng


	void push_back(T value);	// thêm 1 phần tử vào cuối phần lưu trữ
	void push_front(T value);	// thêm 1 phần tử vào đầu phần lưu trữ
	T pop_back();			// trả về phần tử cuối của phần lưu trữ và xóa khỏi lưu trữ
	T pop_front();			// trả về phần tử đầu của phần lưu trữ và xóa khỏi lưu trữ
	void insert(T *p, T value);		// chèn phần tử mới vào sau con trỏ p trỏ tới
	void erase(T *p);		// xóa phần tử mới vào sau con trỏ p trỏ tới
	void sort(bool(*option)(T, T));			// sắp xếp
	~CustomArray();// Hủy	
	T operator[] (int i) const;// lấy a[i]
};

template <typename T>
bool tang(T left, T right)// con trỏ hàm sắp xếp tăng
{
	return left > right;
}

template <typename T>
bool giam(T left, T right)// con trỏ hàm sắp xếp giảm
{
	return left < right;
}

template <typename T>
void swapT(T & a, T & b); // hàm đổi chỗ