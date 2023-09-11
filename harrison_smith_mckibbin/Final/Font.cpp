#include "Font.h"


Font::Font(const std::string filename, const int size)
{
	mFontSize = size;
	mFont = al_load_font(filename.c_str(), mFontSize, 0);
}