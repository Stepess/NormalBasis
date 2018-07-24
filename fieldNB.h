#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

class fieldNB
{
public:
	fieldNB();
	fieldNB(string flag, string input);
	void show(string flag);
	void set(fieldNB& A);
	void add(fieldNB& A, fieldNB& B);
	void squaring(fieldNB& A);
	int trace();
	void cicleLeftShift(fieldNB& A);
	void setCell(int index, int value);
	void null();
	void one();
	void mul(fieldNB& A, fieldNB& B, int** matrix);
	void searchReverseEL(fieldNB& A, int** matrix);
	void power(fieldNB& A, int n, int** matrix);
	~fieldNB();

private:
	int* el = new int[191];
};

fieldNB::fieldNB()
{
	for (int i = 0; i < 191; i++)
		el[i] = 0;
}

fieldNB::fieldNB(string flag, string input)
{
	if (flag == "bin") {
		int s = input.size();
		for (int i = 0; i < s; i++)
			el[i] == input[i] - '0';
	}
	else
		if (flag == "hex") {
			int i = 0;
			int s = input.size();
			int buff;
			int f = 0;
			char symb;
			for (int j = 0; j < s; j++) {
				//cout << input[j];
				f = 0;
				switch (input[j])
				{
				case 'A':
					symb = '0';
					f = 1;
					break;
				case 'B':
					symb = '1';
					f = 1;
					break;
				case 'C':
					symb = '2';
					f = 1;
					break;
				case 'D':
					symb = '3';
					f = 1;
					break;
				case 'E':
					symb = '4';
					f = 1;
					break;
				case 'F':
					symb = '5';
					f = 1;
					break;
				default:
					f = 0;
					break;
				}
				if (f == 1) { buff = symb - '0' + 10; }
				else { buff = input[j] - '0'; }
				for (int k = 3; k > -1; k--) {
					if (i == 0)
						k--;
					if (i != 191)
						el[i] = ((buff >> k) & 1);
					i++;
				}
				
			}
		}
}

void fieldNB::show(string flag)
{
	if (flag == "bin")
	{
		for (int i = 0; i < 191; i++)
			cout << el[i] << "   ";
	}
	else
		if (flag == "hex") {
			string res = "";
			int buff = 0;
			char x;
			for (int i = 0; i < 191; i = i + 4)
			{
				if (i == 0) {
					buff = buff + (el[i] << 2);
					buff = buff + (el[i + 1] << 1);
					buff = buff + el[i + 2];
					i = -1;
				}else
				if (i != 188) {
					buff = buff + (el[i] << 3);
					buff = buff + (el[i + 1] << 2);
					buff = buff + (el[i + 2] << 1);
					buff = buff + (el[i + 3] << 0);
				}
				else {
					buff = buff + (el[i] << 2);
					buff = buff + (el[i + 1] << 1);
					buff = buff + (el[i + 2] << 0);
				}
				switch (buff)
				{
				case 0:
					x = '0';
					break;
				case 1:
					x = '1';
					break;
				case 2:
					x = '2';
					break;
				case 3:
					x = '3';
					break;
				case 4:
					x = '4';
					break;
				case 5:
					x = '5';
					break;
				case 6:
					x = '6';
					break;
				case 7:
					x = '7';
					break;
				case 8:
					x = '8';
					break;
				case 9:
					x = '9';
					break;
				case 10:
					x = 'A';
					break;
				case 11:
					x = 'B';
					break;
				case 12:
					x = 'C';
					break;
				case 13:
					x = 'D';
					break;
				case 14:
					x = 'E';
					break;
				case 15:
					x = 'F';
					break;
				default:
					break;
				}
				res = res + x;
				buff = 0;
			}
			int m = res.size();
			if (m == 0) {
				cout << '0';
				return;
			}
			cout << res;
			return;
		}
}

void fieldNB::set(fieldNB& A)
{
	for (int i = 0; i < 191; i++)
		el[i] = A.el[i];
}

void fieldNB::add(fieldNB& A, fieldNB& B)
{
	fieldNB C;
	for (int i = 0; i < 191; i++)
		C.el[i] = (A.el[i] + B.el[i]) & 1;
	this->set(C);
}

void fieldNB::squaring(fieldNB& A)
{
	fieldNB C;
	for (int i = 1; i < 191; i++)
		C.el[i] = A.el[i-1];
	C.el[0] = A.el[190];
	this->set(C);
}

