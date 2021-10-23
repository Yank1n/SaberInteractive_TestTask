#include "List.h"

#define _CRT_SECURE_NO_WARNINGS

int main()
{
    ListNode* first = new ListNode();
    ListNode* second = new ListNode();
    ListNode* third = new ListNode();
    ListNode* fourth = new ListNode();

    first->data = "Something";
    first->next = second;
    first->prev = nullptr;
    first->rand = third;

    second->data = "stupid";
    second->next = third;
    second->prev = first;
    second->rand = fourth;

    third->data = "going";
    third->next = fourth;
    third->prev = second;
    third->rand = first;

    fourth->data = "on";
    fourth->next = nullptr;
    fourth->prev = third;
    fourth->rand = second;

    List ls(first, fourth, 4);

    FILE* file{};
    ls.Serialize(file);

    ls.Deserialize(file);

    return 0;
}