#pragma once

UENUM()
enum class ESYConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class ESYValidType : uint8
{
	Valid,
	InValid
};

UENUM()
enum class ESYSuccessType : uint8
{
	Successful,
	Failed
};

UENUM()
enum class ESYCountDownActionInput : uint8
{
	Start,
	Cancel
};

UENUM()
enum class ESYCountDownActionOutput : uint8
{
	Updated,
	Completed,
	Cancelled
};

UENUM(BlueprintType)
enum class ESYGameDifficulty : uint8
{
	Easy,
	Normal,
	Hard,
	VeryHard

};