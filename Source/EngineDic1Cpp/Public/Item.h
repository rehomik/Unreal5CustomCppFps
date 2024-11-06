#pragma once

#include "EngineDic1CppCharacter.h"
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Item.generated.h"


class AEngineDic1CppCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENGINEDIC1CPP_API UItem : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItem();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UFUNCTION(BlueprintCallable)
	void AttachJump();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	AEngineDic1CppCharacter* Character; // 캐릭터의 정보를 가지고 옴.
		
};
