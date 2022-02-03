#pragma once

#include <AbstractClass.h>

//forward declarations
class AircraftTypeClass;
class ObjectClass;
class TechnoClass;
class FootClass;

//The AirstrikeClass handles the airstrikes Boris calls in.
class NOVTABLE AirstrikeClass : public AbstractClass
{
public:
	static const AbstractType AbsID = AbstractType::Airstrike;

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm,BOOL fClearDirty) R0;

	//Destructor
	virtual ~AirstrikeClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int	Size() const R0;

	//non-virtual
	void StartMission(ObjectClass* pTarget) { JMP_THIS(0x41D830); }
	void Detach(ObjectClass* pTarget) { JMP_THIS(0x41D540); }
	void SetUp(ObjectClass* pTarget) { JMP_THIS(0x41D860); }
	void SetTarget(ObjectClass* pTarget) { JMP_THIS(0x41DA20);}
	void ResetTarget() { JMP_THIS(0x41DB40); }
	bool CanStrike(ObjectClass* pTarget) { JMP_THIS(0x41D7E0); }

	//Not sure
	int AirstrikeClass_41DC60() { JMP_THIS(0x41DC60); }
	FootClass* RemoveMember(FootClass* FirstObj) { JMP_THIS(0x41DC80); }
	bool IsDissolved() { JMP_THIS(0x41DD10);}

	//Constructor
	AirstrikeClass(TechnoClass* pOwner) noexcept
		: AirstrikeClass(noinit_t())
	{ JMP_THIS(0x41D380); }

protected:
	explicit __forceinline AirstrikeClass(noinit_t) noexcept
		: AbstractClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	int AirstrikeTeam;			//As in the INI files.
	int EliteAirstrikeTeam;	//As in the INI files.
	int AirstrikeTeamTypeIndex;	//As in the INI files.
	int EliteAirstrikeTeamTypeIndex;	//As in the INI files.
	DWORD CurTeamIndex;       //DWORD unknown_34;
	DWORD unknown_38;	//unused?
	bool IsOnMission;	//Is the Aircraft on its way?
	bool IsOnTeam;		//bool unknown_bool_3D;
	DWORD TeamDissolveFrame;	//when was the last time this team was invoked and subsequently dissolved
	int AirstrikeRechargeTime;	//As in the INI files.
	int EliteAirstrikeRechargeTime;	//As in the INI files.
	TechnoClass* Owner;		//The unit that called the Airstrike (usually Boris).
	ObjectClass* Target;	//The Airstrike's target.
	AircraftTypeClass* AirstrikeTeamType;	//As in the INI files.
	AircraftTypeClass* EliteAirstrikeTeamType;	//As in the INI files.
	FootClass* FirstObject;
};

static_assert(sizeof(AirstrikeClass) == 0x60);