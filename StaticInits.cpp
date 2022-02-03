//This file initializes static constant values.

#include <YRPP.h>
#include <ASMMacros.h>
#include <YRPPCore.h>
#include <Unsorted.h>
#include <Helpers/Macro.h>

#include <ArrayClasses.h>
#include <TacticalClass.h>
#include <TechnoClass.h>
#include <InfantryClass.h>
#include <UnitClass.h>
#include <BuildingClass.h>
#include <SlaveManagerClass.h>
#include <RulesClass.h>
#include <Drawing.h>
#include <MapClass.h>
#include <WarheadTypeClass.h>
#include <HouseClass.h>
#include <SuperClass.h>
#include <FactoryClass.h>
#include <ScenarioClass.h>
#include <FootClass.h>
#include <LocomotionClass.h>
#include <GameOptionsClass.h>
#include <WWMouseClass.h>
#include <CoordStruct.h>
#include <Fixed.h>

const CoordStruct CoordStruct::Empty = { 0,0,0 };
const ColorStruct ColorStruct::Empty = { 0,0,0 };
const Color16Struct Color16Struct::Empty = { 0,0,0 };

#pragma region Imports
ALIAS(Imports::FP_OleSaveToStream, Imports::OleSaveToStream, 0x7E15F4);
ALIAS(Imports::FP_OleLoadFromStream, Imports::OleLoadFromStream, 0x7E15F8);
ALIAS(Imports::FP_CoRegisterClassObject, Imports::CoRegisterClassObject, 0x7E15D8);
ALIAS(Imports::FP_TimeGetTime, Imports::TimeGetTime, 0x7E1530);
ALIAS(Imports::FP_GetUpdateRect, Imports::GetUpdateRect, 0x7E139C);
ALIAS(Imports::FP_GetKeyState, Imports::GetKeyState, 0x7E13A8);
ALIAS(Imports::FP_DefWindowProcA, Imports::DefWindowProcA, 0x7E1394);
ALIAS(Imports::FP_MoveWindow, Imports::MoveWindow, 0x7E1398);
ALIAS(Imports::FP_GetFocus, Imports::GetFocus, 0x7E13A0);
ALIAS(Imports::FP_GetDC, Imports::GetDC, 0x7E13A4);
ALIAS(Imports::FP_GetActiveWindow, Imports::GetActiveWindow, 0x7E13AC);
ALIAS(Imports::FP_GetCapture, Imports::GetCapture, 0x7E13B0);
ALIAS(Imports::FP_GetDlgCtrlID, Imports::GetDlgCtrlID, 0x7E13B4);
ALIAS(Imports::FP_ChildWindowFromPointEx, Imports::ChildWindowFromPointEx, 0x7E13B8);
ALIAS(Imports::FP_GetWindowRect, Imports::GetWindowRect, 0x7E13BC);
ALIAS(Imports::FP_GetCursorPos, Imports::GetCursorPos, 0x7E13C0);
ALIAS(Imports::FP_CloseWindow, Imports::CloseWindow, 0x7E13C4);
ALIAS(Imports::FP_EndDialog, Imports::EndDialog, 0x7E13C8);
ALIAS(Imports::FP_SetFocus, Imports::SetFocus, 0x7E13CC);
ALIAS(Imports::FP_SetDlgItemTextA, Imports::SetDlgItemTextA, 0x7E13D0);
ALIAS(Imports::FP_DialogBoxParamA, Imports::DialogBoxParamA, 0x7E13D4);
ALIAS(Imports::FP_DialogBoxIndirectParamA, Imports::DialogBoxIndirectParamA, 0x7E13D8);
ALIAS(Imports::FP_ShowCursor, Imports::ShowCursor, 0x7E13DC);
ALIAS(Imports::FP_GetAsyncKeyState, Imports::GetAsyncKeyState, 0x7E13E0);
ALIAS(Imports::FP_ToAscii, Imports::ToAscii, 0x7E13E4);
ALIAS(Imports::FP_MapVirtualKeyA, Imports::MapVirtualKeyA, 0x7E13E8);
ALIAS(Imports::FP_GetSystemMetrics, Imports::GetSystemMetrics, 0x7E13EC);
ALIAS(Imports::FP_SetWindowPos, Imports::SetWindowPos, 0x7E13F0);
ALIAS(Imports::FP_DestroyWindow, Imports::DestroyWindow, 0x7E13F4);
ALIAS(Imports::FP_ReleaseCapture, Imports::ReleaseCapture, 0x7E13F8);
ALIAS(Imports::FP_SetCapture, Imports::SetCapture, 0x7E13FC);
ALIAS(Imports::FP_AdjustWindowRectEx, Imports::AdjustWindowRectEx, 0x7E1400);
ALIAS(Imports::FP_GetMenu, Imports::GetMenu, 0x7E1404);
ALIAS(Imports::FP_AdjustWindowRect, Imports::AdjustWindowRect, 0x7E1408);
ALIAS(Imports::FP_GetSysColor, Imports::GetSysColor, 0x7E140C);
ALIAS(Imports::FP_IsDlgButtonChecked, Imports::IsDlgButtonChecked, 0x7E1410);
ALIAS(Imports::FP_CheckDlgButton, Imports::CheckDlgButton, 0x7E1414);
ALIAS(Imports::FP_WaitForInputIdle, Imports::WaitForInputIdle, 0x7E1418);
ALIAS(Imports::FP_GetTopWindow, Imports::GetTopWindow, 0x7E141C);
ALIAS(Imports::FP_GetForegroundWindow, Imports::GetForegroundWindow, 0x7E1420);
ALIAS(Imports::FP_LoadIconA, Imports::LoadIconA, 0x7E1424);
ALIAS(Imports::FP_SetActiveWindow, Imports::SetActiveWindow, 0x7E1428);
ALIAS(Imports::FP_RedrawWindow, Imports::RedrawWindow, 0x7E142C);
ALIAS(Imports::FP_GetWindowContextHelpId, Imports::GetWindowContextHelpId, 0x7E1430);
ALIAS(Imports::FP_WinHelpA, Imports::WinHelpA, 0x7E1434);
ALIAS(Imports::FP_ChildWindowFromPoint, Imports::ChildWindowFromPoint, 0x7E1438);
ALIAS(Imports::FP_LoadCursorA, Imports::LoadCursorA, 0x7E143C);
ALIAS(Imports::FP_SetCursor, Imports::SetCursor, 0x7E1440);
ALIAS(Imports::FP_PostQuitMessage, Imports::PostQuitMessage, 0x7E1444);
ALIAS(Imports::FP_FindWindowA, Imports::FindWindowA, 0x7E1448);
ALIAS(Imports::FP_SetCursorPos, Imports::SetCursorPos, 0x7E144C);
ALIAS(Imports::FP_CreateDialogIndirectParamA, Imports::CreateDialogIndirectParamA, 0x7E1450);
ALIAS(Imports::FP_GetKeyNameTextA, Imports::GetKeyNameTextA, 0x7E1454);
ALIAS(Imports::FP_ScreenToClient, Imports::ScreenToClient, 0x7E1458);
ALIAS(Imports::FP_LockWindowUpdate, Imports::LockWindowUpdate, 0x7E145C);
ALIAS(Imports::FP_MessageBoxA, Imports::MessageBoxA, 0x7E1460);
ALIAS(Imports::FP_ReleaseDC, Imports::ReleaseDC, 0x7E1464);
ALIAS(Imports::FP_WindowFromPoint, Imports::WindowFromPoint, 0x7E1468);
ALIAS(Imports::FP_UpdateWindow, Imports::UpdateWindow, 0x7E146C);
ALIAS(Imports::FP_SetWindowLongA, Imports::SetWindowLongA, 0x7E1470);
ALIAS(Imports::FP_GetWindowLongA, Imports::GetWindowLongA, 0x7E1474);
ALIAS(Imports::FP_ValidateRect, Imports::ValidateRect, 0x7E1478);
ALIAS(Imports::FP_IntersectRect, Imports::IntersectRect, 0x7E147C);
ALIAS(Imports::FP_MessageBoxIndirectA, Imports::MessageBoxIndirectA, 0x7E1480);
ALIAS(Imports::FP_PeekMessageA, Imports::PeekMessageA, 0x7E1484);
ALIAS(Imports::FP_CallWindowProcA, Imports::CallWindowProcA, 0x7E1488);
ALIAS(Imports::FP_KillTimer, Imports::KillTimer, 0x7E148C);
ALIAS(Imports::FP_SendDlgItemMessageA, Imports::SendDlgItemMessageA, 0x7E1490);
ALIAS(Imports::FP_SetTimer, Imports::SetTimer, 0x7E1494);
ALIAS(Imports::FP_ShowWindow, Imports::ShowWindow, 0x7E1498);
ALIAS(Imports::FP_InvalidateRect, Imports::InvalidateRect, 0x7E149C);
ALIAS(Imports::FP_EnableWindow, Imports::EnableWindow, 0x7E14A0);
ALIAS(Imports::FP_SendMessageA, Imports::SendMessageA, 0x7E14A4);
ALIAS(Imports::FP_GetDlgItem, Imports::GetDlgItem, 0x7E14A8);
ALIAS(Imports::FP_PostMessageA, Imports::PostMessageA, 0x7E14AC);
ALIAS(Imports::FP_wsprintfA, Imports::wsprintfA, 0x7E14B0);
ALIAS(Imports::FP_SetRect, Imports::SetRect, 0x7E14B4);
ALIAS(Imports::FP_ClientToScreen, Imports::ClientToScreen, 0x7E14B8);
ALIAS(Imports::FP_TranslateMessage, Imports::TranslateMessage, 0x7E14BC);
ALIAS(Imports::FP_DispatchMessageA, Imports::DispatchMessageA, 0x7E14C0);
ALIAS(Imports::FP_GetClientRect, Imports::GetClientRect, 0x7E14C4);
ALIAS(Imports::FP_GetWindow, Imports::GetWindow, 0x7E14C8);
ALIAS(Imports::FP_BringWindowToTop, Imports::BringWindowToTop, 0x7E14CC);
ALIAS(Imports::FP_SetForegroundWindow, Imports::SetForegroundWindow, 0x7E14D0);
ALIAS(Imports::FP_CreateWindowExA, Imports::CreateWindowExA, 0x7E14D4);
ALIAS(Imports::FP_RegisterClassA, Imports::RegisterClassA, 0x7E14D8);
ALIAS(Imports::FP_GetClassNameA, Imports::GetClassNameA, 0x7E14DC);
ALIAS(Imports::FP_IsWindowVisible, Imports::IsWindowVisible, 0x7E14E0);
ALIAS(Imports::FP_EnumChildWindows, Imports::EnumChildWindows, 0x7E14E4);
ALIAS(Imports::FP_IsWindowEnabled, Imports::IsWindowEnabled, 0x7E14E8);
ALIAS(Imports::FP_GetParent, Imports::GetParent, 0x7E14EC);
ALIAS(Imports::FP_GetNextDlgTabItem, Imports::GetNextDlgTabItem, 0x7E14F0);
ALIAS(Imports::FP_IsDialogMessageA, Imports::IsDialogMessageA, 0x7E14F4);
ALIAS(Imports::FP_TranslateAcceleratorA, Imports::TranslateAcceleratorA, 0x7E14F8);
ALIAS(Imports::FP_CharToOemBuffA, Imports::CharToOemBuffA, 0x7E14FC);
ALIAS(Imports::FP_BeginPaint, Imports::BeginPaint, 0x7E1500);
ALIAS(Imports::FP_EndPaint, Imports::EndPaint, 0x7E1504);
ALIAS(Imports::FP_CreateDialogParamA, Imports::CreateDialogParamA, 0x7E1508);
ALIAS(Imports::FP_GetWindowTextA, Imports::GetWindowTextA, 0x7E150C);
ALIAS(Imports::FP_RegisterHotKey, Imports::RegisterHotKey, 0x7E1510);
ALIAS(Imports::FP_InterlockedIncrement, Imports::InterlockedIncrement, 0x7E11C8);
ALIAS(Imports::FP_InterlockedDecrement, Imports::InterlockedDecrement, 0x7E11CC);
#pragma endregion

