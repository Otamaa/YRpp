#pragma once

//Locomotor = {92612C46-F71F-11d1-AC9F-006008055BB5}
#include <LocomotionClass.h>
class __declspec(uuid("92612C46-F71F-11d1-AC9F-006008055BB5")) JumpjetLocomotionClass : public LocomotionClass, public IPiggyback
{
public:
	//IUnknown
	virtual HRESULT __stdcall QueryInterface(REFIID iid, LPVOID* ppvObject) override JMP_STD(0x54DC60);
	virtual ULONG __stdcall AddRef() override JMP_STD(0x54DF50);
	virtual ULONG __stdcall Release() override JMP_STD(0x54DF60);

	virtual HRESULT __stdcall Begin_Piggyback(ILocomotion* pointer) override JMP_STD(0x54DA00);
	virtual HRESULT __stdcall End_Piggyback(ILocomotion** pointer) override JMP_STD(0x54DA50);
	virtual bool __stdcall Is_Ok_To_End() override JMP_STD(0x54DB00);
	virtual HRESULT __stdcall Piggyback_CLSID(GUID* classid) override JMP_STD(0x54DB50);
	virtual bool __stdcall Is_Piggybacking() override JMP_STD(0x54DF70);

	//ILocomotion
	virtual HRESULT __stdcall Link_To_Object(void* pointer) override JMP_STD(0x54AD30);

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) override JMP_STD(0x54B750);
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) override JMP_STD(0x54B7E0);

	//Destructor
	virtual ~JumpjetLocomotionClass() RX;

	//LocomotionClass
	virtual	int Size() override { return sizeof(*this); }

	//JumjetLocomotionClass
	int GetZCoords() const 
	{ JMP_THIS(0x54D820); }

	CoordStruct* GetJumjetCoords() const 
	{ JMP_THIS(0x54D6D0); }

	//Constructor
	JumpjetLocomotionClass()
		: JumpjetLocomotionClass(noinit_t())
	{ JMP_THIS(0x54AC40); }

protected:
	explicit __forceinline JumpjetLocomotionClass(noinit_t)
		: LocomotionClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	int TurnRate;
	int Speed;
	int Climb;
	float Crash;
	int Height;
	float Acceleration;
	float Wobbles;
	int Deviation;
	bool NoWobbles;
	CoordStruct HeadToCoord;
	bool IsMoving;
	int NextState;
	FacingStruct Facing;
	double __currentSpeed;
	double __maxSpeed;
	int __currentHeight;
	double __currentWobble;
	bool DestinationReached;
	void* Raider;
};

static_assert(sizeof(JumpjetLocomotionClass) == 0x98);