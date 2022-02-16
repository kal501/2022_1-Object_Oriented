#include <string.h>

#include <iostream>
using namespace std;

class MyString {
	char* string_content;	 // ���ڿ� �����͸� ����Ű�� ������
	int string_length;		 // ���ڿ� ����
	int memory_capacity;	 // ���� �Ҵ�� �뷮

public:
	// capacity ��ŭ �̸� �Ҵ���.
	explicit MyString(int capacity);

	// ���� �ϳ��� ����
	MyString(char c);
	
	// ���ڿ��� ���� ����
	MyString(const char* str);

	// ���� ������
	MyString(const MyString& str);

	// �Ҹ���
	~MyString();

	
	MyString& assign(const MyString& str);
	
	MyString& assign(const char* str);

	int length() const;

	void print() const;
	
	void println() const;

	char at(int i) const;

	int capacity() const;

	void reserve(int size);

	MyString& insert(int loc, const MyString& str);
	MyString& insert(int loc, const char* str);
	MyString& insert(int loc, char c);

	MyString& erase(int loc, int num);
	int find(int find_from, MyString& str) const;
	int find(int find_from, const char* str) const;
	int find(int find_from, char c) const;

	int compare(const MyString& str) const;
};
// �� ���ڿ��� ���������� ���ϴ� �Լ� compare()
MyString::MyString(int capacity) {
	string_content = new char[capacity];
	string_length = 0;
	memory_capacity = capacity;
}
int MyString::compare(const MyString& str) const {
	// (*this) - (str) �� �����ؼ� �� 1, 0 ,-1�� �� ����� �����մϴ�.
	// 1 �� (*this) �� ���������� �� �ڿ� �´ٴ� �ǹ�.
	// 0 �� �� ���ڿ��� �����ϴ�.
	// -1�� (*this)�� ���������� �� �տ� �´ٴ� �ǹ��Դϴ�.
	for (int i = 0; i < min(string_length, str.string_length); i++) {
		if (string_content[i] > str.string_content[i]) {
			return 1;
		}
		else if (string_content[i] < str.string_content[i]) {
			return -1;
		}
	}

	// ������� �����ߴٸ� �� �κб��� ��� ������ ������ ���̴�.
	// ���� ���ڿ� ���̰� ���ٸ� �� ���ڿ��� ���� ���ڿ��� ���̴�.

	if (string_length == str.string_length) return 0; // ������ ����

	// abc�� abcd�� compare �Ѵٸ� abcd�� ���������� �� �ڿ� ���� �ȴ�. -> -1 ��ȯ
	else if (string_length > str.string_length) {
		return 1;
	}
	return -1;

}

// Ư�� ��ġ�� �������� Ư�� ���ڿ��� �˻��ϴ� �Լ� find()

int MyString::find(int find_from, MyString& str) const {
	int i, j;
	if (str.string_length == 0) return -1;
	for (i = find_from; i <= string_length - str.string_length; i++) {
		for (j = 0; j < str.string_length; j++) {
			if (string_content[i + j] != str.string_content[j]) break;
		}
		if (j == str.string_length) return i;
	}
	return -1;
}

// Ư�� ��ġ�� �������� Ư�� ���ڿ��� �˻��ϴ� �Լ� find()

int MyString::find(int find_from, const char* str) const {
	MyString temp(str);
	return find(find_from, temp);
}

// Ư�� ��ġ�� �������� Ư�� ���ڿ��� �˻��ϴ� �Լ� find()

int MyString::find(int find_from, char c) const {
	MyString temp(c);
	return find(find_from, temp);

}
// Ư�� ��ġ�� Ư�� ������ ���ڸ� ����� �Լ� erase()

MyString& MyString::erase(int loc, int num) {
	// loc �� �պ��� �����ؼ� num ���ڸ� �����.
	if (num < 0 || loc<0 || loc>string_length) return *this;

	// ����ٴ� ���� �ܼ��� ���� ���ڵ��� ������ ���� �´ٰ� �����ϸ�˴ϴ�.

	for (int i = loc + num; i < string_length; i++) {
		string_content[i - num] = string_content[i];
	}
	string_length -= num;
	return *this;
}
// Ư�� ��ġ�� Ư�� ���ڿ��� �����ϴ� �Լ� insert()