#pragma region GlobalVarDeclaration
ALIAS(MouseClass, Map, 0x87F7E8)
ALIAS(GScreenClass, GScreen, 0x87F7E8)
ALIAS(CellClass, WorkingCellInstance, 0xABDC50)
ALIAS(RulesClass*,RulesGlobal,0x8871E0)
ALIAS(ScenarioClass*, ScenarioGlobal ,0xA8B230)
ALIAS(Random2Class, Random2Global ,0x886B88)
ALIAS(ParticleSystemClass*, ParticleSystemGlobal ,0xA8ED78)
ALIAS(GameOptionsClass, GameOptions,0xA8EB60)
ALIAS(GameModeOptionsClass, GameModeOptions ,0xA8B250)
ALIAS(TacticalClass*, TacticalGlobal,0x887324)
ALIAS(MessageListClass, MessageListGlobal,0xA8BC60)
ALIAS(SessionClass, SessionGlobal,0xA8B238)
ALIAS(WWMouseClass*, WWMouse,0x887640)
ALIAS(BombListClass , BombList , 0x87F5D8u)
ALIAS(DynamicVectorClass<ULONG>, ClassFactories, 0xB0BC88)
#pragma endregion


#pragma region Array
ARRAY2D_DEF(0xB4669Cu, short, Wave_LUT_Pythagoras, 300, 300);
ARRAY2D_DEF(0xABC7F8u, Point2D, LaserClass_DrawData, 8, 2);
ARRAY2D_DEF(0x88A118u, char, AlphaShapeArray, 256, 256);
#pragma endregion

