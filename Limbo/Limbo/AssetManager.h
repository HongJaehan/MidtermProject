#pragma once
#include "ObjectXMLData.h"

//class Image;


//모든 resource들을 관리하기 위한 class 
class AssetManager : public Singleton<AssetManager>
{
public:
	AssetManager();
	~AssetManager();
	std::weak_ptr<Gdiplus::Image> GetImage(std::wstring str);
	void SetXMLData(std::vector<Gdiplus::Rect> &Rect, char *fileName);
	void SetXMLData(std::unordered_map<int,Gdiplus::Rect>&, char* fileName);
	void SetObjectXMLData(std::vector<ObjectXMLData>&, char* fileName);
	void SetCheckPointData(std::vector<int>&, char* fileName);


private:
	std::weak_ptr<Gdiplus::Image> MyLoadImage(std::wstring std);

private:
	//size_t 는 그냥 unsigned int
	tinyxml2::XMLDocument* doc;
	std::unordered_map<size_t, std::shared_ptr<Gdiplus::Image>> imgDic;
	//std::unordered_map<size_t, Image*> soundDic;
};

AssetManager* AssetManager::instance = nullptr;

