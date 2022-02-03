#include <ArrayClasses.h>
#include <CRT.h>

#pragma warning(push)
#pragma warning(disable : 4244)

int __cdecl Get_Bit(void const* array, int bit)
{
	__asm
	{
		mov	eax, [bit]
		mov	esi, [array]
		mov	ebx, eax
		shr	ebx, 5
		and eax, 01Fh
		bt[esi + ebx * 4], eax
		setc	al
	}
}

void __cdecl Set_Bit(void* array, int bit, int value)
{
	__asm {
		mov	ecx, [bit]
		mov	eax, [value]
		mov	esi, [array]
		mov	ebx, ecx
		shr	ebx, 5
		and ecx, 01Fh
		btr[esi + ebx * 4], ecx
		or eax, eax
		jz	ok
		bts[esi + ebx * 4], ecx
		ok :
	}
}

int __cdecl First_True_Bit(void const* array)
{
	__asm {
		mov	esi, [array]
		mov	eax, -32
		again:
		add	eax, 32
			mov	ebx, [esi]
			add	esi, 4
			bsf	ebx, ebx
			jz	again
			add	eax, ebx
	}
}

int __cdecl First_False_Bit(void const* array)
{
	__asm {

		mov	esi, [array]
		mov	eax, -32
		again:
		add	eax, 32
			mov	ebx, [esi]
			not ebx
			add	esi, 4
			bsf	ebx, ebx
			jz	again
			add	eax, ebx
	}
}

int __cdecl Bound(int original, int min, int max)
{
	__asm {
		mov	eax, [original]
		mov	ebx, [min]
		mov	ecx, [max]
		cmp	ebx, ecx
		jl	okorder
		xchg	ebx, ecx
		okorder : cmp	eax, ebx
		jg	okmin
		mov	eax, ebx
		okmin : cmp	eax, ecx
		jl	okmax
		mov	eax, ecx
		okmax :
	}
}

void BooleanVectorClass::Fixup(int index) const
{
	/*
	**	If the requested index value is illegal, then force the index
	**	to be -1. This is the default non-index value.
	*/
	if (index >= BitCount)
	{
		index = -1;
	}

	/*
	**	If the new index is different than the previous index, there might
	**	be some fixing up required.
	*/
	if (index != LastIndex)
	{

		/*
		**	If the previously fetched boolean value was changed, then update
		**	the boolean array accordingly.
		*/
		if (LastIndex != -1)
		{
			Set_Bit((void*)&BitArray[0], LastIndex, Copy);
		}

		/*
		**	If this new current index is valid, then fill in the reference boolean
		**	value with the appropriate data from the bit array.
		*/
		if (index != -1)
		{
			((unsigned char&)Copy) = Get_Bit(&BitArray[0], index);
		}

		((int&)LastIndex) = index;
	}
}

bool BooleanVectorClass::Is_True(int index) const
{
	if (index == LastIndex) return(Copy);
	return(Get_Bit(&BitArray[0], index));
}

int BooleanVectorClass::First_False() const
{
	if (LastIndex != -1) Fixup(-1);

	int retval = First_False_Bit(&BitArray[0]);
	if (retval < BitCount) return(retval);

	/*
	**	Failure to find a false boolean value in the vector. Return this
	**	fact in the form of an invalid index number.
	*/
	return(-1);
}

int BooleanVectorClass::First_True() const
{
	if (LastIndex != -1) Fixup(-1);

	int retval = First_True_Bit(&BitArray[0]);
	if (retval < BitCount) return(retval);

	/*
	**	Failure to find a true boolean value in the vector. Return this
	**	fact in the form of an invalid index number.
	*/
	return(-1);
}

void BooleanVectorClass::Set()
{
	LastIndex = -1;
	if (BitArray.Length())
	{
		CRT::_memset(&BitArray[0], '\xFF', BitArray.Length());
	}
}

void BooleanVectorClass::Reset()
{
	LastIndex = -1;
	if (BitArray.Length())
	{
		CRT::_memset(&BitArray[0], '\0', BitArray.Length());
	}
}
#pragma warning(pop)
