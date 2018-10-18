#pragma once

namespace MathTools
{

	/*
	*Check if supplied number lies within supplied bounds (inclusive)	
	*/
	template<class T> 
	bool checkBounds(T value, T upper, T lower)
	{
		static_assert(std::is_arithmetic<T>::value, "Type must be numeric!");

		if (lower > upper)
		{
			std::cout << "Lower bound cannot be greater than lower bound!" << std::endl;
			return false;
		}

		return value <= upper && value >= lower;
	}


	template<class T>
	T clamp(T value, T upper, T lower)
	{
		static_assert(std::is_arithmetic<T>::value, "Type must be numeric!");

		if (lower > upper)
		{
			std::cout << "Lower bound cannot be greater than lower bound!" << std::endl;
			return false;
		}

		if (value < lower)
			return lower;
		if (value > upper)
			return upper;
		return value;
	}

}