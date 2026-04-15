// Copyright Teuku. All Rights Reserved.

#include "MaterialExpressions/MaterialExpressionForgeMaterial.h"
#include "MaterialCompiler.h"

UMaterialExpressionForgeMaterial::UMaterialExpressionForgeMaterial(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITORONLY_DATA
	MenuCategories.Add(FText::FromString(TEXT("Forge")));
#endif
	
	MaterialType = EForgeMaterialType::MoltenOrange;
	PreviewColor = FLinearColor::Black;

#if WITH_EDITORONLY_DATA
	// Setup 5 outputs: Color, Roughness, Emissive, Metallic, Final (Color + Emissive combined)
	Outputs.Reset();
	Outputs.AddZeroed(5);
	
	// Output 0: Color (RGB)
	Outputs[0].OutputName = TEXT("Color");
	Outputs[0].MaskR = true;
	Outputs[0].MaskG = true;
	Outputs[0].MaskB = true;
	
	// Output 1: Roughness
	Outputs[1].OutputName = TEXT("Roughness");
	
	// Output 2: Emissive
	Outputs[2].OutputName = TEXT("Emissive");
	
	// Output 3: Metallic
	Outputs[3].OutputName = TEXT("Metallic");
	
	// Output 4: Final (BaseColor + Emissive combined)
	Outputs[4].OutputName = TEXT("Final");
	Outputs[4].MaskR = true;
	Outputs[4].MaskG = true;
	Outputs[4].MaskB = true;
#endif
}

#if WITH_EDITOR
int32 UMaterialExpressionForgeMaterial::Compile(FMaterialCompiler* Compiler, int32 OutputIndex)
{
	// Get material properties from default palette
	UForgeMaterialPaletteDA* PaletteDA = NewObject<UForgeMaterialPaletteDA>(GetTransientPackage());
	PaletteDA->InitializeWithDefaults();
	
	FLinearColor Color = PaletteDA->GetColor(MaterialType);
	float Roughness = PaletteDA->GetRoughness(MaterialType);
	float Emissive = PaletteDA->GetEmissive(MaterialType);
	float Metallic = PaletteDA->GetMetallic(MaterialType);
	
	PreviewColor = Color;

	// Route to correct output
	switch (OutputIndex)
	{
		case 0: // Color
			return Compiler->Constant3(Color.R, Color.G, Color.B);
			
		case 1: // Roughness
			return Compiler->Constant(Roughness);
			
		case 2: // Emissive
			return Compiler->Constant(Emissive);
			
		case 3: // Metallic
			return Compiler->Constant(Metallic);
			
		case 4: // Final (Color * Emissive + Color)
		{
			// Color with emissive glow baked in
			// Final = Color + (Color * EmissiveIntensity)
			float GlowMultiplier = 1.0f + Emissive;
			return Compiler->Constant3(Color.R * GlowMultiplier, Color.G * GlowMultiplier, Color.B * GlowMultiplier);
		}
			
		default: 
			return Compiler->Constant(0.0f);
	}
}

void UMaterialExpressionForgeMaterial::GetCaption(TArray<FString>& OutCaptions) const
{
	FString MatName = StaticEnum<EForgeMaterialType>()->GetDisplayNameTextByValue((int64)MaterialType).ToString();
	OutCaptions.Add(MatName);
}
#endif
