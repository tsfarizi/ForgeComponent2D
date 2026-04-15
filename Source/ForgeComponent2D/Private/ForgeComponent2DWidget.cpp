// Copyright Teuku. All Rights Reserved.

#include "ForgeComponent2DWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetMathLibrary.h"
#include "ForgeMaterialPaletteDA.h"
#include "Engine/Texture2D.h"

// ==================== INITIALIZATION ====================

void UForgeComponent2DWidget::Initialize()
{
	// Store original position
	if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(this->Slot))
	{
		OriginalPosition = CanvasSlot->GetPosition();
	}

	// Create dynamic material
	CreateDynamicMaterial();

	// Apply initial effects
	ApplyEffectsToMaterial();
}

// ==================== LIFECYCLE ====================

void UForgeComponent2DWidget::OnAddedToViewport()
{
	// Initialize when added to viewport
	Initialize();
}

void UForgeComponent2DWidget::TickAnimation(float DeltaTime)
{
	// Update bounce animation
	if (bIsBouncing && bEnableBounce)
	{
		UpdateBounce(DeltaTime);
	}
}

// ==================== SHADOW EFFECTS ====================

void UForgeComponent2DWidget::ApplyShadow(const FForgeShadowConfig& Config)
{
	ShadowConfig = Config;
	UpdateShadow();
}

void UForgeComponent2DWidget::ApplyShadowPreset(EForgeShadowStyle Style)
{
	switch (Style)
	{
	case EForgeShadowStyle::SoftOuter:
		ShadowConfig.ShadowOffset = FVector2D(0.0f, 8.0f);
		ShadowConfig.ShadowBlur = 15.0f;
		ShadowConfig.ShadowSpread = 5.0f;
		ShadowConfig.bEnableSecondaryShadow = false;
		break;

	case EForgeShadowStyle::HardOuter:
		ShadowConfig.ShadowOffset = FVector2D(0.0f, 10.0f);
		ShadowConfig.ShadowBlur = 2.0f;
		ShadowConfig.ShadowSpread = 3.0f;
		ShadowConfig.bEnableSecondaryShadow = false;
		break;

	case EForgeShadowStyle::InnerSoft:
		ShadowConfig.ShadowOffset = FVector2D(0.0f, 0.0f);
		ShadowConfig.ShadowBlur = 20.0f;
		ShadowConfig.ShadowSpread = -10.0f;
		ShadowConfig.bEnableSecondaryShadow = false;
		break;

	case EForgeShadowStyle::InnerHard:
		ShadowConfig.ShadowOffset = FVector2D(0.0f, 0.0f);
		ShadowConfig.ShadowBlur = 3.0f;
		ShadowConfig.ShadowSpread = -5.0f;
		ShadowConfig.bEnableSecondaryShadow = false;
		break;

	case EForgeShadowStyle::DoubleLayer:
		ShadowConfig.ShadowOffset = FVector2D(0.0f, 6.0f);
		ShadowConfig.ShadowBlur = 10.0f;
		ShadowConfig.ShadowSpread = 3.0f;
		ShadowConfig.bEnableSecondaryShadow = true;
		ShadowConfig.SecondaryShadowOffset = FVector2D(0.0f, 18.0f);
		ShadowConfig.SecondaryShadowBlur = 30.0f;
		break;

	case EForgeShadowStyle::Custom:
		// No changes, user configured
		break;
	}

	UpdateShadow();
}

void UForgeComponent2DWidget::SetShadowEnabled(bool bEnabled)
{
	bEnableShadow = bEnabled;
	UpdateShadow();
}

void UForgeComponent2DWidget::SetShadowOpacity(float Opacity)
{
	CurrentShadowOpacity = FMath::Clamp(Opacity, 0.0f, 1.0f);
	UpdateShadow();
}

// ==================== BOUNCE ANIMATION ====================

void UForgeComponent2DWidget::PlayBounce()
{
	if (!bEnableBounce)
	{
		return;
	}

	bIsBouncing = true;
	BounceElapsedTime = -BounceConfig.StartDelay; // Negative to account for start delay
	CurrentBounceCount = 0;

	// Store original position if not already stored
	if (OriginalPosition == FVector2D::ZeroVector)
	{
		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(this->Slot))
		{
			OriginalPosition = CanvasSlot->GetPosition();
		}
	}
}

