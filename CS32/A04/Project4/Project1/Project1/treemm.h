#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <vector>
struct Node;

template <typename KeyType, typename ValueType>
class TreeMultimap
{
  public:
    class Iterator{
    public:
        Iterator(){
            valid = false;
        }
        
        Iterator(typename std::vector<ValueType>::iterator currValue, typename std::vector<ValueType>::iterator end){
            this->currValue = currValue;
            this->end = end;
            valid = true;
        }
        
        bool is_valid() const{
            return valid;
        }
        
        ValueType& get_value() const{
            if (is_valid())
                return *currValue;
            else
                return *end;
        }
        
        void advance(){
            if (is_valid())
                currValue++;
            if (currValue == end)
                valid = false;
            
        }

      private:
        typename std::vector<ValueType>::iterator currValue;
        typename std::vector<ValueType>::iterator end;
        bool valid;
    };

    TreeMultimap() : root(nullptr)
    {}

    ~TreeMultimap()
    {
        deleteTree(root);
    }
    
    void insert(const KeyType& key, const ValueType& value)
    {
        Node* result = findHelper(root, key);
        if (result == nullptr)
            insertHelper(root, key, value);
        else
            result->addValue(value);
    }
    
    Iterator find(const KeyType& key) const
    {
        Node* result = findHelper(root, key);
        if (result == nullptr)
            return Iterator();
        else
            return Iterator(result->values.begin(), result->values.end());
    }

  private:
    struct Node{
        KeyType key;
        Node* left;
        Node* right;
        std::vector<ValueType> values;
        Node(const KeyType key, const ValueType& value)
        : key(key), left(nullptr), right(nullptr)
        {
            ValueType newV = value;
            values.clear();
            values.push_back(newV);
        }
        void addValue(const ValueType& v){
            ValueType newV = v;
            values.push_back(newV);
        }
    };
    Node* root;
    
    void deleteTree(Node* node){
        if (node != nullptr){
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }
    
    void insertHelper(Node*& node, const KeyType& key, const ValueType& value) const{
        if (node == nullptr)
            node = new Node(key, value);
        else if (key < node->key)
            insertHelper(node->left, key, value);
        else // key > node->key
            insertHelper(node->right, key, value);
    }
    
    Node* findHelper(Node* node, const KeyType& key) const{
        if (node == nullptr)
            return nullptr;
        else if (node->key == key)
            return node;
        else if (key < node->key)
            return findHelper(node->left, key);
        else // key > root->key
            return findHelper(node->right, key);
    }
};

#endif // TREEMULTIMAP_INCLUDED
