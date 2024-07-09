#ifndef ZWOPERATIONUTILS_H
#define ZWOPERATIONUTILS_H

constexpr double  ZWDEFAULT_TOL{ 1e-6 };

namespace ZwOperationUtils
{
	template <typename T>
	bool isEqual(const T& _Ty1, const T& _Ty2)
	{
		return abs(_Ty1 - _Ty2) < ZWDEFAULT_TOL;
	}
};
#endif // !ZWOPERTIONUTILS_H
