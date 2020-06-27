#ifndef singleton_h
#define singleton_h

#include <memory>

template <typename T>
class Singleton
{
private:
	static T* instance_; // シングルトンインスタンス

	// コピーコンストラクタを禁止する
	Singleton(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;

	// コピー代入演算子を禁止する
	Singleton& operator=(const Singleton&) = delete;
	Singleton& operator=(Singleton&&) = delete;

protected:
	Singleton() {} // 外部でのインスタンス作成は禁止
	virtual ~Singleton() {}

public:
	// シングルトンインスタンスへの参照を取得する
	inline static T& instance()
	{
		return *instance_;
	}
	// シングルトンインスタンスを生成する
	inline static void create()
	{
		if (!instance_) instance_ = new T();
	}
	// シングルトンインスタンスを破棄する
	inline static void destroy()
	{
		delete instance_;
		instance_ = nullptr;
	}
};

template <typename T> T* Singleton<T>::instance_ = nullptr;

#endif // !singleton_h