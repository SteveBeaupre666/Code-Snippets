#pragma once
//----------------------------------------------------------------------//
#include <Windows.h>
//----------------------------------------------------------------------//

namespace LinkedList {

// Node 
template <class DataT> class CNode {
public:
	DataT Data;
	CNode<DataT> *Next;
	CNode<DataT> *Prev;
	CNode(){
		ZeroMemory(&Data, sizeof(DataT));
		Next = NULL;
		Prev = NULL;
	}
	CNode(DataT d){
		Data = d;
		Next = NULL;
		Prev = NULL;
	}

	CNode<DataT> *GetNext(){return Next;}
	CNode<DataT> *GetPrev(){return Prev;}
};

//----------------------------------------------------------------------//

// LinkedList 
template <class DataT> class CLinkedList : public CNode<DataT> {	
private:
	CNode<DataT> *First, *Last;
	UINT NumNodesAllocated;
public:
	CLinkedList(){
		First = NULL;
		Last  = NULL;
		NumNodesAllocated = 0;
		srand(GetTickCount());
	}
	~CLinkedList(){
		Clear();
	}
	 
	UINT GetNodesCount();

	CNode<DataT> *GetNode(UINT Indx);
	CNode<DataT> *GetFirstNode();
	CNode<DataT> *GetLastNode();

	CNode<DataT>* Push(DataT *d);
	bool Pop(DataT *d);
	bool Delete(CNode<DataT> *pNode);
	void Clear();

	void Randomize();

	void Fill(CNode<DataT> *pNode);
};

template <class DataT> UINT CLinkedList<DataT>::GetNodesCount()
{
	return NumNodesAllocated;
}

template <class DataT> CNode<DataT>* CLinkedList<DataT>::GetNode(UINT Indx)
{
	CNode<DataT> *pNode = First;
	if(!pNode){return NULL;}
	if(Indx >= NumNodesAllocated){return NULL;}

	UINT i = 0;
	while(i < Indx){
		pNode = pNode->GetNext();
		if(!pNode){return NULL;}
		i++;
	}

	return pNode;
}

template <class DataT> CNode<DataT>* CLinkedList<DataT>::GetFirstNode()
{
	return First;
}

template <class DataT> CNode<DataT>* CLinkedList<DataT>::GetLastNode()
{
	return Last;
}

template <class DataT> CNode<DataT>* CLinkedList<DataT>::Push(DataT *d)
{
	CNode<DataT> *pNewNode = new CNode<DataT>;
	NumNodesAllocated++;

	pNewNode->Data = *d;
	if(First == NULL){
		Last  = pNewNode;
		First = pNewNode;
    } else {
		pNewNode->Prev = Last;
		Last->Next = pNewNode;
		Last = pNewNode;
    }

	return pNewNode;
}

template <class DataT> bool CLinkedList<DataT>::Pop(DataT *d)
{
	if(Last){
		if(d != NULL)
			*d = Last->Data;
		return Delete(Last);
	}

	return false;
}

template <class DataT> bool CLinkedList<DataT>::Delete(CNode<DataT> *pNode)
{
	if(pNode){
		if(pNode->Prev){
			pNode->Prev->Next = pNode->Next;
			if(pNode->Next){
				pNode->Next->Prev = pNode->Prev;
			} else {
				Last = pNode->Prev;
			}
		} else {
			if(pNode->Next){
				pNode->Next->Prev = NULL;
				First = pNode->Next;
			} else {
				First = NULL;
				Last  = NULL;
			}
		}

		delete pNode;
		NumNodesAllocated--;

		return true;
	}

	return false;
}

template <class DataT> void CLinkedList<DataT>::Clear()
{
	while(Pop(NULL));
}

template <class DataT> void CLinkedList<DataT>::Randomize()
{
	CLinkedList<DataT> TmpList;

	UINT NumItems = this->GetNodesCount();

	while(NumItems > 0){
	
		UINT RandVal = rand() % NumItems;
	
		CNode<DataT> *pNode = this->GetNode(RandVal);
		
		DataT d = pNode->Data;
		TmpList.Push(&d);

		this->Delete(pNode);

		NumItems--;
	}
	this->Clear();

	for(UINT Cpt = 0; Cpt < TmpList.GetNodesCount(); Cpt++){

		CNode<DataT> *pNode = TmpList.GetNode(Cpt);

		DataT d = pNode->Data;
		this->Push(&d);
	}

	TmpList.Clear();
}

template <class DataT> void CLinkedList<DataT>::Fill(CNode<DataT> *pNode)
{
	this->Clear();
	
	while(pNode){
		this->Push(&pNode->Data);
		pNode = pNode->GetNext();
	}
}

}