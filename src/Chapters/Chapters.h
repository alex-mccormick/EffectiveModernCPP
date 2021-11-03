#include "../include/stdafx.h"
#include "../Generic/BookChapter.h"
#include <string_view>
#include <mutex>
#include <memory>

class C1_DeducingTypes
    : public BookChapter
{
    public:
        C1_DeducingTypes();
        static void TypeDeduction(void);
        static void TemplateTypeDeduction(void);
        static void AutoTypeDeduction(void);
        static void ViewTypes(void);

    private:
        template<typename T>
        static void DeduceTypeFromFunction(const T&);
        template<typename T>
        static void DeduceTypeFromBoost(const T&);
        template<typename T>
        static void DeduceTypeFromStd(const T&);

        template<typename T>
        static void DeduceTypeFromRValueReference(T&&);

        template<typename T>
        static void DeduceTypeFromPassByValue(T);

        template<typename T, std::size_t N>
        static constexpr std::size_t ArraySize(T (&)[N]) noexcept;
};
class C2_Auto : public BookChapter
{
    public:
        C2_Auto();

        static void BoolArray(void);
        static void ExplicitInitialiser(void);
        static void MutexDemo(void);
};
class C3_ModernCpp : public BookChapter
{
    public:
        C3_ModernCpp();

        static void TuplesAndEnums(void);
        static void Overriding(void);
        static void MemberFunctionQualifiers(void);
        static void ConstexprDemo(void);
        static void RuleOfThree(void);
};
class C4a_SmartPointers : public BookChapter
{
    public:
        C4a_SmartPointers();

        static void ResourceOwnership(void);
        static void CRTP(void);
        static void WeakPtr(void);
};
class C4b_PImpl : public BookChapter
{
    public:
        C4b_PImpl();
        static void PImpl(void);
};
// class C5_Moves : public BookChapter
// {
//     C5_Moves();
//     ~C5_Moves();
// }
class C6_Lambda : public BookChapter
{
    public:
        C6_Lambda();
        ~C6_Lambda();

        static void CaptureModes(void);
        static void InitCapture(void);
        static void Bind(void);
        static void GenericLambda(void);

        static int staticDivisor;
};
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