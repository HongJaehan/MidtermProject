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


//������Ʈ���� �̹����� �ϵ� �����͸� ��������� �ȵǱ� ������ Weak_ptr�� ���������Ѵ�.

std::weak_ptr<Gdiplus::Image> AssetManager::GetImage(std::wstring str)
{
	//hash�� 
	std::hash<std::wstring> makeHash;
	//ret�� return value
	std::weak_ptr<Gdiplus::Image> ret;

	//hash�� ���� imgDic�� �ִ� img������ ã�´�.

	auto it = imgDic.find(makeHash(str));
	
	//���� ���� imgDic�� ���ٸ� MyLoadImage�� ���� img������ �������ش�.
	if (it == imgDic.end())
		ret = MyLoadImage(str);
	else
		ret = it->second;

	//expired�� ����ϸ� ���� ����ϰ��ִ� shared Point�� ���¸� Ȯ���� �� �ִ�.
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