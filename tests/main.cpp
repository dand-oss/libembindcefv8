#include "embindcefv8.h"
#include <iostream>
#include "cef.h"

#ifdef EMSCRIPTEN
    #define EXECUTE_JS      EM_ASM
#else
    #define EXECUTE_JS(src) \
        #src
#endif

struct TestStruct
{
    TestStruct()
        :
        floatMember(123)
    {
    }

    float
        floatMember;
};

int main(int argc, char* argv[])
{
    std::cout << "embindcefv8 - tests" << std::endl;

    #ifdef CEF
        initCef(argc, argv);
    #endif

    embindcefv8::ValueObject<TestStruct>("TestStruct")
        .constructor()
        .field("floatMember", &TestStruct::floatMember)
        ;

    EXECUTE_JS(
        var test = Module.TestStruct();
        console.log(test.floatMember);
    );

    return 0;
}
