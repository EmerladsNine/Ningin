#pragma once
#include <cstddef>
#include <vector>
#include <unordered_map>
#include "../ComponentId.h"

class ECSVector
{
public:
	int entitySize;

	ECSVector();
	~ECSVector();
	void Init(int entitySize);
	void AddComponentPosition(ComponentId componentId, int position);
	bool Empty() const;
	void CreateEntity();
	void SwapRemove(size_t row);
	void PopBack();

	void* GetEntityComponentPointer(size_t row,ComponentId componentId)
	{
		row *= entitySize;
		return reinterpret_cast<void*>(&data[row + componentPositions[componentId]]);
	}
		
	void* GetEntityPointer(size_t row)
	{
		row *= entitySize;
		return data + row;
	}

	int GetComponentPosition(ComponentId componentId)
	{
		return componentPositions[componentId];
	}
private :
	//binary data
	char* data;
	int capacity;
	size_t current;
	std::unordered_map<ComponentId, int> componentPositions;
	void push();
	void pop();
};