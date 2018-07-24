// NormalBasis.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "fieldNB.h"

using namespace std;


int main()
{
	fieldNB f("hex", "4A5E97DDD0235061444E0274039EB64228B3AA09C35FD8EF");
	f.show("hex");
	cout << endl;
	fieldNB f1("hex", "1DCA661CFB2F5C0C699AD93AA3FEEADD2B9906009C5CD540");
	f1.show("hex");
	cout << endl;
	fieldNB f2,f3,f4,f5,f6;
	f2.add(f, f1);
	f2.show("hex");
	cout << endl;
	f3.squaring(f);
	f3.show("hex");
	cout << endl;
	cout << f.trace() << endl;
	int** A = new int*[191];
	for (int i = 0; i < 191; i++)
		A[i] = new int[191];
	A = mulMatrix();


	/*for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
			cout << A[i][j] << " ";
		cout << endl;
	}*/
		
	f4.mul(f, f1, A);
	f4.show("hex");
	cout << endl;
	f5.searchReverseEL(f, A);
	f5.show("hex");
	cout << endl;
	f6.power(f, 2, A);
	f6.show("hex");
	cout << endl;
	for (int i = 0; i < 191; i++)
		delete[] A[i];
	getchar();
    return 0;
}

