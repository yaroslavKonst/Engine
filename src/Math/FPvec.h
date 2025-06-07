#ifndef _FPVEC_TEMPLATE_H
#define _FPVEC_TEMPLATE_H

#include <initializer_list>
#include <cstring>
#include <cmath>

#include "FixedPoint.h"

namespace Math
{
	template<int Dim>
	struct FPVec
	{
		FPNumber Data[Dim];

		FPVec()
		{ }

		FPVec(FPNumber* values)
		{
			for (int i = 0; i < Dim; ++i) {
				Data[i] = values[i];
			}
		}

		FPVec(FPNumber value)
		{
			for (int i = 0; i < Dim; ++i) {
				Data[i] = value;
			}
		}

		FPVec(const FPVec<Dim - 1>& vec, FPNumber value)
		{
			memcpy(Data, vec.Data, sizeof(FPNumber) * (Dim - 1));
			Data[Dim - 1] = value;
		}

		template<int N>
		FPVec(const FPVec<N>& vec)
		{
			if (N < Dim) {
				memcpy(Data, vec.Data, sizeof(vec.Data));
			} else {
				memcpy(Data, vec.Data, sizeof(Data));
			}
		}

		FPVec(std::initializer_list<FPNumber> l)
		{
			int i = 0;

			for (FPNumber v : l) {
				Data[i] = v;
				++i;
			}
		}

		FPNumber& operator[](int index)
		{
			return Data[index];
		}

		FPNumber operator[](int index) const
		{
			return Data[index];
		}

		template<int N>
		FPVec& operator=(const FPVec<N>& vec)
		{
			if (N < Dim) {
				memcpy(Data, vec.Data, sizeof(vec.Data));
			} else {
				memcpy(Data, vec.Data, sizeof(Data));
			}

			return *this;
		}

		FPVec& operator=(FPNumber* values)
		{
			for (int i = 0; i < Dim; ++i) {
				Data[i] = values[i];
			}

			return *this;
		}

		FPVec& operator=(FPNumber value)
		{
			for (int i = 0; i < Dim; ++i) {
				Data[i] = value;
			}

			return *this;
		}

		FPVec operator+(const FPVec& vec) const
		{
			FPVec res;

			for (int i = 0; i < Dim; ++i) {
				res.Data[i] = Data[i] + vec.Data[i];
			}

			return res;
		}

		FPVec operator-(const FPVec& vec) const
		{
			FPVec res;

			for (int i = 0; i < Dim; ++i) {
				res.Data[i] = Data[i] - vec.Data[i];
			}

			return res;
		}

		FPVec operator-() const
		{
			FPVec res;

			for (int i = 0; i < Dim; ++i) {
				res.Data[i] = -Data[i];
			}

			return res;
		}

		void operator+=(const FPVec& vec)
		{
			for (int i = 0; i < Dim; ++i) {
				Data[i] += vec.Data[i];
			}
		}

		void operator-=(const FPVec& vec)
		{
			for (int i = 0; i < Dim; ++i) {
				Data[i] -= vec.Data[i];
			}
		}

		FPVec operator*(FPNumber value) const
		{
			FPVec res;

			for (int i = 0; i < Dim; ++i) {
				res.Data[i] = Data[i] * value;
			}

			return res;
		}

		FPVec operator/(FPNumber value) const
		{
			FPVec res;

			for (int i = 0; i < Dim; ++i) {
				res.Data[i] = Data[i] / value;
			}

			return res;
		}

		void operator*=(FPNumber value)
		{
			for (int i = 0; i < Dim; ++i) {
				Data[i] *= value;
			}
		}

		void operator/=(FPNumber value)
		{
			for (int i = 0; i < Dim; ++i) {
				Data[i] /= value;
			}
		}

		FPNumber Length() const
		{
			FPNumber sum = 0;

			for (int i = 0; i < Dim; ++i) {
				sum += pow(Data[i], 2);
			}

			return sqrt(sum);
		}

		FPNumber Dot(const FPVec& vec) const
		{
			FPNumber sum = 0;

			for (int i = 0; i < Dim; ++i) {
				sum += Data[i] * vec.Data[i];
			}

			return sum;
		}

		FPVec<3> Cross(const FPVec<3>& vec) const
		{
			FPVec<3> res;
			res[0] = Data[1] * vec.Data[2] - Data[2] * vec.Data[1],
			res[1] = Data[2] * vec.Data[0] - Data[0] * vec.Data[2],
			res[2] = Data[0] * vec.Data[1] - Data[1] * vec.Data[0];

			return res;
		}

		FPVec Normalize() const
		{
			return *this / Length();
		}

		FPVec Project(const FPVec& vec) const
		{
			FPVec normVec = vec.Normalize();
			return normVec * Dot(normVec);
		}
	};
}

#endif
