#include <algorithm>
#include <iostream>
#include "Matrix.h"

namespace luMath
{
    template Matrix<int>;
    //template Matrix<int>::Row<int>;
    template <typename T> unsigned Matrix<T>::m_idCounter = 1;
    // Основной конструктор
    template <class T> Matrix<T>::Matrix(int rows, int cols, const T* array)
        : m_id{ m_idCounter++ }
    {
        if (rows <= 0 || cols <= 0)
            throw "Объект №", m_id, ". Размерность строк или столбцов не может быть меньше либо равным нулю";

        m_rows = rows; m_cols = cols;
        m_length = m_rows * m_cols;
        m_item = new T[m_length];
        if (!m_item) throw "\n\t\tФатальное выделение памяти для объекта №", m_id, '\n';
        for (unsigned iii = 0; iii < m_length; ++iii)
            m_item[iii] = array[iii];

        std::cout << "\n\tКонструктор создания объекта с заданными значениями. Создание объекта #" << m_id
            << ": m = " << m_rows
            << ", n = " << m_cols
            << std::endl;
    }

    template <class T> Matrix<T>::Matrix(bool random) : Matrix(5, 5, random)
    {
        std::cout << "\n\tКонструктор по умолчанию." << std::endl;
    }

    template <class T> Matrix<T>::Matrix(int rows, bool random) : Matrix(rows, rows, random)
    {
        std::cout << "\n\tКонструктора квадратной матрицы." << std::endl;
    }

    template <class T> Matrix<T>::Matrix(int rows, int cols, bool random) : m_id{ m_idCounter++ }
    {
        if (rows <= 0 || cols <= 0)
            throw std::logic_error("\n\tРазмерность строк или столбцов не может быть меньше либо равным нулю.");
        m_rows = rows; m_cols = cols;
        m_length = m_rows * m_cols;
        m_item = new T[m_length];
        if (!m_item) throw std::logic_error("\n\t\tФатальное выделение памяти для объекта №");

        if (random) for (unsigned iii = 0; iii < m_length; ++iii)
            m_item[iii] = rand() % 2;

        std::cout << "\n\tКонструктор создания объекта заданной размерности. Создание объекта #" << m_id
            << ": m = " << m_rows
            << ", n = " << m_cols
            << std::endl;
    }

    template <class T> Matrix<T>::Matrix(int size, const T* array) : Matrix(size, size, array)
    {
        std::cout << "\n\tКонструктор создания квадратой матрицы с заданными значеними";
    }

    template <class T> Matrix<T>::Matrix(int size, const std::initializer_list<T> list) : Matrix(size, size, list)
    {
        std::cout << "\n\tКонструктор создания квадратой матрицы со списком инициализации";
    }

    template <class T> Matrix<T>::Matrix(const std::initializer_list<T> list)
        : Matrix((sqrt(list.size()) - static_cast<int>(sqrt(list.size())) == 0) ? static_cast<int>(sqrt(list.size()))
            : static_cast<int>(sqrt(list.size())) + 1,
            (sqrt(list.size()) - static_cast<int>(sqrt(list.size())) == 0) ? static_cast<int>(sqrt(list.size()))
            : static_cast<int>(sqrt(list.size())) + 1,
            list)
    {
        std::cout << "\n\tКонструктор создания квадратной матрицы списком инициализации.";
    }

    template <class T> Matrix<T>::Matrix(int rows, int cols, const std::initializer_list<T> list) : Matrix(rows, cols, false)
    {
        std::cout << "\n\tКонструктор создания прямоугольной матрицы списком инициализации с переданными размерностями";
        unsigned count = 0;
        for (auto& element : list)
        {
            m_item[count] = element;
            count++;
        }
        for (; count < m_rows * m_cols; ++count)
            m_item[count] = 0;
    }

    template <class T> Matrix<T>::Matrix(int size, T(*func)(int, int)) : Matrix(size, size, func)
    {
        std::cout << "\n\tКонструктор создания квадратой матрицы функцией";
    }

    template <class T> Matrix<T>::Matrix(int rows, int cols, T(*func)(int, int)) : Matrix(rows, cols, false)
    {
        for (unsigned iii = 0; iii < m_rows; ++iii)
            for (unsigned jjj = 0; jjj < m_cols; ++jjj)
                m_item[iii * m_cols + jjj] = func(iii, jjj);
        std::cout << "\n\tКонструктор создания прямоугольной матрицы функцией";
    }

