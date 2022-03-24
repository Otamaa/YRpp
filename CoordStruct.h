#pragma once

#include <YRMath.h>
#include <GeneralStructures.h>

/*
		Otamaa : 18/09/2021

		Moved to separate header due to compile error
		Add More element known from Vinivera-TSpp and Tompson-IDB

*/
//obvious

struct Coordinate
{
	int X, Y, Z;
};

#pragma warning(push)
#pragma warning(disable : 4244)
struct CoordStruct
{
	int X, Y, Z;

	/*
	CoordStruct() noexcept :
		X(0), Y(0), Z(0)
	{}

	CoordStruct(int x, int y, int z) noexcept :
		X(x), Y(y), Z(z)
	{}

	//CoordStruct(CoordStruct& nCoord) noexcept :
	//	X(nCoord.X), Y(nCoord.Y), Z(nCoord.Z)
	//{}

	CoordStruct(const CoordStruct& nCoord) noexcept :
		X(nCoord.X), Y(nCoord.Y), Z(nCoord.Z)
	{}

	CoordStruct(Point3D& nPoint3) noexcept :
		X(nPoint3.X), Y(nPoint3.Y), Z(nPoint3.Z)
	{}

	//CoordStruct(const Point3D& nPoint3) noexcept :
	//	X(nPoint3.X), Y(nPoint3.Y), Z(nPoint3.Z)
	//{}

	CoordStruct(Point2D& nPoint, int nZ) noexcept :
		X(nPoint.X), Y(nPoint.Y), Z(nZ)
	{}

	CoordStruct(CellStruct& nPoint, int nZ) noexcept :
		X(nPoint.X * 256), Y(nPoint.Y * 256), Z(nZ)
	{}
	*/
private:
	CellStruct* ToCellStruct(const CellStruct& ret)
	{ JMP_THIS(0x413A30); }
public:

	const char* As_String() const
	{
		static char _buffer[8 + 8 + 8];
		std::snprintf(_buffer, sizeof(_buffer), "%d,%d,%d", X, Y, Z);
		return _buffer;
	}

	CellStruct TocellStruct()
	{
		CellStruct nBuffer;
		ToCellStruct(nBuffer);
		return nBuffer;
	}

	operator bool() const
	{
		return X || Y || Z;
	}

	CoordStruct operator+(const CoordStruct& nThat) const
	{ return { X + nThat.X, Y + nThat.Y, Z + nThat.Z }; }

	CoordStruct& operator+=(const CoordStruct& nThat)
	{
		X += nThat.X;
		Y += nThat.Y;
		Z += nThat.Z;
		return *this;
	}

	CoordStruct operator-(const CoordStruct& nThat) const
	{ return { abs(X - nThat.X), abs(Y - nThat.Y), abs(Z - nThat.Z) }; }

	CoordStruct operator-(int nval) const
	{ return { X - nval, Y - nval, Z - nval }; }

	CoordStruct operator/(int nval) const
	{ return { X / nval, Y / nval, Z / nval }; }

	CoordStruct operator/(double ndVal) const
	{ return { (int)(X / ndVal), (int)(Y / ndVal), (int)(Z / ndVal) };}

	CoordStruct& operator-=(const CoordStruct& nThat)
	{
		X -= nThat.X;
		Y -= nThat.Y;
		Z -= nThat.Z;
		return *this;
	}

	CoordStruct operator-() const
	{ return { -X, -Y, -Z }; }

	CoordStruct operator*(const CoordStruct& nThat) const
	{ return { X * nThat.X, Y * nThat.Y, Z * nThat.Z }; }

	CoordStruct& operator*=(const CoordStruct& nThat)
	{
		X *= nThat.X;
		Y *= nThat.Y;
		Z *= nThat.Z;
		return *this;
	}

	//scalar multiplication
	CoordStruct operator*(double r) const
	{ return { (int)(X * r), (int)(Y * r), (int)(Z * r) }; }

