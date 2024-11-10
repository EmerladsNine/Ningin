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
	ECSVector(int entitySize);
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

private :
	std::vector<int> data;
	std::unordered_map<ComponentId, int> componentPositions;
};