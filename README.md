# ForgeComponent2D - Advanced 2D UI Component with Fake PBR Effects

## Overview

**ForgeComponent2D** is an advanced 2D UI component for Unreal Engine's UMG system that simulates **Physically-Based Rendering (PBR)** effects using purely 2D techniques. Since UI materials don't support traditional 3D lighting calculations (roughness, metallic, shadows), this component creates convincing fake effects through manual material manipulation.

## Features

### 🎨 Fake Shadow System
- **Multi-layer shadows** with primary and secondary shadow layers
- **5 shadow presets**: Soft Outer, Hard Outer, Inner Soft, Inner Hard, Double Layer
- **Real-time controls**: Offset, blur, spread, opacity, color
- **Dynamic shadow updates** without material recompilation

### 🏀 Bounce Animation
- **Physics-based bounce** with parabolic arcs
- **5 bounce styles**: None, Soft, Medium, Hard, Elastic
- **Squash & stretch** for cartoon-style animation
- **Configurable**: Height, duration, bounce count, easing curves
- **Custom curve support** for artist-controlled animation

### ✨ Fake Metallic Effect
- **4 metallic styles**: Brushed, Polished, Hammered, Anisotropic
- **Reflection simulation** using gradient techniques
- **Real-time controls**: Intensity, tint, sharpness, reflection count
- **Anisotropic angle control** for directional metal brushing

### 🔥 Fake Roughness Effect
- **5 roughness presets**: Smooth, Semi-Smooth, Matte, Rough
- **Micro-detail noise** for surface texture simulation
- **Specular highlights** with adjustable intensity and sharpness
- **Noise scale control** for grain size adjustment

### 🔗 Forge Material Integration
- **Automatic color application** from Forge Material Palette
- **12 forge materials** supported (Anvil Carbon, Tempered Steel, etc.)
- **Automatic roughness & metallic extraction** from palette
- **Dynamic material instance** creation and management

---

## Quick Start

### 1. Add Component to Widget

In the Unreal Editor:

1. Open your **Widget Blueprint** in the UMG Editor
2. Drag a **Border** component onto your widget canvas
3. In the **Details** panel, change the component class to **Forge Component 2D**
4. Configure the component properties in the Details panel

### 2. Configure Shadow

```cpp
// In Blueprint or C++
ForgeComponent2D->ApplyShadowPreset(EForgeShadowStyle::SoftOuter);
// Or manually configure:
ForgeComponent2D->ShadowConfig.ShadowOffset = FVector2D(0, 10);
ForgeComponent2D->ShadowConfig.ShadowBlur = 20;
ForgeComponent2D->ShadowConfig.ShadowColor = FLinearColor(0, 0, 0, 0.8);
ForgeComponent2D->ApplyShadow(ForgeComponent2D->ShadowConfig);
```

### 3. Enable Bounce Animation

```cpp
// Configure bounce
ForgeComponent2D->bEnableBounce = true;
ForgeComponent2D->ApplyBouncePreset(EForgeBounceStyle::Medium);
ForgeComponent2D->BounceConfig.BounceHeight = 30;
ForgeComponent2D->PlayBounce();
```

### 4. Apply Fake Metallic

```cpp
// Enable metallic effect
ForgeComponent2D->bEnableMetallic = true;
ForgeComponent2D->ApplyMetallicPreset(EForgeMetallicStyle::Polished);
ForgeComponent2D->MetallicConfig.ReflectionTint = FLinearColor(0.8, 0.9, 1.0, 1.0); // Blue tint
ForgeComponent2D->ApplyMetallic(ForgeComponent2D->MetallicConfig);
```

### 5. Apply Fake Roughness

```cpp
// Enable roughness effect
ForgeComponent2D->bEnableRoughness = true;
ForgeComponent2D->ApplyRoughnessPreset(EForgeRoughnessStyle::Matte);
ForgeComponent2D->RoughnessConfig.SpecularIntensity = 0.7;
ForgeComponent2D->ApplyRoughness(ForgeComponent2D->RoughnessConfig);
```

### 6. Use Forge Material Palette

```cpp
// Automatically applies color + roughness + metallic from palette
ForgeComponent2D->ApplyForgeMaterialColor(
    EForgeMaterialType::TemperedSteel,
    true,  // Include metallic
    true   // Include roughness
);
```

---

## Material Setup (Required)

The component requires a **UI-compatible material** with the correct parameter names. Here's how to create one:

### Creating the Base Material