void SlaveManagerClass::ZeroOutSlaves() {
	for(const auto& pNode : this->SlaveNodes) {
		if(auto pSlave = pNode->Slave) {
			pSlave->SlaveOwner = nullptr;
		}
		pNode->Slave = nullptr;
		pNode->State = SlaveControlStatus::Dead;
		pNode->RespawnTimer.Start(this->RegenRate);
	}
}

bool ObjectClass::IsOnMyView() const
{
	auto coords = this->GetCoords();
	auto Point = TacticalClass::Instance->CoordsToView(coords);
	return Point.X > Drawing::SurfaceDimensions_Hidden().X
		&& Point.Y > Drawing::SurfaceDimensions_Hidden().Y
		&& Point.X < Drawing::SurfaceDimensions_Hidden().X + Drawing::SurfaceDimensions_Hidden().Width
		&& Point.Y < Drawing::SurfaceDimensions_Hidden().Y + Drawing::SurfaceDimensions_Hidden().Height;

}

bool ObjectClass::IsGreenToYellowHP() const
{
	return this->Health / this->GetTechnoType()->Strength
		>= RulesClass::Instance->ConditionYellow;
}

bool ObjectClass::IsFullHP() const
{ return this->GetHealthPercentage() >= RulesClass::Instance->ConditionGreen; }

