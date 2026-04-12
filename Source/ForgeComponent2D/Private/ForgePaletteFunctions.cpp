// Copyright Teuku. All Rights Reserved.

#include "ForgePaletteFunctions.h"

FLinearColor UForgePaletteFunctions::ForgeGetColor(EForgeMaterialType MaterialType)
{
	// Create temp Data Asset with defaults
	UForgeMaterialPaletteDA* PaletteDA = NewObject<UForgeMaterialPaletteDA>(GetTransientPackage());
	PaletteDA->InitializeWithDefaults();
	
	return PaletteDA->GetColor(MaterialType);
}

float UForgePaletteFunctions::ForgeGetRoughness(EForgeMaterialType MaterialType)
{
	UForgeMaterialPaletteDA* PaletteDA = NewObject<UForgeMaterialPaletteDA>(GetTransientPackage());
	PaletteDA->InitializeWithDefaults();
	
	return PaletteDA->GetRoughness(MaterialType);
}

float UForgePaletteFunctions::ForgeGetEmissive(EForgeMaterialType MaterialType)
{
	UForgeMaterialPaletteDA* PaletteDA = NewObject<UForgeMaterialPaletteDA>(GetTransientPackage());
	PaletteDA->InitializeWithDefaults();
	
	return PaletteDA->GetEmissive(MaterialType);
}

float UForgePaletteFunctions::ForgeGetMetallic(EForgeMaterialType MaterialType)
{
	UForgeMaterialPaletteDA* PaletteDA = NewObject<UForgeMaterialPaletteDA>(GetTransientPackage());
	PaletteDA->InitializeWithDefaults();
	
	return PaletteDA->GetMetallic(MaterialType);
}

FForgeMaterialProperties UForgePaletteFunctions::ForgeGetMaterial(EForgeMaterialType MaterialType)
{
	UForgeMaterialPaletteDA* PaletteDA = NewObject<UForgeMaterialPaletteDA>(GetTransientPackage());
	PaletteDA->InitializeWithDefaults();
	
	return PaletteDA->GetMaterialProperties(MaterialType);
}
