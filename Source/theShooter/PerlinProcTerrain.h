// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PerlinProcTerrain.generated.h"

class UProceduralMeshComponent;
class UMaterialInterface;

UCLASS()
class THESHOOTER_API APerlinProcTerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APerlinProcTerrain();

	// SETS THE VALUES FOR UNREAL AND MAKES IT EDITABLE IN UNREAL
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		int XSize = 0;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		int YSize = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite , Meta = (ClampMin = 0))
		float ZMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		float NoiseScale = 1.0f;


	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		float Scale = 0;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
		float UVScale = 0;

	UPROPERTY(EditAnywhere)
		float radius;

	UPROPERTY(EditAnywhere)
		FVector Depth;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// MAKES IT TO WHERE YOU CAN ADD MATS to TERRIAN 
	UPROPERTY(EditAnywhere)
		UMaterialInterface* Mat;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ALTER MESH FUNCTION IS ABLE TO BE CALLED OUTSIDE OF CLASS
	UFUNCTION()
		void AlterMesh(FVector impactPoint);
	
private:
	// ADD THE COMPONENT AND CREATES ARRAYS TO STORE VALUES
	UProceduralMeshComponent* ProcMesh;
	TArray<FVector> Vertices;
	TArray<int> Triangles;
	TArray<FVector2D> UV0;
	TArray<FVector> Normals;
	TArray<FColor> UpVertexColors;

	int sectionID = 0;
	// CREATES FUNCTIONS TO CREATE TERRAIN
	void CreateVertices();
	void CreateTriangles();

};
