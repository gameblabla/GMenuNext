/***************************************************************************
 *   Copyright (C) 2006 by Massimiliano Torromeo   *
 *   massimiliano.torromeo@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef SURFACE_H
#define SURFACE_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using std::string;

const int	HAlignLeft		= 1,
			HAlignRight		= 2,
			HAlignCenter	= 4,
			VAlignTop		= 8,
			VAlignBottom	= 16,
			VAlignMiddle	= 32;



class FontHelper;

struct RGBAColor {
	uint8_t r,g,b,a;
	// static RGBAColor fromString(std::string const& strColor);
	// static string toString(RGBAColor &color);
};

RGBAColor strtorgba(const string &strColor);
string rgbatostr(RGBAColor color);
SDL_Color rgbatosdl(RGBAColor color);

/**
	Wrapper around SDL_Surface
	@author Massimiliano Torromeo <massimiliano.torromeo@gmail.com>
*/
class Surface {
private:
	bool locked;
	int halfW, halfH;
	SDL_Surface *dblbuffer;

public:
	Surface();
	Surface(const string &img, const string &skin="", bool alpha=true);
	Surface(const string &img, bool alpha, const string &skin="");
	Surface(SDL_Surface *s, SDL_PixelFormat *fmt = NULL, uint32_t flags = 0);
	Surface(Surface *s);
	Surface(int w, int h, uint32_t flags = SDL_HWSURFACE|SDL_SRCALPHA);
	~Surface();

	void enableVirtualDoubleBuffer(SDL_Surface *surface, bool alpha=true);
	void enableAlpha();

	SDL_Surface *raw;
	SDL_Surface *ScreenSurface;

	void free();
	void load(const string &img, bool alpha=true, const string &skin="");
	void lock();
	void unlock();
	void flip();
	SDL_PixelFormat *format();

	void putPixel(int,int,RGBAColor);
	void putPixel(int,int,uint32_t);
	RGBAColor pixelColor(int,int);
	uint32_t pixel(int,int);

	void blendAdd(Surface*, int,int);

	void clearClipRect();
	// void setClipRect(int x, int y, int w, int h);
	void setClipRect(SDL_Rect rect);

	// bool blit(Surface *destination, int x, int y, int w=0, int h=0, int a=-1);
	// bool blit(Surface *destination, SDL_Rect container, const uint16_t halign=0, const uint16_t valign=0);
	// bool blit(SDL_Surface *destination, int x, int y, int w=0, int h=0, int a=-1);
	// bool blitCenter(Surface *destination, int x, int y, int w=0, int h=0, int a=-1);
	// bool blitCenter(SDL_Surface *destination, int x, int y, int w=0, int h=0, int a=-1);
	// bool blitRight(Surface *destination, int x, int y, int w=0, int h=0, int a=-1);
	// bool blitRight(SDL_Surface *destination, int x, int y, int w=0, int h=0, int a=-1);

	bool blit(Surface *destination, int x, int y, const uint8_t align = HAlignLeft | VAlignTop, uint8_t alpha=-1);
	bool blit(Surface *destination, SDL_Rect destrect, const uint8_t align = HAlignLeft | VAlignTop, uint8_t alpha=-1);

	void write(FontHelper *font, const string &text, int x, int y, const uint8_t align = HAlignLeft | VAlignTop);
	void write(FontHelper *font, const string &text, int x, int y, const uint8_t align, RGBAColor fgColor, RGBAColor bgColor);

	int box(int16_t, int16_t, int16_t, int16_t, uint8_t, uint8_t, uint8_t, uint8_t);
	int box(int16_t, int16_t, int16_t, int16_t, uint8_t, uint8_t, uint8_t);
	int box(int16_t, int16_t, int16_t, int16_t, RGBAColor);
	int box(SDL_Rect, uint8_t, uint8_t, uint8_t, uint8_t);
	int box(SDL_Rect, uint8_t, uint8_t, uint8_t);
	int box(SDL_Rect, RGBAColor);

	int rectangle(int16_t, int16_t, int16_t, int16_t, uint8_t, uint8_t, uint8_t, uint8_t);
	int rectangle(int16_t, int16_t, int16_t, int16_t, uint8_t, uint8_t, uint8_t);
	int rectangle(int16_t, int16_t, int16_t, int16_t, RGBAColor);
	int rectangle(SDL_Rect, uint8_t, uint8_t, uint8_t, uint8_t);
	int rectangle(SDL_Rect, uint8_t, uint8_t, uint8_t);
	int rectangle(SDL_Rect, RGBAColor);
	
	int hline(int16_t, int16_t, int16_t, uint8_t, uint8_t, uint8_t, uint8_t);
	int hline(int16_t, int16_t, int16_t, RGBAColor);

	void operator = (SDL_Surface*);
	void operator = (Surface*);
};

#endif
