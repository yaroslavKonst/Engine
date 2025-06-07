#ifndef _FPMAT_TEMPLATE_H
#define _FPMAT_TEMPLATE_H

#include <cstring>

#include "vec.h"

namespace Math
{
	template<int Dim>
	struct FPMat
	{
		FPNumber Data[Dim][Dim];

		FPMat()
		{ }

		FPMat(FPNumber diagValue)
		{
			memset(Data, 0, sizeof(Data));

			for (int i = 0; i < Dim; ++i) {
				Data[i][i] = diagValue;
			}
		}

		FPNumber* operator[](int index)
		{
			return Data[index];
		}

		const FPNumber* operator[](int index) const
		{
			return Data[index];
		}

		FPMat operator+(const FPMat& mat) const
		{
			FPMat res;

			for (int row = 0; row < Dim; ++row) {
				for (int col = 0; col < Dim; ++col) {
					res.Data[row][col] =
						Data[row][col] +
						mat.Data[row][col];
				}
			}

			return res;
		}

		FPMat operator-(const FPMat& mat) const
		{
			FPMat res;

			for (int row = 0; row < Dim; ++row) {
				for (int col = 0; col < Dim; ++col) {
					res.Data[row][col] =
						Data[row][col] -
						mat.Data[row][col];
				}
			}

			return res;
		}

		void operator+=(const FPMat& mat)
		{
			for (int row = 0; row < Dim; ++row) {
				for (int col = 0; col < Dim; ++col) {
					Data[row][col] += mat.Data[row][col];
				}
			}
		}

		void operator-=(const FPMat& mat)
		{
			for (int row = 0; row < Dim; ++row) {
				for (int col = 0; col < Dim; ++col) {
					Data[row][col] -= mat.Data[row][col];
				}
			}
		}

		FPMat operator*(const FPMat& mat) const
		{
			FPMat res;

			for (int row = 0; row < Dim; ++row) {
				for (int col = 0; col < Dim; ++col) {
					FPNumber sum = 0;

					for (int i = 0; i < Dim; ++i) {
						sum += Data[row][i] *
							mat.Data[i][col];
					}

					res.Data[row][col] = sum;
				}
			}

			return res;
		}

		void operator*=(const FPMat& mat)
		{
			FPNumber res[Dim][Dim];

			for (int row = 0; row < Dim; ++row) {
				for (int col = 0; col < Dim; ++col) {
					FPNumber sum = 0;

					for (int i = 0; i < Dim; ++i) {
						sum += Data[row][i] *
							mat.Data[i][col];
					}

					res[row][col] = sum;
				}
			}

			memcpy(Data, res, sizeof(Data));
		}

		FPVec<Dim> operator*(const FPVec<Dim>& vec) const
		{
			FPVec<Dim> res;

			for (int row = 0; row < Dim; ++row) {
				FPNumber sum = 0;

				for (int col = 0; col < Dim; ++col) {
					sum += Data[row][col] * vec[col];
				}

				res[row] = sum;
			}

			return res;
		}
	};
}

#endif
