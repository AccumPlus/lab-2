/* ========================================== *
 *           -- class RBTree --               *
 *                                            *
 * Start of writing: 27.04.2016               *
 * End of writing:   xx.xx.xxxx               *
 *                                            *
 * Made by Solntsev S.P.                      *
 *                                            *
 * ========================================== */

#ifndef RBTREE_H
#define RBTREE_H

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

template <class T> class RBTree
{
public:
    RBTree ();
    ~RBTree ();
    // insert value into tree
    int insert (T value);
    // remove value out of tree
    int remove (T value);
    // print tree
    void print () const;
    // save tree to a file
    void save (std::string filepath);
    // load a tree from a file
//    void load (std::string filepath);
    // get count of all elements
    int getCount () const;
    // clear the tree
    void clear ();
private:
    class Node;

    Node *root;
    int count;
};

template <class T>
class RBTree<T>::Node
{
private:
    struct Element
    {
        long long index = -1;
        T value;
		friend std::ostream& operator<<(std::ostream& os, const Element& el)
		{
			os << el.index << '-' << el.value;
		}
    };
public:
    Node ();
    ~Node ();
    enum Color : int {Red = 0, Black};
    bool insert (T value);
    int remove (T value);
    Element getElement () const;
    void setElement (Element value);
    Color getColor () const;
    void setColor (Color color);
	void printLine (int depth) const;
	void clear ();
	void save (std::fstream &stream, int depth);
    static long long count;
    static long long lastInsertedIndex;
private:
    void balanceInsert ();
    void leftRotate ();
    void rightRotate ();
    Element element;
    Color color;
    Node *left, *right;
};

//#include "rbtree.cpp"

#endif
