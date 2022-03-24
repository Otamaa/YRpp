#pragma once

#include <GeneralStructures.h>

/*
		Otamaa : 04/08/2021

		Moved to separate header due to compile error
		Add More element known from Vinivera-TSpp
*/
//obvious
struct RectangleStruct
{
public:

	RectangleStruct()
		: X(0), Y(0), Width(0), Height(0)
	{ }

	RectangleStruct(int const x, int const y, int const width, int const height)
		: X(x), Y(y), Width(width), Height(height)
	{ }

	RectangleStruct(const Point2D& nXY, const Point2D& nWH)
		:X(nXY.X), Y(nXY.Y), Width(nWH.X), Height(nWH.Y)
	{ }

	RectangleStruct(const Point2D& nXY, int const width, int const height)
		:X(nXY.X), Y(nXY.Y), Width(width), Height(height)
	{ }

	RectangleStruct(const RectangleStruct& that)
		:X(that.X), Y(that.Y), Width(that.Width), Height(that.Height)
	{ }

	RectangleStruct &operator=(const RectangleStruct &that)
	{
		if (this != &that) {
			X = that.X;
			Y = that.Y;
			Width = that.Width;
			Height = that.Height;
		}
		return *this;
	}

	bool operator==(const RectangleStruct &that) const
	{
		return (that.X == X) && (that.Width == Width)
			&& (that.Y == Y) && (that.Height == Height);
	}

	bool operator!=(const RectangleStruct &that) const
	{
		return (that.X != X) && (that.Width != Width)
			&& (that.Y != Y) && (that.Height != Height);
	}

	RectangleStruct &operator|=(const RectangleStruct &that) { *this = Union(*this, that); return *this; }
	RectangleStruct &operator+=(const Point2D &point) { X += point.X; Y += point.Y; return *this; }
	RectangleStruct &operator-=(const RectangleStruct &rect)
	{
		X -= rect.X;
		Y -= rect.Y;
		Width -= rect.Width;
		Height -= rect.Height;
		return *this;
	}

	RectangleStruct &operator-=(const Point2D &point) { X -= point.X; Y -= point.Y; return *this; }
	RectangleStruct &operator+=(const RectangleStruct &rect)
	{
		X += rect.X;
		Y += rect.Y;
		Width += rect.Width;
		Height += rect.Height;
		return *this;
	}

	RectangleStruct &operator&=(const RectangleStruct &that)
	{
		*this = Intersect(*this, that, nullptr, nullptr);
		return *this;
	}

	RectangleStruct operator+(const Point2D &point)
	{
		RectangleStruct tmp = *this;
		tmp.X = X + point.X;
		tmp.Y = Y + point.Y;
		return tmp;
	}

	RectangleStruct operator-(const Point2D &point)
	{
		RectangleStruct tmp = *this;
		tmp.X = X - point.X;
		tmp.Y = Y - point.Y;
		return tmp;
	}

	RectangleStruct operator+(const RectangleStruct &that)
	{
		RectangleStruct tmp = *this;
		tmp += that;
		return tmp;
	}

	RectangleStruct operator-(const RectangleStruct &that)
	{
		RectangleStruct tmp = *this;
		tmp -= that;
		return tmp;
	}

	RectangleStruct Bias_To(const RectangleStruct &rect)
	{
		RectangleStruct tmp;
		tmp = RectangleStruct{ (X, Y), (rect.X + rect.Width, rect.Y), Width, Height };
		return tmp;
	}

	inline void Reset_Position() { X = 0; Y = 0; }

	void Move(int x, int y) { X += x; Y += y; }
	void Move(const Point2D &point) { X += point.X; Y += point.Y; }

	inline int Size() const { return Width * Height; }

	bool Is_Valid() const { return Width > 0 && Height > 0; }

