#include "ECSVector.h"

ECSVector::ECSVector() : entitySize(0) {}

ECSVector::ECSVector(int entitySize) : entitySize(entitySize)
{
}

void ECSVector::AddComponentPosition(ComponentId componentId, int position)
{
	componentPositions.insert_or_assign(componentId, position);
}

bool ECSVector::Empty() const
{
	return data.empty();
}

void ECSVector::CreateEntity()
{
	for (int i = 0; i < entitySize; i++)
	{
		data.push_back(0);
	}
}

void ECSVector::SwapRemove(size_t row)
{
	size_t lastRow = data.size()-1;
	row *= entitySize;
	for (int i = 0; i < entitySize; i++)
	{
		std::swap(data[row+i], data[lastRow-i]);
		data.pop_back();
	}
}

void ECSVector::PopBack()
{
	for (int i = 0; i < entitySize; i++)
	{
		data.pop_back();
	}
}
