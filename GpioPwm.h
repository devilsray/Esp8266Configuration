#include "string"

class GpioPwm                   // begin declaration of the class
{
  public:                    // begin public section
    GpioPwm(int initialAge);     // constructor
    GpioPwm(const GpioPwm& copy_from); //copy constructor
    GpioPwm& operator=(const GpioPwm& copy_from); //copy assignment
    ~GpioPwm();                  // destructor

    int GetAge() const;            // accessor function
    void SetAge(int age);    // accessor function
    void Meow();
 private:                   // begin private section
    int itsAge;              // member variable
    char * string;
};

 // constructor of Cat,
GpioPwm::GpioPwm(int initialAge)
{
  itsAge = initialAge;
  string = new char[10]();
}

//copy constructor for making a new copy of a Cat
GpioPwm::GpioPwm(const GpioPwm& copy_from) {
   itsAge = copy_from.itsAge;
   string = new char[10]();
   std::copy(copy_from.string+0, copy_from.string+10, string);
}

//copy assignment for assigning a value from one Cat to another
GpioPwm& GpioPwm::operator=(const GpioPwm& copy_from) {
   itsAge = copy_from.itsAge;
   std::copy(copy_from.string+0, copy_from.string+10, string);
}

GpioPwm::~GpioPwm()                 // destructor, just an example
{
    delete[] string;
}

// GetAge, Public accessor function
// returns value of itsAge member
int GpioPwm::GetAge() const
{
   return itsAge;
}

// Definition of SetAge, public
// accessor function

 void GpioPwm::SetAge(int age)
{
   // set member variable its age to
   // value passed in by parameter age
   itsAge = age;
}

// definition of Meow method
// returns: void
// parameters: None
// action: Prints "meow" to screen
void GpioPwm::Meow()
{
//   cout << "Meow.\n";
}

// create a cat, set its age, have it
// meow, tell us its age, then meow again.
int main()
{
  int Age;
  //cout<<"How old is Frisky? ";
  //cin>>Age;
  GpioPwm Frisky(Age);
  Frisky.Meow();
  //cout << "Frisky is a cat who is " ;
  //cout << Frisky.GetAge() << " years old.\n";
  Frisky.Meow();
  Age++;
  Frisky.SetAge(Age);
  //cout << "Now Frisky is " ;
  //cout << Frisky.GetAge() << " years old.\n";
  return 0;
}
