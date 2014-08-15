#pragma once
template<class T>
class CocosPtr
{
public:
	CocosPtr(T *ptr) : ptr_(ptr)
	{
		if (ptr_) ptr_->retain();
	}
	~CocosPtr()
	{
		if (ptr_) ptr_->release();
	} 

private:
	T *ptr_;
};

