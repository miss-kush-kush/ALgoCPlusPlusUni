template<typename T>
struct Node
{
    Node* pNext;
    Node* pPrev;
    T data;
    Node(T data = T(), Node* pNext = nullptr, Node* pPrev = nullptr)
    {
        this->data = data;
        this->pNext = pNext;
        this->pPrev = pPrev;
    }
};
