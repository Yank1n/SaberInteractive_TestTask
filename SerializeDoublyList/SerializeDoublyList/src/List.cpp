#include "List.h"

#include <stdlib.h>
#include <stdio.h>
#include <vector>

List::List(ListNode* head, ListNode* tail, int count)
    : head{ head }, tail{ tail }, count{ count } {}

void List::Serialize(FILE* file)
{
    file = fopen("out.txt", "wb");
    if (file == 0 && IsEmpty())
        return;

    WriteToFile(file, std::to_string(count).c_str(), 1);

    int offset = 0;
    for (auto node = head; node != nullptr; node = node->next)
    {
        *reinterpret_cast<int*>(&(node->prev)) = offset;
        ++offset;
        WriteToFile(file, node->data.c_str(), strlen(node->data.c_str()));
    }

    for (auto node = head; node != nullptr; node = node->next)
    {
        offset = *reinterpret_cast<int*>(&(node->rand->prev));
        WriteToFile(file, std::to_string(offset).c_str(), 1);
    }

    ListNode* prev = nullptr;
    for (auto node = head; node != nullptr; node = node->next)
    {
        node->prev = prev;
        prev = node;
    }

    fclose(file);
}

void List::Deserialize(FILE* file)
{
    Clear();

    file = fopen("out.txt", "rb");
    if (file == 0)
        return;

    int length = -1;
    fscanf(file, "%d\n", &length);

    if (length < 0)
        return;

    std::vector<ListNode*> pointers;
    pointers.reserve(length);

    char buff[256];
    for (int index = 0; index < length; ++index)
    {
        if (fgets(buff, sizeof(buff), file) != NULL);

        InsertBack(buff);
        pointers.push_back(tail);
    }

    int index{};
    for (auto node = head; node != nullptr; node = node->next)
    {
        fscanf(file, "%d\n", &index);
        node->rand = pointers[index];
    }

    fclose(file);
}

bool List::IsEmpty()
{
    if (!count)
        return true;

    return false;
}

void List::WriteToFile(FILE* file, const char* str, size_t size)
{
    fwrite(str, sizeof(char), size, file);
    fprintf(file, "\n");
}

void List::Clear()
{
    head = new ListNode();
    tail = new ListNode();

    count = 0;
}

void List::InsertBack(const std::string& data)
{
    ListNode* tmp = new ListNode();

    switch (count)
    {
        case 0:
        {
            tmp->prev = nullptr;
            tmp->next = nullptr;
            tmp->rand = nullptr;
            tmp->data = data;
            head = tmp;
            tail = tmp;

            break;
        }
        default:
        {
            tail->next = tmp;
            tmp->next = nullptr;
            tmp->prev = tail;
            tmp->data = data;
            tail = tmp;

            break;
        }
    }

    ++count;
}