// Dragons rule ok


#include "SplinePath.h"
#include <TDGameInstance.h>

// Sets default values
ASplinePath::ASplinePath() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplinePathToFollow"));

	SplineComponent->bInputSplinePointsToConstructionScript = true;
	SetupETDMap();
}

// Called when the game starts or when spawned
void ASplinePath::BeginPlay() {
	Super::BeginPlay();

	Cast<UTDGameInstance>(GetGameInstance())->EnemySplinePath = this;
}

// Called every frame
void ASplinePath::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void ASplinePath::SetupETDMap() {
	SplineComponent->ClearSplinePoints();

	FSplinePoint sPoint0;
	sPoint0.InputKey = 0.f;
	sPoint0.Type = ESplinePointType::Constant;
	sPoint0.Position = FVector(0., 0., 0.);
	SplineComponent->AddPoint(sPoint0);

	FSplinePoint sPoint1;
	sPoint1.InputKey = 1.f;
	sPoint1.Type = ESplinePointType::Constant;
	sPoint1.Position = FVector(-350., 0., 0.);
	SplineComponent->AddPoint(sPoint1);

	FSplinePoint sPoint2;
	sPoint2.InputKey = 2.f;
	sPoint2.Type = ESplinePointType::Constant;
	sPoint2.Position = FVector(-350., -200., 0.);
	SplineComponent->AddPoint(sPoint2);

	FSplinePoint sPoint3;
	sPoint3.InputKey = 3.f;
	sPoint3.Type = ESplinePointType::Constant;
	sPoint3.Position = FVector(-750., -200., 0.);
	SplineComponent->AddPoint(sPoint3);

	FSplinePoint sPoint4;
	sPoint4.InputKey = 4.f;
	sPoint4.Type = ESplinePointType::Constant;
	sPoint4.Position = FVector(-750., 400., 0.);
	SplineComponent->AddPoint(sPoint4);

	FSplinePoint sPoint5;
	sPoint5.InputKey = 5.f;
	sPoint5.Type = ESplinePointType::Constant;
	sPoint5.Position = FVector(-550., 400., 0.);
	SplineComponent->AddPoint(sPoint5);

	FSplinePoint sPoint6;
	sPoint6.InputKey = 6.f;
	sPoint6.Type = ESplinePointType::Constant;
	sPoint6.Position = FVector(-550., 800., 0.);
	SplineComponent->AddPoint(sPoint6);

	FSplinePoint sPoint7;
	sPoint7.InputKey = 7.f;
	sPoint7.Type = ESplinePointType::Constant;
	sPoint7.Position = FVector(-1150., 800., 0.);
	SplineComponent->AddPoint(sPoint7);

	FSplinePoint sPoint8;
	sPoint8.InputKey = 8.f;
	sPoint8.Type = ESplinePointType::Constant;
	sPoint8.Position = FVector(-1150., -200., 0.);
	SplineComponent->AddPoint(sPoint8);

	FSplinePoint sPoint9;
	sPoint9.InputKey = 9.f;
	sPoint9.Type = ESplinePointType::Constant;
	sPoint9.Position = FVector(-1550., -200., 0.);
	SplineComponent->AddPoint(sPoint9);

	FSplinePoint sPoint10;
	sPoint10.InputKey = 10.f;
	sPoint10.Type = ESplinePointType::Constant;
	sPoint10.Position = FVector(-1550., 1200., 0.);
	SplineComponent->AddPoint(sPoint10);

	FSplinePoint sPoint11;
	sPoint11.InputKey = 11.f;
	sPoint11.Type = ESplinePointType::Constant;
	sPoint11.Position = FVector(-150., 1200., 0.);
	SplineComponent->AddPoint(sPoint11);

	FSplinePoint sPoint12;
	sPoint12.InputKey = 12.f;
	sPoint12.Type = ESplinePointType::Constant;
	sPoint12.Position = FVector(-150., 400., 0.);
	SplineComponent->AddPoint(sPoint12);

	FSplinePoint sPoint13;
	sPoint13.InputKey = 13.f;
	sPoint13.Type = ESplinePointType::Constant;
	sPoint13.Position = FVector(0., 400., 0.);
	SplineComponent->AddPoint(sPoint13);
}

