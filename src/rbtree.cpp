#include "rbtree.h"

template <class T>
RBTree<T>::RBTree ()
{
    root = 0;
    count = 0;
}

template <class T>
RBTree<T>::~RBTree ()
{
	//std::cout << "Tree destructor..." << std::endl;
    clear();
}

template <class T>
int RBTree<T>::insert (T value)
{
    if (root == 0)
        root = new Node ();

    root->insert (value);

    root->setColor(Node::Black);

    return Node::lastInsertedIndex;
}

template <class T>
int RBTree<T>::remove (T value)
{
    // coming soon...
    return 0;
}

template <class T>
void RBTree<T>::print () const
{
	//std::cout << "Print start" << std::endl;
    if (root)
	{
		root->printLine(0);
	}

	//std::cout << "Print stop" << std::endl;
}

template <class T>
void RBTree<T>::save (std::string filepath)
{
	std::fstream stream;
	stream.open(filepath.c_str(), std::ios_base::trunc | std::ios_base::out | std::ios_base::binary);
	root->save(stream, 0);
	stream.close();
}

/*template <class T>
int RBTree<T>::load (std::string filepath)
{
	int res;
	std::fstream stream;
	stream.open(filepath.c_str(), std::ios_base::in | std::ios_base::binary);
	std::string line;
	getline (stream, line);
	if (!line.isEmpty())
	{
		if (line[0] == ' ')
			return 1;
		clear();
		if (line != "<None>")
		{
			root = new Node();
			std::vector<std::string> vec = split (line, '-');
			if (vec.size() != 3)
				return 1;
			root->element.index = vec[0];
//			memcpy (&(root->element.value), 
			res = root->load(stream, 0);
		}
	}
	stream.close();
	return res;
}*/

template <class T>
int RBTree<T>::getCount () const
{
    return Node::count;
}

template <class T>
void RBTree<T>::clear ()
{
    if (root)
		root->clear();
	delete root;
	root = 0;
	//std::cout << "End of all!" << std::endl;
}

template <class T>
long long RBTree<T>::Node::count = 0;

template <class T>
long long RBTree<T>::Node::lastInsertedIndex = -1;

template <class T>
RBTree<T>::Node::Node()
{
    left = 0;
    right = 0;
    color = Red;
}

template <class T>
RBTree<T>::Node::~Node()
{
	//std::cout << "Node destructor start" << std::endl;
	/*if (left)
	{
		delete left;
		left = 0;
	}
	if (right)
	{
		delete right;
		right = 0;
	}*/
	//std::cout << "Node destructor stop" << std::endl;
}

template <class T>
bool RBTree<T>::Node::insert (T value)
{
    //std::cout << "Insert start" << std::endl;
    if (element.index == -1)
    {
        //std::cout << "New element start" << std::endl;
        element.value = value;
        Node::lastInsertedIndex = Node::count++;
        element.index = Node::lastInsertedIndex;
        //std::cout << "New element stop" << std::endl;
  //  std::cout << "Insert stop" << std::endl;
        return false;
    }
    else
    {
        //std::cout << "Old element start" << std::endl;
        Node *temp;
        if (value < element.value)
        {
            //std::cout << "Go to left" << std::endl;
            if (left == 0)
                left = new Node ();
            temp = left;
        }
        else if (value > element.value)
        {
            //std::cout << "Go to right" << std::endl;
            if (right == 0)
                right = new Node ();
            temp = right;
        }
        else
        {
            //std::cout << "Equal" << std::endl;
            Node::lastInsertedIndex = element.index;
    //std::cout << "Insert stop" << std::endl;
            return true;
        }

        //std::cout << "TEMP COLOR = " << (temp->getColor()==Black?"Black":"Red") << std::endl;

        //std::cout << "Real inserting start" << std::endl;
        if (temp->insert (value))
        {
            //std::cout << "Return true" << std::endl;
  //  std::cout << "Insert stop" << std::endl;
            return true;
        }
        else
        {
            balanceInsert();
            //std::cout << "Return false" << std::endl;
//    std::cout << "Insert stop" << std::endl;
            return false;
        }
        //std::cout << "Real inserting stop" << std::endl;
        //std::cout << "Old element stop" << std::endl;
    }
}

template <class T>
int RBTree<T>::Node::remove (T value)
{
    // coming soon
    return 0;
}

template <class T>
typename RBTree<T>::Node::Element RBTree<T>::Node::getElement () const
{
    return element;
}

template <class T>
void RBTree<T>::Node::setElement (Element element)
{
    this->element = element;
}

template <class T>
typename RBTree<T>::Node::Color RBTree<T>::Node::getColor () const
{
    return color;
}

template <class T>
void RBTree<T>::Node::setColor (Color color)
{
    this->color = color;
}

