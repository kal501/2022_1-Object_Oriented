# include <iostream>
using namespace std;

class Complex {
private:
	double real, img;
	double get_number(const char* str, int from, int to);
public:
	Complex(double real, double img) : real(real) , img(img){}
	Complex(const Complex& c) { real = c.real, img = c.img; }
	Complex(const char* str);

	Complex operator+(const Complex& c);
	Complex operator-(const Complex& c);
	Complex operator*(const Complex& c);
	Complex operator/(const Complex& c);

	Complex& operator=(const Complex& c); // 대입연산자 -> 깊은복사 생성자와 같은 의미

	Complex& operator+=(const Complex& c);
	Complex& operator-=(const Complex& c);
	Complex& operator*=(const Complex& c);
	Complex& operator/=(const Complex& c);

	Complex operator+(const char* str);

	void println() { cout << "(" << real << "," << img << " ) " << endl;}
};
double Complex::get_number(const char* str, int from, int to) {
	bool minus = false;
	if (from > to) return 0;

	if (str[from] == '-') minus = true;
	if (str[from] == '-' || str[from] == '+') from++;

	double num = 0.0;
	double decimal = 1.0;

	bool integer_part = true;
	for (int i = from; i <= to; i++) {
		if (isdigit(str[i]) && integer_part) {
			num *= 10.0;
			num += (str[i] - '0'); // 정수부분 계산 
			// 그 숫자에 해당하는 실제 정수 값 구하기.
		}
		else if (str[i] == '.') {
			integer_part = false; // 이제 소수부분이다.
		}
		else if (isdigit(str[i]) && !integer_part) {
			decimal /= 10.0;
			num += ((str[i] - '0') * decimal);
		}
		else {
			break;
		}
	}
	if (minus) num *= -1.0;

	return num;
}
Complex:: Complex(const char* str) {
	// 입력 받은 문자열을 분석하여 real 부분과 img 부분을 찾아야 한다.
	// 문자열의 꼴은 다음과 같습니다. "[부호](실수부)[부호]i(허수부)"
	// 이 때 맨 앞의 부호는 생략 가능합니다. (생략시 + 라 가정합니다.)

	int begin = 0, end = strlen(str);
	img = 0.0;
	real = 0.0;

	// 먼저 가장 기준이 되는 'i'의 위치를 찾는다.
	int pos_i = -1;
	for (int i = 0; i != end; i++) {
		if (str[i] == 'i') {
			pos_i = i;
			break;
		}
	}
	// 만약 i가 없다면 실수만 있다.
	if (pos_i == -1) {
		real = get_number(str, begin, end - 1);
		return;
	}

	// 만약 'i'가 있다면, 실수부와 허수부를 나누어서 처리하면 된다.
	real = get_number(str, begin, pos_i - 1);
	img = get_number(str, pos_i + 1, end - 1);

	if (pos_i >= 1 && str[pos_i - 1] == '-') img *= -1.0;

}
Complex& Complex::operator+=(const Complex& c) {
	(*this) = (*this) + c;
	return *this;
}
Complex& Complex::operator-=(const Complex& c) {
	(*this) = (*this) - c;
	return *this;
}
Complex& Complex::operator*=(const Complex& c) {
	(*this) = (*this) * c;
	return *this;
}
Complex& Complex::operator/=(const Complex& c) {
	(*this) = (*this) / c;
	return *this;
}

Complex& Complex::operator=(const Complex& c) {
	real = c.real;
	img = c.img;
	return *this;
}
Complex Complex::operator+(const Complex& c) {
	Complex temp(real + c.real, img + c.img);
	return temp;
}
Complex Complex::operator-(const Complex& c) {
	Complex temp(real - c.real, img - c.img);
	return temp;
}
Complex Complex::operator*(const Complex& c) {
	Complex temp(real * c.real - img * c.img, real * c.img + img * c.real);
	return temp;
}
Complex Complex::operator/(const Complex& c) {
	Complex temp(
		(real * c.real + img * c.img) / (c.real * c.real + c.img * c.img),
		(img * c.real - real * c.img) / (c.real * c.real + c.img * c.img));
	return temp;
}

int main() {
	Complex a(0, 0);
	a = a + "-1.1 + i3.023";
	a.println();
	a = a - "1.2 - i1.823";
	a.println();
	a = a * "2.3+i22";
	a.println();
	a = a / "-12+i55";
	a.println();
}