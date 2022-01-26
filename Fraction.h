#pragma once
#include <iostream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include "Polynomial.h"

namespace luMath 
{
	template<class T>T nod(T a, T b)//алгоритм НОД без рекурсии
	{
		while (b)
		{
			a = (long long)a % (long long)b;
			std::swap(a, b);
		}
		return std::abs(a);
	}

	template<class T>T nok(T a, T b)
	{
		return a * b / nod(a, b);
	}


	template<class T> class Fraction
	{
	private:
		static unsigned s_idCounter;
		unsigned m_id;
		T m_numerator;
		T m_denominator;

		const Fraction& reduce()
		{
			T nod_f = nod(abs(m_numerator), abs(m_denominator));
			m_numerator /= (int)nod_f;
			m_denominator /= nod_f;
			return *this;
		}

	public:
		explicit Fraction(const T& numerator = 0, const T& denominator = 1)
			: m_id(s_idCounter++), m_numerator(numerator), m_denominator(denominator)
		{
			if (!m_denominator)
				throw std::invalid_argument("Деление на ноль. Объект №" + std::to_string(m_id) + '\n');
			if (m_denominator < 0)
			{
				m_denominator = -m_denominator;
				m_numerator = -m_numerator;
			}
			reduce();
		}

		explicit Fraction()
			: m_id(s_idCounter++), m_numerator(0), m_denominator(1)
		{
		}

		Fraction(const Fraction<T>& fraction)
			: Fraction<T>(fraction.m_numerator, fraction.m_denominator) 
		{ }

		
		static double toDecimal(const Fraction& fraction)
		{
			return static_cast<T>(fraction.m_numerator) / fraction.m_denominator;
		}

		const Fraction<T>& operator+=(const Fraction<T>& fraction)
		{
			T nok_f = nok(m_denominator, fraction.m_denominator);
			m_numerator = nok_f / m_denominator * m_numerator
						+ nok_f / fraction.m_denominator * fraction.m_numerator;
			m_denominator = nok_f;
			reduce();
			return *this;
		}

		const Fraction<T>& operator-=(const Fraction<T>& fraction)
		{
			T nok_f = nok(m_denominator, fraction.m_denominator);
			m_numerator = nok_f / m_denominator * m_numerator
						- nok_f / fraction.m_denominator * fraction.m_numerator;
			m_denominator = nok_f;
			reduce();
			return *this;
		}

		const Fraction<T>& operator*=( const Fraction<T>& fraction)
		{
			m_numerator *= fraction.m_numerator;
			m_denominator *= fraction.m_denominator;
			reduce();
			return *this;
		}

		const Fraction<T>& operator/=(const Fraction<T>& fraction)
		{
			m_numerator *= fraction.m_denominator * ((fraction.m_numerator >= 0) ? 1 : -1);
			m_denominator *= abs(fraction.m_numerator);
			reduce();
			return *this;
		}

		const Fraction<T>& operator=(const Fraction<T>& fraction)
		{
			if (this == &fraction)
				return *this;

			m_numerator = fraction.m_numerator;
			m_denominator = fraction.m_denominator;
			return *this;
		}
		  
		const Fraction<T>& operator=(Fraction<T>&& fraction)
		{
			if (this == &fraction)
				return *this;

			std::swap(m_numerator, fraction.m_numerator);
			std::swap(m_denominator, fraction.m_denominator);
			return *this;
		}

		const Fraction<T>& operator=(int number)
		{
			m_numerator = number;
			m_numerator = 1;
			return *this;
		}

		bool is_correct() const
		{
			return std::abs(m_numerator) <= m_denominator;
		}

		std::string to_correct_fraction_string() const
		{
			std::string ss;
			if (is_correct()) return ss = to_incorrect_fraction_string();

			if (m_denominator != 1)
			{
				if (m_numerator < 0) // сложная отрицательная дробь
					ss += '-' + std::to_string(-m_numerator / m_denominator) + '.' + std::to_string((int)- m_numerator % (int)m_denominator);
				else ss += std::to_string(m_numerator / m_denominator) + '.' + std::to_string((int)m_numerator % (int)m_denominator);
				ss += '/' + std::to_string(m_denominator);
			}
			else ss += std::to_string(m_numerator);
			return ss;
		}

		std::string to_incorrect_fraction_string() const
		{
			std::string ss = std::to_string(m_numerator);
			if (m_denominator != 1) ss += '/' + std::to_string(m_denominator);
			return ss;
		}

		friend std::ostream& operator<<(std::ostream& out, const Fraction<T>& fraction)
		{
			return out << fraction.to_correct_fraction_string();
		}


		friend Fraction<T> operator+(const Fraction<T>& f1, const Fraction<T>& f2)
		{
			return Fraction<T>(f1) += f2;
		}
		friend Fraction<T> operator-(const Fraction<T>& f1, const Fraction<T>& f2)
		{
			return Fraction<T>(f1) -= f2;
		}
		friend Fraction<T> operator*(const Fraction<T>& f1, const Fraction<T>& f2)
		{
			return Fraction<T>(f1) *= f2;
		}
		friend Fraction<T> operator/(const Fraction<T>& f1, const Fraction<T>& f2)
		{
			return Fraction<T>(f1) /= f2;
		}

		
		const T& getNumerator() const
		{
			return m_numerator;
		}
		const T& getDenominator() const
		{
			return m_denominator;
		}
		unsigned getID() const
		{
			return m_id;
		}
	};

