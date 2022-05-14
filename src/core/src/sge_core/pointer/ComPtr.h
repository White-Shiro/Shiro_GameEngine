#pragma once

namespace sge {

template<class T>
class ComPtr : public NonCopyable {
public:
	ComPtr() = default;

	ComPtr(const ComPtr& r)	{ reset(r._p); } 				//ctor for LValue
	ComPtr(ComPtr&& r) { reset(r._p); r._p = nullptr; } 	//ctor for RValue/TempValue

	void operator=(const ComPtr& r) { if (r._p == _p) return; reset(r._p); }
	void operator=(ComPtr && r)		{ if (r._p == _p) return; reset(r._p); r._p = nullptr; }

	~ComPtr() noexcept { reset(nullptr); }

	T* operator->() noexcept		{ return _p; }
	operator T*() noexcept			{ return _p; }

			T* ptr() noexcept		{ return _p; }
	const	T* ptr() const noexcept	{ return _p; }


	//reasign a new pointer 
	void reset(T* p) {

		//Prevent Pointer pointing to a same adr eg a=b;b=a;
		if (p == _p) return; 

		//Before Assigning new Pointer, Release current Pointer if any
		if (_p) {
			_p->Release();
			_p = nullptr;
		}

		//Assign new Pointer
		_p = p;
		if (_p) {
			//Add Ref count 
			_p->AddRef();
		}
	}

	T** ptrForInit() noexcept { reset(nullptr); return &_p; }

	T* detach() { T* o = _p; _p = nullptr; return o; }
private:
	T* _p = nullptr;
};

}