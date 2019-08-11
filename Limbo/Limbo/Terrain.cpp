#include "pch.h"
#include "Terrain.h"

Terrain::Terrain()
{

}

Terrain::~Terrain()
{

}

void Terrain::Control()
{

}

void Terrain::Update(float Delta)
{

}

void Terrain::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Bitmap terrainBitmap(1920*2, 1080, PixelFormat32bppARGB);
	Gdiplus::Graphics graphics(&terrainBitmap);
	Gdiplus::Image* img = AssetManager().GetInstance()->GetImage(TEXT("map3.png")).lock().get();

	graphics.DrawImage(img, 0, 0,1920*2, 1080);
	Gdiplus::Rect rect(0, 0, 1920*2, 1080);
	MemG->DrawImage(&terrainBitmap, rect);

	/*int posY = 0;
	Gdiplus::Color color;
	graphics.DrawImage(img, 0, 0, 1920, 1080);


	for (int y = 0; y < 1080; ++y)
	{
		terrainBitmap.GetPixel(563, y, &color);
		if (color.GetAlpha() > 0)
		{
			posY = y;
			break;
		}
	}*/
}