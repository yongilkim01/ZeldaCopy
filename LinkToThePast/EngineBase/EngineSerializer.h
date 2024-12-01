#pragma once
#include <vector>
#include <string>

#include "EngineMath.h"

/**
 *	���� ����ȭ ���� Ŭ����
 */
class UEngineSerializer
{
public:
	/** ������, �Ҹ��� */
	UEngineSerializer();
	~UEngineSerializer();

	/** ��ü ���� ���� */
	UEngineSerializer(const UEngineSerializer& _Other) = delete;
	UEngineSerializer(UEngineSerializer&& _Other) noexcept = delete;
	UEngineSerializer& operator=(const UEngineSerializer& _Other) = delete;
	UEngineSerializer& operator=(UEngineSerializer&& _Other) noexcept = delete;

	/** ����ȭ �޼ҵ� */
	void Write(void* WriteData, unsigned int Size);
	void Read(void* ReadData, unsigned int Size);

	/** ������ */
	void operator<<(std::string& WriteData)
	{
		int Size = static_cast<int>(WriteData.size());
		operator<<(Size);
		if (0 != Size)
		{
			Write(&WriteData[0], static_cast<int>(WriteData.size()));
		}
	}
	template<typename DataType>
	void operator<<(std::vector<DataType>& WriteVector)
	{
		int Size = static_cast<int>(WriteVector.size());
		operator<<(Size);
		for (size_t i = 0; i < WriteVector.size(); i++)
		{
			operator<<(WriteVector[i]);
		}
	}
	void operator>>(std::string& ReadData)
	{
		int Size;
		operator>>(Size);
		ReadData.resize(Size);
		Read(&ReadData[0], static_cast<int>(ReadData.size()));
	}
	template<typename DataType>
	void operator>>(std::vector<DataType>& ReadVector)
	{
		int Size = 0;
		operator>>(Size);
		ReadVector.resize(Size);

		for (size_t i = 0; i < ReadVector.size(); i++)
		{
			operator>>(ReadVector[i]);
		}
	}
	void operator<<(class ISerializObject& Ser);
	void operator>>(class ISerializObject& Ser);
	void operator<<(int& WriteData)
	{
		Write(&WriteData, sizeof(int));
	}
	void operator<<(bool& WriteData)
	{
		Write(&WriteData, sizeof(bool));
	}
	void operator<<(FVector2D& WriteData)
	{
		Write(&WriteData, sizeof(FVector2D));
	}
	void operator<<(FIntPoint& WriteData)
	{
		Write(&WriteData, sizeof(FIntPoint));
	}
	void operator>>(int& ReadData)
	{
		Read(&ReadData, sizeof(int));
	}
	void operator>>(bool& ReadData)
	{
		Read(&ReadData, sizeof(bool));
	}
	void operator>>(FVector2D& ReadData)
	{
		Read(&ReadData, sizeof(FVector2D));
	}
	void operator>>(FIntPoint& ReadData)
	{
		Read(&ReadData, sizeof(FIntPoint));
	}

	/** ��, �� �޼ҵ� */
	void* GetDataPtr()
	{
		return &Data[0];
	}
	int GetWriteOffset()
	{
		return WriteOffset;
	}
	void DataResize(int Value)
	{
		Data.resize(Value);
	}

protected:

private:
	/** ����Ʈ �е� */
	int WriteOffset = 0;
	int ReadOffset = 0;

	std::vector<char> Data;
};

class ISerializObject
{
public:
	virtual void Serialize(UEngineSerializer& Ser) = 0;
	virtual void DeSerialize(UEngineSerializer& Ser) = 0;
};