	//scalar multiplication
	CoordStruct& operator*=(double r)
	{
		X = (int)(X * r);
		Y = (int)(Y * r);
		Z = (int)(Z * r);
		return *this;
	}

	bool operator==(const CoordStruct& nThat) const
	{ return (X == nThat.X && Y == nThat.Y && Z == nThat.Z); }

	bool operator!=(const CoordStruct& nThat) const
	{ return (X != nThat.X || Y != nThat.Y || Z != nThat.Z); }

	double Magnitude() const
	{ return Math::sqrt(MagnitudeSquared()); }

	int MagnitudeInt() const
	{ return (int)(Magnitude() * 0.00390625);}

	double MagnitudeSquared() const
	{
		CoordStruct nBufff = *this * *this;
		return ((double)nBufff.X + (double)nBufff.Y + (double)nBufff.Z);
	}

	int Length() const {
		return (int)Math::sqrt((double)X * (double)X + (double)Y * (double)Y + (double)Z * (double)Z);
	}

	double DistanceFrom(const CoordStruct& nThat) const
	{ return (*this - nThat).Magnitude(); }

	inline int DistanceFromI(const CoordStruct& nThat) const
	{ return (int)(*this - nThat).Magnitude(); }

	static const  CoordStruct Empty;

	CoordStruct Lerp(const CoordStruct& nThat, float t)
	{
		auto coord1 = *this;
		CoordStruct coord;

		coord.X = (int)(((double)coord1.X * (1.0f - (double)t)) + ((double)nThat.X * t));
		coord.Y = (int)(((double)coord1.Y * (1.0f - (double)t)) + ((double)nThat.Y * t));
		coord.Z = (int)(((double)coord1.Z * (1.0f - (double)t)) + ((double)nThat.Z * t));

		return coord;
	}

	CoordStruct Mid(const CoordStruct& nThat)
	{
		auto coord1 = *this;
		CoordStruct coord;
		coord.X = (coord1.X - nThat.X) / 2;
		coord.Y = (coord1.Y - nThat.Y) / 2;
		return coord;
	}

	CoordStruct Mid()
	{
		auto coord1 = *this;
		CoordStruct coord;
		coord.X = (coord1.X) / 2;
		coord.Y = (coord1.Y) / 2;
		return coord;
	}

	CoordStruct Snap()
	{
		auto coord = *this;
		// Convert coord to cell, and back again to get the absolute position.
		int cellX = coord.X / 256;
		int cellY = coord.Y / 256;

		CoordStruct tmp;
		tmp.X = cellX * 256;
		tmp.Y = cellY * 256;

		// Snap coord to cell center.
		tmp.X += 256 / 2;
		tmp.Y += 256 / 2;

		// Restore input coord Z value.
		tmp.Z = coord.Z;

		return tmp;
	}

	CoordStruct Fraction()
	{
		auto coord = *this;
		CoordStruct tmp;
		tmp.X = coord.X % 256;
		tmp.Y = coord.Y % 256;

		return tmp;
	}

	CoordStruct Whole()
	{
		auto coord = *this;
		// Convert coord to cell, and back again to get the absolute position.
		int cellX = coord.X / 256;
		int cellY = coord.Y / 256;

		CoordStruct tmp;
		tmp.X = cellX * 256;
		tmp.Y = cellY * 256;

		return tmp;
	}

	inline int& operator[](int i) { return (&X)[i]; }
	inline const int& operator[](int i) const { return (&X)[i]; }

	CoordStruct CrossProduct(const CoordStruct& nThat) const
	{
		return
		{
			Y * nThat.Z - Z * nThat.Y,
			Z * nThat.X - X * nThat.Z,
			X * nThat.Y - Y * nThat.X
		};
	}

	bool IsCollinearTo(const CoordStruct& nThat) const
	{ return CrossProduct(nThat).MagnitudeSquared() == 0.0; }

