// #include "Error.hpp"

// int main()
// {
//     int on = 0;
//     //  try {
//     //     if ( on == 0)
//     //         throw Error();
//     //         // throw Error();
//     //  }  
//     //  catch (Error & e) 
//     //  {
//     //      e.ERR_NONICKNAMEGIVEN();
//     //  }

//      try {
//         if ( on == 0)
//             throw ERR_ERRONEUSNICKNAME("ddddd");
//             // throw ERR_ERRONEUSNICKNAME();
//      }  
//      catch (ERR_ERRONEUSNICKNAME & e) 
//      {
//          std::cout << e.what() << std::endl;
//      }


// }



// C++ program to demonstrate a custom exception class

// #include <exception>
// #include <iostream>
// #include <string>

// using namespace std;

// class MyException : public std::runtime_error {
// public:
//     MyException(const std::string& msg) : std::runtime_error(msg) {}
// };

// int main() {
//     try {
//         throw MyException("Something went wrong!");
//     }
//     catch (const std::exception& e) {
//         cout << "Caught an exception: " << e.what() << endl;
//     }
//     return 0;
// }



#include <iostream>
#include <string>
#include "Error.hpp"

int main(void){
    Error err;

    std::cout << err.ERR_BADCHANMASK() << std::endl;
}