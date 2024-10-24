#pragma once

#include <array>
#include "utils.h"

// class to represent vectors and points in 3d space
template<Arithmetic T>
class Vec3 final
{
public:
    Vec3() : data{0,0,0} {}
    Vec3(T _x, T _y, T _z) : data{_x, _y, _z} {}

	[[nodiscard]] T x() const { return data[0]; }
	[[nodiscard]] T y() const { return data[1]; }
	[[nodiscard]] T z() const { return data[2]; }

	[[nodiscard]] double cords_squared() const { return x() * x() + y() * y() + z() * z(); }
	[[nodiscard]] double length() const { return std::sqrt(cords_squared()); }

    [[nodiscard]] Vec3<T> operator-() const { return Vec3(-data[0], -data[1], -data[2]); }
	[[nodiscard]] T operator[](int i) const { return data[i]; }
	T& operator[](int i) { return data[i]; }

    Vec3<T>& operator+=(const Vec3<T>& other)
	{
        data[0] += other.x(); data[1] += other.y(); data[2] += other.z();
        return *this;
	}

    Vec3<T>& operator*=(const T& operand)
    {
        data[0] *= operand; data[1] *= operand; data[2] *= operand;
        return *this;
    }

    Vec3<T>& operator/=(const T& operand)
    {
        data[0] /= operand; data[1] /= operand; data[2] /= operand;
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
	std::array<T, 3> data;
};

// friends
template<Arithmetic T>
std::ostream& operator<<(std::ostream& os, const Vec3<T>& vec)
{
    os << "(" << vec.data[0] << ", " << vec.data[1] << ", " << vec.data[2] << ")";
    return os;
}

template<Arithmetic T>
Vec3<T> operator+(const Vec3<T>& lhs, const Vec3<T>& rhs)
{
    return Vec3<T>(
        lhs.data[0] + rhs.data[0],
        lhs.data[1] + rhs.data[1],
        lhs.data[2] + rhs.data[2]
    );
}

template<Arithmetic T>
Vec3<T> operator-(const Vec3<T>& lhs, const Vec3<T>& rhs)
{
    return Vec3<T>(
        lhs.data[0] - rhs.data[0],
        lhs.data[1] - rhs.data[1],
        lhs.data[2] - rhs.data[2]
    );
}

template<Arithmetic T>
Vec3<T> operator*(const Vec3<T>& lhs, const Vec3<T>& rhs)
{
    return Vec3<T>(
        lhs.data[0] * rhs.data[0],
        lhs.data[1] * rhs.data[1],
        lhs.data[2] * rhs.data[2]
    );
}

template<Arithmetic T>
Vec3<T> operator*(const Vec3<T>& lhs, const T& operand)
{
    return Vec3<T>(
        lhs.data[0] * operand,
        lhs.data[1] * operand,
        lhs.data[2] * operand
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
    return lhs.data[0] * rhs.data[0] +
        lhs.data[1] * rhs.data[1] +
        lhs.data[2] * rhs.data[2];
}

template<Arithmetic T>
Vec3<T> cross_product(const Vec3<T>& lhs, const Vec3<T>& rhs)
{
    return Vec3(
        lhs.data[1] * rhs.data[2] - lhs.data[2] * rhs.data[1],
        lhs.data[2] * rhs.data[0] - lhs.data[0] * rhs.data[2],
        lhs.data[0] * rhs.data[1] - lhs.data[1] * rhs.data[0]
    );
}

template<Arithmetic T>
Vec3<T> unit_vector(const Vec3<T>& v)
{
    return v / static_cast<T>(v.length());
}