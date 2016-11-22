#include "BinarySearchTree.h"
#include "BinaryHeap.h"
    #include <iostream>
using namespace std;

    /**
     * Implements an unbalanced binary search tree.
     * Note that all "matching" is based on the compares method.
     * @author Mark Allen Weiss
     */
 /**
  * Construct the tree.
  */

 BinarySearchTree::BinarySearchTree( ) : root(NULL)
 {
 }


 /**
  * Insert x into the tree; duplicates are ignored.
  */
void BinarySearchTree::insert( const Offer &offer )
{
  Offer2 x(&offer);
  
  if(!root)
  {
    root = new BinaryNode(x, NULL, NULL);
    return;
  }

  BinaryNode *t = root;

  while( true )
    if( x.priceTime < t->element.priceTime )
    {
      if(t->left)
        t = t->left;
      else
      {
        t->left = new BinaryNode( x, NULL, NULL );
        return;
      }
    } // if less
    else //  greater
    {
      if(t->right)
        t = t->right;
      else
      {
        t->right = new BinaryNode(x, NULL, NULL);
        return;
      }
    } // else x > element
 }

 /**
  * Remove x from the tree. Nothing is done if x is not found.
  */
 void BinarySearchTree::remove( long long priceTime)
 {
    BinaryNode *t = root, **prev = NULL;

    while(t->element.priceTime != priceTime)
    {
      if(t->element.priceTime < priceTime)
      {
        prev = &t->right;
        t = t->right;
      }
      else
      {
        prev = &t->left;
        t = t->left;
      }
    }
    
    if( t->left != NULL && t->right != NULL ) // Two children
    {
      BinaryNode *t2 = t->right, **prev2 = &t->right;
      
      while(t2->left) // findMin
      {
        prev2 = &t2->left;
        t2 = t2->left;
      }
      
      t->element = t2->element;

      if(t2->right)
        *prev2 = t2->right;
      else
        *prev2 = NULL;

      delete t2;
    } // if two children
    else  // less than two children
    {
      if(prev) // not root
      {
        if(t->left) // only t->left exists
          *prev = t->left;
        else // leaf or only t->right exists
          if(t->right) // only t->right exists
            *prev = t->right;
          else // no children
            *prev = NULL;
      } // if not removing root
      else // removing root
      {
        if(t->left) // only t->left exists
          root = t->left;
        else // leaf or only t->right exists
          if(t->right) // only t->right exists
            root = t->right;
          else // no children
            root = NULL;
      }  // else removing root
      
      delete t;
    } // else less than two children
 }  // remove



 /**
  * Find item x in the tree.
  * Return the matching item or ITEM_NOT_FOUND if not found.
  */
 Offer2* BinarySearchTree::find(double price)
 {
    Offer2 *itemFound = NULL;
    BinaryNode *t = root, **prev2 = NULL;
    prev = NULL;

    while( t != NULL )
      if( price < t->element.offer->price )
      {
        prev2 = &t->left;
        t = t->left;
      }
      else //  if( t->element.offer->price <= price )
      {
        if(!itemFound || t->element.priceTime > itemFound->priceTime)
        {
          prev = prev2;
          itemFound = &t->element;
        }

        prev2 = &t->right;
        t = t->right;
      }

    return itemFound;
 }


 /**
  * Print the tree contents in sorted order.
  */
 void BinarySearchTree::printTree( ) const
 {
  if(root == NULL)
    cout << "Empty tree" << endl;
  else
    printTree( root );
 }


 /**
  * Internal method to print a subtree rooted at t in sorted order.
  */
void BinarySearchTree::printTree( BinaryNode *t ) const
{
  if( t != NULL )
  {
  printTree( t->left );
  cout << t->element.priceTime << ' ' << t->element.offer->price << ' ' << t->element.offer->time << endl;
  printTree( t->right );
     }
 }


