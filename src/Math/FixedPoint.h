#ifndef _FIXED_POINT_H
#define _FIXED_POINT_H

#include <cmath>

#ifdef FP_DUMP
#include <iostream>
#endif

template <int64_t FracDigits>
class FPNumber
{
public:
	FPNumber()
	{
		_value = 0;
	}

	FPNumber(int64_t value)
	{
		_value = value << FracDigits;
	}

	FPNumber(double value)
	{
		_value = value * pow(2, FracDigits);
	}

	operator int64_t() const
	{
		return _value >> FracDigits;
	}

	operator double() const
	{
		return double(_value) / pow(2, FracDigits);
	}

	FPNumber operator+(const FPNumber& number) const
	{
		FPNumber rval;
		rval._value = _value + number._value;
		return rval;
	}

	FPNumber operator*(const FPNumber& number) const
	{
		FPNumber rval;

		asm (
			"\tmov %1, %%rax\n"
			"\timulq %2\n"
			"\tshr %3, %%rax\n"
			"\tshl %4, %%rdx\n"
			"\tor %%rdx, %%rax\n"
			"\tmov %%rax, %0\n"
			: "=r" (rval._value)
			: "r" (_value), "r" (number._value),
			"i" (FracDigits), "i" (64 - FracDigits)
			: "rax", "rdx"
		);

		return rval;
	}

	FPNumber operator/(const FPNumber& number) const
	{
		FPNumber rval;

		asm (
			"\tmov %1, %%rax\n"
			"\tmov %%rax, %%rdx\n"
			"\tshl %3, %%rax\n"
			"\tsar %4, %%rdx\n"
			"\tidivq %2\n"
			"\tmov %%rax, %0\n"
			: "=r" (rval._value)
			: "r" (_value), "r" (number._value),
			"i" (FracDigits), "i" (64 - FracDigits)
			: "rax", "rdx"
		);

		return rval;
	}

#ifdef FP_DUMP
	void Dump() const
	{
		uint64_t mask = 0x8000000000000000;

		for (int i = 0; i < 64; i++) {
			if (_value & mask) {
				std::cout << '1';
			} else {
				std::cout << '0';
			}
			
			if (i == 64 - FracDigits - 1) {
				std::cout << '.';
			}

			mask >>= 1;
		}

		std::cout << std::endl;
	}
#endif

private:
	int64_t _value;
};

typedef FPNumber<30> FixedNumber;

#endif
