#include <iostream>
#include <windows.h>
#include "Matrix.h"


using namespace luMath;


double rand_double(double min, double max) // [min, max)
{
	return min + (double)rand() / RAND_MAX * (max - min);
}

double rand_matrix_initer(size_t m, size_t n, size_t r, size_t c)
{
	return (int)rand_double(-10, 10);
}

double unit_matrix_initer(size_t m, size_t n, size_t r, size_t c)
{
	return r == c;
}

double invert_unit_matrix_initer(size_t m, size_t n, size_t r, size_t c)
{
	return (m - 1 - r) == c;
}


inline void sep()
{
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~\n";
}

inline void hed(std::string header)
{
	std::cout << "~~~ " << header << " ~~~~~~~~~~~~~~~~~\n";
}

int main()
{
	system("color 1E");
	setlocale(LC_ALL, "Rus");
	srand(static_cast<unsigned int>(time(0)));
	rand();



	Matrix<int> matrix0;
	matrix0 = { 0,1,2,3,4,5,6,7,8 };
	std::cout << "\nmatrix0: \n" << matrix0 << std::endl;
	Matrix<int> matrix9({ 11,12,13,14,15,16,17,18,19,20 });
	std::cout << "\nmatrix9: \n" << matrix9 << std::endl;

	matrix0 = matrix9;
	
	Matrix<int> asterix(true);
	std::cout << "\nasterix: \n" << std::setw(25) << asterix << std::endl;
	
	Matrix<int> masterix(8, true);
	std::cout << "\nmasterix: \n" << masterix << std::endl;

	Matrix<int> matrix(4, 8, true);
	std::cout << "\nmatrix: \n" << matrix << std::endl;

	Matrix<int> maMatrix(matrix);
	std::cout << "\nmaMatrix: \n" << maMatrix << std::endl;

	Matrix<int> abelix(matrix + maMatrix);
	abelix = matrix + maMatrix;
	std::cout << "\nabelix: \n" << matrix << '+' << maMatrix << '=' << abelix << std::endl;

	Matrix<int> matrix1(matrix - maMatrix);
	std::cout << "\nmatrix1: \n" << matrix << '-' << maMatrix << '=' << matrix1 << std::endl;

	Matrix<int> matrix2(matrix * masterix);
	std::cout << "\nmatrix2: \n" << matrix << '*' << masterix << "=" << matrix2 << std::endl;

	std::cout << "\nThe max item of matrix2: \n" << matrix2 << "\t\tis " << matrix2.getMax() << std::endl;
	std::cout << "\nThe min item of matrix2: \n" << matrix2 << "\t\tis " << matrix2.getMin() << std::endl;
	int k = 3;
	Matrix<int> matrix3(matrix * k);
	std::cout << "\nmatrix3: \n" << matrix << '*' << k << "\n=" << matrix3 << std::endl;

	Matrix<int> matrix4(4, 8);
	matrix4 = matrix;

	std::cout << "\nmatrix4: \n" << matrix4 << "+=" << abelix << '=' << std::endl;
	matrix4 += abelix;
	std::cout << matrix4 << std::endl;

	std::cout << "\nmatrix4: \n" << matrix4 << "-=" << abelix << '=' << std::endl;
	matrix4 -= abelix;
	std::cout << matrix4 << std::endl;

	std::cout << "\nmatrix4: \n" << matrix4 << "*=" << masterix << '=' << std::endl;
	matrix4 *= masterix;
	std::cout << matrix4 << std::endl;

	std::cout << "\nmatrix4: \n" << matrix4 << '*' << k << "=\n" << std::endl;
	matrix4 *= k;
	std::cout << matrix4 << std::endl;
	try { std::cout << "\nmatrix4[3][7]: \n" << matrix4[3][7] << std::endl; }
	catch (const std::logic_error exception)
	{
		std::cout << exception.what() << "\n\tИсключение обработано: будет выведен элемент: matrix4[2][2]  ->" << '\t'
			<< matrix4[2][2] << std::endl;
	}


	Matrix<int> matrix5(3);
	std::cin >> matrix5;
	std::cout << "\nmatrix5: \n" << matrix5 << std::endl;
	Matrix<int> matrix6(3);
	std::cin >> matrix6;
	std::cout << "\nmatrix6: \n" << matrix6 << std::endl;
	std::cout << "\nmatrix5: \n" << matrix5 << "*=" << matrix6 << '=' << std::endl;
	matrix5 *= matrix6;
	std::cout << "\nmatrix5: \n" << matrix5 << std::endl;
	matrix5[2][2] = 6;
	const Matrix<int> mamAtrix(matrix5);
	std::cout << std::setw(15) << mamAtrix << "\n" << matrix5[2][2] << '\n';
	
	/*
	hed("******************ТЕСТИРОВАНИЕ КЛАССА VECTOR***********************");

	Vector<int> A{ 1,2,3 };
	std::cout << "\nТестирование функций доступа к членам класса\n"
		<< "---> Сеттеры (Запись данных)\n";
	std::cin >> A;

	std::cout << "---> Геттер (Чтение данных)\n"
		<< A << std::endl
		<< "Вычисление модуля(длины) вектора: " << A.module() << std::endl;


	Vector B = A;
	std::cout << "\nКопирование вектора " << A << " в вектор " << B << std::endl;

	std::cout << "Результат: " << B << std::endl;

	std::cout << "\nУмножение вектора на скаляр.\n"
		<< "Введите скалярное значение: ";
	double scal;
	std::cin >> scal;
	std::cout << B << " * " << scal << " = ";
	std::cout << B * scal;

	try {
		std::cout << "\nДвуместные операции над векторами А и B с получением нового вектора С \n"
			<< "Сложение: " << A << " + " << B << " = " << A + B << std::endl
			<< "Разность: " << A << " - " << B << " = " << A - B << std::endl
			<< "Векторное произведение: [ " << A << ", " << B << "] = " << A * B << std::endl;
	}
	catch (const std::logic_error msg)
	{
		std::cout << msg.what();
	}

	Matrix me(3, 5, true), ms(5, 10, true);
	// ve - вектор-строка длиной 5 с рандомными значениями; 
	// vs - вектор-столбец длиной 3 с рандомными значениями;
	Vector ve(5, false, true), vs(5, true, true);
	std::cout << "\n\tve[3]" << ve[3] << std::endl;
	std::cout << "\nУмножение объектов: \n";
	std::cout << "Вектор на матрицу: \n" << ve << "\t*" << ms << "\n=\n" << ve * ms << std::endl;
	std::cout << "Матрицу на вектор: \n" << me << "\t*" << vs << "\n\=\n" << me * vs << std::endl;
	std::cout << "Матрицу на матрицу: \n" << me << "\t*" << ms << "\t=\n" << me * ms << std::endl;
	std::cout << "Вектор-столбец на вектор-строку:\n" << vs << "\t*" << ve << "\n=\n" << ve * vs << std::endl;
	std::cout << "Вектор-строку на вектор-столбец:\n" << ve << "\t*" << vs << "\n=\n" << vs * ve << std::endl;




	hed("*****************************************");

	Matrix
		m0(true),
		m1(2, 3, true),
		m2(2, true),
		m3(2, 3,
			new double[2 * 3]
			{
				1, 2, 3,
				4, 5, 6
			}),
		m4(3, 3, rand_matrix_initer),
		m5(3, 3, unit_matrix_initer),
		m6(3, 3, invert_unit_matrix_initer);

	sep();

	std::cout << m0 << m1 << m2 << m3 << m4 << m5 << m6;

	hed("sum");

	try
	{
		m1 + m2;
	}
	catch (const std::logic_error msg)
	{
		std::cout << msg.what() << std::endl;
	}

	hed("sum");

	m2 + m2;

	hed("sub");

	m2 - m2;

	hed("mul");

	m2* m2;

	sep();

	try
	{
		Matrix::getMin(m0);
	}
	catch (const std::logic_error msg)
	{
		std::cout << msg.what() << std::endl;
	}

	sep();

	std::cout << "(" << Matrix::getId(m3) << ") (min, max) = (" << Matrix::getMin(m3) << ", " << Matrix::getMax(m3) << ")\n";

	sep();

	try
	{
		m4[3][3];
	}
	catch (const std::logic_error msg)
	{
		std::cout << msg.what() << std::endl;
	}

	try
	{
		m4[0][-1];
	}
	catch (const std::logic_error msg)
	{
		std::cout << msg.what() << std::endl;
	}


	hed("MAIN END");*/
}
