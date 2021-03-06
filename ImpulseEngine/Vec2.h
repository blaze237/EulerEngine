#pragma once
#include <type_traits>
#include <cmath>
template <class T>
class Vec2
{
public:

	Vec2(T x, T y)
		: x(x), y(y)
	{
		static_assert(std::is_arithmetic<T>::value, "Position values must be numeric!");
	}

	Vec2()
		:x(0), y(0)
	{

	}

	/***OPERATORS ***/

	//Equality operator
	bool operator==(const Vec2 &p2) const
	{
		return this->x == p2.x && this->y == p2.y;
	}

	//Inequality operator
	bool operator!=(const Vec2 &p2) const
	{
		return !(*this == p2);
	}

	//Addition operator
	Vec2 operator+(const Vec2 &p2) const {
		Vec2 tmp;
		tmp.x = this->x + p2.x;
		tmp.y = this->y + p2.y;

		return tmp;
	}

	//Subtraction operator
	Vec2 operator-(const Vec2 &p2) const {
		Vec2 tmp;
		tmp.x = this->x - p2.x;
		tmp.y = this->y - p2.y;

		return tmp;
	}

	//Numeric division operator
	Vec2 operator/(const T &d) const {
		Vec2 tmp;
		tmp.x = this->x / d;
		tmp.y = this->y / d;

		return tmp;
	}

	//Numeric multiplication operator
	Vec2 operator*(const T &m) const {
		Vec2 tmp;
		tmp.x = this->x * m;
		tmp.y = this->y * m;

		return tmp;
	}
	//Addition assignment operator
	Vec2& operator+=(const Vec2 &p2) {
		this->x += p2.x;
		this->y += p2.y;
		return *this;
	}
	//Subtraction assignment operator
	Vec2& operator-=(const Vec2 &p2) {
		this->x -= p2.x;
		this->y -= p2.y;
		return *this;
	}
	//Multiplication assignment operator
	Vec2& operator*=(const T &m) {
		this->x *= m;
		this->y *= m;
		return *this;
	}
	//Division assignment operator
	Vec2& operator/=(const T &d) {
		this->x /= d;
		this->y /= d;
		return *this;
	}
	//Square bracket 
	T operator[](int i)
	{
		if (i == 0)
			return x;
		if (i == 1)
			return y;
		else
			throw std::invalid_argument("Please supply an index between 0 and 2");
	}



	/***MEMBER FUNCTIONS***/
	//Returns absolute distance to another point as a double
	double distanceTo(const Vec2<T> &p) const {
		return sqrt(pow((p.x - this->x), 2) + pow((p.y - this->y), 2));
	}

	//Returns angle to another point as a double in radians
	double angleTo(const Vec2<T> &p) const {
		T adj = abs(p.x - this->x);
		double hyp = distanceTo(p);

		return acos(adj / hyp);
	}

	void Normalise()
	{
		double mag = getMagnitude();

		if (mag == 0)
			return;

		x /= mag;
		y /= mag;
	}

	//Calculate the dot product of this vector with another
	inline T DotProd(const Vec2<T> v2) const
	{
		return (x * v2.x) + (y * v2.y);
	}

	//Calculate the determinant between two vectors
	inline T Det(const Vec2<T> v2) const
	{
		return (x * v2.y) - (y * v2.x);
	}

	/***GETTERS AND SETTERS ***/
	inline T getX() const
	{
		return x;
	}
	inline T getY() const
	{
		return y;
	}
	inline T getMagnitude() const
	{
		return sqrt(pow(x, 2) + pow(y, 2));;
	}
	inline void setX(T xNew) {
		x = xNew;

	}
	inline void  setY(T yNew) {
		y = yNew;
	}
	inline void set(T xNew, T yNew) {
		x = xNew;
		y = yNew;
	}


	T x;
	T y;

};

template<class T>
void PrintVector(Vec2<T>v)
{
	std::cout << "X: " << v.x << " Y: " << v.y << std::endl;
}