void UForgeComponent2DWidget::StopBounce(bool bResetPosition)
{
	bIsBouncing = false;
	BounceElapsedTime = 0.0f;
	CurrentBounceCount = 0;

	// Reset position if requested
	if (bResetPosition && this->Slot)
	{
		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(this->Slot))
		{
			CanvasSlot->SetPosition(OriginalPosition);
		}
		
		// Reset scale if squash/stretch was applied
		if (BounceConfig.bEnableSquashStretch)
		{
			SetRenderScale(FVector2D(1.0f, 1.0f));
		}
	}
}

void UForgeComponent2DWidget::ApplyBouncePreset(EForgeBounceStyle Style)
{
	BounceConfig.BounceStyle = Style;

	switch (Style)
	{
	case EForgeBounceStyle::Soft:
		BounceConfig.BounceHeight = 10.0f;
		BounceConfig.BounceDuration = 1.5f;
		BounceConfig.bEnableSquashStretch = false;
		break;

	case EForgeBounceStyle::Medium:
		BounceConfig.BounceHeight = 20.0f;
		BounceConfig.BounceDuration = 1.0f;
		BounceConfig.bEnableSquashStretch = true;
		BounceConfig.SquashStretchIntensity = 0.15f;
		break;

	case EForgeBounceStyle::Hard:
		BounceConfig.BounceHeight = 35.0f;
		BounceConfig.BounceDuration = 0.8f;
		BounceConfig.bEnableSquashStretch = true;
		BounceConfig.SquashStretchIntensity = 0.25f;
		break;

	case EForgeBounceStyle::Elastic:
		BounceConfig.BounceHeight = 25.0f;
		BounceConfig.BounceDuration = 1.2f;
		BounceConfig.BounceCount = 3;
		BounceConfig.bEnableSquashStretch = true;
		BounceConfig.SquashStretchIntensity = 0.2f;
		break;

	case EForgeBounceStyle::None:
	case EForgeBounceStyle::Custom:
		// No changes
		break;
	}
}

// ==================== FAKE METALLIC ====================

void UForgeComponent2DWidget::ApplyMetallic(const FForgeMetallicConfig& Config)
{
	MetallicConfig = Config;
	bEnableMetallic = true;
	UpdateMetallic();
}

void UForgeComponent2DWidget::ApplyMetallicPreset(EForgeMetallicStyle Style)
{
	MetallicConfig.MetallicStyle = Style;

	switch (Style)
	{
	case EForgeMetallicStyle::Brushed:
		MetallicConfig.MetallicIntensity = 0.6f;
		MetallicConfig.ReflectionSharpness = 0.4f;
		MetallicConfig.ReflectionCount = 5;
		MetallicConfig.BrushedLineSpacing = 5.0f;
		break;

	case EForgeMetallicStyle::Polished:
		MetallicConfig.MetallicIntensity = 0.9f;
		MetallicConfig.ReflectionSharpness = 0.9f;
		MetallicConfig.ReflectionCount = 3;
		break;

	case EForgeMetallicStyle::Hammered:
		MetallicConfig.MetallicIntensity = 0.7f;
		MetallicConfig.ReflectionSharpness = 0.5f;
		MetallicConfig.ReflectionCount = 8;
		break;

	case EForgeMetallicStyle::Anisotropic:
		MetallicConfig.MetallicIntensity = 0.85f;
		MetallicConfig.ReflectionSharpness = 0.8f;
		MetallicConfig.ReflectionCount = 2;
		MetallicConfig.AnisotropicAngle = 45.0f;
		break;

	case EForgeMetallicStyle::None:
		bEnableMetallic = false;
		break;

	case EForgeMetallicStyle::Custom:
		// No changes
		break;
	}

	UpdateMetallic();
}

void UForgeComponent2DWidget::SetMetallicIntensity(float Intensity)
{
	MetallicConfig.MetallicIntensity = FMath::Clamp(Intensity, 0.0f, 1.0f);
	UpdateMetallic();
}

// ==================== FAKE ROUGHNESS ====================

void UForgeComponent2DWidget::ApplyRoughness(const FForgeRoughnessConfig& Config)
{
	RoughnessConfig = Config;
	bEnableRoughness = true;
	UpdateRoughness();
}

