// Fill out your copyright notice in the Description page of Project Settings.

#include "MPC_Forge_Palette.h"

// ==================== PARAMETER NAME DEFINITIONS ====================

// Color Parameter Names
const FName UMPC_Forge_Palette::Param_AnvilCarbon(TEXT("AnvilCarbon"));
const FName UMPC_Forge_Palette::Param_TemperedSteel(TEXT("TemperedSteel"));
const FName UMPC_Forge_Palette::Param_NobleSilver(TEXT("NobleSilver"));
const FName UMPC_Forge_Palette::Param_MasteryGold(TEXT("MasteryGold"));
const FName UMPC_Forge_Palette::Param_AgedBronze(TEXT("AgedBronze"));
const FName UMPC_Forge_Palette::Param_TannedHide(TEXT("TannedHide"));
const FName UMPC_Forge_Palette::Param_CharredOak(TEXT("CharredOak"));
const FName UMPC_Forge_Palette::Param_CherryRed(TEXT("CherryRed"));
const FName UMPC_Forge_Palette::Param_MoltenOrange(TEXT("MoltenOrange"));
const FName UMPC_Forge_Palette::Param_WhiteHeat(TEXT("WhiteHeat"));
const FName UMPC_Forge_Palette::Param_QuenchBlue(TEXT("QuenchBlue"));
const FName UMPC_Forge_Palette::Param_BrittleRust(TEXT("BrittleRust"));

// Roughness Parameter Names
const FName UMPC_Forge_Palette::Param_AnvilCarbon_Roughness(TEXT("AnvilCarbon_Roughness"));
const FName UMPC_Forge_Palette::Param_TemperedSteel_Roughness(TEXT("TemperedSteel_Roughness"));
const FName UMPC_Forge_Palette::Param_NobleSilver_Roughness(TEXT("NobleSilver_Roughness"));
const FName UMPC_Forge_Palette::Param_MasteryGold_Roughness(TEXT("MasteryGold_Roughness"));
const FName UMPC_Forge_Palette::Param_AgedBronze_Roughness(TEXT("AgedBronze_Roughness"));
const FName UMPC_Forge_Palette::Param_TannedHide_Roughness(TEXT("TannedHide_Roughness"));
const FName UMPC_Forge_Palette::Param_CharredOak_Roughness(TEXT("CharredOak_Roughness"));
const FName UMPC_Forge_Palette::Param_CherryRed_Roughness(TEXT("CherryRed_Roughness"));
const FName UMPC_Forge_Palette::Param_MoltenOrange_Roughness(TEXT("MoltenOrange_Roughness"));
const FName UMPC_Forge_Palette::Param_WhiteHeat_Roughness(TEXT("WhiteHeat_Roughness"));
const FName UMPC_Forge_Palette::Param_QuenchBlue_Roughness(TEXT("QuenchBlue_Roughness"));
const FName UMPC_Forge_Palette::Param_BrittleRust_Roughness(TEXT("BrittleRust_Roughness"));

// Emissive Parameter Names
const FName UMPC_Forge_Palette::Param_CherryRed_Emissive(TEXT("CherryRed_Emissive"));
const FName UMPC_Forge_Palette::Param_MoltenOrange_Emissive(TEXT("MoltenOrange_Emissive"));
const FName UMPC_Forge_Palette::Param_WhiteHeat_Emissive(TEXT("WhiteHeat_Emissive"));
const FName UMPC_Forge_Palette::Param_QuenchBlue_Emissive(TEXT("QuenchBlue_Emissive"));
const FName UMPC_Forge_Palette::Param_MasteryGold_Emissive(TEXT("MasteryGold_Emissive"));

// Metallic Parameter Names
const FName UMPC_Forge_Palette::Param_MasteryGold_Metallic(TEXT("MasteryGold_Metallic"));
const FName UMPC_Forge_Palette::Param_QuenchBlue_Metallic(TEXT("QuenchBlue_Metallic"));

// Rim Light Parameter Names
const FName UMPC_Forge_Palette::Param_NobleSilver_bRimLight(TEXT("NobleSilver_bRimLight"));
const FName UMPC_Forge_Palette::Param_MasteryGold_bRimLight(TEXT("MasteryGold_bRimLight"));
const FName UMPC_Forge_Palette::Param_QuenchBlue_bRimLight(TEXT("QuenchBlue_bRimLight"));

// ==================== HELPER FUNCTION IMPLEMENTATIONS ====================

