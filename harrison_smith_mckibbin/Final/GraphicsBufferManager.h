#pragma once

#include <unordered_map>
#include <string>

#include "GraphicsBuffer.h"
#include "Trackable.h"


typedef std::string Key;

class GraphicsBufferManager : public Trackable
{
public:
	GraphicsBufferManager() {}
	~GraphicsBufferManager() {
		cleanup();
	}
	GraphicsBuffer* createBuffer(const Key& key, std::string filename);
	GraphicsBuffer* createBuffer(const Key& key, int width, int height, Color color);
	GraphicsBuffer* cloneBuffer(const Key& newKey, const Key& existingKey);
	void destroyBuffer(const Key& key);
	void destroyBuffer(GraphicsBuffer* buffer);
	void cleanup();
	unsigned int getBufferMapSize() const { return mGraphicsBufferMap.size(); }
	GraphicsBuffer* getBuffer(const Key& key) { return mGraphicsBufferMap[key]; }
	bool bufferKeyExists(const Key& key);

private:
	std::unordered_map<Key, GraphicsBuffer*> mGraphicsBufferMap;
};
