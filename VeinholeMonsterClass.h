#pragma once
#include <ObjectClass.h>

struct VeinholeAffectedCellData
{
	CellStruct AffectedCell;
	float RandomValue;
};

static_assert(sizeof(VeinholeAffectedCellData) == 0x8);

struct VeinholeGrowthData
{
	VeinholeAffectedCellData* GetData() const
	{ JMP_THIS(0x5AC960); }

	int HeapSize; //wont grow anything if heap 0
	int Capacity; // set from rules
	VeinholeAffectedCellData** Heap; // affected cell table ?
	int Ptr1;
	int Ptr2;
};

static_assert(sizeof(VeinholeGrowthData) == 0x14);

class NOVTABLE VeinholeMonsterClass : public ObjectClass
{
public:
	static const AbstractType AbsID = AbstractType::VeinholeMonster;

	static constexpr reference<BooleanVectorClass*, 0xA83DC8u> const IsCurrentPosAffected {};
	static constexpr reference<SHPStruct*,0xB1D2ECu> const VeinSHPData {};
	static constexpr constant_ptr<DynamicVectorClass<VeinholeMonsterClass*>, 0xB1D290u> const Array {};

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;
	virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize) R0;

	//Destructor
	virtual ~VeinholeMonsterClass() RX;

	//AbstractClass
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int Size() const R0;
	virtual void Update() RX;

	//ObjectClass
	virtual void Draw(Point2D* pLocation, RectangleStruct* pBounds) const RX; //114

	static VeinholeMonsterClass* __fastcall GetVeinholeMonsterAt(CellStruct* pCell)
		{ JMP_STD(0x74CDB0); }

	static VeinholeMonsterClass* __fastcall GetVeinholeMonsterFrom(CellStruct* pCell)
		{ JMP_STD(0x74CD60); }

	void RemoveFrom(CellClass* pCell) const
		{ JMP_THIS(0x74EF10); }

	void ClearVector() const
		{ JMP_THIS(0x74EA30); }

	void ClearSpreadData() const
		{ JMP_THIS(0x74E8A0); }

	static void __fastcall ClearVeinGrowthData()
		{ JMP_STD(0x74E100); }

	//called 687A80
	static void __fastcall InitVeiGrowhData(bool bAllocate = true)
		{ JMP_STD(0x74DE90); }

	static bool __fastcall IsCellEligibleForVeinHole(CellStruct& nWhere)
		{ JMP_STD(0x74D670); }

	static void __fastcall TheaterInit(TheaterType nType)
		{ JMP_STD(0x74D450); }

	void Recalculate() const
		{ JMP_THIS(0x74E930); }

	void RecalculateSpread() const
		{ JMP_THIS(0x74E6B0); }

	void Func_74E1C0_RecalculateCellVector() const
		{ JMP_THIS(0x74E1C0); }

	void Func_74DC00() const
		{ JMP_THIS(0x74DC00); }

	void UpdateGrowth() const
		{ JMP_THIS(0x74D7C0); }

	void AI()const 
		{ JMP_THIS(0x74CE50); }

	static void __fastcall DrawAll()
		{ JMP_STD(0x74D430); }

	static void __fastcall UpdateAll()
	{
		for (auto const& pVeins : *Array())
		{
			if(!pVeins->InLimbo)
				pVeins->AI();
		}
	}

	static TerrainTypeClass* __fastcall GetTerrainType()
		{ JMP_STD(0x74EF00); }

	VeinholeMonsterClass(CellStruct* pWhere) noexcept
		: VeinholeMonsterClass(noinit_t())
		{ JMP_THIS(0x74C5B0); }

protected:
	explicit __forceinline VeinholeMonsterClass(noinit_t) noexcept
		: ObjectClass(noinit_t()) {}
public:
	DWORD CurrentGrowthCount_01;	
	VeinholeGrowthData* GrowthData;
	VeinholeAffectedCellData* AffectedCellData;
	TimerStruct GrowthOrShrinkRateTimer;
	BooleanVectorClass* boolptr;
	DWORD State;
	DamageState DamageState;
	DWORD ___dwordD0Gas;
	BYTE ___byteD4timerstate;
	TimerStruct Timer_1;
	int GasTimerStart;
	DWORD ___dwordE8Gas;
	TimerStruct Timer_2;
	CellStruct MonsterCell;
	int ShapeFrame;
	bool SkipDraw;
	BYTE ToPuffGas;
	DWORD CurrentGrowthCount2;
};

static_assert(sizeof(VeinholeMonsterClass) == 0x108); //264