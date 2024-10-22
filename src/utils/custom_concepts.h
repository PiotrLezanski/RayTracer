#pragma once
#include <concepts>

// concept that guards that type T suppors basic arithmetic operators
template<typename T>
concept Arithmetic = requires(T a, T b) {
	{ -a } -> std::same_as<T>;
	{ a + b } -> std::same_as<T>;
	{ a - b } -> std::same_as<T>;
	{ a * b } -> std::same_as<T>;
	{ a / b } -> std::same_as<T>;

	{ a += b } -> std::same_as<T&>;
	{ a *= b } -> std::same_as<T&>;
	{ a /= b } -> std::same_as<T&>;
};