void UForgeComponent2DWidget::ApplyRoughnessPreset(EForgeRoughnessStyle Style)
{
	RoughnessConfig.RoughnessStyle = Style;

	switch (Style)
	{
	case EForgeRoughnessStyle::Smooth:
		RoughnessConfig.RoughnessValue = 0.1f;
		RoughnessConfig.NoiseIntensity = 0.02f;
		RoughnessConfig.SpecularIntensity = 0.9f;
		RoughnessConfig.SpecularSharpness = 0.8f;
		break;

	case EForgeRoughnessStyle::SemiSmooth:
		RoughnessConfig.RoughnessValue = 0.3f;
		RoughnessConfig.NoiseIntensity = 0.05f;
		RoughnessConfig.SpecularIntensity = 0.7f;
		RoughnessConfig.SpecularSharpness = 0.6f;
		break;

	case EForgeRoughnessStyle::Matte:
		RoughnessConfig.RoughnessValue = 0.5f;
		RoughnessConfig.NoiseIntensity = 0.1f;
		RoughnessConfig.SpecularIntensity = 0.5f;
		RoughnessConfig.SpecularSharpness = 0.3f;
		break;

	case EForgeRoughnessStyle::Rough:
		RoughnessConfig.RoughnessValue = 0.8f;
		RoughnessConfig.NoiseIntensity = 0.2f;
		RoughnessConfig.SpecularIntensity = 0.2f;
		RoughnessConfig.SpecularSharpness = 0.1f;
		break;

	case EForgeRoughnessStyle::Custom:
		// No changes
		break;
	}

	UpdateRoughness();
}

void UForgeComponent2DWidget::SetRoughnessValue(float Value)
{
	RoughnessConfig.RoughnessValue = FMath::Clamp(Value, 0.0f, 1.0f);
	UpdateRoughness();
}

// ==================== FORGE MATERIAL INTEGRATION ====================

void UForgeComponent2DWidget::ApplyForgeMaterialColor(EForgeMaterialType MaterialType, bool bIncludeMetallic, bool bIncludeRoughness)
{
	ForgeMaterialType = MaterialType;

	// Create temporary palette to get values
	UForgeMaterialPaletteDA* Palette = NewObject<UForgeMaterialPaletteDA>();
	Palette->InitializeWithDefaults();

	if (Palette->HasMaterial(MaterialType))
	{
		FForgeMaterialProperties Props = Palette->GetMaterialProperties(MaterialType);

		// Apply base color
		SetMaterialParameterColor(FName("BaseColor"), Props.BaseColor);

		// Apply metallic if requested
		if (bIncludeMetallic)
		{
			MetallicConfig.MetallicIntensity = Props.Metallic;
			UpdateMetallic();
		}

		// Apply roughness if requested
		if (bIncludeRoughness)
		{
			RoughnessConfig.RoughnessValue = Props.Roughness;
			UpdateRoughness();
		}
	}
}

// ==================== INTERNAL METHODS ====================

void UForgeComponent2DWidget::CreateDynamicMaterial()
{
	// Access the Background property from UBorder
	if (Background.GetResourceObject())
	{
		if (UMaterialInterface* Material = Cast<UMaterialInterface>(Background.GetResourceObject()))
		{
			OriginalMaterial = Cast<UMaterial>(Material);
			
			// Create dynamic material instance
			if (OriginalMaterial)
			{
				DynamicMaterial = UMaterialInstanceDynamic::Create(OriginalMaterial, this);
				
				// Update the background brush to point to the dynamic material
				Background.SetResourceObject(DynamicMaterial);
			}
		}
	}

	// If no material was set, log warning
	if (!DynamicMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("ForgeComponent2D: No material found on Border component. Please assign a material to the Brush property."));
	}
}

void UForgeComponent2DWidget::UpdateShadow()
{
	if (!DynamicMaterial)
	{
		return;
	}

	// Primary shadow parameters
	SetMaterialParameter(FName("ShadowEnabled"), bEnableShadow ? 1.0f : 0.0f);
	SetMaterialParameterVector(FName("ShadowOffset"), ShadowConfig.ShadowOffset);
	SetMaterialParameter(FName("ShadowBlur"), ShadowConfig.ShadowBlur);
	SetMaterialParameterColor(FName("ShadowColor"), ShadowConfig.ShadowColor * CurrentShadowOpacity);
	SetMaterialParameter(FName("ShadowSpread"), ShadowConfig.ShadowSpread);
	SetMaterialParameter(FName("ShadowOpacity"), CurrentShadowOpacity);

	// Secondary shadow parameters
	SetMaterialParameter(FName("bEnableSecondaryShadow"), ShadowConfig.bEnableSecondaryShadow ? 1.0f : 0.0f);
	SetMaterialParameterVector(FName("SecondaryShadowOffset"), ShadowConfig.SecondaryShadowOffset);
	SetMaterialParameter(FName("SecondaryShadowBlur"), ShadowConfig.SecondaryShadowBlur);
	SetMaterialParameterColor(FName("SecondaryShadowColor"), ShadowConfig.SecondaryShadowColor * CurrentShadowOpacity);
}

