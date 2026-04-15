// Copyright Teuku. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "MPC_Forge_Palette.h"
#include "ForgeMaterialPaletteDA.h"
#include "Rendering/DrawElements.h"

#include "ForgeComponent2DWidget.generated.h"

/**
 * Enum for shadow style presets
 */
UENUM(BlueprintType, Category = "Forge Component 2D")
enum class EForgeShadowStyle : uint8
{
	SoftOuter     UMETA(DisplayName = "Soft Outer"),
	HardOuter     UMETA(DisplayName = "Hard Outer"),
	InnerSoft     UMETA(DisplayName = "Inner Soft"),
	InnerHard     UMETA(DisplayName = "Inner Hard"),
	DoubleLayer   UMETA(DisplayName = "Double Layer"),
	Custom        UMETA(DisplayName = "Custom")
};

/**
 * Enum for bounce animation presets
 */
UENUM(BlueprintType, Category = "Forge Component 2D")
enum class EForgeBounceStyle : uint8
{
	None          UMETA(DisplayName = "None"),
	Soft          UMETA(DisplayName = "Soft"),
	Medium        UMETA(DisplayName = "Medium"),
	Hard          UMETA(DisplayName = "Hard"),
	Elastic       UMETA(DisplayName = "Elastic"),
	Custom        UMETA(DisplayName = "Custom")
};

/**
 * Enum for fake metallic reflection style
 */
UENUM(BlueprintType, Category = "Forge Component 2D")
enum class EForgeMetallicStyle : uint8
{
	None          UMETA(DisplayName = "None"),
	Brushed       UMETA(DisplayName = "Brushed Metal"),
	Polished      UMETA(DisplayName = "Polished Mirror"),
	Hammered      UMETA(DisplayName = "Hammered Texture"),
	Anisotropic   UMETA(DisplayName = "Anisotropic"),
	Custom        UMETA(DisplayName = "Custom")
};

/**
 * Enum for fake roughness style
 */
UENUM(BlueprintType, Category = "Forge Component 2D")
enum class EForgeRoughnessStyle : uint8
{
	Smooth        UMETA(DisplayName = "Smooth (Low Roughness)"),
	SemiSmooth    UMETA(DisplayName = "Semi-Smooth"),
	Matte         UMETA(DisplayName = "Matte (Medium Roughness)"),
	Rough         UMETA(DisplayName = "Rough (High Roughness)"),
	Custom        UMETA(DisplayName = "Custom")
};

/**
 * Shadow configuration struct
 */
USTRUCT(BlueprintType)
struct FForgeShadowConfig
{
	GENERATED_BODY()

	/** Shadow offset from the component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shadow")
	FVector2D ShadowOffset = FVector2D(0.0f, 8.0f);

	/** Shadow blur radius (0 = hard edge) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shadow", meta = (ClampMin = "0.0", ClampMax = "50.0"))
	float ShadowBlur = 15.0f;

	/** Shadow color (supports alpha for transparency) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shadow")
	FLinearColor ShadowColor = FLinearColor(0.0f, 0.0f, 0.0f, 0.75f);

	/** Shadow spread (positive = larger, negative = smaller) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shadow", meta = (ClampMin = "-20.0", ClampMax = "20.0"))
	float ShadowSpread = 5.0f;

	/** Shadow opacity (0.0 = invisible, 1.0 = fully opaque) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shadow", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float ShadowOpacity = 1.0f;

	/** Enable second shadow layer for double-layer effect */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shadow")
	bool bEnableSecondaryShadow = false;

	/** Secondary shadow offset (for double-layer shadows) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shadow", meta = (EditCondition = "bEnableSecondaryShadow"))
	FVector2D SecondaryShadowOffset = FVector2D(0.0f, 16.0f);

	/** Secondary shadow blur */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shadow", meta = (EditCondition = "bEnableSecondaryShadow", ClampMin = "0.0", ClampMax = "50.0"))
	float SecondaryShadowBlur = 25.0f;

	/** Secondary shadow color */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shadow", meta = (EditCondition = "bEnableSecondaryShadow"))
	FLinearColor SecondaryShadowColor = FLinearColor(0.0f, 0.0f, 0.0f, 0.4f);
};