	double FindScalar(const CoordStruct& nThat) const
	{
		double r = static_cast<double>(nThat.X) / static_cast<double>(X);
		if ((static_cast<int>(r * Y) == nThat.Y) && (static_cast<int>(r * Z) == nThat.Z))
		{
			return r;
		}
		else
		{
			//the vectors are not collinear, return NaN!
			unsigned long NaN[2] = { 0xFFFFFFFF,0x7FFFFFFF };
			return *reinterpret_cast<double*>(NaN);
		}
	}

	double Angle(const CoordStruct& nThat) const
	{
		double Mag = (nThat).Magnitude();
		double MagT = this->Magnitude();
		double Dot = (double)((this->X * nThat.X) + (this->Y * nThat.Y) + (this->Z * nThat.Z));
		double v = Dot / (Mag * MagT);

		v = fmax(v, -1.0);
		v = fmin(v, 1.0);

		return Math::acos(v);
	}

	CoordStruct Max(const CoordStruct& nThat)
	{
		double x = X > nThat.X ? X : nThat.X;
		double y = Y > nThat.Y ? Y : nThat.Y;
		//swapped ?
		double z = Z > nThat.Z ? nThat.Z : Z;

		CoordStruct pBuffer;
		pBuffer.X += static_cast<int>(x);
		pBuffer.Y += static_cast<int>(y);
		pBuffer.Z += static_cast<int>(z);

		return pBuffer;
	}

	CoordStruct MoveTowards(CoordStruct& nThat, double maxDistanceDelta)
	{
		CoordStruct d = nThat - *this;
		double m = d.Magnitude();
		if (m < maxDistanceDelta || m == 0)
			return nThat;
		return *this += (d *= maxDistanceDelta * m);
	}

	double Dot(const CoordStruct& nThat)
	{ return X * nThat.X + Y * nThat.Y + Z * nThat.Z; }

	CoordStruct Reject(const CoordStruct& nThat)
	{ return *this - Project(nThat); }

	CoordStruct Reflect(const CoordStruct& nThat)
	{ return (*this - 2 )* Project(nThat); }

	CoordStruct Project(const CoordStruct& nThat)
	{
		double m = nThat.Magnitude();
		double res = Dot(nThat) / (m * m);
		return nThat * res;
	}

	void Scale(const CoordStruct& nThat)
	{ *this * nThat; }

	bool Equal_Within_Epsilon(const CoordStruct& nThat, double epsilon)
	{ return ((abs(X - nThat.X) < epsilon) && (abs(Y - nThat.Y) < epsilon) && (abs(Z - nThat.Z) < epsilon)); }

	int Cross_Product_X(const CoordStruct& nThat)
	{ return Y * nThat.Z - Z * nThat.Y;}

	int Cross_Product_Y(const CoordStruct& nThat)
	{ return Z * nThat.X - X * nThat.Z;}

	int Cross_Product_Z(const CoordStruct& nThat)
	{ return X * nThat.Y - Y * nThat.X; }

	CoordStruct Normalize()
	{
		CoordStruct buffer {0,0,0};
		double len2 = static_cast<double>(X * X + Y * Y + Z * Z);

		if (len2 != 0.0)
		{
			double oolen = (double)(Math::Q_invsqrt(static_cast<float>(len2)));
			buffer.X = X*oolen;
			buffer.Y = Y*oolen;
			buffer.Z = Z*oolen;
		}

		return buffer;
	}

	double Quick_distance(const CoordStruct& nThat) const
	{
		double max = abs(static_cast<double>(X - nThat.X));
		double mid = abs(static_cast<double>(Y - nThat.Y));
		double min = abs(static_cast<double>(Z - nThat.Z));
		double tmp;

		if (max < mid)
		{
			tmp = max;
			max = mid;
			mid = tmp;
		}

		if (max < min)
		{
			tmp = max;
			max = min;
			min = tmp;
		}

		if (mid < min)
		{
			tmp = mid;
			mid = min;
			min = mid;
		}

		return max + (11.0 / 32.0) * mid + (1.0 / 4.0) * min;
	}