1. **Create New Material**:
   - Right-click in Content Browser → **Material**
   - Name it `M_ForgeComponent2D_Base`
   - Set **Material Domain** to `User Interface`

2. **Add Material Parameters** (all parameters are optional, but enable specific features):

   **Shadow Parameters**:
   - `ShadowEnabled` (Scalar Parameter, default: 1)
   - `ShadowOffset` (Vector2 Parameter, default: (0, 8))
   - `ShadowBlur` (Scalar Parameter, default: 15)
   - `ShadowColor` (Vector Parameter, default: (0, 0, 0, 0.75))
   - `ShadowSpread` (Scalar Parameter, default: 5)
   - `ShadowOpacity` (Scalar Parameter, default: 1)
   - `bEnableSecondaryShadow` (Scalar Parameter, default: 0)
   - `SecondaryShadowOffset` (Vector2 Parameter, default: (0, 16))
   - `SecondaryShadowBlur` (Scalar Parameter, default: 25)
   - `SecondaryShadowColor` (Vector Parameter, default: (0, 0, 0, 0.4))

   **Metallic Parameters**:
   - `MetallicEnabled` (Scalar Parameter, default: 0)
   - `MetallicStyle` (Scalar Parameter, default: 0) // 0=None, 1=Brushed, 2=Polished, 3=Hammered, 4=Anisotropic
   - `MetallicIntensity` (Scalar Parameter, default: 0.8)
   - `ReflectionTint` (Vector Parameter, default: (1, 1, 1, 1))
   - `ReflectionCount` (Scalar Parameter, default: 3)
   - `ReflectionSharpness` (Scalar Parameter, default: 0.7)
   - `AnisotropicAngle` (Scalar Parameter, default: 0.785) // 45 degrees in radians
   - `BrushedLineSpacing` (Scalar Parameter, default: 5)

   **Roughness Parameters**:
   - `RoughnessEnabled` (Scalar Parameter, default: 0)
   - `RoughnessStyle` (Scalar Parameter, default: 0) // 0=Smooth, 1=SemiSmooth, 2=Matte, 3=Rough
   - `RoughnessValue` (Scalar Parameter, default: 0.5)
   - `NoiseIntensity` (Scalar Parameter, default: 0.1)
   - `NoiseScale` (Scalar Parameter, default: 20)
   - `SpecularIntensity` (Scalar Parameter, default: 0.5)
   - `SpecularSharpness` (Scalar Parameter, default: 0.3)

   **Base Color**:
   - `BaseColor` (Vector Parameter, default: (0.1, 0.1, 0.1, 1))

3. **Implement Shadow Logic** (in Material Editor):

   ```
   [Texture Sample: Base Color or Tint]
         ↓
   [Multiply with BaseColor parameter]
         ↓
   [Append to Pixel Output]
   ```

   For shadow rendering, you'll need to use **custom material expressions** that render shadow layers. This is typically done through:
   
   - **Scene Depth-based shadows** (for UI, use fixed offset instead)
   - **Gradient-based shadows** using `LinearGradient` expressions
   - **Blur simulation** using `TextureCoordinate` offsets

4. **Implement Fake Metallic Logic**:

   ```
   [Fresnel-like effect using PixelPosition]
         ↓
   [Multiply with MetallicIntensity]
         ↓
   [Add gradient highlights based on MetallicStyle]
         ↓
   [Blend with Base Color]
   ```

   **Polished Metal**: Use sharp gradient reflections (high ReflectionSharpness)
   **Brushed Metal**: Use repeating line patterns (BrushedLineSpacing)
   **Hammered Metal**: Use noise-based distortion (high ReflectionCount)
   **Anisotropic**: Use directional reflections (AnisotropicAngle)

5. **Implement Fake Roughness Logic**:

   ```
   [Noise Texture or Procedural Noise]
         ↓
   [Multiply with NoiseIntensity]
         ↓
   [Add to base color for micro-detail]
         ↓
   [Calculate specular highlight based on RoughnessValue]
         ↓
   [Add specular to final output]
   ```

---

## Blueprint API Reference

### Shadow Functions

| Function | Description | Parameters |
|----------|-------------|------------|
| `ApplyShadow` | Apply custom shadow configuration | `Config` (FForgeShadowConfig) |
| `ApplyShadowPreset` | Apply preset shadow style | `Style` (EForgeShadowStyle) |
| `SetShadowEnabled` | Toggle shadow on/off | `bEnabled` (bool) |
| `SetShadowOpacity` | Update shadow opacity | `Opacity` (float, 0-1) |

