#include "FPSGameMode.h"
#include "FPS_HUD.h"
#include "../Characters/FPS_Character.h"
#include "UObject/ConstructorHelpers.h"

AFPSGameMode::AFPSGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Player/BP_CPlayer"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	
	HUDClass = AFPS_HUD::StaticClass();
}
