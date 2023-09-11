#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <Trackable.h>
#include <allegro5/allegro.h>
#include <Vector2D.h>
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Color.h"
#include "Font.h"


class GraphicsBuffer;
class Sprite;
class Font;
class Color;

class GraphicsSystem : public Trackable
{

public:
	GraphicsSystem(int width, int height);
	~GraphicsSystem() { 
		delete mBackBuffer;
		al_destroy_display(mDisplay); 
		cleanupDisplay();
	}
	bool initDisplay();
	void flip();
	void draw(GraphicsBuffer* buffer, const Vector2D& loc, Sprite sprite, Vector2D scale = Vector2D(1.0f, 1.0f));
	void writeText(GraphicsBuffer* buffer, const Vector2D& loc, Font* font, Color color, std::string text);
	void saveBuffer(GraphicsBuffer* buffer, std::string fileName);
	void cleanupDisplay();
	GraphicsBuffer* getBackBuffer() { return mBackBuffer; }
	int getScreenWidth() { return mWidth; }
	int getScreenHeight() { return mHeight; }
private:
	void blit(ALLEGRO_BITMAP* dest, ALLEGRO_BITMAP* src, const Vector2D& destLoc, const Vector2D& srcLoc, const Vector2D& srcSize, const Vector2D& scale);
	ALLEGRO_DISPLAY* mDisplay;
	GraphicsBuffer* mBackBuffer;
	int mWidth;
	int mHeight;
};
