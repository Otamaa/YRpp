#pragma once

#include <Helpers/CompileTime.h>

class RandomClass
{
public:
	RandomClass(unsigned seed = 0)
	{
		JMP_THIS(0x65C630);
	}

	operator int() { return operator()(); }

	int operator()()
	{
		JMP_THIS(0x65C640);
	}

	int operator()(int minval, int maxval)
	{
		JMP_THIS(0x65C660)
	}

	template<typename T> T operator()(T minval, T maxval) { return (T)(*this)(int(minval), int(maxval)); }

protected:
	unsigned long Seed;
};

class Random2Class
{
public:
	static constexpr reference<Random2Class, 0x886B88u> const NonCriticalRandomNumber{};
	static constexpr reference<Random2Class, 0x886B88u> const Global{}; // For backward compatibility

	Random2Class(unsigned seed = GetTickCount())
	{
		JMP_THIS(0x65C6D0);
	}

	operator int() { return operator()(); }

	int operator()()
	{
		JMP_THIS(0x65C780);
	}

	int operator()(int minval, int maxval)
	{
		JMP_THIS(0x65C7E0)
	}

	template<typename T> T operator()(T minval, T maxval) { return static_cast<T>((*this)(static_cast<int>(minval), static_cast<int>(maxval))); }

	int operator()(int nNumber)
	{
		return (*this)(0, nNumber);
	}

	// For backward compatibility
	// Otamaa 05/08/2021

	DWORD Random()
	{
		JMP_THIS(0x65C780);
	}

	int RandomRanged(int nMin, int nMax)
	{
		return (*this)(nMin, nMax);
	}

	bool PercentChance(int percent)
	{
		return (*this)(99) < percent;
	}

	bool PercentChance(double dChance)
	{
		return (*this).RandomDouble() < dChance;
	}

	double RandomDouble()
	{
		return (*this)(1, 2147483647) / 2147483648.0;
	}

protected:
	bool unknownBool_00;
	int Index1;
	int Index2;
	DWORD Table[0xFA];

};

class Random3Class
{
public:
	Random3Class(unsigned seed1 = 0, unsigned seed2 = 0)
	{
		JMP_THIS(0x65C890);
	}

	operator int() { return operator()(); }

	int operator()()
	{
		JMP_THIS(0x65C8B0);
	}

	int operator()(int minval, int maxval)
	{
		JMP_THIS(0x65C910);
	}

	template<typename T> T operator()(T minval, T maxval) { return T(*this)(int(minval), int(maxval)); }

protected:
	int Seed;
	int Index;

private:
	static unsigned Mix1[20];
	static unsigned Mix2[20];
};
