#pragma once

template <typename T>
class Singleton
{
protected:
	Singleton() {};
	//Singleton(const Singleton& other);
	virtual ~Singleton() {};

private :
	static void destroy()
	{
		if (instance != nullptr)
		{
			delete instance;
		}
	}
public:
	static T* GetInstance()
	{
		if (instance == nullptr)
			instance = new T();
		return instance;
	}

private:
	static T* instance;
};

template <typename T> 
T* Singleton <T>::instance;