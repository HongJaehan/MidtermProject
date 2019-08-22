#include "pch.h"
#include "AssetManager.h"


//오브젝트들은 이미지의 하드 포인터를 들고있으면 안되기 때문에 Weak_ptr을 사용해줘야한다.
AssetManager::AssetManager()
{
	doc = new tinyxml2::XMLDocument();
}

AssetManager::~AssetManager()
{
	delete doc;
	//imgDic.clear();
}

std::weak_ptr<Gdiplus::Image> AssetManager::GetImage(std::wstring str)
{
	//hash는 
	std::hash<std::wstring> makeHash;
	//ret는 return value
	std::weak_ptr<Gdiplus::Image> ret;

	//hash를 통해 imgDic에 있는 img정보를 찾는다.

	auto it = imgDic.find(makeHash(str));
	
	//만약 현재 imgDic에 없다면 MyLoadImage로 가서 img정보를 저장해준다.
	if (it == imgDic.end())
		ret = MyLoadImage(str);
	else
		ret = it->second;

	//expired를 사용하면 현재 사용하고있는 shared Point의 상태를 확인할 수 있다.
	//if (ret.expired())
	//{
	//	auto p = ret.lock();
	//	p->
	//}
    //https://docs.microsoft.com/ko-kr/cpp/standard-library/weak-ptr-class?view=vs-2019
	
	return ret;
}

std::weak_ptr<Gdiplus::Image> AssetManager::MyLoadImage(std::wstring fileName)
{
	std::wstring temp(TEXT("Image\\"));
	temp.append(fileName);

	std::shared_ptr<Gdiplus::Image> Img = std::make_shared<Gdiplus::Image>(temp.c_str());

	/*if (Img = nullptr)
	{
		return;
	}*/

	std::hash<std::wstring> makeHash;
	imgDic.insert(std::make_pair(makeHash(fileName), Img));
	
	 return Img;
}

void AssetManager::SetXMLData(std::vector<Gdiplus::Rect> &Rects, char* fileName)
{

	doc->LoadFile(fileName);
	
	if (doc == nullptr) return;
	
	tinyxml2::XMLElement* Root = doc->RootElement();
	//tinyxml2::XMLElement* TextureAtlasInfo = Root->FirstChildElement("TextureAtlas");
	tinyxml2::XMLElement* atlasInfo = Root->FirstChildElement("sprite");

	for (tinyxml2::XMLElement* element = atlasInfo; element != nullptr; element = element->NextSiblingElement())
	{
		Gdiplus::Rect rect(Gdiplus::Rect(element->IntAttribute("x"), element->IntAttribute("y"),
			element->IntAttribute("w"), element->IntAttribute("h")) );
	Rects.emplace_back(rect);
	}

}

void AssetManager::SetXMLData(std::unordered_map<int, Gdiplus::Rect>& dic, char* fileName)
{
	doc->LoadFile(fileName);

	if (doc == nullptr) return;

	tinyxml2::XMLElement* Root = doc->RootElement();
	//tinyxml2::XMLElement* TextureAtlasInfo = Root->FirstChildElement("TextureAtlas");
	tinyxml2::XMLElement* atlasInfo = Root->FirstChildElement("sprite");

	for (tinyxml2::XMLElement* element = atlasInfo; element != nullptr; element = element->NextSiblingElement())
	{
		int key = element->IntAttribute("num");
		Gdiplus::Rect rect(element->IntAttribute("x"), element->IntAttribute("y"),
			element->IntAttribute("w"), element->IntAttribute("h"));
		dic.insert(std::make_pair(key,rect));
	}
}

void AssetManager::SetObjectXMLData(std::vector<ObjectXMLData>& objXMLDataVec, char* fileName)
{
	doc->LoadFile(fileName);

	if (doc == nullptr) return;

	tinyxml2::XMLElement* Root = doc->RootElement();
	tinyxml2::XMLElement* atlasInfo = Root->FirstChildElement("object");

	for (tinyxml2::XMLElement* element = atlasInfo; element != nullptr; element = element->NextSiblingElement())
	{
		ObjectXMLData oData(element->IntAttribute("num"), element->IntAttribute("x"), element->IntAttribute("y"), element->IntAttribute("w"), element->IntAttribute("h"));
		objXMLDataVec.emplace_back(oData);
	}
}

void AssetManager::SetCheckPointData(std::vector<int>& vec, char* fileName)
{
	doc->LoadFile(fileName);

	if (doc == nullptr) return;

	tinyxml2::XMLElement* Root = doc->RootElement();
	tinyxml2::XMLElement* atlasInfo = Root->FirstChildElement("point");

	for (tinyxml2::XMLElement* element = atlasInfo; element != nullptr; element = element->NextSiblingElement())
	{
		vec.emplace_back(element->IntAttribute("pos"));
	}
}