    template <class T> Matrix<T>::Matrix(const Matrix& fromMatrix)
        : Matrix(fromMatrix.m_rows, fromMatrix.m_cols, fromMatrix.m_item)
    {
        std::cout << "\n\tКонструктор глубокого копирования матрицы #" << fromMatrix.m_id << " в матрицу #" << m_id;
    }

    template <class T> Matrix<T>::Matrix(Matrix&& fromMatrix) noexcept :
        m_id{ m_idCounter++ }
    {
        std::swap(m_rows, fromMatrix.m_rows);
        std::swap(m_cols, fromMatrix.m_cols);
        std::swap(m_length, fromMatrix.m_length);
        std::swap(m_item, fromMatrix.m_item);
        std::cout << "\n\tПеремещающий конструктор матрицы #" << fromMatrix.m_id << " в матрицу #" << m_id;
    }

    template <class T> Matrix<T>::Row<T>::Row(T* row, unsigned cols) : p_row{ row }, m_cols{ cols } { }

    template <class T> Matrix<T>::~Matrix()
    {
        std::cout << "\n\tДеструктор объекта #" << m_id << std::endl;
        if (m_item != nullptr)
            delete[] m_item;
    }

    template <class T> bool canMltpl(const Matrix<T>& A, const Matrix<T>& B) { return A.m_cols == B.m_rows; }
    template <class T> bool canAdd(const Matrix<T>& A, const Matrix<T>& B) { return A.m_rows == B.m_rows && A.m_cols == B.m_cols; }

    template <class T> const Matrix<T>& Matrix<T>::transpose()
    {
        for (unsigned iii = 0; iii < m_rows; ++iii)
            for (unsigned jjj = 0; jjj < m_cols; ++jjj)
                std::swap(m_item[iii * m_cols * jjj],
                    m_item[jjj * m_cols * iii]);
        std::swap(m_cols, m_rows);
        return *this;
    }

    template <class T> double Matrix<T>::getMax(const Matrix<T>& X)
    {
        T max = X.m_item[0];
        for (unsigned iii = 0; iii < X.m_rows * X.m_cols; ++iii)
            if (max < X.m_item[iii])
                max = X.m_item[iii];
        return max;
    }
    template <class T> double Matrix<T>::getMin(const Matrix<T>& X)
    {
        T min = X.m_item[0];
        for (unsigned iii = 0; iii < X.m_rows * X.m_cols; ++iii)
            if (min > X.m_item[iii])
                min = X.m_item[iii];
        return min;
    }
    template <class T> unsigned Matrix<T>::getId(const Matrix<T>& X) { return X.m_id; }
    template <class T> unsigned Matrix<T>::getRows(const Matrix<T>& X) { return X.m_rows; }
    template <class T> unsigned Matrix<T>::getCols(const Matrix<T>& X) { return X.m_cols; }
    template <class T> Matrix<T> operator+(const Matrix<T>& A, const Matrix<T>& B) { return Matrix<T>(A) += B; }
    template <class T> Matrix<T> operator-(const Matrix<T>& A, const Matrix<T>& B) { return Matrix<T>(A) -= B; }
    template <class T> Matrix<T> operator*(const Matrix<T>& A, const Matrix<T>& B) { return Matrix<T>(A) *= B; }
    template <class T> Matrix<T> operator*(const Matrix<T>& A, T k) { return Matrix<T>(A) *= k; }

