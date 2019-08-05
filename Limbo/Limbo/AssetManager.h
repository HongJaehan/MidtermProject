#pragma once

//class Image;


//모든 resource들을 관리하기 위한 class 
class AssetManager : public Singleton<AssetManager>
{
public:
	std::weak_ptr<Gdiplus::Image> GetImage(std::wstring str);
private:
	std::weak_ptr<Gdiplus::Image> MyLoadImage(std::wstring std);

private:
	std::unordered_map<size_t, std::shared_ptr<Gdiplus::Image>> imgDic;
	//std::unordered_map<size_t, Image*> soundDic;

};
AssetManager* AssetManager::instance = nullptr;

