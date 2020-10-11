#include "sequoia.h"

//Returns a pointer to the first node in this subtree containing x
//Returns null pointer if it can't find x
SequoiaNode* SequoiaNode::search(int x)
{
  if (x == value)
    return this;
  else if (x < value && left != nullptr)
    return left->search(x);
  else if (x > value && right != nullptr)
    return right->search(x);
  else
    return nullptr;  
}

//Inserts a new node into this Sequoia
//Updates root if necessary
//Does *not* update height or ensure tallness
void Sequoia::insert(int x)
{
  if (root != nullptr)
    root->insert(x);
  else
    root = new SequoiaNode(x);
  size++;
  while (root->parent != nullptr)
    root = root->parent;
  /*if this->parent = nullptr;
    root = this;
    */
  
}

//Removes a node from this Sequoia
//Updates root if necessary
//No effect if the tree doesn't contain the given value
//Does *not* update height or enforce tallness
void Sequoia::remove(int x)
{
  if (root == nullptr)
    return;
  SequoiaNode* victim = root->search(x);
  SequoiaNode* p;
  if (victim == nullptr)
    return;
  else
  {
    if (victim == root)
      if (root->left != nullptr)
        root = root->left;
      else
        root = root->right;
    victim = victim->remove();
    p = victim->parent;
    delete victim;
    p->fixBalanceRemove();
    while (root->parent != nullptr)
      root = root->parent;

  }
}

//Basic BST insertion function
//Does *not* update height or ensure tallness
void SequoiaNode::insert(int x)
{
  if (x < value)
  {
    if (left != nullptr)
      left->insert(x);
    else
    {
      left = new SequoiaNode(x);
      left->parent = this;
    }
  }
  else
  {
    if (right != nullptr)
      right->insert(x);
    else
    {
      right = new SequoiaNode(x);
      right->parent = this;
    }
  }
  this->fixBalanceInsert();
}

//Basic BST removal function
//Does *not* update height or ensure tallness
//Returns pointer to the node removed (2 child case)
//Sets children to null but does not delete node
//(see Sequoia::remove(x))
SequoiaNode* SequoiaNode::remove()
{
  if (left == nullptr && right == nullptr)
  {
    if (parent != nullptr)
      if (parent->left == this)
        parent->left = nullptr;
      else
        parent->right = nullptr;
  }
  else if (left != nullptr && right == nullptr)
  {
    left->parent = parent;
    if (parent->left == this)
      parent->left = left;
    else
      parent->right = left;
  }
  else if (left == nullptr && right != nullptr)
  {
    right->parent = parent;
    if (parent->left == this)
      parent->left = right;
    else
      parent->right = right;
  }
  else
  {
    SequoiaNode* swap = left;
    int temp = value;
    while (swap->right != nullptr)
      swap = swap->right;
    value = swap->value;
    swap->value = temp;
    return swap->remove();
  }
  left = right = nullptr;
  return this;
}

// Function for updating the nodes of a Sequoia
// following an insertion to maintain "tallness"
// Not called in driver, so not required to be implemented
// If not implementing, must fix height and tallness elsewhere
void SequoiaNode::fixBalanceInsert()
{
  this->updateHeight();
  //iterate up the tree, starting at parent of newly created node
    //at each node, recalculate height by looking at left and right children (recommend updateHeight() function)
    //check whether height of left and right trees satisfy the tallness property
    if(this->isTall()){
      if(parent != nullptr)
        this->parent;}
    else if(left->height >= right->height && left->height < (2 * right->height))
    {
      //rotate right node left, update height of rotated node
      //right node becomes parent, parent becomes left child
      if(parent == nullptr)
      {
        right->parent = parent;
        parent = right;
        if(right->left = nullptr)
          right = nullptr;
        else
          right = right->left;
        parent->left = this;
      }
      else{
        right->parent = parent;
        if(parent->right == this)
          parent->right = right;
        else
        {
          parent->left = right;
        }
        parent = right;
        right = parent->left;
        parent->left = this;
      }
      this->parent->updateHeight();
      
    }
    else
    {
      //rotate left child to the right, update height of rotated node
      //left child becomes parent, parent becomes right
     if(parent == nullptr)
     {
        left->parent = parent;
        parent = left;
        left = left->right;
        parent->right = this;
     }
     else
     {
       left->parent = parent;
       if(parent->right == this)
          parent->right = left;
      else
      {
        parent->left = left;
      }
       parent = left;
       left = left->right;
       parent->right = this;
     }
     this->parent->updateHeight();
      
    }
}

// Function for adjusting the height of a Sequoia
// following a deletion to maintain "tallness"
// Not called in driver, so not required to be implemented
// If not implementing, must fix height and tallness elsewhere
void SequoiaNode::fixBalanceRemove()
{
  //begin iterating up tree, starting form parent of deleted node
  this->updateHeight();
  if(this->isTall()){
      if(parent != nullptr)
        this->parent->fixBalanceRemove();
  }
  else if(left->height >= right->height && left->height < (2 * right->height))
  {
    //rotate right node left, update height of rotated node
    //right node becomes parent, parent becomes left child
    if(parent == nullptr)
    {
      right->parent = parent;
      parent = right;
      if(right->left = nullptr)
        right = nullptr;
      else
        right = right->left;
      parent->left = this;
    }
    else{
      right->parent = parent;
      parent->right = right;
      parent = right;
      right = right->left;
      parent->left = this;
    }
    parent->updateHeight();
  }
  else
  {
    //rotate left child to the right, update height of rotated node
    //left child becomes parent, parent becomes right
    if(parent == nullptr)
    {
      left->parent = parent;
      parent = left;
      left = left->right;
      parent->right = this;
    }
    else
    {
      left->parent = parent;
      parent->right = left;
      parent = left;
      left = left->right;
      parent->right = this;
    }
    parent->updateHeight();
  }
  //update root incase it was rotated.
}

void SequoiaNode::updateHeight()
{

  if(left != nullptr && right != nullptr)
  {
    if(right->height > left->height)
      height = 1 + right->height;
    else
      height = 1 + left->height;
    
  }
  else if(left == nullptr && right != nullptr)
  {
    height = 1 + right->height;
  }
  else if(left != nullptr && right == nullptr)
  {
    height = 1 + left->height;
  }
  else
  {
    height = 1;
  }
  

  
}
