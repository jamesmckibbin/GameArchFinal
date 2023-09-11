#pragma once

#include <Trackable.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class Font : public Trackable
{
	friend class GraphicsSystem;

public:
	Font(const std::string filename, int size);
	~Font() {}
	int getSize() { return mFontSize; }
private:
	int mFontSize = 0;
	ALLEGRO_FONT* mFont = nullptr;
};