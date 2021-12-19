#pragma once
#include <iostream>
#include <iomanip>


namespace luMath
{
    
    template <class T> class Matrix
    {
    private:
        static unsigned m_idCounter;
        class Row
        {
        private:
            T* p_row;
            unsigned m_cols;
        public:
            Row(T* row, unsigned cols) : p_row{ row }, m_cols{ cols } { }
            T& operator[](unsigned col)
            {
                if (col >= m_cols) throw std::logic_error("\n\tНомер столбца выходит за пределы матрицы\n");
                return p_row[col]; // возвращаем ссылку на col-элемент строки p_row
            }
            const T& operator[](unsigned col) const
            {
                if (col >= m_cols) throw std::logic_error("\n\tНомер столбца выходит за пределы матрицы.\n");
                return p_row[col]; // возвращаем ссылку на col-элемент строки p_row
            }
        };
    protected:
        unsigned m_rows, m_cols, m_id, m_length;
        T* m_item;
    public:
        
        Matrix(int rows, int cols, const T* array) // Конструктор создания прямоугольной матрицы с заданными значениями - основной конструктор
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
        Matrix(int size, const T* array) // Конструктор создания квадратной    матрицы с заданными значениями
            : Matrix(size, size, array)
        {
            std::cout << "\n\tКонструктор создания квадратой матрицы с заданными значеними";
        }

        Matrix(bool random = false) // Конструктор по умолчанию - создание матрицы 5x5 с рандомными значениями (если задано) (по умолчанию матрица не инициализируется)
            : Matrix(5, 5, random)
        {
            std::cout << "\n\tКонструктор по умолчанию." << std::endl;
        }
        Matrix(int rows, bool random = false)           // Конструктор квадратной матрицы с рандомными значениями
            : Matrix(rows, rows, random)
        {
            std::cout << "\n\tКонструктора квадратной матрицы." << std::endl;
        }
        Matrix(int rows, int cols, bool random = false) // Конструктор прямоугольной матрицы с рандомными значениями
            : m_id{ m_idCounter++ }
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

        Matrix(int size, const std::initializer_list<T> list)           // квадратной    матрицы с помощью списка инициализации
            : Matrix(size, size, list)
        {
            std::cout << "\n\tКонструктор создания квадратой матрицы со списком инициализации";
        }
        Matrix(int rows, int cols, const std::initializer_list<T> list) // прямоугольной матрицы с помощью списка инициализации
            : Matrix(rows, cols, false)
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
        Matrix(const std::initializer_list<T> list)    // Конструктор со списком инициализации квадратной матрицы с автоматически заданным размером
            : Matrix((sqrt(list.size()) - static_cast<int>(sqrt(list.size())) == 0) ? static_cast<int>(sqrt(list.size()))
                : static_cast<int>(sqrt(list.size())) + 1,
                (sqrt(list.size()) - static_cast<int>(sqrt(list.size())) == 0) ? static_cast<int>(sqrt(list.size()))
                : static_cast<int>(sqrt(list.size())) + 1,
                list)
        {
            std::cout << "\n\tКонструктор создания квадратной матрицы списком инициализации.";
        }

        Matrix(int size, T(*func)(int, int))           // Конструктор создания квадратной матрицы с помощью функции 
            : Matrix(size, size, func)
        {
            std::cout << "\n\tКонструктор создания квадратой матрицы функцией";
        }
        Matrix(int rows, int cols, T(*func)(int, int)) // Конструктор создания прямоугольной матрицы с помощью функции 
            : Matrix(rows, cols, false)
        {
            for (unsigned iii = 0; iii < m_rows; ++iii)
                for (unsigned jjj = 0; jjj < m_cols; ++jjj)
                    m_item[iii * m_cols + jjj] = func(iii, jjj);
            std::cout << "\n\tКонструктор создания прямоугольной матрицы функцией";
        }

        Matrix(const Matrix& fromMatrix)      // Копирующий конструктор
            : Matrix(fromMatrix.m_rows, fromMatrix.m_cols, fromMatrix.m_item)
        {
            std::cout << "\n\tКонструктор глубокого копирования матрицы #" << fromMatrix.m_id << " в матрицу #" << m_id;
        }
        Matrix(Matrix&& fromMatrix) noexcept  // Конструктор перемещения
            : m_id{ m_idCounter++ }
        {
            std::swap(m_rows, fromMatrix.m_rows);
            std::swap(m_cols, fromMatrix.m_cols);
            std::swap(m_length, fromMatrix.m_length);
            std::swap(m_item, fromMatrix.m_item);
            std::cout << "\n\tПеремещающий конструктор матрицы #" << fromMatrix.m_id << " в матрицу #" << m_id;
        }
        ~Matrix() 
        {
            std::cout << "\n\tДеструктор объекта #" << m_id << std::endl;
            if (m_item != nullptr)
                delete[] m_item;
        }


        // Проверка возможности перемножение матриц/векторов и сложение/вычитания матриц
        friend bool canMltpl(const Matrix& A, const Matrix& B) { return A.m_cols == B.m_rows; }
        friend bool canAdd(const Matrix& A, const Matrix& B) { return A.m_rows == B.m_rows && A.m_cols == B.m_cols; }
        // Нахождение минимального/максимального значения матрицы/вектора
        T getMax() 
        {
            T max = m_item[0];
            for (unsigned iii = 0; iii < m_rows * m_cols; ++iii)
                if (max < m_item[iii])
                    max = m_item[iii];
            return max;
        }
        T getMin()
        {
            T min = m_item[0];
            for (unsigned iii = 0; iii < m_rows * m_cols; ++iii)
                if (min > m_item[iii])
                    min = m_item[iii];
            return min;
        }
        unsigned getRows() { return m_rows; }
        unsigned getCols() { return m_cols; }
        unsigned getId() { return m_id; }
        // Транспозиция матрицы/вектора
        virtual const Matrix& transpose() 
        {
            for (unsigned iii = 0; iii < m_rows; ++iii)
                for (unsigned jjj = 0; jjj < m_cols; ++jjj)
                    std::swap(m_item[iii * m_cols * jjj],
                        m_item[jjj * m_cols * iii]);
            std::swap(m_cols, m_rows);
            return *this;
        }

        // Перегрузка бинарных операторов для матриц/векторов (сложение, вычитание, умножение матриц, умножение матрицы на скаляр)
        friend Matrix operator+(const Matrix& A, const Matrix& B) { return Matrix<T>(A) += B; }
        friend Matrix operator-(const Matrix& A, const Matrix& B) { return Matrix<T>(A) -= B; }
        friend Matrix operator*(const Matrix& A, const Matrix& B) { return Matrix<T>(A) *= B; }
        friend Matrix operator*(const Matrix& A, const T& k)      { return Matrix<T>(A) *= k; }
        // Перегрузка оператора вывода/ввода матрицы/вектора
        friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix)
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
        friend std::istream& operator>>(std::istream& in, Matrix& matrix)
        {
            for (unsigned iii = 0; iii < matrix.m_rows * matrix.m_cols; ++iii)
                in >> matrix.m_item[iii];
            return in;
        }
        // Перегрузка оператора присваивания(копирования) 
        const Matrix& operator=(const Matrix& matrix)
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
        // Перегрузка оператора присваивания(перемещающего)
        const Matrix& operator=(Matrix&& matrix) noexcept
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
        // Перегрузка оператора присваивания списком инициализации
        const Matrix& operator=(const std::initializer_list<T> list)
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
        // Перегрузка оператора суммы/разности/умножения_матриц/умножения_на_скаляр с присваиванием(копированием) 
        const Matrix& operator+=(const Matrix& matrix)
        {
            if (!canAdd(*this, matrix))
                throw std::logic_error("\nС данными матрицами операция сложения не может быть произведена.\n");

            for (unsigned iii = 0; iii < m_rows * m_cols; ++iii)
                m_item[iii] += matrix.m_item[iii];

            return *this;
        }
        const Matrix& operator-=(const Matrix& matrix)
        {
            if (!canAdd(*this, matrix))
                throw std::logic_error("\nС данными матрицами разности сложения не может быть произведена.\n");

            for (unsigned iii = 0; iii < m_rows * m_cols; ++iii)
                m_item[iii] -= matrix.m_item[iii];

            return *this;
        }
        const Matrix& operator*=(const Matrix& matrix)
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
        const Matrix& operator*=(const T& k)
        {
            for (unsigned iii = 0; iii < m_rows * m_cols; ++iii)
                m_item[iii] *= k;
            return *this;
        }

