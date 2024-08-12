
// Name
// Creator

#pragma once
#include "CoreMinimal.h"
#include "MyEnum.generated.h"

// Include this heading to use the enum
// #include "MyEnum.h"

/** Template Unreal enumeration script. */
UENUM(BlueprintType, meta = (Bitflags), Category = "Category")
enum class EMyEnum : uint8
{
    NONE = 0    UMETA(DisplayName = "None"),
    FLAG1 = 1   UMETA(DisplayName = "Flag 1"),
    FLAG2 = 2   UMETA(DisplayName = "Flag 2"),
    FLAG3 = 4   UMETA(DisplayName = "Flag 3"),
    FLAG4 = 8   UMETA(DisplayName = "Flag 4"),
    FLAG5 = 16  UMETA(DisplayName = "Flag 5"),
    FLAG6 = 32  UMETA(DisplayName = "Flag 6"),
    FLAG7 = 64  UMETA(DisplayName = "Flag 7"),
    FLAG8 = 128 UMETA(DisplayName = "Flag 8"),
};
