#pragma once

template <class T>
struct Node
{
	Node(T data)
	{
		mNext = nullptr;
		mPrevious = nullptr;
		mData = data;
	}

	Node* mNext;
	Node* mPrevious;
	T mData;
};

template <class T>
class Stack
{
public:
	Stack();
	~Stack();

	T pop();
	void push(T data);
	bool contains(T data);
	T find(int index);

private:
	Node<T>* mTop;
	//Node<T>* mBottom;
	int mLength;
};

template <class T>
Stack<T>::Stack():mTop(nullptr), mBottom(nullptr), mLength(0){ }

template <class T>
Stack<T>::~Stack()
{
	Node<T>* temp = mTop;
	mTop == nullptr;

	while (temp != nullptr)
	{
		temp = temp->mNext;
		delete temp->mPrevious;
		temp->mPrevious = nullptr;
	}

}

template <class T>
T Stack<T>::pop()
{
	if (mTop == nullptr)
	{
		//Throw exception
		return T();
	}

	Node<T>* toPop = mTop;
	T popData = mTop->mData;

	mTop = mTop->mNext();
	delete toPop;
	mLength--;

	return popData;
}

template <class T>
void Stack<T>::push(T data)
{
	Node<T>* newNode = new Node<T>(data);

	if (mTop == nullptr)
	{
		mTop = newNode;
	}
	else
	{	
		mTop->mPrevious = newNode;
		newNode->mNext = mTop;
		mTop = newNode;
		mLength++;
	}
}

template <class T>
bool Stack<T>::contains(T data)
{
	Node<T>* temp = mTop;

	while(temp != nullptr)
	{
		if (temp->mData == data)
		{
			return true;
		}
	}

	return false;
}

template <class T>
T Stack<T>::find(int index)
{
	if (index >= mLength)
	{
		//Throw exception
		return T();
	}

	Node<T>* temp = mTop;

	for(int i = 0; i <= index; i++)
	{
		temp = temp->mNext;
	}

	return temp->mData;
}
