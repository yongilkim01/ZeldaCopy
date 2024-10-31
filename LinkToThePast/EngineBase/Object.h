#pragma once
#include <string>

// Ό³Έν :
class UObject
{
public:
	// constrcuter destructer
	UObject();
	virtual ~UObject();

	// delete Function
	UObject(const UObject& _Other) = delete;
	UObject(UObject&& _Other) noexcept = delete;
	UObject& operator=(const UObject& _Other) = delete;
	UObject& operator=(UObject&& _Other) noexcept = delete;

	virtual void SetName(std::string_view _Name)
	{
		Name = _Name.data();
	}

	inline std::string GetName() const { return Name; }
	inline std::string_view GetNameView() const { return Name.c_str(); }

protected:

private:
	std::string Name;
};

