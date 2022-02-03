/*
	AnimTypes are initialized by INI files.
*/

#pragma once

#include <TechnoTypeClass.h>

struct DoStruct
{
	BYTE Interrupt;	// Can it be interrupted?
	BYTE IsMobile;		// Can it move while doing this?
	BYTE RandomStart;	// Should animation be "randomized"?
	BYTE Rate;		// Frame rate.
};

static_assert(sizeof(DoStruct) == 0x4);

struct DoInfoStruct
{
	int StartFrame;
	int CountFrames;
	int FacingMultiplier;
	DoTypeFacing Facing;
	int SoundCount;
	int Sound1StartFrame;
	int Sound1Index; // VocClass
	int Sound2StartFrame;
	int Sound2Index; // VocClass
};

static_assert(sizeof(DoInfoStruct) == 0x24);
static_assert(sizeof(DoType) == 0x4);

struct DoControls
{
	static constexpr reference<DoStruct, 0x7EAF7Cu, 42> const MasterArray { };

	DoInfoStruct& GetSequence(DoType sequence) {
		return this->Sequences[(int)sequence];
	}

	const DoInfoStruct& GetSequence(DoType sequence) const {
		return this->Sequences[(int)sequence];
	}

	static DoStruct& GetSequenceData(DoType sequence)
	{
		return MasterArray[(int)sequence];
	}

	DoInfoStruct Sequences[42];
};

class NOVTABLE InfantryTypeClass : public TechnoTypeClass
{
public:
	static const AbstractType AbsID = AbstractType::InfantryType;

	//Array
	ABSTRACTTYPE_ARRAY(InfantryTypeClass, 0xA8E348u);

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~InfantryTypeClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int	Size() const R0;

	//ObjectTypeClass
	virtual bool SpawnAtMapCoords(CellStruct* pMapCoords, HouseClass* pOwner) R0;
	virtual ObjectClass* CreateObject(HouseClass* pOwner) R0;

	//Constructor
	InfantryTypeClass(const char* pID) noexcept
		: InfantryTypeClass(noinit_t())
	{ JMP_THIS(0x5236A0); }

protected:
	explicit __forceinline InfantryTypeClass(noinit_t) noexcept
		: TechnoTypeClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	int ArrayIndex;
	PipIndex Pip;
	PipIndex OccupyPip;
	WeaponStruct OccupyWeapon;
	WeaponStruct EliteOccupyWeapon;
	DoControls* Sequence;
	int FireUp;
	int FireProne;
	int SecondaryFire;
	int SecondaryProne;
	TypeList<AnimTypeClass*> DeadBodies;
	TypeList<AnimTypeClass*> DeathAnims;
	TypeList<int> VoiceComment;
	int EnterWaterSound;
	int LeaveWaterSound;
	bool Cyborg;
	bool NotHuman;
	bool Ivan; //used for the bomb attack cursor...
	int DirectionDistance;
	bool Occupier;
	bool Assaulter;
	int HarvestRate;
	bool Fearless;
	bool Crawls;
	bool Infiltrate;
	bool Fraidycat;
	bool TiberiumProof;
	bool Civilian;
	bool C4;
	bool Engineer;
	bool Agent;
	bool Thief;
	bool VehicleThief;
	bool Doggie;
	bool Deployer;
	bool DeployedCrushable;
	bool UseOwnName;
	bool JumpJetTurn;
	PRIVATE_PROPERTY(DWORD, align_ECC);
};

static_assert(sizeof(InfantryTypeClass) == 0xED0);
