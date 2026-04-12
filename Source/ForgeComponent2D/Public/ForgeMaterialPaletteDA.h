// Copyright Teuku. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MPC_Forge_Palette.h"
#include "ForgeMaterialPaletteDA.generated.h"

/**
 * Forge Material Definition
 * Extends FForgeMaterialProperties with the material type identifier.
 */
USTRUCT(BlueprintType)
struct FForgeMaterialDefinition
{
	GENERATED_BODY()

	/** Material type identifier */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Definition")
	EForgeMaterialType MaterialType = EForgeMaterialType::AnvilCarbon;

	/** Material properties (color, roughness, emissive, etc.) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Definition")
	FForgeMaterialProperties Properties;
};

/**
 * UForgeMaterialPaletteDA - Data Asset Controller
 * 
 * Central controller for managing forge material palette configurations.
 * Separates material data management from MPC storage, following
 * Separation of Concerns principles.
 * 
 * Usage:
 * 1. Create Data Asset: Right-click in Content Browser -> Miscellaneous -> Data Asset -> ForgeMaterialPaletteDA
 * 2. Configure all 12 material properties in the editor
 * 3. Call InjectToMPC() to apply values to an MPC_Forge_Palette instance
 * 4. Materials automatically reference MPC parameters
 * 
 * Benefits:
 * - Designer-friendly: Edit palettes without code changes
 * - Runtime swappable: Change palettes via Blueprint/C++
 * - Version control friendly: Data Assets diff cleanly in Git
 * - Multiple palettes: Create different themes (e.g., Classic, HDR, Mobile)
 */
UCLASS(BlueprintType, Const)
class FORGECOMPONENT2D_API UForgeMaterialPaletteDA : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	// ==================== CONSTRUCTOR ====================
	
	UForgeMaterialPaletteDA();

	// ==================== MATERIAL DEFINITIONS ====================
	
	/**
	 * Array of all 12 forge material definitions.
	 * Edit this in the Data Asset editor to configure your palette.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forge Palette")
	TArray<FForgeMaterialDefinition> MaterialDefinitions;

	/**
	 * Palette display name for editor organization
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Palette Settings")
	FText PaletteName = FText::FromString("Default Forge Palette");

	/**
	 * Palette description
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Palette Settings", meta = (MultiLine = true))
	FText PaletteDescription = FText::FromString("Default material palette with all 12 forge material identities.");

	// ==================== VALUE RETRIEVAL API ====================
	
	/**
	 * Get color value for a specific material type from this palette.
	 * Use this in Material Dynamic Material Instances (DMIs) at runtime.
	 * 
	 * @param MaterialType The forge material type
	 * @return The color value (LinearColor format)
	 */
	UFUNCTION(BlueprintPure, Category = "Forge Palette|Values")
	FLinearColor GetColor(EForgeMaterialType MaterialType) const;

	/**
	 * Get roughness value for a specific material type from this palette.
	 * 
	 * @param MaterialType The forge material type
	 * @return The roughness value (0.0-1.0)
	 */
	UFUNCTION(BlueprintPure, Category = "Forge Palette|Values")
	float GetRoughness(EForgeMaterialType MaterialType) const;

	/**
	 * Get emissive intensity value for a specific material type from this palette.
	 * 
	 * @param MaterialType The forge material type
	 * @return The emissive intensity value
	 */
	UFUNCTION(BlueprintPure, Category = "Forge Palette|Values")
	float GetEmissive(EForgeMaterialType MaterialType) const;

	/**
	 * Get metallic value for a specific material type from this palette.
	 * 
	 * @param MaterialType The forge material type
	 * @return The metallic value (0.0-1.0)
	 */
	UFUNCTION(BlueprintPure, Category = "Forge Palette|Values")
	float GetMetallic(EForgeMaterialType MaterialType) const;

	/**
	 * Get rim light flag for a specific material type from this palette.
	 * 
	 * @param MaterialType The forge material type
	 * @return True if material has rim light enabled
	 */
	UFUNCTION(BlueprintPure, Category = "Forge Palette|Values")
	bool HasRimLight(EForgeMaterialType MaterialType) const;

	// ==================== QUERY API ====================
	
	/**
	 * Get material properties by type
	 * 
	 * @param MaterialType The forge material type to query
	 * @return Material properties struct (returns defaults if not found)
	 */
	UFUNCTION(BlueprintPure, Category = "Forge Palette|Query")
	FForgeMaterialProperties GetMaterialProperties(EForgeMaterialType MaterialType) const;

	/**
	 * Get all material definitions
	 * 
	 * @return Array of all material definitions
	 */
	UFUNCTION(BlueprintPure, Category = "Forge Palette|Query")
	const TArray<FForgeMaterialDefinition>& GetAllMaterialDefinitions() const { return MaterialDefinitions; }

	/**
	 * Check if a material type exists in this palette
	 * 
	 * @param MaterialType The forge material type to check
	 * @return True if material exists in palette
	 */
	UFUNCTION(BlueprintPure, Category = "Forge Palette|Query")
	bool HasMaterial(EForgeMaterialType MaterialType) const;

	/**
	 * Get the number of materials defined in this palette
	 * 
	 * @return Material count
	 */
	UFUNCTION(BlueprintPure, Category = "Forge Palette|Query")
	int32 GetMaterialCount() const { return MaterialDefinitions.Num(); }

	// ==================== DEFAULT PALETTE ====================
	
	/**
	 * Initialize this Data Asset with default palette values from the table.
	 * Useful for resetting to defaults or initializing new palettes.
	 */
	UFUNCTION(BlueprintCallable, Category = "Forge Palette|Management")
	void InitializeWithDefaults();

protected:
	/**
	 * Find material definition by type
	 * 
	 * @param MaterialType The forge material type to find
	 * @return Pointer to material definition, or nullptr if not found
	 */
	const FForgeMaterialDefinition* FindMaterial(EForgeMaterialType MaterialType) const;
};
