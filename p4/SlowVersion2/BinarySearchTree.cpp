    #include "BinarySearchTree.h"
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
        template <class Comparable>
        BinarySearchTree<Comparable>::BinarySearchTree( const Comparable & notFound ) :
          root(NULL), ITEM_NOT_FOUND( notFound )
        {
        }


        /**
         * Copy constructor.
         */
        template <class Comparable>
        BinarySearchTree<Comparable>::
        BinarySearchTree( const BinarySearchTree<Comparable> & rhs ) :
          root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND )
        { 
            *this = rhs;
        }

        /**
         * Destructor for the tree.
         */
        template <class Comparable>
        BinarySearchTree<Comparable>::~BinarySearchTree( )
        {
            makeEmpty( );
        }

        /**
         * Insert x into the tree; duplicates are ignored.
         */
        template <class Comparable>
        void BinarySearchTree<Comparable>::insert( const Comparable & x )
        {
            insert( x, root );
        }

        /**
         * Remove x from the tree. Nothing is done if x is not found.
         */
        template <class Comparable>
        void BinarySearchTree<Comparable>::remove( const Comparable & x )
        {
            remove( x, root );
        }


        /**
         * Find the smallest item in the tree.
         * Return smallest item or ITEM_NOT_FOUND if empty.
         */
        template <class Comparable>
        Comparable * BinarySearchTree<Comparable>::findMin( )
        {
            return &( findMin( root )->element );
        }

        /**
         * Find the largest item in the tree.
         * Return the largest item of ITEM_NOT_FOUND if empty.
         */
        template <class Comparable>
        Comparable * BinarySearchTree<Comparable>::findMax( )
        {
            return &( findMax( root )->element );
        }

        /**
         * Find item x in the tree.
         * Return the matching item or ITEM_NOT_FOUND if not found.
         */
        template <class Comparable>
        Comparable * BinarySearchTree<Comparable>::
                                 find( const Comparable & x )
        {
            return &( find( x, root )->element );
        }

        template <class Comparable>
        Comparable * BinarySearchTree<Comparable>::
                                 findClosest( const Comparable & x )
        {
            BinaryNode <Comparable> *t =root;
            BinaryNode <Comparable> *closest = t;
            //if(x.time == 12849)
            //  cout<<" T:"<<t->element.price<<endl;

            while(t != NULL)
            {
                if(t->element.price > x.price)
                {  
                    
                    t = t->left;
                }
                else if(t->element.price <= x.price)
                {
                    closest = t;
                    t = t->right;
                }
                else
                    break;
            }

            /*while(t->right && t->right->left && t->right->left->element.price < x.price)
                t = t->right->left;
            while( t != NULL && t->element.price > x.price && t->left)
            {
                t = t->left;
            }
            while( t != NULL && t->element.price < x.price && t->right && t->right->element.price < x.price)
            {
                t = t->right;
            }*/
            if((closest->right && closest -> element.price == closest->right->element.price) || ( closest-> left && closest -> element.price == closest->left->element.price))
            {
                if(closest->right && closest -> element.price == closest->right->element.price && closest -> element.time > closest->right->element.time)
                    closest = closest->right;
                if(closest->left && closest -> element.price == closest->left->element.price && closest -> element.time > closest->left->element.time)
                    closest = closest->left;
            }
            return &(closest->element);   // No match
        }

        /**
         * Make the tree logically empty.
         */
        template <class Comparable>
        void BinarySearchTree<Comparable>::makeEmpty( )
        {
            makeEmpty( root );
        }

        /**
         * Test if the tree is logically empty.
         * Return true if empty, false otherwise.
         */
        template <class Comparable>
        bool BinarySearchTree<Comparable>::isEmpty( ) const
        {
            return root == NULL;
        }

        /**
         * Print the tree contents in sorted order.
         */
        template <class Comparable>
        void BinarySearchTree<Comparable>::printTree( ) const
        {
            if( isEmpty( ) )
                cout << "Empty tree" << endl;
            else
                printTree( root );
        }

        /**
         * Deep copy.
         */
        template <class Comparable>
        const BinarySearchTree<Comparable> &
        BinarySearchTree<Comparable>::
        operator=( const BinarySearchTree<Comparable> & rhs )
        {
            if( this != &rhs )
            {
                makeEmpty( );
                root = clone( rhs.root );
            }
            return *this;
        }

        /**
         * Internal method to get element field in node t.
         * Return the element field or ITEM_NOT_FOUND if t is NULL.
         */
        template <class Comparable>
        const Comparable & BinarySearchTree<Comparable>::
        elementAt( BinaryNode<Comparable> *t ) const
        {
            return t == NULL ? ITEM_NOT_FOUND : t->element;
        }

        /**
         * Internal method to insert into a subtree.
         * x is the item to insert.
         * t is the node that roots the tree.
         * Set the new root.
         */
        template <class Comparable>
        void BinarySearchTree<Comparable>::
        insert( const Comparable & x, BinaryNode<Comparable> * & t ) const
        {
            if( t == NULL )
                t = new BinaryNode<Comparable>( x, NULL, NULL );
            else if( x.price <= t->element.price )
                insert( x, t->left );
            else if( t->element.price < x.price )
                insert( x, t->right );
            else
                ;  // Duplicate; do nothing
        }

        /**
         * Internal method to remove from a subtree.
         * x is the item to remove.
         * t is the node that roots the tree.
         * Set the new root.
         */
        template <class Comparable>
        void BinarySearchTree<Comparable>::
        remove( const Comparable & x, BinaryNode<Comparable> * & t ) const
        {
            if( t == NULL )
                return;   // Item not found; do nothing
            if( x.price < t->element.price || (x.price == t->element.price && x.time > t->element.time))
                remove( x, t->left );
            else if( t->element.price < x.price || (x.price == t->element.price && x.time < t->element.time))
                remove( x, t->right );
            else if( t->left != NULL && t->right != NULL ) // Two children
            {
                t->element = findMin( t->right )->element;
                remove( t->element, t->right );
            }
            else
            {
                BinaryNode<Comparable> *oldNode = t;
                t = ( t->left != NULL ) ? t->left : t->right;
                delete oldNode;
            }
        }

        /**
         * Internal method to find the smallest item in a subtree t.
         * Return node containing the smallest item.
         */
        template <class Comparable>
        BinaryNode<Comparable> *
        BinarySearchTree<Comparable>::findMin( BinaryNode<Comparable> *t ) const
        {
            if( t == NULL )
                return NULL;
            if( t->left == NULL )
                return t;
            return findMin( t->left );
        }

        /**
         * Internal method to find the largest item in a subtree t.
         * Return node containing the largest item.
         */
        template <class Comparable>
        BinaryNode<Comparable> *
        BinarySearchTree<Comparable>::findMax( BinaryNode<Comparable> *t ) const
        {
            if( t != NULL )
                while( t->right != NULL )
                    t = t->right;
            return t;
        }

        /**
         * Internal method to find an item in a subtree.
         * x is item to search for.
         * t is the node that roots the tree.
         * Return node containing the matched item.
         */
        template <class Comparable>
        BinaryNode<Comparable> *
        BinarySearchTree<Comparable>::
        find( const Comparable & x, BinaryNode<Comparable> *t ) const
        {
            if( t == NULL )
                return NULL;
            else if( x.price < t->element.price || (x.price == t->element.price && x.time > t->element.time))
                return find( x, t->left );
            else if( t->element.price < x.price || (x.price == t->element.price && x.time < t->element.time))
                return find( x, t->right );
            else
                return t;    // Match
        }