void UForgeComponent2DWidget::UpdateMetallic()
{
	if (!DynamicMaterial)
	{
		return;
	}

	if (!bEnableMetallic)
	{
		SetMaterialParameter(FName("MetallicEnabled"), 0.0f);
		return;
	}

	// Metallic style as integer for material switch
	int32 StyleIndex = static_cast<int32>(MetallicConfig.MetallicStyle);
	SetMaterialParameter(FName("MetallicStyle"), static_cast<float>(StyleIndex));
	SetMaterialParameter(FName("MetallicEnabled"), 1.0f);
	SetMaterialParameter(FName("MetallicIntensity"), MetallicConfig.MetallicIntensity);
	SetMaterialParameterColor(FName("ReflectionTint"), MetallicConfig.ReflectionTint);
	SetMaterialParameter(FName("ReflectionCount"), static_cast<float>(MetallicConfig.ReflectionCount));
	SetMaterialParameter(FName("ReflectionSharpness"), MetallicConfig.ReflectionSharpness);
	SetMaterialParameter(FName("AnisotropicAngle"), FMath::DegreesToRadians(MetallicConfig.AnisotropicAngle));
	SetMaterialParameter(FName("BrushedLineSpacing"), MetallicConfig.BrushedLineSpacing);
}

void UForgeComponent2DWidget::UpdateRoughness()
{
	if (!DynamicMaterial)
	{
		return;
	}

	if (!bEnableRoughness)
	{
		SetMaterialParameter(FName("RoughnessEnabled"), 0.0f);
		return;
	}

	// Roughness style as integer for material switch
	int32 StyleIndex = static_cast<int32>(RoughnessConfig.RoughnessStyle);
	SetMaterialParameter(FName("RoughnessStyle"), static_cast<float>(StyleIndex));
	SetMaterialParameter(FName("RoughnessEnabled"), 1.0f);
	SetMaterialParameter(FName("RoughnessValue"), RoughnessConfig.RoughnessValue);
	SetMaterialParameter(FName("NoiseIntensity"), RoughnessConfig.NoiseIntensity);
	SetMaterialParameter(FName("NoiseScale"), RoughnessConfig.NoiseScale);
	SetMaterialParameter(FName("SpecularIntensity"), RoughnessConfig.SpecularIntensity);
	SetMaterialParameter(FName("SpecularSharpness"), RoughnessConfig.SpecularSharpness);
}

void UForgeComponent2DWidget::UpdateBounce(float DeltaTime)
{
	BounceElapsedTime += DeltaTime;

	// Check if we should stop (if bounce count is limited)
	if (BounceConfig.BounceCount > 0 && CurrentBounceCount >= BounceConfig.BounceCount)
	{
		StopBounce(true);
		return;
	}

	// Check if current bounce cycle is complete
	float CycleTime = BounceElapsedTime - FMath::Max(0.0f, -BounceConfig.StartDelay);
	if (CycleTime >= BounceConfig.BounceDuration)
	{
		BounceElapsedTime = 0.0f;
		CurrentBounceCount++;
		
		// Check again if we should stop
		if (BounceConfig.BounceCount > 0 && CurrentBounceCount >= BounceConfig.BounceCount)
		{
			StopBounce(true);
			return;
		}
	}

	// Calculate bounce value (only if elapsed time is positive)
	if (BounceElapsedTime > 0)
	{
		float BounceValue = CalculateBounceValue(
			BounceElapsedTime,
			BounceConfig.BounceDuration,
			BounceConfig.BounceHeight
		);

		// Apply vertical offset
		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(this->Slot))
		{
			FVector2D NewPosition = OriginalPosition;
			NewPosition.Y -= BounceValue;
			CanvasSlot->SetPosition(NewPosition);
		}

		// Apply squash and stretch
		if (BounceConfig.bEnableSquashStretch)
		{
			float SquashStretch = CalculateSquashStretch(BounceValue, BounceConfig.BounceHeight);
			float StretchX = 1.0f + (SquashStretch * BounceConfig.SquashStretchIntensity);
			float StretchY = 1.0f - (SquashStretch * BounceConfig.SquashStretchIntensity * 0.5f);
			
			SetRenderScale(FVector2D(StretchX, StretchY));
		}
	}
}

