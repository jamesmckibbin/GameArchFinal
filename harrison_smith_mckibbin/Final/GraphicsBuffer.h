#pragma once

#include <Trackable.h>
#include <allegro5/allegro.h>
#include "Color.h"

class GraphicsSystem;

class GraphicsBuffer : public Trackable
{
	friend class GraphicsSystem;

public:
	GraphicsBuffer(int width, int height, Color color);
	GraphicsBuffer(const std::string filename);
	GraphicsBuffer(GraphicsBuffer&) = delete;
	~GraphicsBuffer() { 
		if (!mIsBackBuffer)
		{
			al_destroy_bitmap(mBitmap);
		}
	}
	int getWidth() const { return al_get_bitmap_width(mBitmap); }
	int getHeight() const { return al_get_bitmap_height(mBitmap); }
private:
	GraphicsBuffer(ALLEGRO_DISPLAY* display);
	ALLEGRO_BITMAP* mBitmap;
	bool mIsBackBuffer;
};