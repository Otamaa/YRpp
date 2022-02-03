#pragma once

#include <LocomotionClass.h>

class __declspec(uuid("4A582744-9839-11d1-B709-00A024DDAFD1")) WalkLocomotionClass : public LocomotionClass, public IPiggyback
{
public:
	//IUnknown
	virtual HRESULT __stdcall QueryInterface(REFIID iid, LPVOID* ppvObject) override JMP_STD(0x75C7F0);
	virtual ULONG __stdcall AddRef() override JMP_STD(0x75CB80);
	virtual ULONG __stdcall Release() override JMP_STD(0x75CB90);

	//IPiggyback
	virtual HRESULT __stdcall Begin_Piggyback(ILocomotion* pointer) override JMP_STD(0x75C850);
	virtual HRESULT __stdcall End_Piggyback(ILocomotion** pointer) override JMP_STD(0x75C8A0);
	virtual bool __stdcall Is_Ok_To_End() override JMP_STD(0x75C8E0);
	virtual HRESULT __stdcall Piggyback_CLSID(GUID* classid) override JMP_STD(0x75C920);
	virtual bool __stdcall Is_Piggybacking() override JMP_STD(0x75CBA0);

	//ILocomotion
	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x75C680);
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x75C700);

	//Destructor
	virtual ~WalkLocomotionClass() RX;

	//LocomotionClass
	virtual	int Size() override { return sizeof(*this); }

	//WalkLocomotionClass

	//Constructor
	WalkLocomotionClass()
		: WalkLocomotionClass(noinit_t())
	{ JMP_THIS(0x75AA90); }

protected:
	explicit __forceinline WalkLocomotionClass(noinit_t)
		: LocomotionClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	CoordStruct MovingDestination;
	CoordStruct CoordHeadTo;
	bool IsMoving;
	bool _bool35;
	bool IsReallyMoving;
	LocomotionClass* PiggyBackee;
};

static_assert(sizeof(WalkLocomotionClass) == 0x3C);