### Bounce Functions

| Function | Description | Parameters |
|----------|-------------|------------|
| `PlayBounce` | Start bounce animation | None |
| `StopBounce` | Stop bounce animation | `bResetPosition` (bool) |
| `ApplyBouncePreset` | Apply bounce preset | `Style` (EForgeBounceStyle) |
| `IsBouncing` | Check if currently bouncing | Returns: bool |

### Metallic Functions

| Function | Description | Parameters |
|----------|-------------|------------|
| `ApplyMetallic` | Apply metallic effect | `Config` (FForgeMetallicConfig) |
| `ApplyMetallicPreset` | Apply metallic preset | `Style` (EForgeMetallicStyle) |
| `SetMetallicIntensity` | Update metallic intensity | `Intensity` (float, 0-1) |

### Roughness Functions

| Function | Description | Parameters |
|----------|-------------|------------|
| `ApplyRoughness` | Apply roughness effect | `Config` (FForgeRoughnessConfig) |
| `ApplyRoughnessPreset` | Apply roughness preset | `Style` (EForgeRoughnessStyle) |
| `SetRoughnessValue` | Update roughness value | `Value` (float, 0-1) |

### Forge Material Functions

| Function | Description | Parameters |
|----------|-------------|------------|
| `ApplyForgeMaterialColor` | Apply color from Forge Palette | `MaterialType`, `bIncludeMetallic`, `bIncludeRoughness` |
| `GetForgeDynamicMaterial` | Get current material instance | Returns: UMaterialInstanceDynamic |

---

## Configuration Structs

### FForgeShadowConfig

```cpp
struct FForgeShadowConfig
{
    FVector2D ShadowOffset;        // Shadow offset (X, Y)
    float ShadowBlur;              // Blur radius (0-50)
    FLinearColor ShadowColor;      // Shadow color with alpha
    float ShadowSpread;            // Shadow spread (-20 to 20)
    float ShadowOpacity;           // Shadow opacity (0-1)
    bool bEnableSecondaryShadow;   // Enable second shadow layer
    FVector2D SecondaryShadowOffset;
    float SecondaryShadowBlur;
    FLinearColor SecondaryShadowColor;
};
```

### FForgeBounceConfig

```cpp
struct FForgeBounceConfig
{
    EForgeBounceStyle BounceStyle;
    float BounceHeight;            // Max bounce height (0-100)
    float BounceDuration;          // Duration in seconds (0.1-5)
    int32 BounceCount;             // 0 = infinite
    float StartDelay;              // Delay before starting
    UCurveFloat* CustomBounceCurve;
    bool bEnableSquashStretch;
    float SquashStretchIntensity;
};
```

### FForgeMetallicConfig

```cpp
struct FForgeMetallicConfig
{
    EForgeMetallicStyle MetallicStyle;
    float MetallicIntensity;       // 0-1
    FLinearColor ReflectionTint;
    int32 ReflectionCount;         // Number of highlights
    float ReflectionSharpness;     // 0-1
    float AnisotropicAngle;        // 0-360 degrees
    float BrushedLineSpacing;
};
```

### FForgeRoughnessConfig

```cpp
struct FForgeRoughnessConfig
{
    EForgeRoughnessStyle RoughnessStyle;
    float RoughnessValue;          // 0-1
    float NoiseIntensity;          // 0-1
    float NoiseScale;              // 1-100
    float SpecularIntensity;       // 0-2
    float SpecularSharpness;       // 0-1
};
```

---

## Enumerations

### EForgeShadowStyle
- `SoftOuter` - Soft, diffused outer shadow
- `HardOuter` - Sharp, hard outer shadow
- `InnerSoft` - Soft inner shadow (inset effect)
- `InnerHard` - Sharp inner shadow
- `DoubleLayer` - Two-layer shadow for depth
- `Custom` - User-defined configuration

### EForgeBounceStyle
- `None` - No bounce animation
- `Soft` - Gentle, smooth bounce
- `Medium` - Standard parabolic bounce
- `Hard` - Sharp, energetic bounce
- `Elastic` - Bouncy with overshoot
- `Custom` - User-defined curve

### EForgeMetallicStyle
- `None` - No metallic effect
- `Brushed` - Brushed metal with lines
- `Polished` - Mirror-like polished metal
- `Hammered` - Textured hammered metal
- `Anisotropic` - Directional brushed metal
- `Custom` - User-defined settings

