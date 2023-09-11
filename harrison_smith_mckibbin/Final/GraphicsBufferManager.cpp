#include "GraphicsBufferManager.h"
#include "GraphicsBuffer.h"

GraphicsBuffer* GraphicsBufferManager::createBuffer(const Key& key, const std::string filename)
{
	GraphicsBuffer* buffer = nullptr;

	if (!bufferKeyExists(key))
	{
		buffer = new GraphicsBuffer(filename);
		mGraphicsBufferMap[key] = buffer;
	}

	return buffer;
}

GraphicsBuffer* GraphicsBufferManager::createBuffer(const Key& key, const int width, const int height, const Color color)
{
	GraphicsBuffer* buffer = nullptr;

	if (!bufferKeyExists(key))
	{
		buffer = new GraphicsBuffer(width, height, color);
		mGraphicsBufferMap[key] = buffer;
	}

	return buffer;
}

GraphicsBuffer* GraphicsBufferManager::cloneBuffer(const Key& newKey, const Key& existingKey)
{
	GraphicsBuffer* buffer = nullptr;

	if (!(bufferKeyExists(newKey) && bufferKeyExists(existingKey)))
	{
		buffer = mGraphicsBufferMap[existingKey];
		mGraphicsBufferMap[newKey] = buffer;
	}

	return buffer;
}

void GraphicsBufferManager::destroyBuffer(const Key& key)
{
	for (auto it : mGraphicsBufferMap)
	{
		if (it.first == key)
		{
			delete it.second;
			mGraphicsBufferMap.erase(key);
			return;
		}
	}
}

void GraphicsBufferManager::destroyBuffer(GraphicsBuffer* buffer)
{
	for (auto it : mGraphicsBufferMap)
	{
		if (it.second == buffer)
		{
			delete buffer;
			mGraphicsBufferMap.erase(it.first);
			return;
		}
	}
}

void GraphicsBufferManager::cleanup()
{
	for (auto it : mGraphicsBufferMap)
	{
		delete it.second;
	}

	mGraphicsBufferMap.clear();
}

bool GraphicsBufferManager::bufferKeyExists(const Key& key)
{
	auto it = mGraphicsBufferMap.find(key);

	if (it != mGraphicsBufferMap.end())
	{
		return true;
	}
	
	return false;
}