/****** NONRECURSIVE VERSION*************************
        template <class Comparable>
        BinaryNode<Comparable> *
        BinarySearchTree<Comparable>::
        find( const Comparable & x, BinaryNode<Comparable> *t ) const
        {
            while( t != NULL )
                if( x < t->element )
                    t = t->left;
                else if( t->element < x )
                    t = t->right;
                else
                    return t;    // Match

            return NULL;   // No match
        }
*****************************************************/

        /**
         * Internal method to make subtree empty.
         */
        template <class Comparable>
        void BinarySearchTree<Comparable>::
        makeEmpty( BinaryNode<Comparable> * & t ) const
        {
            if( t != NULL )
            {
                makeEmpty( t->left );
                makeEmpty( t->right );
                delete t;
            }
            t = NULL;
        }

        /**
         * Internal method to print a subtree rooted at t in sorted order.
         */
        template <class Comparable>
        void BinarySearchTree<Comparable>::printTree( BinaryNode<Comparable> *t ) const
        {
            if( t != NULL )
            {
                printTree( t->left );
                cout << t->element.price << endl;
                printTree( t->right );
            }
        }

        /**
         * Internal method to clone subtree.
         */
        template <class Comparable>
        BinaryNode<Comparable> *
        BinarySearchTree<Comparable>::clone( BinaryNode<Comparable> * t ) const
        {
            if( t == NULL )
                return NULL;
            else
                return new BinaryNode<Comparable>( t->element, clone( t->left ), clone( t->right ) );
        }
