#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include <allegro5/allegro.h>

GraphicsBuffer::GraphicsBuffer(ALLEGRO_DISPLAY* display)
{
	mBitmap = al_get_backbuffer(display);
	mIsBackBuffer = true;
}

GraphicsBuffer::GraphicsBuffer(const std::string filename)
{
	mBitmap = al_load_bitmap(filename.c_str());
	mIsBackBuffer = false;
}

GraphicsBuffer::GraphicsBuffer(const int width, const int height, Color color)
{
	mBitmap = al_create_bitmap(width, height);
	mIsBackBuffer = false;

	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
	al_set_target_bitmap(mBitmap);

	al_clear_to_color(al_map_rgba(color.getR(), color.getG(), color.getB(), color.getA()));

	al_set_target_bitmap(pOldTarget);
}