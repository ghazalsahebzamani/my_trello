#ifndef __EXP_H__
#define __EXP_H__
#include <iostream>
using namespace std;
class MyException{
public:
    virtual const char* what(){
    }
};
class Quit:public MyException{

};
class BadAccess:public MyException{
public:
    const char*what(){
        return "You don't have the permission to access the following";
    }
};
class BadIO :public MyException{
public:
        virtual const char*what(){
        return "invalid input!try again.";
    }
};
class UserTaken:public BadIO{
public:
    const char* what(){
        return"already taken.choose a different one";
    }
};
class ShortWord:public BadIO{
public:
    const char* what(){
        return "input should conain at least 3 carachters.try again.";
    }

};
class WeakPass:public BadIO{
public:
    const char* what(){
        return "week password.It should contain at least 6 characters.try again.";
    }
};
class DoesntExist:public BadIO{
public:
    const char* what(){
        return "invalid login.user/pass doesnt exist.try again:t back to menu:b register:r";
    }
};
class NotFound:public BadIO{
public:
    virtual const char* what(){
        return "the desired was not found";
    }
};
class NotaNumber: public BadIO{
public:
    const char* what(){
        return "not a number!";
    }

};
class NoCardsFound:public NotFound
{
public:
    const char* what(){
        return "no cards found.";
    }
};
class NoMemFound:public NotFound
{
public:
    const char* what(){
        return "no members found.";
    }
};
#endif
