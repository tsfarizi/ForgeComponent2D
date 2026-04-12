// Copyright Teuku. All Rights Reserved.

#include "ForgeMaterialPaletteDA.h"
#include "MPC_Forge_Palette.h"

UForgeMaterialPaletteDA::UForgeMaterialPaletteDA()
{
	// Initialize with default palette on construction
	InitializeWithDefaults();
}

FLinearColor UForgeMaterialPaletteDA::GetColor(EForgeMaterialType MaterialType) const
{
	const FForgeMaterialDefinition* MaterialDef = FindMaterial(MaterialType);
	if (MaterialDef)
	{
		return MaterialDef->Properties.BaseColor;
	}
	return FLinearColor::Black;
}

float UForgeMaterialPaletteDA::GetRoughness(EForgeMaterialType MaterialType) const
{
	const FForgeMaterialDefinition* MaterialDef = FindMaterial(MaterialType);
	if (MaterialDef)
	{
		return MaterialDef->Properties.Roughness;
	}
	return 0.5f;
}

float UForgeMaterialPaletteDA::GetEmissive(EForgeMaterialType MaterialType) const
{
	const FForgeMaterialDefinition* MaterialDef = FindMaterial(MaterialType);
	if (MaterialDef)
	{
		return MaterialDef->Properties.EmissiveIntensity;
	}
	return 0.0f;
}

float UForgeMaterialPaletteDA::GetMetallic(EForgeMaterialType MaterialType) const
{
	const FForgeMaterialDefinition* MaterialDef = FindMaterial(MaterialType);
	if (MaterialDef)
	{
		return MaterialDef->Properties.Metallic;
	}
	return 0.0f;
}

bool UForgeMaterialPaletteDA::HasRimLight(EForgeMaterialType MaterialType) const
{
	const FForgeMaterialDefinition* MaterialDef = FindMaterial(MaterialType);
	if (MaterialDef)
	{
		return MaterialDef->Properties.bHasRimLight;
	}
	return false;
}

FForgeMaterialProperties UForgeMaterialPaletteDA::GetMaterialProperties(EForgeMaterialType MaterialType) const
{
	const FForgeMaterialDefinition* MaterialDef = FindMaterial(MaterialType);
	if (MaterialDef)
	{
		return MaterialDef->Properties;
	}

	// Return default properties if not found
	FForgeMaterialProperties DefaultProps;
	DefaultProps.DisplayName = FText::FromString(TEXT("Material Not Found"));
	return DefaultProps;
}

bool UForgeMaterialPaletteDA::HasMaterial(EForgeMaterialType MaterialType) const
{
	return FindMaterial(MaterialType) != nullptr;
}

