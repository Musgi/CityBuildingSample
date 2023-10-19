#pragma once
// UENUM()
// enum EObjectState
// {
// 	HoveredOn UMETA(DisplayName = "HoverOn"),
// 	Selected UMETA(DisplayName = "Selected"),
// 	Editing UMETA(DisplayName = "Editing"),
// 	Idle UMETA(DisplayName = "Idle"),
// 	Preview UMETA(DisplayName = "Preview"),
// 	CanSet UMETA(DisplayName = "CanSet"),
// 	Colliding UMETA(DisplayName = "Colliding"),
// 	Fade UMETA(DisplayName = "Fade"),
// 	NoState UMETA(DisplayName = "NoState"),
// 	
// };
UENUM()
enum EBuildingType
{
	Cube UMETA(DisplayName = "Cube"),
	LShape UMETA(DisplayName = "LShape"),
	Slide UMETA(DisplayName = "Slide"),
	Home UMETA(DisplayName = "Home"),
	None UMETA(DisplayName = "None")
};

UENUM()
enum EGameState
{
	Observing UMETA(DisplayName = "Observing"),
	Modifying UMETA(DisplayName = "Modifying"),
	Moving UMETA(DisplayName = "Moving"),
	Spawning UMETA(DisplayName = "Spawning"),
};