#pragma once
//----------------------------------------------------------------------//
#include <Windows.h>
//----------------------------------------------------------------------//

// Node 
template <class DataT> class CNode {
public:
	DataT Data;
	CNode<DataT> *pParent, *pLeftChild, *pRightChild;

	CNode(){
		Init();
	}
	CNode(DataT d){
		Init();
		Data = d;
	}

	void Init(){
		ZeroMemory(&Data, sizeof(DataT));
		pParent = NULL;
		pLeftChild = NULL;
		pRightChild = NULL;
	}

	CNode<DataT> *GetParent(){return pParent;}
	CNode<DataT> *GetLeftChild(){return pLeftChild;}
	CNode<DataT> *GetRightChild(){return pRightChild;}
};

//----------------------------------------------------------------------//

// LinkedList 
template <class DataT> class CBinaryTree : public CNode<DataT> {	
private:
	CNode<DataT> *Root;
	UINT NumNodesAllocated;
public:
	CBinaryTree(){
		Root = NULL;
		NumNodesAllocated = 0;
	}
	~CBinaryTree(){
		Clear();
	}
	 
	UINT GetNodesCount();
	CNode<DataT> *GetRootNode();
	void CreateChildrens(CNode<DataT> *pNode);
	void DeleteNode(CNode<DataT> *pNode);
	void Clear();
};

template <class DataT> UINT CLinkedList<DataT>::GetNodesCount()
{
	return NumNodesAllocated;
}

template <class DataT> CNode<DataT>* CBinaryTree<DataT>::GetRootNode()
{
	return Root;
}

template <class DataT> void CLinkedList<DataT>::CreateChildrens(CNode<DataT> *pNode)
{
	if(!pNode)
		return;

	CNode<DataT> *pLeft  = new CNode<DataT>;
	CNode<DataT> *pRight = new CNode<DataT>;

	pLeft->pParent  = pNode;
	pRight->pParent = pNode;

	pNode->pLeftChild  = pLeft;
	pNode->pRightChild = pRight;
}

template <class DataT> void CLinkedList<DataT>::DeleteNode(CNode<DataT> *pNode)
{
	if(!pNode)
		return;

	CNode<DataT> *pLeft  = pNode->GetLeftChild();
	CNode<DataT> *pRight = pNode->GetRightChild();

	if(pLeft)
		DeleteNode(pLeft);
	if(pRight)
		DeleteNode(pRight);

	NumNodesAllocated--;
	delete pNode;
}

template <class DataT> void CLinkedList<DataT>::Clear()
{
	DeleteNode(GetRootNode());
}
