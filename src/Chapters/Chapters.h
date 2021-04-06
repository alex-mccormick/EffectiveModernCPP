#include "../include/stdafx.h"
#include "../Generic/BookChapter.h"
#include <string_view>

class C1_DeducingTypes
    : public BookChapter
{
    public:
        C1_DeducingTypes();
        ~C1_DeducingTypes();
        static void TypeDeduction(void);

    private:
        template<typename T>
        static void DeduceTypeFromFunction(const T&);
};
// class C2_Auto : public BookChapter
// {
//     C2_Auto();
//     ~C2_Auto();
// }
// class C3_ModernCpp : public BookChapter
// {
//     C3_ModernCpp();
//     ~C3_ModernCpp();
// }
// class C4_SmartPointers : public BookChapter
// {
//     C4_SmartPointers();
//     ~C4_SmartPointers();
// }
// class C5_Moves : public BookChapter
// {
//     C5_Moves();
//     ~C5_Moves();
// }
// class C6_Lambda : public BookChapter
// {
//     C6_Lambda();
//     ~C6_Lambda();
// }
// class C7_ConcurrencyAPI : public BookChapter
// {
//     C7_ConcurrencyAPI();
//     ~C7_ConcurrencyAPI();
// }
// class C8_Tweaks : public BookChapter
// {
//     C8_Tweaks();
//     ~C8_Tweaks();
// }