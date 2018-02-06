#include "ListTemplate.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

CList::CList()
{
	NumNodesAllocated = 0;
	InitRootNode();
}

/////////////////////////////////////////////////////////////////////////////////////////////////

CList::~CList()
{
	ClearAll();
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void CList::InitRootNode()
{
	Root.Indx = ROOT_NODE;

	// To customize...
	Root.Data = 0;

	Root.Prev = NULL;
	Root.Next = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void CList::RecreateIndex()
{
	UINT Count = 0;
	CNode *pNode = &Root;
	
	// Loop throught the nodes until we hit the last one
	while(pNode->Next != NULL){
		pNode = pNode->Next;
		pNode->Indx = Count;
		Count++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////

UINT CList::GetNodesCount()
{
	UINT Count = 0;
	CNode *pNode = &Root;
	
	// Loop throught the nodes until we hit the last one
	while(pNode->Next != NULL){
		pNode = pNode->Next;
		Count++;
	}

	// Return the number of nodes of this pile
	return Count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

CNode* CList::GetNode(UINT Indx)
{
	UINT Count = 0;
	CNode *pNode = &Root;
	
	// Loop throught the nodes until we hit the one we want
	while(pNode->Next != NULL){
		pNode = pNode->Next;
		if(Count == Indx)
			return pNode;
		Count++;
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

CNode* CList::GetRootNode()
{
	return &Root;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

CNode* CList::GetFirstNode(bool CanReturnRoot)
{
	CNode *pNode = &Root;
	
	// Loop throught the nodes until we hit the last one
	if(pNode->Next != NULL)
		pNode = pNode->Next;

	if(CanReturnRoot)
		return pNode;
	
	// Return the last node pointer
	return pNode == &Root ? NULL : pNode;
}


/////////////////////////////////////////////////////////////////////////////////////////////////

CNode* CList::GetLastNode(bool CanReturnRoot)
{
	CNode *pNode = &Root;
	
	// Loop throught the nodes until we hit the last one
	while(pNode->Next != NULL)
		pNode = pNode->Next;

	if(CanReturnRoot)
		return pNode;

	// Return the last node pointer
	return pNode == &Root ? NULL : pNode;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void CList::PushNode(CNode *pNodeData)
{
	CNode *pNode = GetLastNode(true);

	// Allocate the new node
	pNode->Next = new CNode;
	NumNodesAllocated++;
	CNode *pNewNode = pNode->Next;

	// Update pointers
	pNewNode->Next = NULL;
	pNewNode->Prev = pNode;

	//
	pNewNode->Indx = pNewNode->Prev->Indx + 1;

	// To customize...
	pNewNode->Data = pNodeData->Data;


}

/////////////////////////////////////////////////////////////////////////////////////////////////

bool CList::InsertNode(CNode *pNodeData, UINT Indx, BOOL InsAfter)
{
	// Update pointers
	if(InsAfter)
		Indx++;

	CNode *pNode = GetNode(Indx);
	if(!pNode){return false;}

	// Allocate the new node
	CNode *pNewNode = new CNode;
	NumNodesAllocated++;

	pNewNode->Data = pNodeData->Data;

	pNode->Prev->Next = pNewNode;
	pNewNode->Prev = pNode->Prev;
	pNewNode->Next = pNode;
	pNode->Prev = pNewNode;

	// To customize...


	RecreateIndex();
	
	// return success
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

bool CList::PopNode()
{
	CNode *pNode = GetLastNode(true);

	// If this the root node, we're done...
	if(pNode == NULL || pNode == &Root){return false;} // return faillure

	// Update pointers
	pNode->Prev->Next = NULL;

	// Delete the node
	SAFE_DELETE_OBJECT(pNode);
	NumNodesAllocated--;

	// return success
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

bool CList::DeleteNode(UINT Indx)
{
	CNode *pNode = GetNode(Indx);

	// If this the root node, we're done...
	if(!pNode || pNode == &Root){return false;} // return faillure

	// Update pointers
	CNode *pPrevNode = pNode->Prev;
	CNode *pNextNode = pNode->Next;

	pPrevNode->Next  = pNextNode;
	if(pNextNode)
		pNextNode->Prev = pPrevNode;

	// Delete the node
	SAFE_DELETE_OBJECT(pNode);
	NumNodesAllocated--;

	RecreateIndex();

	// return success
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void CList::ClearAll()
{
	// Delete everything...
	while(PopNode());
}


/////////////////////////////////////////////////////////////////////////////////////////////////

void CList::PrintNodesData()
{
	UINT Count = 0;
	CNode *pNode = &Root;
	
	// Loop throught the nodes until we hit the one we want
	while(pNode->Next != NULL){
		pNode = pNode->Next;
		printf("Node #%d data = %d\n", Count, pNode->Data);
		Count++;
	}
}

