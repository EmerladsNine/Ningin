#include "ECSVector.h"

ECSVector::ECSVector() : entitySize(0), capacity(1), current(0)
{
	data = new int[1];
}

ECSVector::~ECSVector()
{
	delete[] data;
}

void ECSVector::Init(int entitySize)
{
	delete[] data;
	capacity = entitySize;
	this->entitySize = entitySize;
	data = new int[entitySize];
}

void ECSVector::AddComponentPosition(ComponentId componentId, int position)
{
	componentPositions.insert_or_assign(componentId, position);
}

bool ECSVector::Empty() const
{
	return current == 0;
}

#include "../../sceneSystem/components/ScriptVec.h"
void ECSVector::Test()
{
	for (int row = 0; row < 2; row++)
	{
		ScriptVec& vec = *reinterpret_cast<ScriptVec*>(GetEntityComponentPointer(row, typeid(ScriptVec)));
		int i = 0;
	}
}

void ECSVector::push()
{
	if (current == capacity) {
		Test();
		int* temp = new int[capacity * 2];
		for (int i = 0; i < capacity; i++) {
			temp[i] = data[i];
		}
		delete[] data;
		capacity *= 2;
		data = temp;
		Test();
	}

	data[current] = 0;
	current++;
}

void ECSVector::pop()
{
	current--;
}

void ECSVector::CreateEntity()
{
	for (int i = 0; i < entitySize; i++)
	{
		push();
	}
}

void ECSVector::SwapRemove(size_t row)
{
	size_t lastRow = current-1;
	row *= entitySize;
	for (int i = 0; i < entitySize; i++)
	{
		std::swap(data[row+i], data[lastRow-i]);
	}
	current -= entitySize;
}

void ECSVector::PopBack()
{
	for (int i = 0; i < entitySize; i++)
	{
		pop();
	}
}

void ECSVector::Insert(size_t row, ComponentId componentId, void* data)
{
	void* dest = GetEntityComponentPointer(row, componentId);

}