	template <class T> unsigned Fraction<T>::s_idCounter = 1;

	template <class T> 
	Polynomial<T> nod(const Polynomial<T>& A, const Polynomial<T>& B)
	{
		Polynomial<T> X(A), Y(B);
		if (A.getPower() < B.getPower()) std::swap(X, Y);
		
		Polynomial<T> Z = X % Y;
		while (Z.getPower() > 0 && Z[Z.getPower()])
		{
			std::cout << Z;

			X = Y;
			Y = Z;
			Z = X % Y;
			if (Z.getPower() == 1)
				if (( Z[0] * -1) / Z[1] == 0) break;
			
		}
		return Y;
	}
	template <class T>
	Polynomial<T> nok(Polynomial<T> X, Polynomial<T> Y)
	{
		return X * Y / nod(X, Y);
	}

	
	template<class T> class Fraction<Polynomial<T>>
	{
	private:
		static unsigned s_idCounter;
		unsigned m_id;
		Polynomial<T> m_numerator;
		Polynomial<T> m_denominator;

		const Fraction& reduce()
		{
			Polynomial<T> nod_f = nod(m_numerator, m_denominator);
			m_numerator /= nod_f;
			m_denominator /= nod_f;
			return *this;
		}

	public:
		explicit Fraction()
			: m_id(s_idCounter++), m_numerator({ 0.0 }), m_denominator({ 1.0 })
		{
		}

		explicit Fraction(const Polynomial<T>& numerator)
			: m_id(s_idCounter++), m_numerator(numerator), m_denominator({ 1.0 })
		{
		}

		explicit Fraction(const Polynomial<T>& numerator, const Polynomial<T>& denominator)
			: m_id(s_idCounter++), m_numerator(numerator), m_denominator()
		{
			if (denominator.getPower() == 0 )
				throw std::invalid_argument("Деление на нулевой полином. Объект №" + std::to_string(m_id) + '\n');

			m_denominator = denominator;
			reduce();
		}

		Fraction(const Fraction<Polynomial<T>>& fraction)
			: Fraction<Polynomial<T>>(fraction.m_numerator, fraction.m_denominator)
		{ }

		const Fraction<Polynomial<T>>& operator+=(const Fraction<Polynomial<T>>& fraction)
		{
			Polynomial<T> nok_f = nok(m_denominator, fraction.m_denominator);
			m_numerator      = nok_f / m_denominator * m_numerator
							 + nok_f / fraction.m_denominator * fraction.m_numerator;
			m_denominator    = nok_f;
			reduce();
			return *this;
		}
		const Fraction<Polynomial<T>>& operator+=(const Polynomial<T>& polynom)
		{
			m_numerator += polynom * m_denominator;
			reduce();
			return *this;
		}

		const Fraction<Polynomial<T>>& operator-=(const Fraction<Polynomial<T>>& fraction)
		{
			Polynomial<T> nok_f = nok(m_denominator, fraction.m_denominator);
			m_numerator      = nok_f / m_denominator * m_numerator
						     - nok_f / fraction.m_denominator * fraction.m_numerator;
			m_denominator = nok_f;
			reduce();
			return *this;
		}
		const Fraction<Polynomial<T>>& operator-=(const Polynomial<T>& polynom)
		{
			m_numerator -= polynom * m_denominator;
			reduce();
			return *this;
		}
		const Fraction<Polynomial<T>>& operator*=(const Fraction<Polynomial<T>>& fraction)
		{
			m_numerator *= fraction.m_numerator;
			m_denominator *= fraction.m_denominator;
			reduce();
			return *this;
		}
		const Fraction<Polynomial<T>>& operator*=(const Polynomial<T>& polynom)
		{
			m_numerator *= polynom;
			reduce();
			return *this;
		}
		const Fraction<Polynomial<T>>& operator/=(const Fraction<Polynomial<T>>& fraction)
		{
			m_numerator *= fraction.m_denominator;
			m_denominator *= fraction.m_numerator;
			reduce();
			return *this;
		}
		const Fraction<Polynomial<T>>& operator/=(const Polynomial<T>& polynom)
		{
			m_denominator *= polynom;
			reduce();
			return *this;
		}
		const Fraction<Polynomial<T>>& operator=(const Fraction<Polynomial<T>>& fraction)
		{
			if (this == &fraction)
				return *this;

			m_numerator = fraction.m_numerator;
			m_denominator = fraction.m_denominator;
			return *this;
		}
		const Fraction<Polynomial<T>>& operator=(const Polynomial<T>& polynom)
		{
			m_numerator = polynom;
			m_denominator = Polynomial<T>({ 1.0 });
			return *this;
		}
		const Fraction<Polynomial<T>>& operator=(Fraction<Polynomial<T>>&& fraction)
		{
			if (this == &fraction)
				return *this;

			std::swap(m_numerator, fraction.m_numerator);
			std::swap(m_denominator, fraction.m_denominator);
			return *this;
		}

		bool is_correct() const
		{
			return m_numerator.getPower() < m_denominator.getPower();
		}
		friend std::ostream& operator<<(std::ostream& out, const Fraction<Polynomial<T>>& fraction)
		{
			std::streamsize width = out.width(), precision = out.precision();
			out  << std::setw(width) << std::setprecision(precision) << fraction.m_numerator
		  << "/" << std::setw(width) << std::setprecision(precision) << fraction.m_denominator;
			return out;
		}
		void out_incorrect_fraction_polynom() const
		{
			std::streamsize width = std::cout.width(), precision = std::cout.precision();
			std::cout << std::setw(width) << std::setprecision(precision) << m_numerator / m_denominator 
					  << ". " << std::setw(width) << std::setprecision(precision) << m_numerator % m_denominator
					  << "/" << std::setw(width) << std::setprecision(precision) << m_denominator;
		}
		friend Fraction<Polynomial<T>> operator+(const Fraction<Polynomial<T>>& f1, const Fraction<Polynomial<T>>& f2)
		{
			return Fraction<Polynomial<T>>(f1) += f2;
		}
		friend Fraction<Polynomial<T>> operator-(const Fraction<Polynomial<T>>& f1, const Fraction<Polynomial<T>>& f2)
		{
			return Fraction<Polynomial<T>>(f1) -= f2;
		}
		friend Fraction<Polynomial<T>> operator*(const Fraction<Polynomial<T>>& f1, const Fraction<Polynomial<T>>& f2)
		{
			return Fraction<Polynomial<T>>(f1) *= f2;
		}
		friend Fraction<Polynomial<T>> operator/(const Fraction<Polynomial<T>>& f1, const Fraction<Polynomial<T>>& f2)
		{
			return Fraction<Polynomial<T>>(f1) /= f2;
		}
		
		friend bool operator==(const Fraction<T>& f1, int x)
		{
			return f1.getNumerator == x;
		}

		const Polynomial<T>& getNumerator() const
		{
			return m_numerator;
		}
		const Polynomial<T>& getDenominator() const
		{
			return m_denominator;
		}
		unsigned getID() const
		{
			return m_id;
		}
	};

	 template<class T> unsigned Fraction<Polynomial<T>>::s_idCounter = 1;
}
