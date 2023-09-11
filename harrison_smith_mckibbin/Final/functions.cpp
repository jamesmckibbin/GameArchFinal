#include "functions.h"
using namespace std;

bool initSystem()
{
	return al_init();
}

bool initGraphicsSubsystem()
{
	return al_init_image_addon() && al_init_primitives_addon();
}

bool initFontSubsystem()
{
	return al_init_font_addon() && al_init_ttf_addon();
}

bool initAllSubsystems()
{
	if (!al_init())
	{
		cout << "ERROR - System not initted\n";
		return false;
	}
	if (!initGraphicsSubsystem())
	{
		cout << "ERROR - Graphics subsystem not initted\n";
		return false;
	}
	if (!al_init_font_addon() && al_init_ttf_addon())
	{
		cout << "ERROR - Font subsystem not initted\n";
		return false;
	}
	return true;
}

ALLEGRO_BITMAP* loadBitmap(const std::string& filename)
{
	return al_load_bitmap(filename.c_str());
}

ALLEGRO_BITMAP* createBitmap(const int width, const int height)
{
	return al_create_bitmap(width, height);
}

ALLEGRO_FONT* loadFont(const std::string& filename, const int size)
{
	return al_load_ttf_font(filename.c_str(),size,0);
}

ALLEGRO_DISPLAY* createDisplay(const int width, const int height)
{
	return al_create_display(width, height);
}

ALLEGRO_BITMAP* getBackBuffer(ALLEGRO_DISPLAY* pDisplay)
{
	return al_get_backbuffer(pDisplay);
}

void blit(ALLEGRO_BITMAP* dest, ALLEGRO_BITMAP* src, const Vector2D& destLoc, const Vector2D& srcLoc, const Vector2D& srcSize, const Vector2D& scale)
{
	ALLEGRO_BITMAP* oldTarget = al_get_target_bitmap();
	al_set_target_bitmap(dest);

	al_draw_scaled_bitmap(src, srcLoc.getX(), srcLoc.getY(), srcSize.getX(), srcSize.getY(), destLoc.getX(), destLoc.getY(), srcSize.getX() * scale.getX(), srcSize.getY() * scale.getY(), 0);

	al_set_target_bitmap(oldTarget);
}

void drawBitmap(ALLEGRO_BITMAP* dest, ALLEGRO_BITMAP* src, const Vector2D& loc)
{
	
	blit(dest, src, loc, Vector2D(0,0), getSize(src), Vector2D(1,1));
}

void flip()
{
	al_flip_display();
}

void setBitmapToColor(ALLEGRO_BITMAP* bitmap, const ALLEGRO_COLOR& color)
{
	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
	al_set_target_bitmap(bitmap);

	al_clear_to_color(color);

	al_set_target_bitmap(pOldTarget);
}

ALLEGRO_COLOR createColor(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a)
{
	return al_map_rgba(r, g, b, a);
}

void drawCircle(ALLEGRO_BITMAP* dest, const Vector2D& center, const float radius, const ALLEGRO_COLOR& color, const bool filled)
{
	ALLEGRO_BITMAP* oldTarget = al_get_target_bitmap();
	al_set_target_bitmap(dest);

	if (filled) { al_draw_filled_circle(center.getX(), center.getY(), radius, color); }
	else { al_draw_circle(center.getX(), center.getY(), radius, color, 3); }

	al_set_target_bitmap(oldTarget);
}

void drawText(ALLEGRO_BITMAP* dest, ALLEGRO_FONT* pFont, const Vector2D& loc, const int alignment, const std::string& text, const ALLEGRO_COLOR& color)
{
	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
	al_set_target_bitmap(dest);

	al_draw_text(pFont, color, loc.getX(), loc.getY(), alignment, text.c_str());

	al_set_target_bitmap(pOldTarget);

}

Vector2D getSize(ALLEGRO_BITMAP* bitmap)
{
	int width = al_get_bitmap_width(bitmap);
	int height = al_get_bitmap_height(bitmap);

	return Vector2D(width, height);
}

//void save(ALLEGRO_BITMAP* bitmap, const std::string filename)
//{
	//al_save_bitmap(filename.c_str(), bitmap);
//}

void destroyBitmap(ALLEGRO_BITMAP* bitmap)
{
	al_destroy_bitmap(bitmap);
}

void destroyFont(ALLEGRO_FONT* font)
{
	al_destroy_font(font);
}

void destroyDisplay(ALLEGRO_DISPLAY* pDisplay)
{
	al_destroy_display(pDisplay);
}

void cleanupAllegro()
{
	al_uninstall_system();
}