        // Конструктор создания временной строки
        Row operator[](unsigned row)
        {
            if (row >= m_rows) throw std::logic_error("\n\tНомер строки выходит за пределы матрицы\n");
            return  Row(m_item + (row * m_cols), m_cols);
        }
        const Row operator[](unsigned row) const
        {
            if (row >= m_rows) throw std::logic_error("\n\tНомер строки выходит за пределы матрицы\n");
            return  Row(m_item + (row * m_cols), m_cols);
        }
    };
    template <class T> unsigned Matrix<T>::m_idCounter = 1;
    /*
    template <class T> class Vector 
        : public Matrix<T>
    {
    public:

        Vector(bool random) : Matrix<T>(1, 3, random)
        {
            std::cout << "\n\tКонструктор создания вектора без параметров";
        }

        Vector(int length, bool _transpose, bool random) : Matrix<T>(1, length, random)
        {
            if (_transpose)//если true - то вектор столбец
                transpose();
            std::cout << "\n\tКонструктор создания вектора заданной длины";
        }

        Vector(int length, const T* array, bool transpose_vec) : Matrix<T>(1, length, array)
        {
            if (transpose_vec) transpose();
            std::cout << "\n\tКонструктор создания вектора с заданными массивом значений";
        }

        Vector(const std::initializer_list<T> list) : Matrix<T>(1, static_cast<int>(list.size()), list)
        {
            std::cout << "\n\tКонструктор создания вектора списком инициализации";
        }

        Vector(int size, double(*func)(int, int)) : Matrix<T>::Matrix(1, size, func)
        {
            std::cout << "\n\tКонструктор создания вектора функцией";
        }


        Vector(const Vector<T>& fromVector)
            : Matrix<T>::Matrix(1, fromVector.m_length, fromVector.m_item)
        {
            if (!m_item) throw std::logic_error("\nПамять не была выделена! Объект НЕ создан\n");
            if (!fromVector.isString()) transpose();

            std::cout << "\n\tКонструктор глубокого копирования. Копируется вектор #" << fromVector.m_id
                << " в вектор #" << m_id << std::endl;
        }

        Vector(Vector<T>&& fromVector) noexcept
            : Matrix<T>::Matrix(1, fromVector.m_length, fromVector.m_item)
        {
            if (!fromVector.isString()) transpose();
            fromVector.m_item = nullptr;
            std::cout << "\n\tПеремещающий конструктор. Копируется вектор #" << fromVector.m_id
                << " в вектор #" << m_id << std::endl;
        }


        Vector(const Matrix<T>& fromMatrix) : Matrix<T>::Matrix(fromMatrix)
        {
            if (m_rows == 1 || m_cols == 1)
                return;
            else
                throw std::logic_error("\n\tМатрица не может быть преобразована в вектор");
            std::cout << "\n\tКонструктор глубокого копирования. Копируется матрица #" << fromMatrix.m_id
                << " в вектор #" << m_id << std::endl;
        }

        Vector(Matrix<T>&& fromMatrix) noexcept
            : Matrix<T>::Matrix(fromMatrix)
        {
            if (m_rows == 1 || m_cols == 1)
                return;
            else throw std::logic_error("\n\tМатрица не может быть преобразована в вектор");
            std::cout << "\n\tПеремещающий конструктор. Копируется матрица #" << fromMatrix.m_id
                << " в вектор #" << m_id << std::endl;
        }

        const Vector<T>& operator=(const Matrix<T>& matrix)
        {
            if (matrix.m_rows == 1 || matrix.m_cols == 1)
            {
                for (unsigned iii = 0; iii < matrix.m_length; ++iii)
                    m_item[iii] = matrix.m_item[iii];
                return *this;
            }
            else throw std::logic_error("\n\tМатрица не может быть преобразована в вектор");
        }

        const Vector<T>& operator=(Matrix<T>&& matrix) noexcept
        {
            if (matrix.m_rows == 1 || matrix.m_cols == 1)
            {
                std::swap(m_cols, matrix.m_cols);
                std::swap(m_rows, matrix.m_rows);
                std::swap(m_id, matrix.m_id);
                std::swap(m_item, matrix.m_item);
                return *this;
            }
            else  throw std::logic_error("\n\tМатрица не может быть преобразована в вектор");
        }


        unsigned getLength() const { return m_length; };

        double module() const
        {
            double _module = 0;
            for (unsigned iii = 0; iii < m_length; ++iii)
                _module += m_item[iii] * m_item[iii];
            _module = sqrt(_module);
            return _module;
        }

        const Vector<T>& normVec()
        {
            double _module = module();
            for (unsigned iii = 0; iii < m_length; ++iii)
                m_item[iii] /= _module;
            return *this;
        }

        const Matrix<T>& transpose()
        {
            std::swap(m_rows, m_cols);
            return *this;
        }

        bool isString() const { return m_rows == 1; }

        const double& operator[](int index) const
        {
            if (index >= m_length) throw std::logic_error("\n\tИндекс элемента выходит за пределы размерности константного вектора.\n");
            return m_item[index];
        }
        double& operator[](int index)
        {
            if (index >= m_length) throw std::logic_error("\n\tИндекс элемента выходит за пределы размерности вектора.\n");
            return m_item[index];
        }
    };
    */
}
