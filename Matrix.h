#pragma once
#include <iostream>
#include <iomanip>


namespace luMath
{
    
    template <class T> class Matrix
    {
    private:
        static unsigned m_idCounter;
        template <class T> class Row
        {
        private:
            T* p_row;
            unsigned m_cols;
        public:
            Row(T* row, unsigned m_cols);
            T& operator[](unsigned col);
            const T& operator[](unsigned col) const;
        };
    protected:
        unsigned m_rows, m_cols, m_id, m_length;
        T* m_item;
    public:
        friend class Vector;
        Matrix(int rows, int cols, const T* array); // Конструктор создания прямоугольной матрицы с заданными значениями - основной конструктор
        Matrix(int size, const T* array); // Конструктор создания квадратной    матрицы с заданными значениями

        Matrix(bool random = false); // Конструктор по умолчанию - создание матрицы 5x5 с рандомными значениями (если задано) (по умолчанию матрица не инициализируется)
        Matrix(int rows, bool random = false);           // Конструктор квадратной матрицы с рандомными значениями
        Matrix(int rows, int cols, bool random = false); // Конструктор прямоугольной матрицы с рандомными значениями

        Matrix(int size, const std::initializer_list<T> list);           // квадратной    матрицы с помощью списка инициализации
        Matrix(int rows, int cols, const std::initializer_list<T> list); // прямоугольной матрицы с помощью списка инициализации
        Matrix(const std::initializer_list<T> list);    // Конструктор со списком инициализации квадратной матрицы с автоматически заданным размером

        Matrix(int size, T(*func)(int, int));           // Конструктор создания квадратной матрицы с помощью функции 
        Matrix(int rows, int cols, T(*func)(int, int)); // Конструктор создания прямоугольной матрицы с помощью функции 

        Matrix(const Matrix& fromMatrix);      // Копирующий конструктор
        Matrix(Matrix&& fromMatrix) noexcept;  // Конструктор перемещения
        ~Matrix();


        // Проверка возможности перемножение матриц/векторов и сложение/вычитания матриц
        friend bool canMltpl(const Matrix& A, const Matrix& B);
        friend bool canAdd(const Matrix& A, const Matrix& B);
        // Нахождение минимального/максимального значения матрицы/вектора
        static T getMax(const Matrix& X);
        static T getMin(const Matrix& X);
        static unsigned getRows(const Matrix& X);
        static unsigned getCols(const Matrix& X);
        static unsigned getId(const Matrix& X);
        // Транспозиция матрицы/вектора
        virtual const Matrix& transpose();

        // Перегрузка бинарных операторов для матриц/векторов (сложение, вычитание, умножение матриц, умножение матрицы на скаляр)
        friend Matrix operator+(const Matrix& A, const Matrix& B);
        friend Matrix operator-(const Matrix& A, const Matrix& B);
        friend Matrix operator*(const Matrix& A, const Matrix& B);
        friend Matrix operator*(const Matrix& A, double k);
        // Перегрузка оператора вывода/ввода матрицы/вектора
        friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix);
        friend std::istream& operator>>(std::istream& in, Matrix& matrix);
        // Перегрузка оператора присваивания(копирования) 
        const Matrix& operator=(const Matrix& matrix);
        // Перегрузка оператора присваивания(перемещающего)
        const Matrix& operator=(Matrix&& matrix) noexcept;
        // Перегрузка оператора присваивания списком инициализации
        const Matrix& operator=(const std::initializer_list<double> list);
        // Перегрузка оператора суммы/разности/умножения_матриц/умножения_на_скаляр с присваиванием(копированием) 
        const Matrix& operator+=(const Matrix& matrix);
        const Matrix& operator-=(const Matrix& matrix);
        const Matrix& operator*=(const Matrix& matrix);
        const Matrix& operator*=(double k);

        // Конструктор создания временной строки
        Row operator[](unsigned row);
        const Row operator[](unsigned row) const;
    };

    
}

#include "Matrix.inl"
