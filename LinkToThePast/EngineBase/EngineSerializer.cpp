#include "PreCompile.h"
#include "EngineSerializer.h"

UEngineSerializer::UEngineSerializer()
{
}

UEngineSerializer::~UEngineSerializer()
{
}

void UEngineSerializer::Write(void* WriteData, unsigned int Size)
{
	if (WriteOffset + Size >= Data.size())
	{
		Data.resize(Data.size() * 2 + Size);
	}

	memcpy_s(&Data[WriteOffset], Size, WriteData, Size);
	WriteOffset += Size;
}

void UEngineSerializer::operator<<(ISerializObject& Ser)
{
	Ser.Serialize(*this);
}

void UEngineSerializer::Read(void* ReadData, unsigned int Size)
{
	memcpy_s(ReadData, Size, &Data[ReadOffset], Size);
	ReadOffset += Size;
}

void UEngineSerializer::operator>>(ISerializObject& Ser)
{
	Ser.DeSerialize(*this);
}
