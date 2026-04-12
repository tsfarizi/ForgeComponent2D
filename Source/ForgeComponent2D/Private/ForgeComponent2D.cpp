// Copyright Epic Games, Inc. All Rights Reserved.

#include "ForgeComponent2D.h"
#include "MaterialExpressions/MaterialExpressionForgeMaterial.h"

#define LOCTEXT_NAMESPACE "FForgeComponent2DModule"

void FForgeComponent2DModule::StartupModule()
{
	// Material expressions auto-register via UCLASS and MenuCategories
}

void FForgeComponent2DModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FForgeComponent2DModule, ForgeComponent2D)