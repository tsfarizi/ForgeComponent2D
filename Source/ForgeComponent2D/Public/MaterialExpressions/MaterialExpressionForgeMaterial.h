// Copyright Teuku. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Materials/MaterialExpression.h"
#include "ForgeMaterialPaletteDA.h"
#include "MaterialExpressionForgeMaterial.generated.h"

/**
 * Material Function: Forge Material (All-in-One)
 * 
 * Langsung tersedia di Material Editor!
 * 
 * Features:
 * - 4 Output Pins: Color, Roughness, Emissive, Metallic
 * - Color preview ditampilkan langsung di node
 * - Editable via node details
 * 
 * ZERO SETUP REQUIRED!
 */
UCLASS(MinimalAPI, collapsecategories, hidecategories=Object)
class UMaterialExpressionForgeMaterial : public UMaterialExpression
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category = Material, meta = (DisplayName = "Material Type"))
	EForgeMaterialType MaterialType;

	UPROPERTY(EditAnywhere, Category = Material)
	FLinearColor PreviewColor;

	//~ Begin UMaterialExpression Interface
#if WITH_EDITOR
	virtual int32 Compile(FMaterialCompiler* Compiler, int32 OutputIndex) override;
	virtual void GetCaption(TArray<FString>& OutCaptions) const override;
#endif
	//~ End UMaterialExpression Interface
};