### EForgeRoughnessStyle
- `Smooth` - Mirror-smooth surface (low roughness)
- `SemiSmooth` - Slightly textured
- `Matte` - Medium roughness
- `Rough` - Very rough surface
- `Custom` - User-defined settings

### EForgeMaterialType (from Forge Palette)
- `AnvilCarbon` - Dark structure color
- `TemperedSteel` - Neutral metal gray
- `NobleSilver` - Bright silver
- `MasteryGold` - Gold/yellow legendary
- `AgedBronze` - Warm bronze
- `TannedHide` - Leather brown
- `CharredOak` - Dark wood
- `CherryRed` - Hot red (heating)
- `MoltenOrange` - Glowing orange (forge)
- `WhiteHeat` - Extreme white heat
- `QuenchBlue` - Cool blue
- `BrittleRust` - Rust orange (warning)

---

## Performance Considerations

### Optimizations
1. **Dynamic Material Instances**: The component creates one DMI per instance, which is efficient
2. **Parameter Caching**: Material parameters are cached to avoid redundant updates
3. **Conditional Updates**: Effects only update when configuration changes
4. **Tick Only When Needed**: Bounce animation only runs when active

### Best Practices
- **Limit Active Bounces**: Don't play bounce on dozens of components simultaneously
- **Reuse Materials**: Share the same base material across multiple ForgeComponent2D instances
- **Avoid Frequent Updates**: Batch configuration changes instead of calling apply functions repeatedly
- **Use Presets**: Presets are optimized configurations; use them as starting points

---

## Troubleshooting

### Shadow Not Showing
- ✅ Check that `bEnableShadow` is true
- ✅ Verify material has shadow parameters defined
- ✅ Ensure `ShadowOpacity` > 0
- ✅ Check `ShadowColor` alpha value

### Bounce Not Playing
- ✅ Ensure `bEnableBounce` is true
- ✅ Call `PlayBounce()` to start animation
- ✅ Verify component is in a CanvasPanel (required for position animation)
- ✅ Check `BounceDuration` and `BounceHeight` are > 0

### Metallic/Roughness Not Visible
- ✅ Enable `bEnableMetallic` or `bEnableRoughness`
- ✅ Verify material has the corresponding parameters
- ✅ Check that intensity values are > 0
- ✅ Ensure material domain is set to "User Interface"

### Material Parameters Not Found
- ✅ Parameter names are case-sensitive
- ✅ Check spelling matches exactly (e.g., `ShadowEnabled`, not `shadow_enabled`)
- ✅ Create parameters in material if missing
- ✅ Use dynamic material instance, not material instance constant

---

## Examples

### Example 1: Forge Button with Hover Effect

```cpp
// In your Widget Blueprint's Event Graph

Event OnHovered:
    ForgeButton->PlayBounce()
    ForgeButton->SetShadowOpacity(0.9)

Event OnUnhovered:
    ForgeButton->StopBounce(true)
    ForgeButton->SetShadowOpacity(0.5)
```

### Example 2: Inventory Item with Metallic Border

```cpp
// Apply gold metallic border to legendary items
if (ItemQuality == EItemQuality::Legendary)
{
    BorderComponent->bEnableMetallic = true;
    BorderComponent->ApplyMetallicPreset(EForgeMetallicStyle::Polished);
    BorderComponent->MetallicConfig.ReflectionTint = FLinearColor(1, 0.84, 0, 1); // Gold tint
    BorderComponent->ApplyForgeMaterialColor(EForgeMaterialType::MasteryGold);
}
```

### Example 3: Health Bar with Roughness

```cpp
// Apply rough metallic to health bar background
HealthBarBG->bEnableRoughness = true;
HealthBarBG->ApplyRoughnessPreset(EForgeRoughnessStyle::SemiSmooth);
HealthBarBG->bEnableMetallic = true;
HealthBarBG->ApplyMetallicPreset(EForgeMetallicStyle::Brushed);
HealthBarBG->MetallicConfig.MetallicIntensity = 0.4;
```

---

## Credits

**ForgeComponent2D** is part of the ProjectForge plugin system, integrating with the Forge Material Palette for consistent theming across UI components.

### Related Documentation
- Forge Material Palette: `MPC_Forge_Palette.h`
- Material Definitions: `ForgeMaterialPaletteDA.h`
- Custom Material Expressions: `MaterialExpressionForgeMaterial.h`

---

## License

Copyright Teuku. All Rights Reserved.