	__forceinline bool Is_Within(const RectangleStruct &rect) const { return (rect.X >= X && rect.X < (X + Width)) && (rect.Width >= Y && rect.Width < (Y + Height)); }
	__forceinline bool Is_Within(int x, int y) const { return (x >= X && x < (X + Width)) && (y >= Y && y < (Y + Height)); }
	__forceinline bool Is_Within(const Point2D &point) const { return (point.X >= X && point.X < (X + Width)) && (point.Y >= Y && point.Y < (Y + Height)); }

	const RectangleStruct Intersect_With(const RectangleStruct &rectangle, int *x = nullptr, int *y = nullptr) { return Intersect(*this, rectangle, x, y); }

	bool Intersects_With(const RectangleStruct &with) const { return (X > with.Width) || (Width < with.X) || (Y > with.Height) || (Height < with.Y); }

	inline RectangleStruct InvalidRect() { return RectangleStruct{0, 0, 0, 0}; }

	bool Is_Overlapping(const RectangleStruct &rect)
	{
		return X < rect.X + rect.Width
			&& Y < rect.Y + rect.Height
			&& X + Width > rect.X
			&& Y + Height > rect.Y;
	}

	void Inflate(int w, int h, bool adjust_xy = false)
	{
		if (adjust_xy)
		{
			X -= w;
			Y -= h;
		}
		Width += w;
		Height += h;
	}

	inline Point2D Center_Point() const { return Point2D{ X + (Width / 2), Y + (Height / 2) }; }
	inline Point2D Top_Left() const { return Point2D{ X, Y }; }
	inline Point2D Top_Right() const { return Point2D{ X + Width, Y }; }
	inline Point2D Bottom_Left() const { return Point2D{ X, Y + Height }; }
	inline Point2D Bottom_Right() const { return Point2D{ X + Width, Y + Height }; }
	inline Point2D Top_Center() const { return Point2D{ (X + Width) / 2, Y }; }
	inline Point2D Bottom_Center() const { return Point2D{ (X + Width) / 2, Height }; }
	inline Point2D Left_Center() const { return Point2D{ X, (Y + Height) / 2 }; }
	inline Point2D Center_Right() const { return Point2D{ Width, (Y + Height) / 2 }; }

	int &operator[](int index) { return (&X)[index]; }
	const int &operator[](int index) const { return (&X)[index]; }

	static const RectangleStruct Union(const RectangleStruct &rect1, const RectangleStruct &rect2)
	{
		RectangleStruct r = rect1;

		if (r.X > rect2.X) {
			r.Width += r.X - rect2.X;
			r.X = rect2.X;
		}
		if (r.Y > rect2.Y) {
			r.Height += r.Y - rect2.Y;
			r.Y = rect2.Y;
		}
		if (r.X + r.Width < rect2.X + rect2.Width) {
			r.Width = ((rect2.X + rect2.Width) - r.X) + 1;
		}
		if (r.Y + r.Height < rect2.Y + rect2.Height) {
			r.Height = ((rect2.Y + rect2.Height) - r.Y) + 1;
		}
		return r;
	}

	static const RectangleStruct Intersect(const RectangleStruct &rect1, const RectangleStruct &rect2, int *x, int *y)
	{
		RectangleStruct rect{ 0, 0, 0, 0 };
		RectangleStruct r = rect2;

		if (r.X < rect1.X) {
			r.Width -= rect1.X - r.X;
			r.X = rect1.X;
		}
		if (r.Width < 1) return rect;

		if (r.Y < rect1.Y) {
			r.Height -= rect1.Y - r.Y;
			r.Y = rect1.Y;
		}
		if (r.Height < 1) return rect;

		if (r.X + r.Width > rect1.X + rect1.Width) {
			r.Width = rect1.X + rect1.Width - r.X;
		}
		if (r.Width < 1) return rect;

		if (r.Y + r.Height > rect1.Y + rect1.Height) {
			r.Height = rect1.Y + rect1.Height - r.Y;
		}
		if (r.Height < 1) return rect;

		if (x != nullptr) {
			*x -= (r.X - rect2.X);
		}
		if (y != nullptr) {
			*y -= (r.Y - rect2.Y);
		}

		return r;
	}


	int X, Y, Width, Height;

};