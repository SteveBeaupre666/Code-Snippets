#ifndef _LIST_H_
#define _LIST_H_
#ifdef __cplusplus

#define WIN32_LEAN_AND_MEAN // Trim libraies.
#define VC_LEANMEAN         // Trim even further.
#include "Windows.h"
#include "stdio.h"
#include "SafeKill.h"

//----------------------------------------------------------------------//
// 
//----------------------------------------------------------------------//
struct CNode {
	// To customize...
	UINT Data;

	struct CNode *Prev;
	struct CNode *Next;
};

//----------------------------------------------------------------------//
// 
//----------------------------------------------------------------------//
class CList {
public:
	CList();
	~CList();
private:
	UINT NumNodesAllocated;
private:
	CNode Root;
	void  InitRootNode();
private:
	CNode* GetRootNode();
public:
	CNode* GetNode(UINT Indx);
	UINT   GetNodesCount();
	CNode* GetFirstNode(bool CanReturnRoot = false);
	CNode* GetLastNode(bool CanReturnRoot = false);
	UINT   GetNumAllocatedNodes(){return NumNodesAllocated;}
public:
	void Push(CNode *pNodeData);
	bool Insert(CNode *pNodeData, UINT Indx, BOOL InsAfter = false);
	bool Pop();
	bool Delete(UINT Indx);
	void Clear();
};

#endif
#endif //_LIST_H_