double ObjectClass::GetHealthPercentage_() const
{ return static_cast<double>(this->Health) / this->GetType()->Strength; }

int HouseClass::CountOwnedNow(const TechnoTypeClass* const pItem) const {
	switch(pItem->WhatAmI()) {
	case AbstractType::BuildingType:
		return this->CountOwnedNow(
			static_cast<BuildingTypeClass const*>(pItem));

	case AbstractType::UnitType:
		return this->CountOwnedNow(
			static_cast<UnitTypeClass const*>(pItem));

	case AbstractType::InfantryType:
		return this->CountOwnedNow(
			static_cast<InfantryTypeClass const*>(pItem));

	case AbstractType::AircraftType:
		return this->CountOwnedNow(
			static_cast<AircraftTypeClass const*>(pItem));

	default:
		__assume(0);
	}
}

int HouseClass::CountOwnedAndPresent(const TechnoTypeClass* const pItem) const {
	switch(pItem->WhatAmI()) {
	case AbstractType::BuildingType:
		return this->CountOwnedAndPresent(
			static_cast<BuildingTypeClass const*>(pItem));

	case AbstractType::UnitType:
		return this->CountOwnedAndPresent(
			static_cast<UnitTypeClass const*>(pItem));

	case AbstractType::InfantryType:
		return this->CountOwnedAndPresent(
			static_cast<InfantryTypeClass const*>(pItem));

	case AbstractType::AircraftType:
		return this->CountOwnedAndPresent(
			static_cast<AircraftTypeClass const*>(pItem));

	default:
		__assume(0);
	}
}

int HouseClass::CountOwnedEver(TechnoTypeClass const* const pItem) const {
	switch(pItem->WhatAmI()) {
	case AbstractType::BuildingType:
		return this->CountOwnedEver(
			static_cast<BuildingTypeClass const*>(pItem));

	case AbstractType::UnitType:
		return this->CountOwnedEver(
			static_cast<UnitTypeClass const*>(pItem));

	case AbstractType::InfantryType:
		return this->CountOwnedEver(
			static_cast<InfantryTypeClass const*>(pItem));

	case AbstractType::AircraftType:
		return this->CountOwnedEver(
			static_cast<AircraftTypeClass const*>(pItem));

	default:
		__assume(0);
	}
}

bool HouseClass::CanExpectToBuild(const TechnoTypeClass* const pItem) const {
	auto const parentOwnerMask = this->Type->FindParentCountryIndex();
	return this->CanExpectToBuild(pItem, parentOwnerMask);
}

