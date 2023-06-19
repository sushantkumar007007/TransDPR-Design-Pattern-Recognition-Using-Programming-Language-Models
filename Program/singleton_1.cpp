#include <stdexcept>
 
template <typename Self>
class singleton
{
protected:
	static Self*
		sentry;
public:	
	static Self& 
		instance()
	{
		return *sentry;
	}
	singleton()
	{
		if(sentry)		
      throw std::logic_error("Error: attempt to instantiate a singleton over a pre-existing one!");
		sentry = (Self*)this;
	}
	virtual ~singleton()
	{
		if(sentry == this)
			sentry = 0;
	}
};
template <typename Self>
Self* 
	singleton<Self>::sentry = 0;
 

#include <iostream>
#include <string>
 
using namespace 
	std;
 
class controller : public singleton<controller>
{
public:
	controller(string const& name)
	: name(name)
	{
		trace("begin");
	}
	~controller()
	{
		trace("end");
	}
	void
		work()
	{
		trace("doing stuff");
	}
	void
		trace(string const& message)
	{
		cout << name << ": " << message << endl;
	}
	string
		name;
};
int
	main()
{
	controller*
		first = new controller("first");
	controller::instance().work();
	delete first;

	controller
		second("second");
	controller::instance().work();
	try
	{
	
		controller
			goner("goner");
		controller::instance().work();
	}
	catch(exception const& error)
	{
		cout << error.what() << endl; 
	}
	controller::instance().work();

	controller
		goner("goner");
	controller::instance().work();
}


#include <iostream>
using namespace std;

int main() {
    char c;
    bool isLowercaseVowel, isUppercaseVowel;

    cout << "Enter an alphabet: ";
    cin >> c;

    // evaluates to 1 (true) if c is a lowercase vowel
    isLowercaseVowel = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');

    // evaluates to 1 (true) if c is an uppercase vowel
    isUppercaseVowel = (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');

    // show error message if c is not an alphabet
    if (!isalpha(c))
      printf("Error! Non-alphabetic character.");
    else if (isLowercaseVowel || isUppercaseVowel)
        cout << c << " is a vowel.";
    else
        cout << c << " is a consonant.";

    return 0;
}