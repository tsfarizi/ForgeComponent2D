// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MPC_Forge_Palette.generated.h"

/**
 * Forge Material Type Enumeration
 * Defines the 12 semantic material identities used in the forging system.
 */
UENUM(BlueprintType, Category = "Forge Materials")
enum class EForgeMaterialType : uint8
{
	AnvilCarbon     UMETA(DisplayName = "Anvil Carbon", Tooltip = "Struktur dasar paron, palu, dan bingkai UI utama."),
	TemperedSteel   UMETA(DisplayName = "Tempered Steel", Tooltip = "Bilah senjata, plat baju besi, dan aksen logam netral."),
	NobleSilver     UMETA(DisplayName = "Noble Silver", Tooltip = "Senjata kualitas tinggi, ukiran mewah, atau koin perak."),
	MasteryGold     UMETA(DisplayName = "Mastery Gold", Tooltip = "Mata uang koin emas, item legendaris, atau status aktif."),
	AgedBronze      UMETA(DisplayName = "Aged Bronze", Tooltip = "Pelindung tangan (crossguard), koin perunggu, baut."),
	TannedHide      UMETA(DisplayName = "Tanned Hide", Tooltip = "Lilitan gagang kulit, tas penyimpanan, elemen organik."),
	CharredOak      UMETA(DisplayName = "Charred Oak", Tooltip = "Gagang kayu palu godam, struktur meja kerja."),
	CherryRed       UMETA(DisplayName = "Cherry Red", Tooltip = "Tahap awal pemanasan logam (Status: Heating)."),
	MoltenOrange    UMETA(DisplayName = "Molten Orange", Tooltip = "Logam siap tempa (Status: Ready to Forge)."),
	WhiteHeat       UMETA(DisplayName = "White Heat", Tooltip = "Suhu ekstrem (Status: Critical Heat)."),
	QuenchBlue      UMETA(DisplayName = "Quench Blue", Tooltip = "Tombol konfirmasi, air pendingin, mana/stamina."),
	BrittleRust     UMETA(DisplayName = "Brittle Rust", Tooltip = "Peringatan durabilitas rendah, kegagalan crafting.")
};

/**
 * Forge Material Properties Struct
 * Encapsulates all physical and visual properties of a forge material.
 */
USTRUCT(BlueprintType)
struct FForgeMaterialProperties
{
	GENERATED_BODY()

	/** Base color of the material (Hex to LinearColor conversion) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FLinearColor BaseColor = FLinearColor::Black;

	/** Surface roughness (0.0 = mirror, 1.0 = completely matte) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float Roughness = 0.5f;

	/** Metallic property (0.0 = non-metal, 1.0 = full metal) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float Metallic = 0.0f;

	/** Emissive intensity for glowing materials (0.0 = no glow) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material", meta = (ClampMin = "0.0"))
	float EmissiveIntensity = 0.0f;

	/** Whether this material has rim lighting effect */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	bool bHasRimLight = false;

	/** Whether this material has ambient glow effect */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	bool bHasGlow = false;

	/** Display name for editor visualization */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FText DisplayName = FText::GetEmpty();

	/** Semantic usage description */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FText UsageDescription = FText::GetEmpty();
};

/**
 * MPC_Forge_Palette - Parameter Name Registry
 * 
 * Provides static parameter name constants and helper functions for the 
 * Forge Material MPC system. This class does NOT store values directly -
 * instead, it serves as a registry for parameter names used by 
 * UMaterialParameterCollection assets created in the editor.
 * 
 * Usage:
 * 1. Create UMaterialParameterCollection asset in editor (named MPC_Forge_Palette)
 * 2. Add Vector Parameters (12 colors) and Scalar Parameters (roughness, emissive, etc.)
 * 3. Use parameter names from this class when setting up the MPC
 * 4. UForgeMaterialPaletteDA injects values into the MPC at runtime
 * 
 * Design Rationale:
 * - UMaterialParameterCollection should be editor-created assets, not C++ classes
 * - This avoids linker errors from improper UMaterialParameterCollection subclassing
 * - Separation of Concerns: Data Asset (logic) vs MPC (storage) vs Registry (names)
 */
