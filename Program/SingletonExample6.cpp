// Singleton use in an example from github repo   https://github.com/herpec-j/Singleton   author herpec-j
// Several files merged into one

#include <atomic>
#include <mutex>
#include <utility>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <stack>
#include <cassert>

namespace AO
{
	namespace Singleton
	{
		inline namespace Version_1
		{
			namespace Private
			{
				class SpinLock final
				{
				public:
					// Constructors
					inline SpinLock(void)
						: atomicLock(false)
					{
						return;
					}

					SpinLock(SpinLock const&) = default;

					SpinLock(SpinLock&&) = default;

					// Assignment Operators
					SpinLock& operator=(SpinLock const&) = default;

					SpinLock& operator=(SpinLock&&) = default;

					// Destructor
					~SpinLock(void) = default;

					// Methods
					inline void lock(void)
					{
						while (atomicLock.exchange(true));
					}

					inline void unlock(void)
					{
						atomicLock = false;
					}

					inline bool isLocked(void) const
					{
						return atomicLock;
					}

				private:
					// Attributes
					std::atomic_bool atomicLock;
				};
			}
		}
	}
}

namespace AO
{
	namespace Singleton
	{
		inline namespace Version_1
		{
			template <class Derived>
			class Singleton
			{
			public:
				// Static Methods
				template <typename... Args>
				static inline Derived& GetInstance(Args &&...args)
				{
					return *GetInstancePointer(std::forward<Args>(args)...);
				}

				template <typename... Args>
				static inline Derived* GetInstancePointer(Args &&...args)
				{
					static Derived* instancePointer = CreateInstance(std::forward<Args>(args)...);
					return instancePointer;
				}

			protected:
				using Access = Singleton<Derived>;

				// Constructors
				Singleton(void) = default;

				Singleton(Singleton const&) = default;

				Singleton(Singleton&&) = default;

				// Assignment Operators
				Singleton& operator=(Singleton const&) = default;

				Singleton& operator=(Singleton&&) = default;

				// Destructor
				virtual ~Singleton(void) = default;

			private:
				// Static Attributes
				static Derived* InstancePointer;

				static Private::SpinLock Lock;

				// Static Methods
				template <typename... Args>
				static inline Derived* CreateInstance(Args &&...args)
				{
					if (Singleton::InstancePointer == nullptr)
					{
						std::lock_guard<decltype(Singleton::Lock)> lock(Singleton::Lock);
						if (Singleton::InstancePointer == nullptr)
						{
							void* data = static_cast<void*>(GetData());
							new (data) Derived(std::forward<Args>(args)...);
							Singleton::InstancePointer = reinterpret_cast<Derived*>(data);
							std::atexit(&Singleton::DestroyInstance);
						}
					}
					return Singleton::InstancePointer;
				}

				static inline void DestroyInstance(void)
				{
					reinterpret_cast<Derived*>(GetData())->~Derived();
				}

				static inline unsigned char* GetData(void)
				{
					static unsigned char data[sizeof(Derived)];
					return data;
				}
			};

			template <class Derived>
			Derived* Singleton<Derived>::InstancePointer = nullptr;

			template <class Derived>
			Private::SpinLock Singleton<Derived>::Lock;
		}
	}
}

static char const* __success = "Success!";
static std::queue<char> __letters;
static std::stack<std::size_t> __numbers;

template <std::size_t N>
class Class final : public AO::Singleton::Singleton < Class<N> >
{
private:
	friend typename Class::Access;

	// Constructors
	Class(void)
	{
		initialize();
		__numbers.push(N);
		__letters.push(*__success++);
	}

	Class(Class const&) = default;

	Class(Class&&) = default;

	// Assignment Operators
	Class& operator=(Class const&) = default;

	Class& operator=(Class&&) = default;

	// Destructor
	~Class(void)
	{
		assert(__numbers.top() == N && "Invalid destruction order");
		__numbers.pop();
		std::cout << __letters.front();
		__letters.pop();
		if (__letters.empty())
		{
			std::cout << std::endl;
		}
	}

	// Methods
	void initialize(void) const;
};

template <>
void Class<1>::initialize(void) const
{
	Class<4>::GetInstance();
	Class<6>::GetInstance();
}

template <>
void Class<2>::initialize(void) const
{
	return;
}

template <>
void Class<3>::initialize(void) const
{
	Class<1>::GetInstance();
}

template <>
void Class<4>::initialize(void) const
{
	Class<2>::GetInstance();
}

template <>
void Class<5>::initialize(void) const
{
	return;
}

template <>
void Class<6>::initialize(void) const
{
	return;
}

template <>
void Class<7>::initialize(void) const
{
	Class<8>::GetInstance();
}

template <>
void Class<8>::initialize(void) const
{
	Class<6>::GetInstance();
	Class<5>::GetInstance();
	Class<3>::GetInstance();
}

int main(int argc, char* argv[])
{
	Class<1>::GetInstance();
	Class<2>::GetInstance();
	Class<3>::GetInstance();
	Class<4>::GetInstance();
	Class<5>::GetInstance();
	Class<6>::GetInstance();
	Class<7>::GetInstance();
	Class<8>::GetInstance();
	return EXIT_SUCCESS;
}