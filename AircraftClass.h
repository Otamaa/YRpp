/*
	Aircraft
*/

#pragma once

#include <FootClass.h>
#include <AircraftTypeClass.h>

//forward declarations

//What are these?
class StageClass : public IFlyControl{ };
class FlasherClass : public StageClass{ };

class BulletClass;
//AircraftClass
class NOVTABLE AircraftClass : public FootClass, public FlasherClass
{
public:
	static const AbstractType AbsID = AbstractType::Aircraft;

	//Static
	static constexpr constant_ptr<DynamicVectorClass<AircraftClass*>, 0xA8E390u> const Array{};

	//IFlyControl
	virtual int __stdcall Landing_Altitude() R0;
	virtual int __stdcall Landing_Direction() R0;
	virtual long __stdcall Is_Loaded() R0;
	virtual long __stdcall Is_Strafe() R0;
	virtual long __stdcall Is_Fighter() R0;
	virtual long __stdcall Is_Locked() R0;

	//IUnknown
	virtual HRESULT __stdcall QueryInterface(REFIID iid, void** ppvObject) R0;
	virtual ULONG __stdcall AddRef() R0;
	virtual ULONG __stdcall Release() R0;

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int	Size() const R0;
	virtual void Update() override JMP_THIS(0x414BB0);

	//Destructor
	virtual ~AircraftClass() RX;

	//MissionClass
	virtual void Override_Mission(Mission mission, AbstractClass* tarcom = nullptr, AbstractClass* navcom = nullptr) override JMP_THIS(0x41BB30);

	//Techno Class
	virtual BulletClass* Fire(AbstractClass* pTarget, int nWeaponIndex) override JMP_THIS(0x415EE0);

	//FootClass
	virtual TechnoClass* FindDockingBayInVector(DynamicVectorClass<TechnoTypeClass*>* pVec, int unusedarg3, bool bForced) const override JMP_THIS(0x41BBD0);

	//some stuffs here may from FootClass::vtable , which is missing
	CellClass* GoodLandingZone() const { JMP_THIS(0x41A160); }
	CellClass* NewLandingZone(CellClass* pOldCell) { JMP_THIS(0x418E20); }
	void GoodTargetLoc(AbstractClass* pTarget) const { JMP_THIS(0x4197C0); }
	bool CellSeemsOk(CellStruct& nCell, bool bStrich) { JMP_THIS(0x419B00); }

	void DropOffCarryAllCargo() const { JMP_THIS(0x416AF0); }
	void DropOffParadropCargo() const { JMP_THIS(0x415C60); }

	void Tracker_4134A0() { AircraftTracker_4134A0(this); }

	static void AircraftTracker_4134A0(AircraftClass* pThis)
	{
		EPILOG_THISCALL;
		PUSH_IMM(pThis);
		THISCALL_EX(0x887888, 0x4134A0);
	}

	//Constructor
	AircraftClass(AircraftTypeClass* pType, HouseClass* pOwner) noexcept
		: AircraftClass(noinit_t())
	{ JMP_THIS(0x413D20); }

protected:
	explicit __forceinline AircraftClass(noinit_t) noexcept
		: FootClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	AircraftTypeClass* Type;
	bool unknown_bool_6C8; //loseAmmo
	bool HasPassengers;	//parachutes
	bool IsKamikaze; // when crashing down, duh
	TechnoClass* DockedTo;
	bool unknown_bool_6D0;
	bool unknown_bool_6D1;
	bool unknown_bool_6D2;
	BYTE ___paradrop_attempts; //6D3
	bool carrayall6D4;
	bool retreating_idle; //6D5
};

static_assert(sizeof(AircraftClass) == 0x6D8);