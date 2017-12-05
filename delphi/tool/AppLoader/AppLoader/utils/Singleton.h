#ifndef _SINGLETON_H
#define _SINGLETON_H
template<typename T> 
class Sigleton{

protected:
	static T* mTheMe;

protected:
	Sigleton()
	{
		Init();
	}
	~Sigleton()
	{
		UnInit();
	}
public:
	virtual void Init(){}
	virtual void UnInit(){}

public:
	static T* GetInstance()
	{
		if (mTheMe==NULL)
		{
			mTheMe = new T();
		}

		return mTheMe;
	}

	static void Release()
	{
		if (mTheMe!=NULL)
		{
			delete mTheMe;
			mTheMe = NULL;
		}
	}

};

template <typename T> 
T* Sigleton<T>::mTheMe = NULL;



#endif