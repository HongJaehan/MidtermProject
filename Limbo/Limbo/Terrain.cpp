#include "pch.h"
#include "Terrain.h"

Terrain::Terrain()
{
	img = AssetManager().GetInstance()->GetImage(TEXT("map3.png")).lock().get();
}

Terrain::~Terrain()
{
	delete img;
}

void Terrain::Update(float Delta)
{

}

void Terrain::Render(Gdiplus::Graphics* MemG)
{
	//Gdiplus::Bitmap terrainBitmap(defines.screenSizeX*2, defines.screenSizeY, PixelFormat32bppARGB);
	//Gdiplus::Graphics graphics(&terrainBitmap);
	//Gdiplus::Image* img = AssetManager().GetInstance()->GetImage(TEXT("map3.png")).lock().get();

//	graphics.DrawImage(img, 0, 0,defines.screenSizeX*2, defines.screenSizeY);
	Gdiplus::Rect rect(0, 0, defines.screenSizeX, defines.screenSizeY);
	MemG->DrawImage(img, rect);
	//MemG->DrawImage(AssetManager().GetInstance()->GetImage(TEXT("map3.png")).lock().get(), rect);

	//AssetManager().GetInstance()->GetImage(TEXT("map3.png")).reset();
	/*int posY = 0;
	Gdiplus::Color color;
	graphics.DrawImage(img, 0, 0, defines.screenSizeX, defines.screenSizeY);


	for (int y = 0; y < defines.screenSizeY; ++y)
	{
		terrainBitmap.GetPixel(563, y, &color);
		if (color.GetAlpha() > 0)
		{
			posY = y;
			break;
		}
	}*/
}

bool Terrain::GetEnable()
{
	return enable;
}

void Terrain::SetEnable(bool bFlag)
{
	enable = bFlag;
}

int Terrain::GetPosX()
{
	return x;
}

int Terrain::GetPosY()
{
	return y;
}

int Terrain::GetWidth()
{
	return width;
}

int Terrain::GetHeight()
{
	return height;
}

ETag Terrain::GetTag()
{
	return tag;
}