/**
 * Bounce animation configuration
 */
USTRUCT(BlueprintType)
struct FForgeBounceConfig
{
	GENERATED_BODY()

	/** Bounce animation style */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bounce")
	EForgeBounceStyle BounceStyle = EForgeBounceStyle::Medium;

	/** Bounce height in pixels */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bounce", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float BounceHeight = 20.0f;

	/** Bounce duration in seconds */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bounce", meta = (ClampMin = "0.1", ClampMax = "5.0"))
	float BounceDuration = 1.0f;

	/** Number of bounces before stopping (0 = infinite) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bounce")
	int32 BounceCount = 0;

	/** Delay before starting bounce animation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bounce", meta = (ClampMin = "0.0", ClampMax = "5.0"))
	float StartDelay = 0.0f;

	/** Custom easing curve (optional, uses built-in if not set) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bounce")
	UCurveFloat* CustomBounceCurve;

	/** Enable squash and stretch effect */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bounce")
	bool bEnableSquashStretch = true;

	/** Squash/stretch intensity */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bounce", meta = (ClampMin = "0.0", ClampMax = "0.5"))
	float SquashStretchIntensity = 0.15f;
};

/**
 * Fake metallic configuration
 */
USTRUCT(BlueprintType)
struct FForgeMetallicConfig
{
	GENERATED_BODY()

	/** Metallic reflection style */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metallic")
	EForgeMetallicStyle MetallicStyle = EForgeMetallicStyle::Polished;

	/** Metallic intensity (0.0 = none, 1.0 = full metal) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metallic", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float MetallicIntensity = 0.8f;

	/** Reflection color tint */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metallic")
	FLinearColor ReflectionTint = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	/** Number of reflection highlights */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metallic", meta = (ClampMin = "1", ClampMax = "8"))
	int32 ReflectionCount = 3;

	/** Reflection sharpness (0.0 = soft, 1.0 = sharp) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metallic", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float ReflectionSharpness = 0.7f;

	/** Anisotropic direction angle in degrees (for anisotropic style) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metallic", meta = (ClampMin = "0.0", ClampMax = "360.0"))
	float AnisotropicAngle = 45.0f;

	/** Brushed metal line spacing (for brushed style) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Metallic", meta = (ClampMin = "1.0", ClampMax = "20.0"))
	float BrushedLineSpacing = 5.0f;
};

/**
 * Fake roughness configuration
 */
USTRUCT(BlueprintType)
struct FForgeRoughnessConfig
{
	GENERATED_BODY()

	/** Roughness style */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roughness")
	EForgeRoughnessStyle RoughnessStyle = EForgeRoughnessStyle::Matte;

	/** Roughness value (0.0 = mirror smooth, 1.0 = completely rough) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roughness", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float RoughnessValue = 0.5f;

	/** Micro-detail noise intensity */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roughness", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float NoiseIntensity = 0.1f;

	/** Noise scale (larger = bigger grains) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roughness", meta = (ClampMin = "1.0", ClampMax = "100.0"))
	float NoiseScale = 20.0f;

	/** Specular highlight intensity */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roughness", meta = (ClampMin = "0.0", ClampMax = "2.0"))
	float SpecularIntensity = 0.5f;

	/** Specular sharpness (0.0 = broad, 1.0 = pinpoint) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roughness", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float SpecularSharpness = 0.3f;
};

/**
 * UForgeComponent2DWidget
 *
 * Advanced 2D UI component with fake shadow, bounce animation,
 * and manual roughness/metallic effects for UI materials.
 * 
 * This component simulates PBR-like effects (shadow, roughness, metallic)
 * using purely 2D techniques that work with UI materials which normally
 * don't support 3D lighting calculations.
 *
 * Features:
 * - Multi-layer fake shadows with customizable blur and offset
 * - Bounce animation with squash & stretch
 * - Fake metallic reflection (brushed, polished, hammered, anisotropic)
 * - Fake roughness with noise-based micro-detail and specular highlights
 * - Integration with Forge Material Palette system
 *
 * Usage:
 * 1. Add this widget to your UMG widget tree (as a Border widget)
 * 2. Configure shadow, bounce, metallic, and roughness settings
 * 3. The component automatically creates dynamic material instances
 * 4. Call PlayBounce() to trigger bounce animation
 */
UCLASS(ClassGroup=(Forge, Custom), meta=(DisplayName = "Forge Component 2D"))
class FORGECOMPONENT2D_API UForgeComponent2DWidget : public UBorder
{
	GENERATED_BODY()

public:
	// ==================== INITIALIZATION ====================

