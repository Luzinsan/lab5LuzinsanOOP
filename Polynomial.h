#pragma once
#include <iostream>

namespace luMath
{
	class Polynomial
	{
	private:
		static unsigned s_idCounter;
		unsigned m_id;
		unsigned m_length;
		double* m_coeff;

	public:
		explicit Polynomial(unsigned length = 0, double* coeff = nullptr)
			: m_id{ s_idCounter++ }, m_length{ length }
		{
			if (m_length < 0)
				throw  std::invalid_argument("Степень полинома отрицательна.");

			m_coeff = new double[m_length];
			if (coeff)
			{
				for (unsigned i = 0; i < m_length; i++)
					m_coeff[i] = coeff[i];
				reduce();
			}
			else for (unsigned i = 0; i < m_length; i++)
				m_coeff[i] = 0.0;
		}

		Polynomial(double number)
			: m_id{ s_idCounter++ }, m_length{ 1 }, m_coeff{ new double[m_length] }
		{ 
			m_coeff[0] = number; 
		}

		Polynomial(std::initializer_list<double> list)
			: m_id{ s_idCounter++ }
		{
			m_length = list.size();
			m_coeff = new double[m_length];
			unsigned count = 0;
			for (auto& element : list)
				m_coeff[count++] = element;
		}
		Polynomial(const Polynomial& polynomial)
			: Polynomial(polynomial.m_length, polynomial.m_coeff) 
		{	}
		Polynomial(Polynomial&& polynomial) noexcept
			: m_id{ polynomial.m_id }, m_length{ polynomial.m_length }
		{
			m_coeff = polynomial.m_coeff;
			polynomial.m_coeff = nullptr;
		}

		~Polynomial()
		{
			delete[] m_coeff;
		}

		const Polynomial& reduce()
		{

			for (int max_index = m_length-1; max_index >= 0; max_index--)
				if (m_coeff[max_index])
				{
					if (m_length != max_index+1)
					{
						m_length = max_index + 1;
						double* new_coeff = new double[m_length];
						std::swap(new_coeff, m_coeff);
						for (int j = 0; j < m_length; j++) m_coeff[j] = new_coeff[j];
						delete[] new_coeff;
					}
					break;
				}
			return *this;
		}

		const Polynomial& operator+=(const Polynomial& polynomial)
		{
			unsigned i = 0;
			if (m_length >= polynomial.m_length)
			{
				for (; i < polynomial.m_length; i++)
					m_coeff[i] += polynomial.m_coeff[i];
				reduce();
			}
			else
			{
				double* temp_array = new double[polynomial.m_length];
				for (; i < m_length; i++)
					temp_array[i] = m_coeff[i] + polynomial.m_coeff[i];
				delete[] m_coeff;
				m_length = polynomial.m_length;
				for (; i < m_length; i++)
					temp_array[i] = polynomial.m_coeff[i];
				m_coeff = temp_array;
				temp_array = nullptr;
			}
			return *this;
		}
		const Polynomial& operator-=(const Polynomial& polynomial)
		{
			unsigned i = 0;
			if (m_length >= polynomial.m_length)
			{
				for (; i < polynomial.m_length; i++)
					m_coeff[i] -= polynomial.m_coeff[i];
				reduce();
			}
			else
			{
				double* temp_array = new double[polynomial.m_length];
				for (; i < m_length; i++)
					temp_array[i] = m_coeff[i] - polynomial.m_coeff[i];
				delete[] m_coeff;
				m_length = polynomial.m_length;
				for (; i < m_length; i++)
					temp_array[i] = -polynomial.m_coeff[i];
				m_coeff = temp_array;
				temp_array = nullptr;
			}
			return *this;
		}
		const Polynomial& operator*=(const Polynomial& polynomial)
		{
			unsigned power_of_new = m_length * polynomial.m_length;
			double* new_coeff = new double[power_of_new];
			memset(new_coeff, 0, power_of_new * sizeof(double));
			for (unsigned i = 0; i < m_length; i++)
				for (unsigned j = 0; j < polynomial.m_length; j++)
					new_coeff[i + j] += m_coeff[i] * polynomial.m_coeff[j];
			m_length = power_of_new;
			delete[]  m_coeff;
			m_coeff = new_coeff;
			new_coeff = nullptr;
			return *this;
		}

		const Polynomial& operator/=(const Polynomial& polynomial)
		{
			if (!polynomial.m_coeff[polynomial.m_length - 1])
				throw std::logic_error("Деление на ноль\n");

			int new_power = getPower() - polynomial.getPower();
			if (new_power < 0) return *this = 0.0;
			double* new_coeff = new double[new_power+1];

			int i = -1, j = -1;
			for ( i = 0; i < new_power + 1; i++)
			{
				new_coeff[new_power - i] = m_coeff[m_length - i - 1] / polynomial.m_coeff[polynomial.m_length - 1];
				for ( j = 0; j < polynomial.m_length; j++)
					m_coeff[m_length - j - i - 1] -= polynomial.m_coeff[polynomial.m_length - j - 1] * new_coeff[new_power - i];
				j = 0;
			}
			m_length = new_power+1;
			delete[] m_coeff;
			m_coeff = new_coeff;
			reduce();
			return *this;
		}