void UForgeMaterialPaletteDA::InitializeWithDefaults()
{
	// Clear existing definitions
	MaterialDefinitions.Empty();

	// ==================== STRUCTURAL MATERIALS ====================
	
	// Anvil Carbon: #1A1A1B, Matte (0.7), No Glow
	{
		FForgeMaterialDefinition& Def = MaterialDefinitions.AddDefaulted_GetRef();
		Def.MaterialType = EForgeMaterialType::AnvilCarbon;
		Def.Properties.BaseColor = FLinearColor(0.102f, 0.102f, 0.106f, 1.0f);
		Def.Properties.Roughness = 0.7f;
		Def.Properties.Metallic = 0.0f;
		Def.Properties.EmissiveIntensity = 0.0f;
		Def.Properties.bHasRimLight = false;
		Def.Properties.bHasGlow = false;
		Def.Properties.DisplayName = FText::FromString(TEXT("Anvil Carbon"));
		Def.Properties.UsageDescription = FText::FromString(TEXT("Struktur dasar paron, palu, dan bingkai UI utama."));
	}

	// Tempered Steel: #464E56, Semi-Gloss (0.3), No Glow
	{
		FForgeMaterialDefinition& Def = MaterialDefinitions.AddDefaulted_GetRef();
		Def.MaterialType = EForgeMaterialType::TemperedSteel;
		Def.Properties.BaseColor = FLinearColor(0.275f, 0.306f, 0.337f, 1.0f);
		Def.Properties.Roughness = 0.3f;
		Def.Properties.Metallic = 0.0f;
		Def.Properties.EmissiveIntensity = 0.0f;
		Def.Properties.bHasRimLight = false;
		Def.Properties.bHasGlow = false;
		Def.Properties.DisplayName = FText::FromString(TEXT("Tempered Steel"));
		Def.Properties.UsageDescription = FText::FromString(TEXT("Bilah senjata, plat baju besi, dan aksen logam netral."));
	}

	// Noble Silver: #C0C0C0, High-Gloss (0.1), Subtle Rim
	{
		FForgeMaterialDefinition& Def = MaterialDefinitions.AddDefaulted_GetRef();
		Def.MaterialType = EForgeMaterialType::NobleSilver;
		Def.Properties.BaseColor = FLinearColor(0.753f, 0.753f, 0.753f, 1.0f);
		Def.Properties.Roughness = 0.1f;
		Def.Properties.Metallic = 0.0f;
		Def.Properties.EmissiveIntensity = 0.0f;
		Def.Properties.bHasRimLight = true;
		Def.Properties.bHasGlow = false;
		Def.Properties.DisplayName = FText::FromString(TEXT("Noble Silver"));
		Def.Properties.UsageDescription = FText::FromString(TEXT("Senjata kualitas tinggi, ukiran mewah, atau koin perak."));
	}

	// Mastery Gold: #FFD700, Metallic (0.2), Soft Glow
	{
		FForgeMaterialDefinition& Def = MaterialDefinitions.AddDefaulted_GetRef();
		Def.MaterialType = EForgeMaterialType::MasteryGold;
		Def.Properties.BaseColor = FLinearColor(1.0f, 0.843f, 0.0f, 1.0f);
		Def.Properties.Roughness = 0.2f;
		Def.Properties.Metallic = 0.2f;
		Def.Properties.EmissiveIntensity = 5.0f;
		Def.Properties.bHasRimLight = true;
		Def.Properties.bHasGlow = true;
		Def.Properties.DisplayName = FText::FromString(TEXT("Mastery Gold"));
		Def.Properties.UsageDescription = FText::FromString(TEXT("Mata uang koin emas, item legendaris, atau status aktif."));
	}

	// Aged Bronze: #614E3F, Worn (0.5), No Glow
	{
		FForgeMaterialDefinition& Def = MaterialDefinitions.AddDefaulted_GetRef();
		Def.MaterialType = EForgeMaterialType::AgedBronze;
		Def.Properties.BaseColor = FLinearColor(0.380f, 0.306f, 0.247f, 1.0f);
		Def.Properties.Roughness = 0.5f;
		Def.Properties.Metallic = 0.0f;
		Def.Properties.EmissiveIntensity = 0.0f;
		Def.Properties.bHasRimLight = false;
		Def.Properties.bHasGlow = false;
		Def.Properties.DisplayName = FText::FromString(TEXT("Aged Bronze"));
		Def.Properties.UsageDescription = FText::FromString(TEXT("Pelindung tangan (crossguard), koin perunggu, baut."));
	}

	// Tanned Hide: #7B3F00, Non-Metal (0.9), No Glow
	{
		FForgeMaterialDefinition& Def = MaterialDefinitions.AddDefaulted_GetRef();
		Def.MaterialType = EForgeMaterialType::TannedHide;
		Def.Properties.BaseColor = FLinearColor(0.482f, 0.247f, 0.0f, 1.0f);
		Def.Properties.Roughness = 0.9f;
		Def.Properties.Metallic = 0.0f;
		Def.Properties.EmissiveIntensity = 0.0f;
		Def.Properties.bHasRimLight = false;
		Def.Properties.bHasGlow = false;
		Def.Properties.DisplayName = FText::FromString(TEXT("Tanned Hide"));
		Def.Properties.UsageDescription = FText::FromString(TEXT("Lilitan gagang kulit, tas penyimpanan, elemen organik."));
	}

	// Charred Oak: #281E15, Rough (0.85), No Glow
	{
		FForgeMaterialDefinition& Def = MaterialDefinitions.AddDefaulted_GetRef();
		Def.MaterialType = EForgeMaterialType::CharredOak;
		Def.Properties.BaseColor = FLinearColor(0.157f, 0.118f, 0.082f, 1.0f);
		Def.Properties.Roughness = 0.85f;
		Def.Properties.Metallic = 0.0f;
		Def.Properties.EmissiveIntensity = 0.0f;
		Def.Properties.bHasRimLight = false;
		Def.Properties.bHasGlow = false;
		Def.Properties.DisplayName = FText::FromString(TEXT("Charred Oak"));
		Def.Properties.UsageDescription = FText::FromString(TEXT("Gagang kayu palu godam, struktur meja kerja."));
	}

	// ==================== HEAT STATE MATERIALS ====================
	
	// Cherry Red: #9B111E, Mid-Glow (2.0 Emissive) - Heating
	{
		FForgeMaterialDefinition& Def = MaterialDefinitions.AddDefaulted_GetRef();
		Def.MaterialType = EForgeMaterialType::CherryRed;
		Def.Properties.BaseColor = FLinearColor(0.608f, 0.067f, 0.118f, 1.0f);
		Def.Properties.Roughness = 0.5f;
		Def.Properties.Metallic = 0.0f;
		Def.Properties.EmissiveIntensity = 2.0f;
		Def.Properties.bHasRimLight = false;
		Def.Properties.bHasGlow = true;
		Def.Properties.DisplayName = FText::FromString(TEXT("Cherry Red"));
		Def.Properties.UsageDescription = FText::FromString(TEXT("Tahap awal pemanasan logam (Status: Heating)."));
	}

	// Molten Orange: #FF4500, High-Glow (10.0 Emissive) - Ready to Forge
	{
		FForgeMaterialDefinition& Def = MaterialDefinitions.AddDefaulted_GetRef();
		Def.MaterialType = EForgeMaterialType::MoltenOrange;
		Def.Properties.BaseColor = FLinearColor(1.0f, 0.271f, 0.0f, 1.0f);
		Def.Properties.Roughness = 0.4f;
		Def.Properties.Metallic = 0.0f;
		Def.Properties.EmissiveIntensity = 10.0f;
		Def.Properties.bHasRimLight = false;
		Def.Properties.bHasGlow = true;
		Def.Properties.DisplayName = FText::FromString(TEXT("Molten Orange"));
		Def.Properties.UsageDescription = FText::FromString(TEXT("Logam siap tempa (Status: Ready to Forge)."));
	}

	// White Heat: #FFF5E1, Extreme-Glow (50.0 Emissive) - Critical Heat
	{
		FForgeMaterialDefinition& Def = MaterialDefinitions.AddDefaulted_GetRef();
		Def.MaterialType = EForgeMaterialType::WhiteHeat;
		Def.Properties.BaseColor = FLinearColor(1.0f, 0.961f, 0.882f, 1.0f);
		Def.Properties.Roughness = 0.3f;
		Def.Properties.Metallic = 0.0f;
		Def.Properties.EmissiveIntensity = 50.0f;
		Def.Properties.bHasRimLight = false;
		Def.Properties.bHasGlow = true;
		Def.Properties.DisplayName = FText::FromString(TEXT("White Heat"));
		Def.Properties.UsageDescription = FText::FromString(TEXT("Suhu ekstrem (Status: Critical Heat)."));
	}

	// ==================== EFFECT MATERIALS ====================
	
	// Quench Blue: #005B96, Clear (0.2), Ambient Glow
	{
		FForgeMaterialDefinition& Def = MaterialDefinitions.AddDefaulted_GetRef();
		Def.MaterialType = EForgeMaterialType::QuenchBlue;
		Def.Properties.BaseColor = FLinearColor(0.0f, 0.357f, 0.588f, 1.0f);
		Def.Properties.Roughness = 0.2f;
		Def.Properties.Metallic = 0.2f;
		Def.Properties.EmissiveIntensity = 3.0f;
		Def.Properties.bHasRimLight = true;
		Def.Properties.bHasGlow = true;
		Def.Properties.DisplayName = FText::FromString(TEXT("Quench Blue"));
		Def.Properties.UsageDescription = FText::FromString(TEXT("Tombol konfirmasi, air pendingin, mana/stamina."));
	}

	// Brittle Rust: #B7410E, Gritty (1.0), No Glow
	{
		FForgeMaterialDefinition& Def = MaterialDefinitions.AddDefaulted_GetRef();
		Def.MaterialType = EForgeMaterialType::BrittleRust;
		Def.Properties.BaseColor = FLinearColor(0.718f, 0.255f, 0.055f, 1.0f);
		Def.Properties.Roughness = 1.0f;
		Def.Properties.Metallic = 0.0f;
		Def.Properties.EmissiveIntensity = 0.0f;
		Def.Properties.bHasRimLight = false;
		Def.Properties.bHasGlow = false;
		Def.Properties.DisplayName = FText::FromString(TEXT("Brittle Rust"));
		Def.Properties.UsageDescription = FText::FromString(TEXT("Peringatan durabilitas rendah, kegagalan crafting."));
	}

	PaletteName = FText::FromString(TEXT("Default Forge Palette"));
	PaletteDescription = FText::FromString(TEXT("Default material palette with all 12 forge material identities."));

	UE_LOG(LogTemp, Log, TEXT("ForgeMaterialPaletteDA: Initialized with %d default material definitions."), MaterialDefinitions.Num());
}

const FForgeMaterialDefinition* UForgeMaterialPaletteDA::FindMaterial(EForgeMaterialType MaterialType) const
{
	for (const FForgeMaterialDefinition& MaterialDef : MaterialDefinitions)
	{
		if (MaterialDef.MaterialType == MaterialType)
		{
			return &MaterialDef;
		}
	}
	return nullptr;
}
