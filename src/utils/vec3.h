#pragma once
#include <iostream>
#include <array>

#include "custom_concepts.h"

// class to represent vectors and points in 3d space
template<Arithmetic T = double>
class Vec3 final
{
public:
    Vec3() : m_data{0,0,0} {}
    Vec3(T _x, T _y, T _z) : m_data{_x, _y, _z} {}

	[[nodiscard]] T x() const { return m_data[0]; }
	[[nodiscard]] T y() const { return m_data[1]; }
	[[nodiscard]] T z() const { return m_data[2]; }

	[[nodiscard]] double cords_squared() const { return x() * x() + y() * y() + z() * z(); }
	[[nodiscard]] double length() const { return std::sqrt(cords_squared()); }
    [[nodiscard]] bool isCloseToZero() const;

    [[nodiscard]] Vec3<T> operator-() const { return Vec3(-m_data[0], -m_data[1], -m_data[2]); }
	[[nodiscard]] T operator[](int i) const { return m_data[i]; }
	T& operator[](int i) { return m_data[i]; }

    Vec3<T>& operator+=(const Vec3<T>& other)
	{
        m_data[0] += other.x(); m_data[1] += other.y(); m_data[2] += other.z();
        return *this;
	}

    Vec3<T>& operator*=(const T& operand)
    {
        m_data[0] *= operand; m_data[1] *= operand; m_data[2] *= operand;
        return *this;
    }

    Vec3<T>& operator/=(const T& operand)
    {
        m_data[0] /= operand; m_data[1] /= operand; m_data[2] /= operand;
        return *this;
    }

    template<Arithmetic T>
	friend std::ostream& operator<<(std::ostream& os, const Vec3<T>& vec);

    template<Arithmetic T>
	friend Vec3<T> operator+(const Vec3<T>&, const Vec3<T>&);

    template<Arithmetic T>
	friend Vec3<T> operator-(const Vec3<T>&, const Vec3<T>&);

    template<Arithmetic T>
	friend Vec3<T> operator*(const Vec3<T>&, const Vec3<T>&);

    template<Arithmetic T>
	friend Vec3<T> operator*(const Vec3<T>&, const T&);

    template<Arithmetic T>
	friend Vec3<T> operator*(const T&, const Vec3<T>&);

    template<Arithmetic T>
	friend Vec3<T> operator/(const Vec3<T>&, const T&);

    template<Arithmetic T>
	friend T dot_product(const Vec3<T>&, const Vec3<T>&);

    template<Arithmetic T>
	friend Vec3<T> cross_product(const Vec3<T>&, const Vec3<T>&);

    template<Arithmetic T>
	friend Vec3<T> unit_vector(const Vec3<T>&);
private:
	std::array<T, 3> m_data;
};

template<Arithmetic T>
inline bool Vec3<T>::isCloseToZero() const
{
    const double prec = 1e-8;
    return (std::fabs(m_data[0]) < prec) && (std::fabs(m_data[1]) < prec) && (std::fabs(m_data[2] < prec));
}

// friends
template<Arithmetic T>
std::ostream& operator<<(std::ostream& os, const Vec3<T>& vec)
{
    os << "(" << vec.m_data[0] << ", " << vec.m_data[1] << ", " << vec.m_data[2] << ")";
    return os;
}

template<Arithmetic T>
Vec3<T> operator+(const Vec3<T>& lhs, const Vec3<T>& rhs)
{
    return Vec3<T>(
        lhs.m_data[0] + rhs.m_data[0],
        lhs.m_data[1] + rhs.m_data[1],
        lhs.m_data[2] + rhs.m_data[2]
    );
}

template<Arithmetic T>
Vec3<T> operator-(const Vec3<T>& lhs, const Vec3<T>& rhs)
{
    return Vec3<T>(
        lhs.m_data[0] - rhs.m_data[0],
        lhs.m_data[1] - rhs.m_data[1],
        lhs.m_data[2] - rhs.m_data[2]
    );
}

template<Arithmetic T>
Vec3<T> operator*(const Vec3<T>& lhs, const Vec3<T>& rhs)
{
    return Vec3<T>(
        lhs.m_data[0] * rhs.m_data[0],
        lhs.m_data[1] * rhs.m_data[1],
        lhs.m_data[2] * rhs.m_data[2]
    );
}

template<Arithmetic T>
Vec3<T> operator*(const Vec3<T>& lhs, const T& operand)
{
    return Vec3<T>(
        lhs.m_data[0] * operand,
        lhs.m_data[1] * operand,
        lhs.m_data[2] * operand
    );
}

template<Arithmetic T>
Vec3<T> operator*(const T& operand, const Vec3<T>& rhs)
{
    return rhs * operand;
}

template<Arithmetic T>
Vec3<T> operator/(const Vec3<T>& v, const T& operand)
{
    return (1 / operand) * v;
}

template<Arithmetic T>
T dot_product(const Vec3<T>& lhs, const Vec3<T>& rhs)
{
    return lhs.m_data[0] * rhs.m_data[0] +
        lhs.m_data[1] * rhs.m_data[1] +
        lhs.m_data[2] * rhs.m_data[2];
}

template<Arithmetic T>
Vec3<T> cross_product(const Vec3<T>& lhs, const Vec3<T>& rhs)
{
    return Vec3(
        lhs.m_data[1] * rhs.m_data[2] - lhs.m_data[2] * rhs.m_data[1],
        lhs.m_data[2] * rhs.m_data[0] - lhs.m_data[0] * rhs.m_data[2],
        lhs.m_data[0] * rhs.m_data[1] - lhs.m_data[1] * rhs.m_data[0]
    );
}

template<Arithmetic T>
Vec3<T> unit_vector(const Vec3<T>& v)
{
    return v / static_cast<T>(v.length());
}