bool HouseClass::CanExpectToBuild(const TechnoTypeClass* const pItem, int const idxParent) const {
	auto const parentOwnerMask = 1u << idxParent;
	if(pItem->InOwners(parentOwnerMask)) {
		if(this->InRequiredHouses(pItem)) {
			if(!this->InForbiddenHouses(pItem)) {
				auto const BaseSide = pItem->AIBasePlanningSide;
				if(BaseSide == -1 || BaseSide == this->Type->SideIndex) {
					return true;
				}
			}
		}
	}
	return false;
}

int HouseClass::FindSuperWeaponIndex(SuperWeaponType const type) const {
	for(int i = 0; i < this->Supers.Count; ++i) {
		if(this->Supers.Items[i]->Type->Type == type) {
			return i;
		}
	}
	return -1;
}

SuperClass* HouseClass::FindSuperWeapon(SuperWeaponType const type) const {
	auto index = this->FindSuperWeaponIndex(type);
	return this->Supers.GetItemOrDefault(index);
}

bool HouseClass::IsIonCannonEligibleTarget(const TechnoClass* const pTechno) const {
	if(pTechno->InWhichLayer() == Layer::Ground && pTechno->IsAlive && !pTechno->InLimbo) {
		return true;
	}

	// hard difficulty shoots the tank in the factory
	if(this->AIDifficulty == AIDifficulty::Hard) {
		for(const auto* pFactory : *FactoryClass::Array) {
			if(pFactory->Object == pTechno
				&& pFactory->Production.Timer.Duration
				&& !pFactory->IsSuspended)
			{
				return true;
			}
		}
	}

	return false;
}

CellStruct FootClass::GetRandomDirection(FootClass* pFoot)
{
	CellStruct nRet = CellStruct::Empty;

	if (auto pCell = MapClass::Instance->GetCellAt(pFoot->GetCoords()))
	{
		int rnd = ScenarioClass::Instance->Random.RandomRanged(0, 7);
		for (int j = 0; j < 8; ++j)
		{
			// get the direction in an overly verbose way
			int dir = ((j + rnd) % 8) & 7;

			if (auto pNeighbour = pCell->GetNeighbourCell(dir))
			{
				if (pFoot->IsCellOccupied(pNeighbour, -1, -1, nullptr, true) == Move::OK)
				{
					nRet = pNeighbour->MapCoords;
					break;
				}
			}
		}
	}

	return nRet;
}

int TechnoClass::GetIonCannonValue(AIDifficulty const difficulty) const {
	const auto& rules = *RulesClass::Instance;

	const TypeList<int>* pValues = nullptr;
	int value = 1;

	if(auto pUnit = abstract_cast<const UnitClass*>(this)) {
		auto pType = pUnit->Type;

		if(pType->Harvester) {
			pValues = &rules.AIIonCannonHarvesterValue;

		} else if(rules.BuildConst.FindItemIndex(pType->DeploysInto) != -1) {
			pValues = &rules.AIIonCannonMCVValue;

		} else if(pType->Passengers > 0) {
			pValues = &rules.AIIonCannonAPCValue;

		} else {
			value = 2;
		}

	} else if(auto pBuilding = abstract_cast<const BuildingClass*>(this)) {
		auto pType = pBuilding->Type;

		if(pType->Factory == AbstractType::BuildingType) {
			pValues = &rules.AIIonCannonConYardValue;

		} else if(pType->Factory == AbstractType::UnitType && !pType->Naval) {
			pValues = &rules.AIIonCannonWarFactoryValue;

		} else if(pType->PowerBonus > pType->PowerDrain) {
			pValues = &rules.AIIonCannonPowerValue;

		} else if(pType->IsBaseDefense) {
			pValues = &rules.AIIonCannonBaseDefenseValue;

		} else if(pType->IsPlug) {
			pValues = &rules.AIIonCannonPlugValue;

		} else if(pType->IsTemple) {
			pValues = &rules.AIIonCannonTempleValue;

		} else if(pType->HoverPad) {
			pValues = &rules.AIIonCannonHelipadValue;

		} else if(rules.BuildConst.FindItemIndex(pType) != -1) {
			pValues = &rules.AIIonCannonTechCenterValue;

		} else {
			value = 4;
		}

	} else if(auto pInfantry = abstract_cast<const InfantryClass*>(this)) {
		auto pType = pInfantry->Type;

		if(pType->Engineer) {
			pValues = &rules.AIIonCannonEngineerValue;

		} else if(pType->VehicleThief) {
			pValues = &rules.AIIonCannonThiefValue;

		} else {
			value = 2;
		}
	}

	if(pValues) {
		value = pValues->GetItemOrDefault(static_cast<int>(difficulty), value);
	}

	return value;
}