	void Swap(CoordStruct& nThat)
	{
		CoordStruct tmp(*this);
		*this = nThat;
		nThat = tmp;
	}

	void Update_Min(const CoordStruct& nThat)
	{
		if (nThat.X < X) X = nThat.X;
		if (nThat.Y < Y) Y = nThat.Y;
		if (nThat.Z < Z) Z = nThat.Z;
	}

	void Update_Max(const CoordStruct& nThat)
	{
		if (nThat.X > X) X = nThat.X;
		if (nThat.Y > Y) Y = nThat.Y;
		if (nThat.Z > Z) Z = nThat.Z;
	}

	void Cap_Absolute_To(const CoordStruct& nThat)
	{
		if (X > 0)
		{
			if (nThat.X < X)
			{
				X = nThat.X;
			}
		}
		else
		{
			if (-nThat.X > X)
			{
				X = -nThat.X;
			}
		}

		if (Y > 0)
		{
			if (nThat.Y < Y)
			{
				Y = nThat.Y;
			}
		}
		else
		{
			if (-nThat.Y > Y)
			{
				Y = -nThat.Y;
			}
		}

		if (Z > 0)
		{
			if (nThat.Z < Z)
			{
				Z = nThat.Z;
			}
		}
		else
		{
			if (-nThat.Z > Z)
			{
				Z = -nThat.Z;
			}
		}
	}

	void Rotate_X(double angle)
	{ Rotate_X(Math::sin(angle), Math::cos(angle)); }

	void Rotate_X(double s_angle, double c_angle)
	{
		double tmp_y = static_cast<double>(Y);
		double tmp_z = static_cast<double>(Z);

		Y = c_angle * tmp_y - s_angle * tmp_z;
		Z = s_angle * tmp_y + c_angle * tmp_z;
	}

	void Rotate_Y(double angle)
	{ Rotate_X(Math::sin(angle), Math::cos(angle)); }

	void Rotate_Y(double s_angle, double c_angle)
	{
		double tmp_x = static_cast<double>(X);
		double tmp_z = static_cast<double>(Z);

		X = c_angle * tmp_x + s_angle * tmp_z;
		Z = -s_angle * tmp_x + c_angle * tmp_z;
	}

	void Rotate_Z(double angle)
	{ Rotate_X(Math::sin(angle), Math::cos(angle)); }

	void Rotate_Z(double s_angle, double c_angle)
	{
		double tmp_x = static_cast<double>(X);
		double tmp_y = static_cast<double>(Y);

		X = c_angle * tmp_x - s_angle * tmp_y;
		Y = s_angle * tmp_x + c_angle * tmp_y;
	}

	int Find_X_At_Y(int y, const CoordStruct& nThat)
	{ return (X + ((y - Y) * ((nThat.X - X) / (nThat.Y - Y)))); }

	int Find_X_At_Z(int z, const CoordStruct& nThat)
	{ return (X + ((z - Z) * ((nThat.X - X) / (nThat.Z - Z)))); }

	int Find_Y_At_X(int x, const CoordStruct& nThat)
	{ return (Y + ((x - X) * ((nThat.Y - Y) / (nThat.X - X)))); }

	int Find_Y_At_Z(int z, const CoordStruct& nThat)
	{ return (Y + ((z - Z) * ((nThat.Y - Y) / (nThat.Z - Z)))); }

	int Find_Z_At_X(int x, const CoordStruct& nThat)
	{ return (Z + ((x - X) * ((nThat.Z - Z) / (nThat.X - X))));}

	int Find_Z_At_Y(int y, const CoordStruct& nThat)
	{ return (Z + ((y - Y) * ((nThat.Z - Z) / (nThat.Y - Y)))); }

};
#pragma warning(pop)