UCLASS(BlueprintType)
class FORGECOMPONENT2D_API UMPC_Forge_Palette : public UObject
{
	GENERATED_BODY()

public:
	// ==================== PARAMETER NAME CONSTANTS ====================
	// Use these names when configuring the MPC asset in the editor

	// Color Parameter Names (Vector Parameters in MPC)
	static const FName Param_AnvilCarbon;
	static const FName Param_TemperedSteel;
	static const FName Param_NobleSilver;
	static const FName Param_MasteryGold;
	static const FName Param_AgedBronze;
	static const FName Param_TannedHide;
	static const FName Param_CharredOak;
	static const FName Param_CherryRed;
	static const FName Param_MoltenOrange;
	static const FName Param_WhiteHeat;
	static const FName Param_QuenchBlue;
	static const FName Param_BrittleRust;

	// Roughness Parameter Names (Scalar Parameters in MPC)
	static const FName Param_AnvilCarbon_Roughness;
	static const FName Param_TemperedSteel_Roughness;
	static const FName Param_NobleSilver_Roughness;
	static const FName Param_MasteryGold_Roughness;
	static const FName Param_AgedBronze_Roughness;
	static const FName Param_TannedHide_Roughness;
	static const FName Param_CharredOak_Roughness;
	static const FName Param_CherryRed_Roughness;
	static const FName Param_MoltenOrange_Roughness;
	static const FName Param_WhiteHeat_Roughness;
	static const FName Param_QuenchBlue_Roughness;
	static const FName Param_BrittleRust_Roughness;

	// Emissive Parameter Names (Scalar Parameters in MPC)
	static const FName Param_CherryRed_Emissive;
	static const FName Param_MoltenOrange_Emissive;
	static const FName Param_WhiteHeat_Emissive;
	static const FName Param_QuenchBlue_Emissive;
	static const FName Param_MasteryGold_Emissive;

	// Metallic Parameter Names (Scalar Parameters in MPC)
	static const FName Param_MasteryGold_Metallic;
	static const FName Param_QuenchBlue_Metallic;

	// Rim Light Parameter Names (Scalar Parameters in MPC, 0.0 or 1.0)
	static const FName Param_NobleSilver_bRimLight;
	static const FName Param_MasteryGold_bRimLight;
	static const FName Param_QuenchBlue_bRimLight;

	// ==================== HELPER FUNCTIONS ====================
	
	/**
	 * Get all parameter names as an array (useful for validation)
	 * @return Array of all MPC parameter names used by Forge Palette
	 */
	UFUNCTION(BlueprintPure, Category = "Forge Palette|Registry")
	static TArray<FName> GetAllParameterNames();

	/**
	 * Get color parameter name for a specific material type
	 * @param MaterialType The forge material type
	 * @return The parameter name used in the MPC
	 */
	UFUNCTION(BlueprintPure, Category = "Forge Palette|Registry")
	static FName GetColorParamName(EForgeMaterialType MaterialType);

	/**
	 * Get roughness parameter name for a specific material type
	 * @param MaterialType The forge material type
	 * @return The parameter name used in the MPC
	 */
	UFUNCTION(BlueprintPure, Category = "Forge Palette|Registry")
	static FName GetRoughnessParamName(EForgeMaterialType MaterialType);

	/**
	 * Get emissive parameter name for a specific material type
	 * @param MaterialType The forge material type
	 * @return The parameter name used in the MPC (returns NAME_None if material has no emissive)
	 */
	UFUNCTION(BlueprintPure, Category = "Forge Palette|Registry")
	static FName GetEmissiveParamName(EForgeMaterialType MaterialType);
};
