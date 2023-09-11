#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"

GraphicsSystem::GraphicsSystem(const int width, const int height)
{
	mWidth = width;
	mHeight = height;
	mDisplay = nullptr;
	mBackBuffer = nullptr;
}

bool GraphicsSystem::initDisplay()
{
	if (!al_init())
	{
		std::cout << "ERROR - System not initted\n";
		return false;
	}
	if (!(al_init_image_addon() && al_init_primitives_addon()))
	{
		std::cout << "ERROR - Graphics subsystem not initted\n";
		return false;
	}
	if (!(al_init_font_addon() && al_init_ttf_addon()))
	{
		std::cout << "ERROR - Font subsystem not initted\n";
		return false;
	}
	mDisplay = al_create_display(mWidth, mHeight);
	mBackBuffer = new GraphicsBuffer(mDisplay);
	return true;
}

void GraphicsSystem::writeText(GraphicsBuffer* buffer, const Vector2D& loc, Font* font, Color color, std::string text)
{
	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
	al_set_target_bitmap(buffer->mBitmap);

	al_draw_text(font->mFont, al_map_rgba(color.getR(), color.getG(), color.getB(), color.getA()), loc.getX(), loc.getY(), 0, text.c_str());

	al_set_target_bitmap(pOldTarget);
}

void GraphicsSystem::saveBuffer(GraphicsBuffer* buffer, std::string fileName)
{
	al_save_bitmap(fileName.c_str(), buffer->mBitmap);
}

void GraphicsSystem::draw(GraphicsBuffer* buffer, const Vector2D& loc, Sprite sprite, Vector2D scale)
{
	blit(buffer->mBitmap, sprite.getGraphicsBuffer()->mBitmap, loc, sprite.getSource(), Vector2D(sprite.getWidth(), sprite.getHeight()), scale);
}

void GraphicsSystem::flip()
{
	al_flip_display();
}

void GraphicsSystem::cleanupDisplay()
{
	al_uninstall_system();
}

void GraphicsSystem::blit(ALLEGRO_BITMAP* dest, ALLEGRO_BITMAP* src, const Vector2D& destLoc, const Vector2D& srcLoc, const Vector2D& srcSize, const Vector2D& scale)
{
	ALLEGRO_BITMAP* oldTarget = al_get_target_bitmap();
	al_set_target_bitmap(dest);

	al_draw_scaled_bitmap(src, srcLoc.getX(), srcLoc.getY(), srcSize.getX(), srcSize.getY(), destLoc.getX(), destLoc.getY(), srcSize.getX() * scale.getX(), srcSize.getY() * scale.getY(), 0);

	al_set_target_bitmap(oldTarget);
}