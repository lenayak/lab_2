#include <iostream>
#include <stdio.h>
#include <Windows.h> 
#include <cmath>
#include <limits>
#include <complex>
using namespace std;

template<typename T>
class vector
{
private:
	int size;
	T* vect;
public:
	int get_size() const
	{
		return size;
	}

	vector(int _size, T* _vect) : size(_size), vect(new T[_size])
	{
		memcpy(vect, _vect, sizeof(T) * size);              
	}

	vector(int _size) : size(_size), vect(new T[_size])
	{
		memset(vect, 0, sizeof(T) * size);               
	}

	vector(const vector& v) : size(v.size), vect(new T[v.size])
	{
		memcpy(vect, v.vect, sizeof(T) * size);
	}

	~vector()
	{
		delete[] vect;
	}

	void swap_(vector& v)
	{
		swap(size, v.size);
		swap(vect, v.vect);
	}

	vector& operator=(vector v)
	{
		swap_(v);
		return *this;
	}

	vector& operator +=(const vector& v)
	{
		if (size != v.size) throw 1;
		for (int i = 0; i < size; i++)
		{
			vect[i] += v.vect[i];
		}
		return *this;
	}

	vector& operator -=(const vector& v)
	{
		if (size != v.size)throw 1;
		for (int i = 0; i < size; i++)
		{
			vect[i] -= v.vect[i];
		}
		return *this;
	}

	vector& operator *=(T number)
	{
		for (int i = 0; i < size; i++)
		{
			vect[i] *= number;
		}
		return *this;
	}

	vector& operator/=(T num)
	{
		if (num == 0.0) throw 1;
		for (int i = 0; i < size; i++)
		{
			vect[i] /= num;
		}
		return *this;
	}

	T& operator[](int index)
	{
		if (index >= size) throw 2;
		return vect[index];
	}

	const T& operator[](int index) const
	{
		if (index >= size)throw 2;
		return vect[index];
	}

	vector operator* (T number)
	{
		vector copy(size, vect);
		copy *= number;
		return copy;
	}
};


template<typename T>
vector<T> operator+(const vector<T>& v1, const vector<T>& v2)
{
	if (v1.get_size() != v2.get_size()) throw 3;
	vector<T> copy = v1;
	copy += v2;
	return copy;
}

template<typename T>
vector<T> operator-(const vector<T>& v1, const vector<T>& v2)
{
	if (v1.get_size() != v2.get_size()) throw 3;
	vector<T> copy = v1;
	copy -= v2;
	return copy;
}

template<typename T>
double operator*(const vector<T>& v1, const vector<T>& v2)
{
	double res = 0;
	for (int i = 0; i < v1.get_size(); i++)
	{
		res += v1[i] * v2[i];
	}
	return res;
}

template<typename T>
complex<T> operator*(const vector<complex<T>>& v1, const vector<complex<T>>& v2)
{
	if (v1.get_size() != v2.get_size()) throw 3;
	std::complex<T> result(0, 0);
	for (int i = 0; i < v1.get_size(); i++) {
		result += complex<T>(v1[i].real() * v2[i].real() - v1[i].imag() * v2[i].imag(), v1[i].real() * v2[i].imag() + v1[i].imag() * v2[i].real());
	}
	return result;
}

// оператор умножени€ вектора на скал€р
template<typename T>
vector<T> operator*(const vector<T>& v, double num)
{
	vector<T> copy = v;
	copy *= num;
	return copy;
}

template<typename T>
vector<T> operator*(double num, const vector<T>& v)
{
	vector<T> copy = v;
	copy *= num;
	return copy;
}

//оператор делени€ вектора на скал€р
template<typename T>
vector<T> operator/(const vector<T>& v, double num)
{
	vector<T> copy = v;
	copy /= num;
	return copy;
}

template<typename T>
ostream& operator <<(ostream& out, const vector<T>& v)
{
	out << "[";
	for (int i = 0; i < v.get_size(); i++)
	{
		out << v[i];
		if (i != v.get_size() - 1)out << ",";
	}
	out << "]" << "\n";
	return out;
}

template<typename T>
bool is_equal(T x, T y, T eps)
{
	if (eps < 0)
		eps = -eps;
	if ((x - y >= eps) || (x - y < -eps))
		return false;
	else
		return true;
}


template<typename T>
bool operator==(const vector<T>& v1, const vector<T>& v2)
{
	T eps = 0;
	cout << "Enter the precision with which you want to compare the numbers." << endl;
	cout << "For example: 0.0001" << endl;
	cin >> eps;
	if (v1.get_size() != v2.get_size()) throw 3;
	for (int i = 0; i < v1.get_size(); i++)
	{
		if (is_equal(v1[i], v2[i], eps) == false)
			return false;
	}
	return true;
}

