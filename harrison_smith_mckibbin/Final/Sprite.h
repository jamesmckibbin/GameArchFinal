#pragma once

#include <Trackable.h>
#include "Vector2D.h"
#include "GraphicsBuffer.h"

class GraphicsBuffer;

class Sprite : public Trackable
{
public:
	Sprite(GraphicsBuffer* buffer) : mGraphicsBuffer(buffer), mSource(Vector2D(0, 0)), mWidth(buffer->getWidth()), mHeight(buffer->getHeight()) {}
	Sprite(GraphicsBuffer* buffer, const Vector2D& source, const int width, const int height) : mSource(source), mGraphicsBuffer(buffer), mWidth(width), mHeight(height) {}
	~Sprite() {}
	GraphicsBuffer* getGraphicsBuffer() { return mGraphicsBuffer; }
	Vector2D getSource() { return mSource; }
	int getWidth() { return mWidth; }
	int getHeight() { return mHeight; }
private:
	Vector2D mSource;
	GraphicsBuffer* mGraphicsBuffer;
	int mWidth;
	int mHeight;
};
