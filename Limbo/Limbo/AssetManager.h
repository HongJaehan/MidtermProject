#pragma once

//class Image;


//��� resource���� �����ϱ� ���� class 
class AssetManager : public Singleton<AssetManager>
{
public:
	std::weak_ptr<Gdiplus::Image> GetImage(std::wstring str);
	void SetXMLData(std::vector<Gdiplus::Rect> &Rect, char *fileName);
private:
	std::weak_ptr<Gdiplus::Image> MyLoadImage(std::wstring std);

private:
	//size_t �� �׳� unsigned int
	std::unordered_map<size_t, std::shared_ptr<Gdiplus::Image>> imgDic;
	//std::unordered_map<size_t, Image*> soundDic;

};
AssetManager* AssetManager::instance = nullptr;

