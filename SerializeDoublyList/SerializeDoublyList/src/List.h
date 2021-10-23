#pragma once

#include <string>

struct ListNode 
{
    ListNode*   prev;
    ListNode*   next;
    ListNode*   rand;
    std::string data;
};

class List 
{
public:
    List(ListNode* head, ListNode* tail, int count);

    void Serialize(FILE* file);
    void Deserialize(FILE* file);
private:
    bool IsEmpty();
    void WriteToFile(FILE* file, const char* str, size_t size);
    void Clear();
    void InsertBack(const std::string& data);
private:
    ListNode* head;
    ListNode* tail;
    int       count;
};
