// Copyright Teuku. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ForgeMaterialPaletteDA.h"
#include "ForgePaletteFunctions.generated.h"

/**
 * Forge Palette Blueprint Functions
 * 
 * Langsung bisa dipanggil dari Blueprint tanpa setup apapun!
 * 
 * Usage:
 * 1. Right-click di Blueprint graph
 * 2. Search "Forge Get Color"
 * 3. Pilih Material Type
 * 4. Done!
 */
UCLASS()
class FORGECOMPONENT2D_API UForgePaletteFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Get color for a forge material type
	 * 
	 * @param MaterialType Which material (MoltenOrange, CherryRed, dll)
	 * @return The material's base color
	 */
	UFUNCTION(BlueprintPure, Category = "Forge|Palette")
	static FLinearColor ForgeGetColor(EForgeMaterialType MaterialType);

	/**
	 * Get roughness for a forge material type
	 * 
	 * @param MaterialType Which material
	 * @return The material's roughness (0.0-1.0)
	 */
	UFUNCTION(BlueprintPure, Category = "Forge|Palette")
	static float ForgeGetRoughness(EForgeMaterialType MaterialType);

	/**
	 * Get emissive intensity for a forge material type
	 * 
	 * @param MaterialType Which material
	 * @return The material's emissive intensity
	 */
	UFUNCTION(BlueprintPure, Category = "Forge|Palette")
	static float ForgeGetEmissive(EForgeMaterialType MaterialType);

	/**
	 * Get metallic for a forge material type
	 * 
	 * @param MaterialType Which material
	 * @return The material's metallic value (0.0-1.0)
	 */
	UFUNCTION(BlueprintPure, Category = "Forge|Palette")
	static float ForgeGetMetallic(EForgeMaterialType MaterialType);

	/**
	 * Get all material properties at once
	 * 
	 * @param MaterialType Which material
	 * @return Complete material properties struct
	 */
	UFUNCTION(BlueprintPure, Category = "Forge|Palette")
	static FForgeMaterialProperties ForgeGetMaterial(EForgeMaterialType MaterialType);
};
