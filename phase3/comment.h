#ifndef __COMMENT_H__
#define __COMMENT_H__
#include "member.h"
class Comment{
public:
    Comment(Member* _composer,vector<string> _text):composer(_composer),text(_text){}
    void show_comment(ostream& out);
private:
    Member* composer;
    vector<string> text;
};
#endif