MyString& MyString::insert(int loc, const MyString& str) {
	// �̴� i�� ��ġ �ٷ� �տ� ���ڸ� �����ϰ� �˴ϴ�.
	// abc ��� ���ڿ��� insert(1, "d")�� �����Ѵٸ� adbc�� �˴ϴ�.

	// ������ ����� �Է¿� ���ؼ��� ������ �������� ����.
	if (loc < 0 || loc>string_length) return *this;

	if (string_length + str.string_length > memory_capacity) {
		// ���Ӱ� �ٽ� �����Ҵ��� �ؾߵ˴ϴ�.
		if (memory_capacity * 2 > string_length + str.string_length)
		{
			memory_capacity *= 2;
		}
		else {
			memory_capacity = string_length + str.string_length;
		}
		char* prev_string_content = string_content;
		string_content = new char[memory_capacity];

		// �ϴ� insert �Ǵ� �κ� ���������� ������ �����Ѵ�.
		int i;
		for (i = 0; i < loc; i++) {
			string_content[i] = prev_string_content[i];
		}
		for (int j = 0; j != str.string_length; j++) {
			string_content[i + j] = str.string_content[j];
		}

		// ���� �ٽ� �� ���ڿ��� ������ �޺κ��� �����մϴ�.
		for (; i < string_length; i++) {
			string_content[str.string_length + i] = prev_string_content[i];
		}

		delete[] prev_string_content;

		string_length = string_length + str.string_length;
		return *this;
	}
	// ���� �ʰ����� �ʴ� ��� ���� �����Ҵ��� �� �ʿ䰡 ���� �ȴ�.
	// ȿ�������� insert �ϱ� ����, �и��� �κ��� ���� �ڷ� �о������.

	for (int i = string_length - 1; i >= loc; i++) {
		// �ڷ� �б�. �� �� ������ ���ڿ� �����Ͱ� ������� �ʰ� �մϴ�.
		string_content[i + str.string_length] = string_content[i];
	}
	// �׸��� insert �Ǵ� ���� �ٽ� ���� �ֱ�
	for (int i = 0; i < str.string_length; i++) {
		string_content[i + loc] = str.string_content[i];
	}
	string_length = string_length + str.string_length;
	return *this;
}
// Ư�� ��ġ�� Ư�� ���ڿ��� �����ϴ� �Լ� insert()

MyString& MyString::insert(int loc, const char* str) {
	MyString temp(str);
	return insert(loc, temp);
}
// Ư�� ��ġ�� Ư�� ���ڿ��� �����ϴ� �Լ� insert()

MyString& MyString::insert(int loc, char c) {
	MyString temp(c);
	return insert(loc, temp);
}

// Ư�� ��ġ�� ���ڸ� �����ϴ� �Լ� at()

char MyString::at(int i) const {
	if (i >= string_length || i < 0) {
		// �ùٸ��� ���� ������ �迭�� �����Ѵٸ�
		return NULL; // null�� ��ȯ�մϴ�.
	}
	else
		return string_content[i];
}
// ���� �Ҵ�� ũ�⸦ �������ִ� �Լ� capacity()

int MyString::capacity() const { return memory_capacity; }


// ���ڿ� �޸𸮸� �̸� �Ҵ��ϴ� �Լ� reserve()
void MyString::reserve(int size) {
	if (size > memory_capacity) {
		char* prev_string_content = string_content;
		string_content = new char[size];
		memory_capacity = size;

		for (int i = 0; i != string_length; i++) {
			string_content[i] = prev_string_content[i];
		}
		delete[] prev_string_content;
	}
}

// ���� c or C ���� ���ڿ� str���� ������ �� �ִ� �����ڿ� ���������
MyString::MyString(char c) {
	string_content = new char[1];
	string_content[0] = c;
	string_length = 1;
}

MyString::MyString(const char* str) {
	string_length = strlen(str);
	string_content = new char[string_length];

	for (int i = 0; i != string_length; i++) {
		string_content[i] = str[i];
	}
}

MyString::MyString(const MyString& str) {
	string_length = str.string_length;
	for (int i = 0; i != string_length; i++) {
		string_content[i] = str.string_content[i];
	}
}
//

//�����ڿ� ���� �Ҹ��� ����
MyString::~MyString() { delete[] string_content; }

// ���ڿ��� ���̸� �����ϴ� length() �Լ�
int MyString::length() const { return string_length; }


void MyString::print() const {
	for (int i = 0; i != string_length; i++) {
		cout << string_content[i];
	}

}

void MyString::println() const {
	for (int i = 0; i != string_length; i++) {
		cout << string_content[i];
	}
	cout << endl;
}
// ���ڿ� �����Լ� assign()
MyString& MyString::assign(const MyString& str) {
	if (str.string_length > memory_capacity) {
		// �׷��� �ٽ� �Ҵ��� ����߸� �Ѵ�.
		delete[] string_content;

		string_content = new char[str.string_length];
		memory_capacity = str.string_length;
	}

	for (int i = 0; i != str.string_length; i++) {
		string_content[i] = str.string_content[i];
	}

	// �׸��� ���� str.string_length + 1 ~ string_length �κ��� �ʱ�ȭ ��ų �ʿ䰡 ����.
	// �ֳ��ϸ� �ű� ������ �о������ �ʱ� �����̴�.

	string_length = str.string_length;

	return *this;
}
// ���ڿ� �����Լ� assign()
MyString& MyString::assign(const char* str) {
	int str_length = strlen(str);
	if (str_length > memory_capacity) {
		delete[] string_content;

		string_content = new char[str_length];
		memory_capacity = str_length;
	}
	for (int i = 0; i != str_length; i++) {
		string_content[i] = str[i];
	}

	string_length = str_length;

	return *this;
}
int main() {
	MyString s(3); //��� explicit Ű���� ��� 
}
