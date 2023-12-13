#include <UnitTest++/UnitTest++.h>
#include "Cipher.h"
#include <iostream>
#include <locale>
#include <codecvt>
using namespace std;
SUITE(KeyTest) 
{
    TEST(LargeLetters) {
        Gronsveld test(L"ПРИВЕТ");
        CHECK(true);
    }
    TEST(LargeAndSmallLetters) {
        Gronsveld test(L"ПрИвеТ");
        CHECK(true);
    }
    TEST(EmptyKey) {
        CHECK_THROW(Gronsveld test(L""), cipher_error);
    }
    TEST(Key_with_a_space) {
        CHECK_THROW(Gronsveld test(L"при вет"), cipher_error);
    }
    TEST(Key_with_invalid_characters_number) {
        CHECK_THROW(Gronsveld test(L"пр1вет"), cipher_error);
    }
    TEST(Key_with_invalid_characters_special_character) {
        CHECK_THROW(Gronsveld test(L"пр!в3т"), cipher_error);
    }
}

struct KeyAB_fixture { 
    Gronsveld * pointer;
    KeyAB_fixture()
    {
        pointer = new Gronsveld(L"АВ");
    }
    ~KeyAB_fixture()
    {
        delete pointer;
    }
};

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyAB_fixture, LargeLetters) {
        wstring open_text = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
        wstring result_correct = L"АГВЕДЖЁИЗКЙМЛОНРПТСФУЦХШЧЪЩЬЫЮЭАЯ";
        CHECK_EQUAL(true, result_correct == pointer->encrypt(open_text));
    }
    TEST_FIXTURE(KeyAB_fixture, SmallLetters) {
        wstring open_text = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
        wstring result_correct = L"АГВЕДЖЁИЗКЙМЛОНРПТСФУЦХШЧЪЩЬЫЮЭАЯ";
        CHECK_EQUAL(true, result_correct == pointer->encrypt(open_text));
    }
    TEST_FIXTURE(KeyAB_fixture,NumberInText ) {
        wstring open_text = L"пр1в3т";
        CHECK_THROW(pointer->encrypt(open_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,TextWithSpecialSymbol) {
        wstring open_text = L"пр!в3т^_^";
        CHECK_THROW(pointer->encrypt(open_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,TextWithASpace ) {
        wstring open_text = L"п р ивет";
        CHECK_THROW(pointer->encrypt(open_text),cipher_error);
    }

}
SUITE(DecryptTest) 
{
   TEST_FIXTURE(KeyAB_fixture, LargeLetters) {
        wstring cipher_text = L"АГВЕДЖЁИЗКЙМЛОНРПТСФУЦХШЧЪЩЬЫЮЭАЯ";
        wstring result_correct = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
        CHECK_EQUAL(true, result_correct == pointer->decrypt(cipher_text));
    }
    TEST_FIXTURE(KeyAB_fixture, Smallletters) {
        wstring cipher_text = L"агведжёизкймлонрптсфуцхшчъщьыюэая";
        wstring result_correct = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
        CHECK_EQUAL(true, result_correct == pointer->decrypt(cipher_text));
    }
    TEST_FIXTURE(KeyAB_fixture,LargeAndSmallLetters ) {
        wstring cipher_text = L"ЗДраВстуЙТЕ";
        wstring result_correct = L"ЗВРЮВПТСЙРЕ";
        CHECK_EQUAL(true, result_correct == pointer->decrypt(cipher_text));
    }

    TEST_FIXTURE(KeyAB_fixture, EmptyText) {
        wstring cipher_text = L"";
        CHECK_THROW(pointer->decrypt(cipher_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,TextWithNumber) {
        wstring cipher_text = L"п0ка";
        CHECK_THROW(pointer->decrypt(cipher_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,TextWithSymbol) {
        wstring cipher_text = L"пок^_^еда";
        CHECK_THROW(pointer->decrypt(cipher_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,TextWithASpace ) {
        wstring cipher_text = L"по ка";
        CHECK_THROW(pointer->decrypt(cipher_text),cipher_error);
    }
}
int main()
{
    return UnitTest::RunAllTests();
}