float UForgeComponent2DWidget::CalculateBounceValue(float Time, float Duration, float Height)
{
	// Normalize time to 0-1 range
	float NormalizedTime = Time / Duration;
	NormalizedTime = NormalizedTime - FMath::FloorToFloat(NormalizedTime); // Loop (Fract alternative)

	// Use custom curve if provided
	if (BounceConfig.CustomBounceCurve)
	{
		return BounceConfig.CustomBounceCurve->GetFloatValue(NormalizedTime) * Height;
	}

	// Physics-based bounce: h(t) = 4h * t * (1 - t) for parabolic arc
	// This gives a smooth bounce that starts and ends at 0, peaking at t=0.5
	float ParabolicBounce = 4.0f * Height * NormalizedTime * (1.0f - NormalizedTime);

	// Apply style-specific modifications
	switch (BounceConfig.BounceStyle)
	{
	case EForgeBounceStyle::Soft:
		// Smoother curve with easing
		return FMath::Sin(NormalizedTime * PI) * Height;

	case EForgeBounceStyle::Medium:
		// Standard parabolic bounce
		return ParabolicBounce;

	case EForgeBounceStyle::Hard:
		// Sharper peak, more linear in the middle
		return FMath::Pow(ParabolicBounce / Height, 0.7f) * Height;

	case EForgeBounceStyle::Elastic:
		{
			// Add elastic overshoot
			float ElasticBounce = FMath::Sin(NormalizedTime * PI * 2.5f) * FMath::Exp(-NormalizedTime * 3.0f);
			return FMath::Max(0.0f, ElasticBounce * Height * 1.2f);
		}

	default:
		return 4.0f * Height * NormalizedTime * (1.0f - NormalizedTime);
	}
}

float UForgeComponent2DWidget::CalculateSquashStretch(float BounceValue, float Height)
{
	// Maximum squash at the bottom (when bounce value is 0)
	// Maximum stretch at the top (when bounce value is maximum)
	float NormalizedHeight = BounceValue / Height;
	
	// Squash when near ground, stretch when high
	// Returns 0 at peak, 1 at bottom
	return 1.0f - NormalizedHeight;
}

void UForgeComponent2DWidget::ApplyEffectsToMaterial()
{
	if (!DynamicMaterial)
	{
		CreateDynamicMaterial();
	}

	// Apply all configured effects
	UpdateShadow();
	UpdateMetallic();
	UpdateRoughness();

	// Apply forge material color if set
	if (ForgeMaterialType != EForgeMaterialType::AnvilCarbon)
	{
		ApplyForgeMaterialColor(ForgeMaterialType, bEnableMetallic, bEnableRoughness);
	}
}

void UForgeComponent2DWidget::SetMaterialParameter(FName ParameterName, float Value)
{
	if (!DynamicMaterial)
	{
		return;
	}

	// Cache the parameter
	FloatParameterCache.FindOrAdd(ParameterName) = Value;
	
	// Try to set on material (will fail gracefully if parameter doesn't exist)
	DynamicMaterial->SetScalarParameterValue(ParameterName, Value);
}

void UForgeComponent2DWidget::SetMaterialParameterColor(FName ParameterName, FLinearColor Value)
{
	if (!DynamicMaterial)
	{
		return;
	}

	// Cache the parameter
	ColorParameterCache.FindOrAdd(ParameterName) = Value;
	
	// Try to set on material
	DynamicMaterial->SetVectorParameterValue(ParameterName, Value);
}

void UForgeComponent2DWidget::SetMaterialParameterVector(FName ParameterName, FVector2D Value)
{
	if (!DynamicMaterial)
	{
		return;
	}

	// Convert to FVector4 for material (Z and W are 0)
	FVector4 VectorValue(Value.X, Value.Y, 0.0f, 0.0f);
	DynamicMaterial->SetVectorParameterValue(ParameterName, FLinearColor(VectorValue));
}