	/**
	 * Initialize the component (call from Blueprint after construction)
	 * This sets up materials and applies initial effects
	 */
	UFUNCTION(BlueprintCallable, Category = "Forge Component 2D")
	void Initialize();

	// ==================== LIFECYCLE ====================

	/** Called when the widget is added to the viewport */
	UFUNCTION(BlueprintCallable, Category = "Forge Component 2D")
	void OnAddedToViewport();

	/** Called every frame for animation */
	void TickAnimation(float DeltaTime);

	// ==================== SHADOW EFFECTS ====================

	/**
	 * Apply fake shadow effect with custom configuration
	 * @param Config Shadow configuration struct
	 */
	UFUNCTION(BlueprintCallable, Category = "Forge Component 2D|Shadow")
	void ApplyShadow(const FForgeShadowConfig& Config);

	/**
	 * Apply preset shadow style
	 * @param Style Shadow style preset
	 */
	UFUNCTION(BlueprintCallable, Category = "Forge Component 2D|Shadow")
	void ApplyShadowPreset(EForgeShadowStyle Style);

	/**
	 * Toggle shadow on/off
	 * @param bEnabled Enable or disable shadow
	 */
	UFUNCTION(BlueprintCallable, Category = "Forge Component 2D|Shadow")
	void SetShadowEnabled(bool bEnabled);

	/**
	 * Update shadow opacity dynamically
	 * @param Opacity New opacity value (0.0-1.0)
	 */
	UFUNCTION(BlueprintCallable, Category = "Forge Component 2D|Shadow")
	void SetShadowOpacity(float Opacity);

	// ==================== BOUNCE ANIMATION ====================

	/**
	 * Play bounce animation with current configuration
	 */
	UFUNCTION(BlueprintCallable, Category = "Forge Component 2D|Bounce")
	void PlayBounce();

	/**
	 * Stop bounce animation
	 * @param bResetPosition Reset to original position
	 */
	UFUNCTION(BlueprintCallable, Category = "Forge Component 2D|Bounce")
	void StopBounce(bool bResetPosition = true);

	/**
	 * Apply bounce preset configuration
	 * @param Style Bounce style preset
	 */
	UFUNCTION(BlueprintCallable, Category = "Forge Component 2D|Bounce")
	void ApplyBouncePreset(EForgeBounceStyle Style);

	/**
	 * Check if bounce animation is currently playing
	 * @return True if bounce is active
	 */
	UFUNCTION(BlueprintPure, Category = "Forge Component 2D|Bounce")
	bool IsBouncing() const { return bIsBouncing; }

	// ==================== FAKE METALLIC ====================

	/**
	 * Apply fake metallic effect
	 * @param Config Metallic configuration
	 */
	UFUNCTION(BlueprintCallable, Category = "Forge Component 2D|Metallic")
	void ApplyMetallic(const FForgeMetallicConfig& Config);

	/**
	 * Apply metallic preset
	 * @param Style Metallic style preset
	 */
	UFUNCTION(BlueprintCallable, Category = "Forge Component 2D|Metallic")
	void ApplyMetallicPreset(EForgeMetallicStyle Style);

	/**
	 * Update metallic intensity dynamically
	 * @param Intensity New metallic intensity value (0.0-1.0)
	 */
	UFUNCTION(BlueprintCallable, Category = "Forge Component 2D|Metallic")
	void SetMetallicIntensity(float Intensity);

	// ==================== FAKE ROUGHNESS ====================

	/**
	 * Apply fake roughness effect
	 * @param Config Roughness configuration
	 */
	UFUNCTION(BlueprintCallable, Category = "Forge Component 2D|Roughness")
	void ApplyRoughness(const FForgeRoughnessConfig& Config);

	/**
	 * Apply roughness preset
	 * @param Style Roughness style preset
	 */
	UFUNCTION(BlueprintCallable, Category = "Forge Component 2D|Roughness")
	void ApplyRoughnessPreset(EForgeRoughnessStyle Style);

