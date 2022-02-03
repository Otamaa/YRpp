#pragma once

#include <ASMMacros.h>
#include <Helpers/CompileTime.h>
/*
		Otamaa : 18/09/2021

		Moved to separate header due to compile error
		Add More element known from Thompson YR-IDB

*/

// used for particle ColorList
//using RGBClass = ColorStruct; // <pd> wuhaha

struct Color16Struct;
#pragma pack(push, 1)
struct ColorStruct
{
	static constexpr reference<ColorStruct, 0xA80220> White {};
	static constexpr reference<int, 0x8A0DD0> RedShiftLeft {};
	static constexpr reference<int, 0x8A0DD4> RedShiftRight {};
	static constexpr reference<int, 0x8A0DE0> GreenShiftLeft {};
	static constexpr reference<int, 0x8A0DE4> GreenShiftRight {};
	static constexpr reference<int, 0x8A0DD8> BlueShiftLeft {};
	static constexpr reference<int, 0x8A0DDC> BlueShiftRight {};

	ColorStruct() = default;

	ColorStruct(BYTE const r, BYTE const g, BYTE const b)
		: R(r), G(g), B(b)
	{ }

	ColorStruct(const ColorStruct& c)
		: R(c.R), G(c.G), B(c.B)
	{ }

	ColorStruct(int rgb, bool wordcolor = false)
	{
		if (!wordcolor)
		{
			R = GetRValue(rgb);
			G = GetGValue(rgb);
			B = GetBValue(rgb);
		}
		else
		{
			R = (BYTE)((WORD)rgb >> RedShiftLeft) << RedShiftRight;
			G = (BYTE)((WORD)rgb >> GreenShiftLeft) << GreenShiftRight;
			B = (BYTE)((WORD)rgb >> BlueShiftLeft) << BlueShiftRight;
		}
	}

	inline explicit ColorStruct(Color16Struct const color);
	static const ColorStruct Empty;

	explicit ColorStruct(DWORD const color) 
	{ memcpy(this, &color, sizeof(ColorStruct)); }

	inline explicit ColorStruct(WORD const color);

	bool operator == (ColorStruct const rhs) const 
	{ return R == rhs.R && G == rhs.G && B == rhs.B; }

	bool operator != (ColorStruct const rhs) const
	{ return !(*this == rhs); }

	explicit operator DWORD() const 
	{
		DWORD ret = 0;
		memcpy(&ret, this, sizeof(ColorStruct));
		return ret;
	}

	inline explicit operator WORD() const;

	ColorStruct* Adjust_Brightness(ColorStruct& color, float adjust)
	{ JMP_THIS(0x661190); }

	ColorStruct* Adjust_Brightness(ColorStruct* color, float adjust)
	{ JMP_THIS(0x661190); }

	static ColorStruct AdjustBrightness(ColorStruct& color, float adjust)
	{
		ColorStruct nRet;

		constexpr auto nClamp = [](float nInput)
		{
			nInput = std::clamp(nInput, 0.0f, 255.0f);
			return static_cast<BYTE>(nInput);
		};

		nRet.R = nClamp(color.R * adjust);
		nRet.G = nClamp(color.G * adjust);
		nRet.B = nClamp(color.B * adjust);

		return nRet;
	}

	ColorStruct* Lerp(ColorStruct& lower, ColorStruct& upper, float adjust)
	{ JMP_THIS(0x661020); }

	unsigned int ToInit()
	{ JMP_THIS(0x63DAD0); }

	void Adjust(int adjust, const ColorStruct& that)
	{ JMP_THIS(0x6612C0); }

	int Difference(const ColorStruct& that) const
	{ JMP_THIS(0x661350); }

	enum { MAX_VALUE = 255 };

	BYTE R, G, B;
};
#pragma pack(pop)

struct BytePalette
{
	ColorStruct Entries[256];

	ColorStruct& operator [](int const idx)
	{ return this->Entries[idx]; }

	ColorStruct const& operator [](int const idx) const
	{ return this->Entries[idx]; }
};

//16bit colors
#pragma pack(push, 1)
struct Color16Struct
{
	Color16Struct() = default;

	explicit Color16Struct(ColorStruct const color) :
		B(static_cast<unsigned short>(color.B >> 3u)),
		G(static_cast<unsigned short>(color.G >> 2u)),
		R(static_cast<unsigned short>(color.R >> 3u))
	{ }

	explicit Color16Struct(WORD const color)
	{ memcpy(this, &color, sizeof(Color16Struct)); }

	explicit Color16Struct(DWORD const color)
		: Color16Struct(ColorStruct(color))
	{ }

	Color16Struct(WORD const r, WORD const g, WORD const b)
		: R(r), G(g), B(b)
	{ }

	bool operator == (Color16Struct const rhs) const
	{ return R == rhs.R && G == rhs.G && B == rhs.B; }

	bool operator != (Color16Struct const rhs) const
	{ return !(*this == rhs); }

	static const Color16Struct Empty;

	explicit operator WORD() const 
	{
		WORD ret;
		memcpy(&ret, this, sizeof(Color16Struct));
		return ret;
	}

	explicit operator DWORD() const 
	{ return static_cast<DWORD>(ColorStruct(*this)); }

	unsigned short B : 5;
	unsigned short G : 6;
	unsigned short R : 5;
};
#pragma pack(pop)

inline ColorStruct::ColorStruct(Color16Struct const color) :
	B(static_cast<BYTE>(color.B << 3u | color.B >> 2u)),
	G(static_cast<BYTE>(color.G << 2u | color.G >> 4u)),
	R(static_cast<BYTE>(color.R << 3u | color.R >> 2u))
{ }

inline ColorStruct::ColorStruct(WORD const color) :
	ColorStruct(Color16Struct(color))
{ }

ColorStruct::operator WORD() const 
{
	return static_cast<WORD>(Color16Struct(*this));
}

/*
#pragma pack(push, 1)
// this one just packed ColorSturct
class RGBClass : public ColorStruct {};
#pragma pack(pop)*/