bool operator==(const vector<int>& v1, const vector<int>& v2)
{
	if (v1.get_size() != v2.get_size()) throw 3;
	for (int i = 0; i < v1.get_size(); i++)
	{
		if (is_equal(v1[i], v2[i],0) == false)
			return false;
	}
	return true;
}

template<typename T>
bool operator!=(const vector<T>& v1, const vector<T>& v2)
{
	return!(v1 == v2);
}

//ƒл€ параллелограмма, заданного 2 радиус - векторами a и b, рассчитать углы.
template<typename T>
double len_of_vector(const vector<T>& v)
{
	double l = 0;
	for (int i = 0; i < v.get_size(); i++)
	{
		l += pow(v[i], 2);
	}
	return sqrt(l);
}

template<typename T>
double find_first_angle(const vector<T>& a, const vector<T>& b)
{
	double pi = 3.14159265;
	double numenator = a * b;
	double denominator = len_of_vector(a) * len_of_vector(b);
	double cos_angle = numenator / denominator;
	double angle_r1 = acos(cos_angle);
	double angle_1 = 180 / pi * angle_r1;
	return angle_1;
}

template<typename T>
double find_second_angle(const vector<T>& a, const vector<T>& b)
{
	double angle_1 = find_first_angle(a, b);
	double angle_2 = 180 - angle_1;
	return angle_2;
}

int main()
{
	double m[2] = { 1,1 };
	double n[2] = { 1,4 };
	vector<double> a(2, m);
	vector<double> b(2, n);
	a[1] = 4.2;
	cout << "vector<double> a:  "<< a << "\nvector<double> b:  "<< b << endl;

	if (a != b)
		cout << "Vectors<double> are not equal." << endl;
	else
		cout << "Vectors<double> are equal." << endl;

	int m1[2] = { 2,3 };
	int n1[4] = { 1,2,3,4 };
	vector<int> a1(2, m1);
	vector<int> b1(4, n1);
	cout << "vector<int> a1:  " << a1 << "  \nvector<int> b1:  " << b1 << endl;

	float m2[2] = { 2,5 };
	float n2[2] = { 1,3.4 };
	vector<float> a2(2, m2);
	vector<float> b2(2, n2);
	cout << "vector<float> a2:  " << a2 << "  \nvector<float> b2:  " << b2 << endl;

	if (a2 != b2)
		cout << "Vectors<float> are not equal." << endl;
	else
		cout << "Vectors<float> are equal." << endl;


	try
	{
		if (a1 != b1)
			cout << "Vectors<int> are not equal." << endl;
		else
			cout << "Vectors<int> are equal." << endl;

		vector<double> sum = a + b;
		cout << "Sum<double>: " << sum;

		vector<int> sum1 = a1 + b1;
		cout << "Sum<int>: " << sum1;

		vector<float> sum2 = a2 + b2;
		cout << "Sum<float>: " << sum2;

		vector<double> div_by0 = a / 0;
		cout << "a/0: " << endl;

		vector<int> div_by0_1 = a1 / 0;
		cout << "a1/0: " << endl;

		vector<float> div_by0_2 = a2 / 0;
		cout << "a2/0: " << endl;

	}
	catch (int thr)
	{
		if (thr == 1)
		{
			cout << "Error:  Division by zero." << endl;
		}
		if (thr == 2)
		{
			cout << "Error:  Incorrect index entry." << endl;
		}
		if (thr == 3)
		{
			cout << "Error:  Vectors of different dimensions" << endl;
		}
	}

	double l[2] = { 1,4 };
	vector<double> v1(2, l);
	double k[2] = { 4,3 };
	vector<double> v2(2, k);
	cout << "vector a: " << v1 << "\n" << "vector b: " << v2 << endl;
	cout << "first angle: " << find_first_angle(v1, v2) << endl;
	cout << "second angle: " << find_second_angle(v1, v2) << endl;

	complex<double> c1(2.5, 3.4);
	complex<double> c2(2, 3);
	complex<double> arr[2] = { c1,c2 };
	vector<complex<double>> vc(2, arr);
	cout << "vc    " << vc;
	complex<double> c_1(2, 3);
	complex<double> c_2(5, 4);
	complex<double> arr_1[2] = { c_1, c_2 };
	vector<complex<double>> vc1(2,arr_1);
	cout << "vc1   " << vc1;
	vector<complex<double>> sum_vc = vc + vc1;
	cout << "vc + vc1 = " << sum_vc << endl;
	complex<double> multi = vc * vc1;
	cout << "vc * vc1 = " << multi;

	return 0;
}