int fieldNB::trace()
{
	int res;
	for (int i = 0; i < 191; i++)
		res = (res + el[i]) & 1;
	return res;
}

void fieldNB::cicleLeftShift(fieldNB& A)
{
	fieldNB C;
	for (int i = 1; i < 191; i++)
		C.el[i-1] = A.el[i];
	C.el[190] = A.el[0];
	this->set(C);
}

void fieldNB::setCell(int index, int value)
{
	el[index] = value;
}

void fieldNB::null()
{
	for (int i = 0; i < 191; i++)
		el[i] = 0;
}

void fieldNB::mul(fieldNB& A, fieldNB& B, int** matrix)
{
	fieldNB X,Y,C,res;
	int k=0;
	X.set(A);
	Y.set(B);
	for (int l = 0; l < 191; l++)
	{
		k = 0;
		C.null();
		for (int j = 0; j < 191; j++)
			for (int i = 0; i < 191; i++)
				C.el[j] = (C.el[j] + X.el[i] * matrix[i][j]) % 2;
		for (int i = 0; i < 191; i++)
			k = (k + C.el[i] * Y.el[i]) % 2;
		res.setCell(l, k);
		X.cicleLeftShift(X);
		Y.cicleLeftShift(Y);
	}
	
	this->set(res);
}

string converToBin(int n)
{
	string res = "", buff = "";
	if (n == 0) {
		res = "0";
		return res;
	}
	if (n == 1) {
		res = "1";
		return res;
	}
	int m = log2(n) + 1;
	for (int i = 0; i < m; i++)
		res = res + to_string((n >> i) & 1);
	reverse(res.begin(), res.end());
	return res;
}

void fieldNB::searchReverseEL(fieldNB& A, int** matrix)
{
	string s = converToBin(190);
	fieldNB C,buff;
	C.set(A);
	int k = 1;
	for (int i = s.size()-1; i > -1; i--)
	{
		buff.set(C);
		for (int j = 0; j < k; j++)
			buff.squaring(buff);
		C.mul(C, buff, matrix);
		k = k * 2;
		if (s[i] == '1') {
			buff.squaring(C);
			C.mul(buff, A, matrix);
			k++;
		}
	}
	C.squaring(C);
	this->set(C);
}

void fieldNB::one()
{
	for (int i = 0; i < 191; i++)
		el[i] = 1;
}

void fieldNB::power(fieldNB& A, int n, int** matrix)
{
	fieldNB C;
	C.one();
	string bin = converToBin(n);
	for (int i = 0; i < bin.size(); i++) {
		if (bin[i] == '1') {
			C.mul(C, A, matrix);
		}
		if (i != bin.size() - 1) {
			C.squaring(C);
		}
	}
	this->set(C);
}

fieldNB::~fieldNB()
{
	delete[] el;
}


int** mulMatrix()
{
	int** matrix = new int*[191];
	int x = 0, y = 0, buff = 0;
	int size = 191;
	int p = size * 2 + 1;
	for (int i = 0; i < 191; i++)
		matrix[i] = new int[191];
	for (int i = 0; i < 191; i++)
		for (int j = 0; j < 191; j++)
			matrix[i][j] = 0;
	for (int i = 0; i<size; i++)
		for (int j = i; j < size; j++) {
			x = 1;
			for (int k = 0; k < i; k++)
				x = (x * 2) % p;
			y = 1;
			for (int k = 0; k < j; k++)
				y = (y * 2) % p;
			buff = (x + y) % p;
			if (buff == 1)
				matrix[i][j] = 1;
			else {
				buff = (x - y);
				if (buff < 0)
					buff = buff + p;
			}
			if (buff == 1)
				matrix[i][j] = 1;
			else {
				buff = (-x + y);
				if (buff < 0)
					buff = buff + p;
			}
			if (buff == 1)
				matrix[i][j] = 1;
			else {
				buff = -x - y;
				if (buff < 0)
					buff = buff + p;
			}
			if (buff == 1)
				matrix[i][j] = 1;
		}
	for (int j = 0; j < size; j++)
		for (int i = j; i < size; i++)
			matrix[i][j] = matrix[j][i];
	return matrix;
	for (int i = 0; i < 191; i++)
		delete[] matrix[i];
}