    template <class T> std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix)
    {
        int size = static_cast<int>(std::cout.width());
        if (!size) size = 10;
        out << "\n";
        for (unsigned i = 0; i < matrix.m_rows; i++)
        {
            for (unsigned j = 0; j < matrix.m_cols; j++)
                out << std::fixed << std::setprecision(2) << std::setw(size) << matrix.m_item[i * matrix.m_cols + j];
            out << "\n";
        }
        return out;
    }
    template <class T> std::istream& operator>>(std::istream& in, Matrix<T>& matrix)
    {
        for (unsigned iii = 0; iii < matrix.m_rows * matrix.m_cols; ++iii)
            in >> matrix.m_item[iii];
        return in;
    }

    template <class T> const Matrix<T>& Matrix<T>::operator=(const Matrix<T>& matrix)
    {
        if (this == &matrix)
            return *this;

        if (m_length != matrix.m_length)
        {
            m_cols = matrix.m_cols;
            m_rows = matrix.m_rows;
            delete[] m_item;
            m_length = matrix.m_length;
            m_item = new T[m_length];
        }
        else if (m_rows != matrix.m_rows || m_cols != matrix.m_cols)
        {
            m_cols = matrix.m_cols;
            m_rows = matrix.m_rows;
        }


        for (unsigned iii = 0; iii < m_length; ++iii)
            m_item[iii] = matrix.m_item[iii];
        return *this;
    }

    template <class T> const Matrix<T>& Matrix<T>::operator=(Matrix<T>&& matrix) noexcept
    {
        if (this == &matrix)
            return *this;

        std::swap(m_rows, matrix.m_rows);
        std::swap(m_cols, matrix.m_cols);
        std::swap(m_id, matrix.m_id);
        std::swap(m_length, matrix.m_length);
        std::swap(m_item, matrix.m_item);

        return *this;
    }

    template <class T> const Matrix<T>& Matrix<T>::operator=(const std::initializer_list<T> list)
    {
        if (list.size() != static_cast<size_t>(m_length))
        {
            delete[] m_item;
            m_length = static_cast<int>(list.size());
            m_rows = (sqrt(list.size()) - static_cast<int>(sqrt(list.size())) == 0) ? static_cast<int>(sqrt(list.size()))
                : static_cast<int>(sqrt(list.size())) + 1;
            m_cols = m_rows;
            m_item = new T[m_length];
        }
        unsigned count = 0;
        for (auto& element : list)
        {
            m_item[count] = element;
            count++;
        }
        for (; count < m_rows * m_cols; ++count)
            m_item[count] = 0;
        return *this;
    }

    template <typename T> const Matrix<T>& Matrix<T>::operator+=(const Matrix& matrix)
    {
        if (!canAdd(*this, matrix))
            throw std::logic_error("\nС данными матрицами операция сложения не может быть произведена.\n");

        for (unsigned iii = 0; iii < m_rows * m_cols; ++iii)
            m_item[iii] += matrix.m_item[iii];

        return *this;
    }

    template <typename T> const Matrix<T>& Matrix<T>::operator-=(const Matrix& matrix)
    {
        if (!canAdd(*this, matrix))
            throw std::logic_error("\nС данными матрицами разности сложения не может быть произведена.\n");

        for (unsigned iii = 0; iii < m_rows * m_cols; ++iii)
            m_item[iii] -= matrix.m_item[iii];

        return *this;
    }

    template <typename T> const Matrix<T>& Matrix<T>::operator*=(const Matrix& matrix)
    {
        if (!(canMltpl(*this, matrix)))
            throw std::logic_error("\nС данными объектами операция умножения не может быть произведена.\n\t");

        T temp;
        m_length = m_rows * matrix.m_cols;
        T* array = new T[m_length];
        for (unsigned iii = 0; iii < m_rows; ++iii)
            for (unsigned jjj = 0; jjj < matrix.m_cols; ++jjj)
            {
                temp = 0;
                for (unsigned kkk = 0; kkk < matrix.m_rows; ++kkk)
                    temp += m_item[iii * m_cols + kkk]
                    * matrix.m_item[kkk * matrix.m_cols + jjj];
                array[iii * matrix.m_cols + jjj] = temp;
            }
        delete[] this->m_item;
        this->m_item = array;
        m_cols = matrix.m_cols;
        return *this;
    }

    template <typename T> const Matrix<T>& Matrix<T>::operator*=(double k)
    {
        for (unsigned iii = 0; iii < m_rows * m_cols; ++iii)
            m_item[iii] *= k;
        return *this;
    }

    template <typename T> T& Matrix<T>::Row<T>::operator[](unsigned col)
    {
        if (col >= m_cols) throw std::logic_error("\n\tНомер столбца выходит за пределы матрицы\n");
        return p_row[col]; // возвращаем ссылку на col-элемент строки p_row
    }

    template <typename T> Matrix<T>::Row<T> Matrix<T>::operator[](unsigned row)
    {
        if (row >= m_rows) throw std::logic_error("\n\tНомер строки выходит за пределы матрицы\n");
        return  Row(m_item + (row * m_cols), m_cols);
    }

    template <typename T> const T& Matrix<T>::Row<T>::operator[](unsigned col) const
    {
        if (col >= m_cols) throw std::logic_error("\n\tНомер столбца выходит за пределы матрицы.\n");
        return p_row[col]; // возвращаем ссылку на col-элемент строки p_row
    }

    template <typename T> const Matrix<T>::Row<T> Matrix<T>::operator[](unsigned row) const
    {
        if (row >= m_rows) throw std::logic_error("\n\tНомер строки выходит за пределы матрицы\n");
        return  Row(m_item + (row * m_cols), m_cols);
    }
}