template <class T>
void RBTree<T>::Node::balanceInsert ()
{
//    std::cout << "Balance start" << std::endl;
    //std::cout << " Color = " << (color==Black?"Black":"Red") << std::endl;
    if (color == Black)
    {
        if (left  && left->getColor() == Red)
        {
            //std::cout << " Left red" << std::endl;
            if (left->right && left->right->getColor() == Red)
            {
                //std::cout << " Left->right red" << std::endl;
                left->leftRotate();
            }
            if (left->left && left->left->getColor() == Red)
            {
                //std::cout << " Left->left red" << std::endl;
                color = Red;
                left->setColor(Black);
                if (right && right->getColor() == Red)
                {
                    //std::cout << " Uncle red" << std::endl;
                    left->left->setColor(Red);
                    right->setColor(Black);
                }
                else
                {
                    //std::cout << " Uncle black" << std::endl;
                    rightRotate();
                }
            }
        }

        if (right  && right->getColor() == Red)
        {
            if (right->left && right->left->getColor() == Red)
                right->rightRotate();
            if (right->right && right->right->getColor() == Red)
            {
                color = Red;
                right->setColor(Black);
                if (left && left->getColor() == Red)
                {
                    right->right->setColor(Red);
                    left->setColor(Black);
                }
                else
                {
                    leftRotate();
                }
            }
        }
        
    }
   // std::cout << "Balance end" << std::endl;
}

template <class T>
void RBTree<T>::Node::rightRotate ()
{
 //   std::cout << "  Right rotate start" << std::endl;
    Node *temp = new Node ();
    temp->setElement(this->element);
	temp->setColor(color);
    temp->right = this->right;
    if (this->left)
        temp->left = this->left->right;
    this->right = temp;

   // std::cout << "  temp inserted" << std::endl;

    if (this->left)
	{
		element = left->getElement();
		color = left->getColor();
		temp = left;
        this->left = left->left;
		delete temp;
		temp = 0;
	}
   // std::cout << "  Right rotate stop" << std::endl;
}

template <class T>
void RBTree<T>::Node::leftRotate ()
{
//    std::cout << "  Left rotate start" << std::endl;
    Node *temp = new Node ();
    temp->setElement(this->element);
	temp->setColor(color);
    temp->left = this->left;
    if (this->right)
        temp->right = this->right->left;
    this->left = temp;

  //  std::cout << "  temp inserted" << std::endl;

	if (this->right)
	{
		element = right->getElement();
		color = right->getColor();
		temp = right;
		this->right = this->right->right;
		delete temp;
		temp = 0;
	}
    //std::cout << "  Left rotate stop" << std::endl;
}

template <class T>
void RBTree<T>::Node::printLine(int depth) const
{
	std::cout << element << ':' << (color == Red?"Red":"Black") << std::endl;
	if (left || right)
	{
		std::cout << std::string (depth * 2, ' ') << "|-";
		if (left)
			left->printLine(depth + 1);
		else
			std::cout << "<None>" << std::endl;

		std::cout << std::string (depth * 2, ' ') << "|-";
		if (right)
			right->printLine(depth + 1);
		else
			std::cout << "<None>" << std::endl;
	}
}

template <class T>
void RBTree<T>::Node::clear()
{
	//std::cout << "Clear node " << element.value << " start!" << std::endl;
	if (!left && !right)
		return;

	if (left)
	{
	//	std::cout << " -left: " << left->getElement().value << std::endl;
		left->clear();
		delete left;
		left = 0;
	}
	if (right)
	{
	//	std::cout << " -left: " << right->getElement().value << std::endl;
		right->clear();
		delete right;
		right = 0;
	}
	//this->~Node();
	//std::cout << "Clear node stop!" << std::endl;
}

template <class T>
void RBTree<T>::Node::save (std::fstream &stream, int depth)
{
	stream << element << '-' << (color == Red?"Red":"Black") << std::endl;
	stream << std::string (++depth, ' ');
	if (left)
		left->save(stream, depth);
	else
		stream << "<None>" << std::endl;

	stream << std::string (depth, ' ');
	if (right)
		right->save(stream, depth);
	else
		stream << "<None>" << std::endl;
}

/*template <class T>
int RBTree<T>::Node::load (std::fstream &stream, int &depth)
{
	std::string line;
	getline (stream, line);
	if (line.isEmpty())
		return 0;

	if (line == "<None>")



	std::vector<std::string> vec = split (line, '-');
	if (vec.size() != 3)
		return 1;


	


	int spaces = 0;

	


	// Проверяем, чтобы коичество пробелов слева совпадало с глубиной
	for (auto it = line.begin(); it != line.end(); ++it)
		if (*it == ' ')
			++spaces;
		else
			break;
	if (spaces != depth)
		return 1;
	
	// Отбрасываем пробелы слева

}*/