TArray<FName> UMPC_Forge_Palette::GetAllParameterNames()
{
	TArray<FName> ParamNames;
	ParamNames.Reserve(34); // 12 colors + 12 roughness + 5 emissive + 2 metallic + 3 rim light

	// Colors
	ParamNames.Add(Param_AnvilCarbon);
	ParamNames.Add(Param_TemperedSteel);
	ParamNames.Add(Param_NobleSilver);
	ParamNames.Add(Param_MasteryGold);
	ParamNames.Add(Param_AgedBronze);
	ParamNames.Add(Param_TannedHide);
	ParamNames.Add(Param_CharredOak);
	ParamNames.Add(Param_CherryRed);
	ParamNames.Add(Param_MoltenOrange);
	ParamNames.Add(Param_WhiteHeat);
	ParamNames.Add(Param_QuenchBlue);
	ParamNames.Add(Param_BrittleRust);

	// Roughness
	ParamNames.Add(Param_AnvilCarbon_Roughness);
	ParamNames.Add(Param_TemperedSteel_Roughness);
	ParamNames.Add(Param_NobleSilver_Roughness);
	ParamNames.Add(Param_MasteryGold_Roughness);
	ParamNames.Add(Param_AgedBronze_Roughness);
	ParamNames.Add(Param_TannedHide_Roughness);
	ParamNames.Add(Param_CharredOak_Roughness);
	ParamNames.Add(Param_CherryRed_Roughness);
	ParamNames.Add(Param_MoltenOrange_Roughness);
	ParamNames.Add(Param_WhiteHeat_Roughness);
	ParamNames.Add(Param_QuenchBlue_Roughness);
	ParamNames.Add(Param_BrittleRust_Roughness);

	// Emissive
	ParamNames.Add(Param_CherryRed_Emissive);
	ParamNames.Add(Param_MoltenOrange_Emissive);
	ParamNames.Add(Param_WhiteHeat_Emissive);
	ParamNames.Add(Param_QuenchBlue_Emissive);
	ParamNames.Add(Param_MasteryGold_Emissive);

	// Metallic
	ParamNames.Add(Param_MasteryGold_Metallic);
	ParamNames.Add(Param_QuenchBlue_Metallic);

	// Rim Light
	ParamNames.Add(Param_NobleSilver_bRimLight);
	ParamNames.Add(Param_MasteryGold_bRimLight);
	ParamNames.Add(Param_QuenchBlue_bRimLight);

	return ParamNames;
}

FName UMPC_Forge_Palette::GetColorParamName(EForgeMaterialType MaterialType)
{
	switch (MaterialType)
	{
	case EForgeMaterialType::AnvilCarbon:     return Param_AnvilCarbon;
	case EForgeMaterialType::TemperedSteel:   return Param_TemperedSteel;
	case EForgeMaterialType::NobleSilver:     return Param_NobleSilver;
	case EForgeMaterialType::MasteryGold:     return Param_MasteryGold;
	case EForgeMaterialType::AgedBronze:      return Param_AgedBronze;
	case EForgeMaterialType::TannedHide:      return Param_TannedHide;
	case EForgeMaterialType::CharredOak:      return Param_CharredOak;
	case EForgeMaterialType::CherryRed:       return Param_CherryRed;
	case EForgeMaterialType::MoltenOrange:    return Param_MoltenOrange;
	case EForgeMaterialType::WhiteHeat:       return Param_WhiteHeat;
	case EForgeMaterialType::QuenchBlue:      return Param_QuenchBlue;
	case EForgeMaterialType::BrittleRust:     return Param_BrittleRust;
	default:                                  return NAME_None;
	}
}

FName UMPC_Forge_Palette::GetRoughnessParamName(EForgeMaterialType MaterialType)
{
	switch (MaterialType)
	{
	case EForgeMaterialType::AnvilCarbon:     return Param_AnvilCarbon_Roughness;
	case EForgeMaterialType::TemperedSteel:   return Param_TemperedSteel_Roughness;
	case EForgeMaterialType::NobleSilver:     return Param_NobleSilver_Roughness;
	case EForgeMaterialType::MasteryGold:     return Param_MasteryGold_Roughness;
	case EForgeMaterialType::AgedBronze:      return Param_AgedBronze_Roughness;
	case EForgeMaterialType::TannedHide:      return Param_TannedHide_Roughness;
	case EForgeMaterialType::CharredOak:      return Param_CharredOak_Roughness;
	case EForgeMaterialType::CherryRed:       return Param_CherryRed_Roughness;
	case EForgeMaterialType::MoltenOrange:    return Param_MoltenOrange_Roughness;
	case EForgeMaterialType::WhiteHeat:       return Param_WhiteHeat_Roughness;
	case EForgeMaterialType::QuenchBlue:      return Param_QuenchBlue_Roughness;
	case EForgeMaterialType::BrittleRust:     return Param_BrittleRust_Roughness;
	default:                                  return NAME_None;
	}
}

FName UMPC_Forge_Palette::GetEmissiveParamName(EForgeMaterialType MaterialType)
{
	switch (MaterialType)
	{
	case EForgeMaterialType::CherryRed:       return Param_CherryRed_Emissive;
	case EForgeMaterialType::MoltenOrange:    return Param_MoltenOrange_Emissive;
	case EForgeMaterialType::WhiteHeat:       return Param_WhiteHeat_Emissive;
	case EForgeMaterialType::QuenchBlue:      return Param_QuenchBlue_Emissive;
	case EForgeMaterialType::MasteryGold:     return Param_MasteryGold_Emissive;
	default:                                  return NAME_None;
	}
}