TechnoTypeClass* BuildingClass::GetSecretProduction() const {
	auto const pType = this->Type;

	if(pType->SecretInfantry) {
		return pType->SecretInfantry;
	}
	if(pType->SecretUnit) {
		return pType->SecretUnit;
	}
	if(pType->SecretBuilding) {
		return pType->SecretBuilding;
	}
	return this->SecretProduction;
}

void InfantryClass::RemoveMe_FromGunnerTransport()
{
	if (auto pTransport = this->Transporter)
	{
		if (auto pUnit = specific_cast<UnitClass*>(pTransport))
		{
			if (pUnit->GetTechnoType()->Gunner)
			{
				pUnit->RemoveGunner(this);
			}
		}
	}
}

bool BuildingClass::BuildingUnderAttack()
{
	if (this->Owner)
	{
		this->Owner->BuildingUnderAttack(this);
		return true;
	}

	return false;
}

#pragma warning(push)
#pragma warning(disable : 4244)

const Fixed Fixed::_1_2(1, 2);		// 1/2
const Fixed Fixed::_1_3(1, 3);		// 1/3
const Fixed Fixed::_1_4(1, 4);		// 1/4
const Fixed Fixed::_3_4(3, 4);		// 3/4
const Fixed Fixed::_2_3(2, 3);		// 2/3

Fixed::Fixed(int numerator, int denominator)
{
	if (denominator == 0)
	{
		Data.Raw = 0U;
	}
	else
	{
		Data.Raw = (unsigned int)(((unsigned __int64)numerator * PRECISION) / denominator);
	}
}

Fixed::Fixed(const char* ascii)
{
	if (ascii == nullptr)
	{
		Data.Raw = 0U;
		return;
	}

	char const* wholepart = ascii;

	while (isspace(*ascii))
	{
		ascii++;
	}

	char const* tptr = ascii;
	while (isdigit(*tptr))
	{
		tptr++;
	}

	if (*tptr == '%')
	{
		Data.Raw = (unsigned short)(((unsigned __int64)CRT::atoi(ascii) * PRECISION) / 100ULL);
	}
	else
	{

		Data.Composite.Whole = Data.Composite.Fraction = 0U;
		if (wholepart && *wholepart != '.')
		{
			Data.Composite.Whole = (unsigned char)CRT::atoi(wholepart);
		}

		const char* fracpart = CRT::strchr(ascii, '.');
		if (fracpart) fracpart++;
		if (fracpart)
		{
			unsigned short frac = (unsigned short)CRT::atoi(fracpart);

			int len = 0;
			unsigned int base = 1;
			char const* fptr = fracpart;
			while (isdigit(*fptr))
			{
				fptr++;
				len++;
				base *= 10U;
			}

			Data.Composite.Fraction = (unsigned char)(((unsigned __int64)frac * PRECISION) / base);
		}
	}
}

int Fixed::To_ASCII(char* buffer, int maxlen) const
{
	if (buffer == nullptr) return 0;

	unsigned int whole = Data.Composite.Whole;
	unsigned int frac = ((unsigned int)Data.Composite.Fraction * 1000U) / PRECISION;
	char tbuffer[32];

	if (frac == 0)
	{
		sprintf_s(tbuffer, "%u", whole);
	}
	else
	{
		sprintf_s(tbuffer, "%u.%02u", whole, frac);

		char* ptr = &tbuffer[CRT::strlen(tbuffer) - 1];
		while (*ptr == '0')
		{
			*ptr = '\0';
			ptr--;
		}
	}

	if (maxlen == -1)
	{
		maxlen = CRT::strlen(tbuffer) + 1;
	}

	CRT::strncpy(buffer, tbuffer, maxlen);

	int len = CRT::strlen(tbuffer);
	if (len < maxlen - 1) return(len);
	return(maxlen - 1);
}

const char* Fixed::As_ASCII() const
{
	static char buffer[32];

	To_ASCII(buffer, sizeof(buffer));
	return buffer;
}
#pragma warning(pop)
