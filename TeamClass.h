#pragma once

#include <AbstractClass.h>

class HouseClass;
class FootClass;
class CellClass;
class ScriptClass;
class TagClass;
class TeamTypeClass;
class TechnoTypeClass;

class NOVTABLE TeamClass : public AbstractClass
{
public:
	static const AbstractType AbsID = AbstractType::Team;

	//Static
	static constexpr constant_ptr<DynamicVectorClass<TeamClass*>, 0x8B40E8u> const Array{};

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm,BOOL fClearDirty) R0;

	//Destructor
	virtual ~TeamClass() RX;

	// fills dest with all types needed to complete this team. each type is
	// included as often as it is needed.
	void GetTaskForceMissingMemberTypes(DynamicVectorClass<TechnoTypeClass *>& dest) const { JMP_THIS(0x6EF4D0); }
	bool Is_LeavingMap() const { JMP_THIS(0x6EC300); }
	void LiberateMember(FootClass* pFoot, int idx=-1, byte count=0) const { JMP_THIS(0x6EA870); }
	bool Add(FootClass* pFoot, bool bArg) const { JMP_THIS(0x6EA500); }
	FootClass* FetchLeader() const { JMP_THIS(0x6EC3D0); }

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;

	//Constructor
	TeamClass(TeamTypeClass* pType , HouseClass* pOwner, int investigate_me) noexcept
		: TeamClass(noinit_t())
	{ JMP_THIS(0x6E8A90); }

protected:
	explicit __forceinline TeamClass(noinit_t) noexcept
		: AbstractClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	TeamTypeClass* Type;
	ScriptClass*   CurrentScript;
	HouseClass*    Owner;
	HouseClass*    Target;
	CellClass*     SpawnCell;
	FootClass*	   ClosestMember;
	AbstractClass* QueuedFocus;
	AbstractClass* Focus;
	int            unknown_44;
	int            TotalObjects;
	int            TotalThreatValue;
	int            CreationFrame;
	FootClass *    FirstUnit;
	TimerStruct	   GuardAreaTimer;
	TimerStruct	   SuspendTimer;
	TagClass*      Tag;
	bool           IsTransient;
	bool           NeedsReGrouping;
	bool           GuardSlowerIsNotUnderStrength;
	bool           IsForcedActive;

	bool           IsHasBeen;
	bool           IsFullStrength;
	bool           IsUnderStrength;
	bool           IsReforming;

	bool           IsLagging;
	bool           NeedsToDisappear;
	bool           JustDisappeared;
	bool           IsMoving;

	bool           StepCompleted; // can proceed to the next step of the script
	bool           TargetNotAssigned;
	bool           IsLeavingMap;
	bool           IsSuspended;

	bool           AchievedGreatSuccess; // executed script action 49, 0

	int CountObjects [6]; // counts of each object specified in the Type
};

static_assert(sizeof(TeamClass) == 0xA0);
