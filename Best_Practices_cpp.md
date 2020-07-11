Source: Youtube - https://www.youtube.com/watch?v=nqfgOCU_Do4

# Best Practices in C++.

1. Construction separate from assignments
 
 ```cpp
  void do_work()
  {
      std::string str;                                                                    
      str = "Hello-world"
  }
```
```cpp
    void do_work()
    {
        const std::string str = "Hello-world"
    }
```

2. Construction / Assignment /Out Variables
   https://stlab.cc/tips/stop-using-out-arguments.html
    
3. Raw Loops 

4. Multi-Step functions
   Instead decompose steps into functions and/or lambdas
    
5. Non-Cannonical Operators

6. Code With Conversion - implicit/explicit/casts
    
```cpp
    #include <string>   
    void use_string(const std::string &s)
    std::string get_string();
 
    int main()
    {
      const std::string str = get_string();
      use_string(str.c_str()); // string->c_str->string
    }
```

 7. Code With Conversions
    What is std::move ? It is cast
    
```cpp
std::string s;
std::move(s) // unconditional cast to 'std::string &&'
```
```cpp
#include<string>

std::string get_Value()
{
  std::string s = "Hello-World"
  return std::move(s);
}
std::string s;
std::move(s) // unconditional cast to 'std::string &&'
```
Pessimizing "return by move" prevents move elision.
std::move is another type of conversion that is code smell.

8. Casting Away const

```cpp
int main()
{
  const int i = 4;
  const_cast<int &>(i) = 13;
  return i; //What is returned - Undefined behaviour
}
```
Modifying a const object during its lifetime is UB. const_cast is another explicit conversion that is a code smell.

9. What are the implications of using a static variable?

```cpp
#include<string>

void log_error(std::string const &location, 
               std::dtring const &desc);
void do_things(bool const error)
{
  static std::string const FunctionName("do_things");
  //constexpr std::string const FunctionName("do_things");
  
  if(error)
  {
  log_error(FunctionName, "Error Occured!");
  }
}
```
thread safe initialisation for static.
*static const* is a code smell that should probably should be *constexpr*

10. extern const

```cpp
extern int const Value;

int getValue 
{
  return Value;
}
```
Its like we are telling the compiler: I have some really imp info for you, but I'am not
going to tell you what it is.
This is also a code smell.

11. Raw *new* and *delete*

```cpp
#include<memory>

void use_int()
{
  auto i = std::make_unique<int>(5);
}
of course this wasteful and the heap should be avoided if possible.

12. code example 

## 1
```cpp
#include<iostream>
using namespace std;

int main()
{
  int length;
  string greet1 = "Hello";
  string greet1 = "-World";
  string greet3= greet1 + greet2;
  
  length = greet3.size();
}
```
Changes done to make it better:

```cpp
#include<string>

int main()
{
  const std::g greet1 = "Hello";
  const std::string greet1 = "-World";
  auto const greet3 = greet1 + greet2;
  
  const auto length = greet3.size();
  return length;
}
```
## 2

Read user inputs and calc factorial
```cpp
#include<iostream>

int main()
{
  int i, n, fact = 1;
  
  std::cout << "Enter a whole number:";
  std::cin << n;
  
  for(i = 0; i <= n; ++i)
  {
    fact *= i;
  }
  
  std::cout << "\n Factorial of " << n << "=" << fact << std::endl;
  return 0;
}
```
```cpp
#include<iostream>

int main()
{
  int i, n, fact = 1;
  
  std::cout << "Enter a whole number:";
  std::cin << n;
  
  for(i = 0; i <= n; ++i)
  {
    fact *= i;
  }
  
  std::cout << "\n Factorial of " << n << "=" << fact << std::endl;
  return 0;
}
```
# Conclusion
There is one thing that keeps coming up
...That has not been explicitly mentioned

## *const*

### Mark Everything as *const* as possibly can. 
### When you make static data *const*, Compiler moves readonly memory section.
