#include "pch.h"
#include "AssetManager.h"


struct BulletData
{
public:
	void reset()
	{
		radius = 0;
		
	}
	char Name[256];
	float radius;
};

//struct MemoryPool
//{
//	float radius;
//public:
//	MemoryPool()
//	{
//		Datas.reserve(10000);
//		Datas.resize(10000);
//	}
//
//	BulletData CreateBullet()
//	{
//		for (auto& it : Datas)
//		{
//			if (it.first == 0)
//			{
//				it.first = 1;
//				return it.second;
//			}
//		}
//		return nullptr;
//	}
//
//	void RetrunBullet(BulletData* pBullet)
//	{
//		for (auto& it : Datas)
//		{
//			if (&it.second == pBullet)
//			{
//				it.first = 0;
//				it.second.reset();
//			}
//		}
//	}
//private:
//	std::vector<std::pair<int, BulletData>> Datas;
//};


//오브젝트들은 이미지의 하드 포인터를 들고있으면 안되기 때문에 Weak_ptr을 사용해줘야한다.

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

std::weak_ptr<Gdiplus::Image> AssetManager::MyLoadImage(std::wstring str)
{
	std::wstring temp(TEXT("Asset\\"));
	temp.append(str);
	std::shared_ptr<Gdiplus::Image> Img(new Gdiplus::Image(str.c_str()));

	//if (Img = nullptr)
	//{
	//	return nullptr;
	//}

	std::hash<std::wstring> makeHash;
	imgDic.insert(std::make_pair(makeHash(str), Img));
	
	 return Img;
}