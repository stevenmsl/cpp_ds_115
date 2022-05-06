#ifndef NODE_H
#define NODE_H

#include <vector>
#include <cinttypes>
using namespace std;

namespace sol940
{
    struct Node
    {
        Node *left;
        Node *right;
        int val;
        Node(int val) : val(val), left(nullptr), right(nullptr){};
    };
}
#endif