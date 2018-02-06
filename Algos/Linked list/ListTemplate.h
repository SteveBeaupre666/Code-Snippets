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
#ifndef ROOT_NODE
	#define ROOT_NODE    -1
#endif

//----------------------------------------------------------------------//
// 
//----------------------------------------------------------------------//
struct CNode {
	UINT   Indx;

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
	void  RecreateIndex();
private:
	CNode* GetRootNode();
public:
	CNode* GetNode(UINT Indx);
	UINT   GetNodesCount();
	CNode* GetFirstNode(bool CanReturnRoot = false);
	CNode* GetLastNode(bool CanReturnRoot = false);
	UINT   GetNumAllocatedNodes(){return NumNodesAllocated;}
public:
	void PushNode(CNode *pNodeData);
	bool InsertNode(CNode *pNodeData, UINT Indx, BOOL InsAfter = false);
	bool PopNode();
	bool DeleteNode(UINT Indx);
	void ClearAll();
public:
	void PrintNodesData();
};

#endif
#endif //_LIST_H_