		const Polynomial& operator%=(const Polynomial& polynomial)
		{
			if (!polynomial.m_coeff[polynomial.m_length-1])
				throw std::logic_error("Деление на ноль\n");

			int new_power = getPower() - polynomial.getPower();

			if (new_power < 0) return *this;
			int i=-1, j=-1;
			for (i = 0; i < new_power + 1; i++)
			{
				double element = m_coeff[m_length - 1 - i] / polynomial.m_coeff[polynomial.m_length - 1];
				for (j = 0; j < polynomial.m_length; j++)
					m_coeff[m_length - 1 - j - i] -= polynomial.m_coeff[polynomial.m_length - 1 - j] * element;
				j=0;
				
			}
			m_length = m_length - j - i;
			reduce();
			return *this;
		}

		const Polynomial& operator=(const Polynomial& polynomial)
		{
			if (this == &polynomial)
				return *this;

			if (m_length != polynomial.m_length)
			{
				delete[] m_coeff;
				m_length = polynomial.m_length;
				m_coeff = new double[m_length];
			}

			for (unsigned i = 0; i < m_length; i++)
				m_coeff[i] = polynomial.m_coeff[i];
			return *this;
		}

		const Polynomial& operator=(double number)
		{
			if (m_length != 1)
			{
				delete[] m_coeff;
				m_length = 1;
				m_coeff = new double[1];
			}

			m_coeff[0] = number;
			return *this;
		}
		const Polynomial& operator=(Polynomial&& polynomial) noexcept
		{
			if (this == &polynomial)
				return *this;
			std::swap(m_length, polynomial.m_length);
			std::swap(m_coeff, polynomial.m_coeff);
			return *this;
		}

		double operator()(double arg) const
		{
			double res = 0.0;
			for (unsigned i = 0; i < m_length; i++)
				res += m_coeff[i] * std::pow(arg, i);
			return res;
		}
		double& operator[](int index)
		{
			if (index >= static_cast<int>(m_length) || static_cast<int>(m_length) + index < 0)
				throw std::invalid_argument("Индекс члена полинома больше количества членов");
			else if (index < 0)
				index += m_length;
			return m_coeff[index];
		}
		const double& operator[](int index) const  
		{
			if (index >= static_cast<int>(m_length) || static_cast<int>(m_length) + index < 0)
				throw std::invalid_argument("Индекс члена полинома больше количества членов");
			else if (index < 0)
				index += m_length;
			return m_coeff[index];
		}

		friend std::ostream& operator<<(std::ostream& out, const Polynomial& polynomial)
		{
			std::streamsize width = out.width();

			out.width(width);

			std::cout << " ( " << polynomial.m_coeff[0];

			for (unsigned i = 1; i < polynomial.m_length; i++)
			{
				if (!polynomial.m_coeff[i])
					continue;

				out << (polynomial.m_coeff[i] > 0 ? " + " : " - ");
				out.width(width);

				if (std::abs(polynomial.m_coeff[i]) != 1)
					out << (polynomial.m_coeff[i] > 0 ? polynomial.m_coeff[i] : -polynomial.m_coeff[i]);

				if (i == 1) out << "x";
				else    	out << "x^" << i;
			}
			std::cout << " ) ";
			return out;
		}
		friend std::istream& operator>>(std::istream& in, const Polynomial& polynomial)
		{
			for (unsigned i = 0; i <= polynomial.m_length; ++i)
				in >> polynomial.m_coeff[i];
			return in;
		}

		unsigned getId() const
		{
			return m_id;
		}
		unsigned getPower() const
		{
			return m_length-1;
		}

		friend Polynomial operator*(const Polynomial& p1, const Polynomial& p2)
		{
			return Polynomial(p1) *= p2;
		}
		friend Polynomial operator/(const Polynomial& p1, const Polynomial& p2)
		{
			return Polynomial(p1) /= p2;
		}
		friend Polynomial operator%(const Polynomial& p1, const Polynomial& p2)
		{
			return Polynomial(p1) %= p2;
		}
		friend Polynomial operator+(const Polynomial& p1, const Polynomial& p2)
		{
			return Polynomial(p1) += p2;
		}
		friend Polynomial operator-(const Polynomial& p1, const Polynomial& p2)
		{
			return Polynomial(p1) -= p2;
		}
	};

	unsigned Polynomial::s_idCounter = 0;
}