	/**
	 * Update roughness value dynamically
	 * @param Value New roughness value (0.0-1.0)
	 */
	UFUNCTION(BlueprintCallable, Category = "Forge Component 2D|Roughness")
	void SetRoughnessValue(float Value);

	// ==================== FORGE MATERIAL INTEGRATION ====================

	/**
	 * Apply color from Forge Material Palette
	 * @param MaterialType Forge material type
	 * @param bIncludeMetallic Whether to also apply metallic property
	 * @param bIncludeRoughness Whether to also apply roughness property
	 */
	UFUNCTION(BlueprintCallable, Category = "Forge Component 2D|Forge Material")
	void ApplyForgeMaterialColor(EForgeMaterialType MaterialType, bool bIncludeMetallic = true, bool bIncludeRoughness = true);

	/**
	 * Get current dynamic material instance (custom wrapper)
	 * @return Dynamic material instance
	 */
	UFUNCTION(BlueprintPure, Category = "Forge Component 2D|Material", DisplayName = "GetForgeMaterialInstance")
	UMaterialInstanceDynamic* GetForgeMaterialInstance() const { return DynamicMaterial; }

	// ==================== PROPERTIES ====================

	/** Enable/disable shadow effect */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forge Component 2D|Shadow")
	bool bEnableShadow = true;

	/** Shadow configuration */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forge Component 2D|Shadow")
	FForgeShadowConfig ShadowConfig;

	/** Enable/disable bounce animation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forge Component 2D|Bounce")
	bool bEnableBounce = false;

	/** Bounce configuration */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forge Component 2D|Bounce")
	FForgeBounceConfig BounceConfig;

	/** Enable/disable fake metallic effect */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forge Component 2D|Metallic")
	bool bEnableMetallic = false;

	/** Metallic configuration */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forge Component 2D|Metallic")
	FForgeMetallicConfig MetallicConfig;

	/** Enable/disable fake roughness effect */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forge Component 2D|Roughness")
	bool bEnableRoughness = true;

	/** Roughness configuration */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forge Component 2D|Roughness")
	FForgeRoughnessConfig RoughnessConfig;

	/** Forge Material Type for automatic color application */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forge Component 2D|Forge Material")
	EForgeMaterialType ForgeMaterialType = EForgeMaterialType::AnvilCarbon;

protected:
	// ==================== INTERNAL METHODS ====================

	/** Create dynamic material instance */
	void CreateDynamicMaterial();

	/** Update shadow rendering */
	void UpdateShadow();

	/** Update metallic rendering */
	void UpdateMetallic();

	/** Update roughness rendering */
	void UpdateRoughness();

	/** Update bounce animation */
	void UpdateBounce(float DeltaTime);

	/** Calculate bounce value using physics-based formula */
	float CalculateBounceValue(float Time, float Duration, float Height);

	/** Calculate squash/stretch factor */
	float CalculateSquashStretch(float BounceValue, float Height);

	/** Apply all effects to material */
	void ApplyEffectsToMaterial();

	/** Set material parameter with safety check */
	void SetMaterialParameter(FName ParameterName, float Value);
	void SetMaterialParameterColor(FName ParameterName, FLinearColor Value);
	void SetMaterialParameterVector(FName ParameterName, FVector2D Value);

	// ==================== INTERNAL STATE ====================

	/** Dynamic material instance */
	UPROPERTY(Transient)
	UMaterialInstanceDynamic* DynamicMaterial = nullptr;

	/** Original material reference */
	UPROPERTY(Transient)
	UMaterial* OriginalMaterial = nullptr;

	/** Is bounce animation playing */
	bool bIsBouncing = false;

	/** Bounce animation elapsed time */
	float BounceElapsedTime = 0.0f;

	/** Current bounce count */
	int32 CurrentBounceCount = 0;

	/** Original render transform position */
	FVector2D OriginalPosition = FVector2D::ZeroVector;

	/** Current shadow opacity */
	float CurrentShadowOpacity = 1.0f;

	/** Material parameter cache */
	TMap<FName, float> FloatParameterCache;
	TMap<FName, FLinearColor> ColorParameterCache;
};
