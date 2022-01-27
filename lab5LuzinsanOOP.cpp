#include <iostream>
#include <iomanip>
#include "Matrix.h"
#include "Vector.h"
#include "MatrixAdd.h"
#include "Polynomial.h"
#include "Fraction.h"
using namespace luMath;

template<class T> T rand_double(T min=0, T max=100) // [min, max)
{
    return min + (int)rand() % (int)(max - min);
}
template<class T> T unit_matrix_initer(size_t m, size_t n, size_t r, size_t c)
{
    return r == c;
}
template<class T> T invert_unit_matrix_initer(size_t m, size_t n, size_t r, size_t c)
{
    return (m - 1 - r) == c;
}
inline void sep()
{
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~\n";
}
inline void hed(std::string header)
{
    std::cout << "~~~~~~~~~~~~~~ " << header << " ~~~~~~~~~~~~~~~~~\n";
}

int main()
{
    setlocale(LC_ALL, "Rus");
    srand(static_cast<unsigned int>(time(0)));
    rand();
    /*
    {
        hed("ТЕСТИРОВАНИЕ КЛАССА MATRIX");

        Matrix<int> matrix0;
        std::cout << matrix0 << std::endl;
        system("pause");
        system("cls");

        hed("ТЕСТИРОВАНИЕ КЛАССА MATRIX");
        Matrix<double> matrix1(2, 3);
        std::cout << matrix1 << std::endl;
        system("pause");
        system("cls");

        hed("ТЕСТИРОВАНИЕ КЛАССА MATRIX");
        int array0[] = { 1,2,3,4,5,6,7,8,9 };
        Matrix<int> matrix2(3, 3, array0);
        std::cout << matrix2 << std::endl;
        system("pause");
        system("cls");

        hed("ТЕСТИРОВАНИЕ КЛАССА MATRIX");
        Matrix<int> matrix3({ 4,9,7,8,4,6,2,0,3 });
        std::cout << matrix3 << std::endl;
        system("pause");
        system("cls");

        hed("ТЕСТИРОВАНИЕ КЛАССА MATRIX");
        try {
            Matrix<int> matrix4({ 1,5,9,44,5 }, 2);
            std::cout << matrix4 << std::endl;
        }
        catch (std::length_error err)
        {
            std::cout << err.what();
            Matrix<int> matrix4({ 1,5,9,44 }, 2);
            std::cout << matrix4 << std::endl;
        }
        system("pause");
        system("cls");

        hed("ТЕСТИРОВАНИЕ КЛАССА MATRIX");
        Matrix<int> matrix5({ 1,5,9,44,77,10 }, 2, 3);
        std::cout << matrix5 << std::endl;
        system("pause");
        system("cls");

        hed("ТЕСТИРОВАНИЕ КЛАССА MATRIX");
        Matrix<char> matrix6(15, rand_double, 10, 190);
        std::cout <<std::setw(5) << matrix6 << std::endl;
        std::cout << "Min=" << matrix6.getMin() << "; Max=" << matrix6.getMax() << std::endl;
        system("pause");
        system("cls");

        hed("ТЕСТИРОВАНИЕ КЛАССА MATRIX");
        Matrix <double> matrix7(9, 10, unit_matrix_initer);
        std::cout << matrix7 << std::endl;
        Matrix<double> matrix8(10, 9, invert_unit_matrix_initer);
        std::cout << matrix8 << std::endl;
        system("pause");
        system("cls");

        hed("ТЕСТИРОВАНИЕ КЛАССА MATRIX");
        Matrix<int> matrix9(matrix3);
        std::cout << matrix9 << std::endl;
        system("pause");
        system("cls");

        hed("ТЕСТИРОВАНИЕ КЛАССА MATRIX");
        sep();
        Matrix<int> matrix10(matrix9 + matrix3);
        std::cout << "\t№" << matrix9.getId() << '\n' << matrix9 << "\n+\t№" << matrix3.getId() << '\n' << matrix3 << "\n=\n" << matrix10 << std::endl;
        sep();

        Matrix<int> matrix11(matrix10 - matrix9);
        std::cout << "\t№" << matrix10.getId() << '\n' << matrix10 << "\n-\t№" << matrix9.getId() << '\n' << matrix9 << "\n=\n" << matrix11 << std::endl;
        sep();

        Matrix<int> matrix12(matrix5 * matrix2);
        std::cout << "\t№" << matrix5.getId() << '\n' << matrix5 << "\n*\t№" << matrix2.getId() << '\n' << matrix2 << "\n=\n" << matrix12 << std::endl;
        sep();

        Matrix<double> matrix13(matrix7 * 3);
        std::cout << "\t№" << matrix7.getId() << '\n' << matrix7 << "\n*\t3\n=\n" << matrix13 << std::endl;
        sep();
        system("pause");
        system("cls");

        hed("ТЕСТИРОВАНИЕ КЛАССА MATRIX");
        try
        {
            std::cout << matrix6 << "\nmatrix6[3][15]: \n" << matrix6[3][15] << std::endl;
        }
        catch (const std::out_of_range exception)
        {
            std::cout << exception.what() << matrix6
                << "\nmatrix6[-1][-1]: \n" << matrix6[-1][-1] << std::endl;
        }
        system("pause");
        system("cls");
    }
    system("pause");
    system("cls");
    {
        hed("ТЕСТИРОВАНИЕ КЛАССА VECTOR");
        Vector<int> vector0;
        std::cout << vector0 << std::endl;
        system("pause");
        system("cls");

        hed("ТЕСТИРОВАНИЕ КЛАССА VECTOR");
        Vector<int> vector1(3);
        std::cout << vector1 << std::endl;
        system("pause");
        system("cls");

        hed("ТЕСТИРОВАНИЕ КЛАССА VECTOR");
        int array0[] = { 1,2,3,4,5,6,7,8,9 };
        Vector<int> vector2(9, array0);
        std::cout << vector2 << std::endl;
        system("pause");
        system("cls");

        hed("ТЕСТИРОВАНИЕ КЛАССА VECTOR");
        Vector<int> vector3(9, array0, true);
        std::cout << vector3 << std::endl;
        system("pause");
        system("cls");

        hed("ТЕСТИРОВАНИЕ КЛАССА VECTOR");
        Vector<int> vector4({ 4,9,7,8,4,6,2,0,3 });
        std::cout << vector4 << std::endl;
        system("pause");
        system("cls");

        hed("ТЕСТИРОВАНИЕ КЛАССА VECTOR");
        Vector<int> vector5({ 1,5,9,44,77,10,7,49,2 }, true);
        std::cout << vector5 << std::endl;
        system("pause");
        system("cls");

        hed("ТЕСТИРОВАНИЕ КЛАССА VECTOR");
        Vector<int> vector6(15, rand_double, 45, 160);
        std::cout << vector6 << std::endl;
        std::cout << "Min=" << vector6.getMin() << "; Max=" << vector6.getMax() << std::endl;
        system("pause");
        system("cls");

        hed("ТЕСТИРОВАНИЕ КЛАССА VECTOR");
        Vector<int> vector7(vector5);
        std::cout << vector7 << std::endl;
        system("pause");
        system("cls");

        hed("ТЕСТИРОВАНИЕ КЛАССА VECTOR");
        sep();
        Vector<int> vector8(vector2 + vector4);
        std::cout << "\t№" << vector2.getId() << '\n' << vector2 << "\n+\t№" << vector4.getId() << '\n' << vector4 << "\n=\n" << vector8 << std::endl;
        sep();

        Vector<int> vector9(vector8 - vector4);
        std::cout << "\t№" << vector8.getId() << '\n' << vector8 << "\n-\t№" << vector4.getId() << '\n' << vector4 << "\n=\n" << vector9 << std::endl;
        sep();

        Vector<int> vector10(Vector<int>(2, rand_double, 2, 15, false));
        Vector<int> vector11(Vector<int>(2, rand_double, 2, 9, true));
        Vector<int> vector12(vector10 * vector11);
        std::cout << "\t№" << vector10.getId() << '\n' << vector10 << "\n*\t№" << vector11.getId() << '\n' << vector11 << "\n=\n" << vector12 << std::endl;
        sep();

        Vector<int> vector13(vector3 * 3);
        std::cout << "\t№" << vector3.getId() << '\n' << vector3 << "\n*\t3\n=\n" << vector13 << std::endl;
        sep();
        system("pause");
        system("cls");

        hed("ТЕСТИРОВАНИЕ КЛАССА VECTOR");
        try
        {
            std::cout << vector13 << "\nvector13[15]: \n" << vector13[15] << std::endl;
        }
        catch (const std::out_of_range exception)
        {
            std::cout << exception.what() << vector13
                << "\nvector13[-1]: \n" << vector13[-1] << std::endl;
        }
        system("pause");
        system("cls");

        hed("ТЕСТИРОВАНИЕ КЛАССА VECTOR И КЛАССА MATRIX");
        Matrix<int> me(3, 5, rand_double), ms(5, 10, rand_double);
         //ve - вектор-строка длиной 5 с рандомными значениями; 
         //vs - вектор-столбец длиной 5 с рандомными значениями;
        Vector<int> ve(5, rand_double, 0,20,false), vs(5, rand_double, 0, 20, true);
        std::cout << "\n\tve[3]" << ve[3] << std::endl;
        std::cout << "\nУмножение объектов: \n";
        std::cout << "Вектор на матрицу: \n" << ve << "*\n" << ms << "\n=\n" << ve * ms << std::endl;
        sep();
        std::cout << "Матрицу на вектор: \n" << me << "*\n" << vs << "\n\=\n" << me * vs << std::endl;
        sep();
        sep();
        std::cout << "Матрицу на матрицу: \n" << me << "*\n" << ms << "\t=\n" << std::setw(10) << me * ms << std::endl;
        sep();
        std::cout << "Вектор-столбец на вектор-строку:\n" << vs << "*\n" << ve << "\n=\n" << ve * vs << std::endl;
        sep();
        std::cout << "Вектор-строку на вектор-столбец:\n" << ve << "*\n" << vs << "\n=\n" << vs * ve << std::endl;
        sep();
        system("pause");
        system("cls");
    }
    system("pause");
    system("cls");
    */
    
    /*Matrix<int>* array_matrix0 = new Matrix<int>[]
                                    { Matrix<int>({ 4,5,9,4 }, 2, 2),
                                      Matrix<int>({ 94, 6, 71, 4, 6, 7, 5, 1, 16, 5, 2, 20, 21, 22, 48 }, 3, 5),
                                      Matrix<int>({ 94,6,71 }, 1, 3),
                                      Matrix<int>({ 4,5,9,4 }, 2, 2) };
    Matrix<Matrix<int>> matrix166(2, 2, array_matrix0);
    std::cout << std::setw(5) << matrix166 << std::endl;*/
    /*

    MatrixAdd array_matrix[] = { MatrixAdd(2, 2, {4,5,9,4}), MatrixAdd(3, 5,{94,6,71,4,6,7,5,1,16,5,2,20,21,22,48}),
                                 MatrixAdd(1, 3, {94,6,71}), MatrixAdd(2, 2,{4,5,9,4})};
    Matrix<MatrixAdd> matrix16(2,2, array_matrix);
    std::cout << std::setw(5) << matrix16 << std::endl;
    system("pause");
    system("cls");


    Vector<double>* listVectors = new Vector<double>[]
                                { Vector<double>(10, rand_double),
                                  Vector<double>(7, rand_double), 
                                  Vector<double>(5, rand_double) };
    Matrix<Vector<double>> matrixTest2(3, 1, listVectors);
    std::cout << std::setw(6) << matrixTest2 << std::endl;
    system("pause");
    system("cls");


    Matrix<Vector<double>> matrixTest3(1, 3, listVectors);
    Matrix<Vector<double>> matrixTest4(matrixTest3);
    std::cout << std::setw(6) << matrixTest3 << '\n';
    std::cout << std::setw(6) << matrixTest4 << '\n';
    std::cout << std::setw(10) << matrixTest3 + matrixTest4;
    system("pause");
    system("cls");
    */
    
    std::cout << "\n\tПроверка класса Fraction:\n\t"
		<< Fraction<int>(1, 8) << " + " << Fraction<int>(7, 12) << " = " << Fraction<int>(1, 8) + Fraction<int>(7, 12) << "\n\t"
		<< Fraction<double>(1) << " - " << Fraction<double>(3, 4) << " = " << Fraction<double>(1) - Fraction<double>(3, 4) << "\n\t"
		<< Fraction<char>(25, -31) << " + " << Fraction<char>(4.2) << " = " << Fraction<char>(25, -31) + Fraction<char>(4.2) << "\n\t"
		<< Fraction<char>(25, 31) << " * " << Fraction<char>(4) << " = " << Fraction<char>(25, 31) * Fraction<char>(4) << "\n\t"
		<< Fraction<short>(17, 46) << " / " << Fraction<short>(17, -4) << " = " << Fraction<short>(17, 46) / Fraction<short>(17, -4) << "\n\t"
		<< Fraction<long>(24) << " / " << Fraction<long>(4, 5) << " = " << Fraction<long>(24) / Fraction<long>(4, 5) << "\n\t";
	
	std::cout << "\n\tПроверка класса Polynomial:\n\t";
	int array1[5] = { 0,2,0,4,5 };
	int array2[5] = { 0,2,0,-4,-5 };
	Polynomial<int> polymon1(5, array1);
	//Polynomial polymon2(5.5);
	Polynomial<int> polymon2(5, array2);
	Polynomial<int> polymon3(polymon1+ polymon2);
	std::cout << "\n\tСложение полиномов:\n\t+"
		<< std::setw(3) << polymon1 << "\n\t "
		<< std::setw(3) << polymon2 << "\n\t ============================\n\t "
		<< std::setw(3) << polymon3 << std::endl;


	int array3[4] = { 0,2,0,-4 };
	int array4[8] = { 1,2,0,4,5,0,15,0 };
	Polynomial<int> polymon4(4, array3);
	Polynomial<int> polymon5(8, array4);
	Polynomial<int> polymon6(polymon4 - polymon5);
	std::cout << "\n\tРазница полиномов:\n\t-"
		<< std::setw(3) << polymon4 << "\n\t "
		<< std::setw(3) << polymon5 << "\n\t ====================================\n\t "
		<< std::setw(3) << polymon6 << std::endl;

	int array5[2] = { 2,2 };
	int array6[2] = { 3,1 };
	Polynomial<int> polymon7(2, array5);
	Polynomial<int> polymon8(2, array6);
	Polynomial<int> polymon9(polymon7 * polymon8);
	std::cout << "\n\tПроизведение полиномов:\n\t( "
	    << polymon7 << ") * ( "
	    << polymon8 << " ) = ( "
		<< polymon9 << " )\n";

	std::cout << "\n\tДеление полиномов:\n";
	std::cout << "\n\tСлучай, когда степень делимого больше степени делителя:\n\t";
	Polynomial<int> p1({ 4,-2,-1,1 });
	Polynomial<int> p2({ 1,-3,1 });
	Polynomial<int> res_int = p1 / p2;
	Polynomial<int> res_rest = p1 % p2;
	std::cout << "делимое= " << p1 << "\t||"
			  << "делитель= " << p2 << "\n\t"
			  << "\t\t\t\t|||||||||||||||||||||||||\n\t"
			  << "остаток= " << res_rest << "\t\t\t||"
			  << "целое= " << res_int << std::endl;
	Polynomial<int> check = res_int * p2 + res_rest;
	std::cout << "\n\tПроверка\n\t:> целое * делитель + остаток = \n\t\tделимое = " << check << '\n';

	std::cout << "\n\tСлучай, когда степень делимого меньше степени делителя:\n\t";
	Polynomial<int> p3({ 1,-3,1 });
	Polynomial<int> p4({ 4,-2,-1,1 });
	Polynomial<int> res_int_less = p3 / p4;
	Polynomial<int> res_rest_less = p3 % p4;
	std::cout << "делимое= " << p3 << "\t\t||"
		<< "делитель= " << p4 << "\n\t"
		<< "\t\t\t\t||||||||||||||||||||||||||||||\n\t"
		<< "остаток= " << res_rest_less << "\t\t||"
		<< "целое= " << res_int_less << std::endl;
	Polynomial<int> check_less = res_int_less * p4 + res_rest_less;
	std::cout << "\n\tПроверка\n\t:> целое * делитель + остаток = \n\t\tделимое = " << check_less << '\n';


	std::cout << "\n\tСлучай, когда степень делимого равна степени делителя:\n\t";
	Polynomial<int> p5({ 1,-3,1 });
	Polynomial<int> p6({ 4,-2,-1 });
	Polynomial<int> res_int_equal = p5 / p6;
	Polynomial<int> res_rest_equal = p5 % p6;
	std::cout << "делимое= " << p5 << "\t\t||"
		<< "делитель= " << p6 << "\n\t"
		<< "\t\t\t\t||||||||||||||||||||||||||||||\n\t"
		<< "остаток= " << res_rest_equal << "\t\t\t||"
		<< "целое= " << res_int_equal << std::endl;
	Polynomial<int> check_equal = res_int_equal * p6 + res_rest_equal;
	std::cout << "\n\tПроверка\n\t:> целое * делитель + остаток = \n\t\tделимое = " << check_equal << '\n';
    

    
    Fraction<Polynomial<int>> polyfrac0(Polynomial<int>({ 0,2,0,-4,-5 }), Polynomial<int>({ 0,2,0,-4 }));
    Polynomial<int> p7({ 0,4,0,17,14 });
    Polynomial<int> p8({ 0,-4,0,19 });
    Fraction<Polynomial<int>> polyfrac1(p7, p8);

    std::cout << "\n\tПроверка полиномиальной дроби: \n" 
        << polymon2 << '/' << polymon4 << "\n=" << polyfrac0 << "\n\n"
        << p7 << '/' << p8 << "\n=" << polyfrac1 << "\n";
    std::cout << "\n\tСложение полиномов";
    std::cout << polyfrac0 << '+'<< polyfrac1  << " = \n" << polyfrac0 + polyfrac1;
    std::cout << "\n\tВычитание полиномов";
    std::cout << polyfrac1 << '-' << polyfrac0 << " = \n" << polyfrac1 - polyfrac0;
    std::cout << "\n\tДеление полиномов";
    std::cout << polyfrac0 << '*' << polyfrac1 << " = \n" << polyfrac0 / polyfrac1;


   /* Fraction<Polynomial<Fraction<int>>> polyfrac2(
        Polynomial<Fraction<int>>({ Fraction<int>(1,5),Fraction<int>(-4,5),Fraction<int>(7,2),Fraction<int>(81,9)}),
        Polynomial<Fraction<int>>({ Fraction<int>(21,7),Fraction<int>(2,22),Fraction<int>(4,1) }));*/

}
