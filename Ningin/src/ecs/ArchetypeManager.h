#pragma once

#include "ArchetypeTypeHasher.h"
#include "ArchetypeRecord.h"
#include <unordered_map>
#include "archetype.h"
#include <functional>
#include <typeindex>
#include <stdexcept>
#include <optional>
#include <cstddef>
#include <vector>

using namespace std;

using ArchetypeId = size_t;
using ArchetypeMap = unordered_map<ArchetypeId, ArchetypeRecord>;

class ArchetypeManager
{
	public:
		ArchetypeManager();

		// These are used to remove components data depending on the component type
		static unordered_map<type_index, function<void(void*)>> deleters;
		static unordered_map<type_index, function<void(void*,size_t)>> swapRemove;
		static unordered_map<type_index, function<void(void*)>> removeLast;
		static unordered_map<type_index, function<void(void*,void*)>> pushBack;
		static unordered_map<type_index, function<void(void*,size_t,void*)>> insert;
		static unordered_map<type_index, function<void*(void*,size_t)>> getRow;
		static unordered_map<type_index, function<void*()>> createColumn;

		template <typename T> static void RegisterComponentType()
		{
			ArchetypeManager::deleters[typeid(T)] = [](void* p) { delete static_cast<T*>(p); };

			ArchetypeManager::swapRemove[typeid(T)] = [](void* column,size_t row) { 
				std::vector<T>& columnPtr = *reinterpret_cast<std::vector<T>*>(column);
				size_t lastRow = columnPtr.size() - 1;
				swap(columnPtr[row], columnPtr[lastRow]);
				columnPtr.pop_back();
			};
			
			ArchetypeManager::removeLast[typeid(T)] = [](void* column) { 
				std::vector<T>& columnPtr = *reinterpret_cast<std::vector<T>*>(column);
				columnPtr.pop_back();
			};
			
			ArchetypeManager::pushBack[typeid(T)] = [](void* column,void* data) { 
				std::vector<T>& columnPtr = *reinterpret_cast<std::vector<T>*>(column);
				T& dataRef = *reinterpret_cast<T*>(data);
				columnPtr.push_back(std::move(dataRef));
			};
			
			ArchetypeManager::insert[typeid(T)] = [](void* column,size_t row,void* data) { 
				std::vector<T>& columnPtr = *reinterpret_cast<std::vector<T>*>(column);
				if (row < columnPtr.size()) { 
					columnPtr[row] = std::move(*reinterpret_cast<T*>(data));
				}
				else {
					throw std::out_of_range("Row index out of bounds in ArchetypeManager::insert");
				}

			};

			ArchetypeManager::getRow[typeid(T)] = [](void* column, size_t row)  -> void* {
				std::vector<T>& columnPtr = *reinterpret_cast<std::vector<T>*>(column);
				T* rowPointer = &columnPtr[row];
				return rowPointer;
			};
			ArchetypeManager::createColumn[typeid(T)] = []()  -> void* {
				return new std::vector<T>();
			};
		}

		optional<Archetype*> GetArchetypeByType(const ArchetypeType& type);

		Archetype* GenerateArchetype(ArchetypeType&& type);

		unordered_map<ArchetypeType, Archetype, VectorHasher> archetypeIndex;
		unordered_map<ComponentId, ArchetypeMap> componentIndex;

	private:
		ArchetypeId _archetypeCount;
};
