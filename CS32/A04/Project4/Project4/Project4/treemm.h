#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED
#include <vector>

template <typename KeyType, typename ValueType>
struct Node {
    KeyType key;
    std::vector<ValueType> values;
    Node* left;
    Node* right;
    Node(const KeyType& k, const ValueType& v) : key(k), left(nullptr), right(nullptr) {
        values.push_back(v);
    }
    void Add(const ValueType& v) {
        values.push_back(v);
    }
};
template <typename KeyType, typename ValueType>
class TreeMultimap
{
  public:
    class Iterator
    {
    public:
        Iterator()
        {
            m_ptr = nullptr;
        }

        Iterator(std::vector<ValueType>& a) {
            m_ptr = &a.front();
            m_end = &a.back();
        }

        Iterator(ValueType* iter, ValueType* end) {
            m_ptr = iter;
            m_end = end;
        }

        ValueType& get_value() const
        {
            if (is_valid()) {
                return *m_ptr;
            }
            else {
                return *m_end;
            }
            
        }

        bool is_valid() const
        {
            return m_ptr != nullptr;
        }

        void advance()
        {
            if (m_ptr == nullptr) return;
            else if (m_ptr == m_end) m_ptr = nullptr;
            else m_ptr++;
        }



    private:
        ValueType* m_ptr;
        ValueType* m_end;
    };

    TreeMultimap()
    {
        m_root = nullptr;
    }

    ~TreeMultimap()
    {
        deconstructNode(m_root);
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        // Replace this line with correct code.
        if (m_root == nullptr) {
            m_root = new Node<KeyType, ValueType>(key, value);
            return;
        }
        Node<KeyType, ValueType>* root = m_root;    //search BST
        for (;;) {
            if (key > root->key) {
                if(root->right != nullptr){
                    root = root->right;
                }
                else {
                    root->right = new Node<KeyType, ValueType>(key, value);
                    return;
                }
            }
            else if (key < root->key) {
                if(root->left != nullptr){
                    root = root->left;
                }
                else {
                    root->left = new Node<KeyType, ValueType>(key, value);
                    return;
                }
            }
            else {
                root->Add(value);
                return;
            }
        }
    }

    Iterator find(const KeyType& key) const {
        Node<KeyType, ValueType>* cur = m_root;
        if (cur == nullptr) return Iterator();  // if no root node, return invalid iterator


        while (cur != nullptr) {
            if (key > cur->key) {   // if key large than current node's value 
                if (cur->right != nullptr){
                    cur = cur->right;
                    continue;
                }
                else {
                    return Iterator();
                }
            }
            else if (key < cur->key) { //if key less than current node's value
                if (cur->left != nullptr) { //go left if can
                    cur = cur->left;
                    continue;
                }
                else {
                    return Iterator();
                }
            }
            else {
                return Iterator(cur->values);   //if found key, return it's value's iterator
            }
        }
        return Iterator();
    }
    private:
        Node<KeyType, ValueType>* m_root;
        void deconstructNode(Node<KeyType, ValueType>* root) {
            if (root == nullptr) return;
            deconstructNode(root->left);
            deconstructNode(root->right);
        }
};


#endif // TREEMULTIMAP_INCLUDED

