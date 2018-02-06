unit LinkedList;
interface

uses
  Windows;

const
ROOT_NODE: DWORD = $FFFFFFFF;

type
//----------------------------------------------------------------------//
//
//----------------------------------------------------------------------//
TNode = record
  Indx: DWORD;

  // To customize...

  Prev: Pointer;
  Next: Pointer;
end;
PNode = ^TNode;

//----------------------------------------------------------------------//
// 
//----------------------------------------------------------------------//
type
  TList = class
  private
    NumNodesAllocated: DWORD;
    Root: TNode;

    procedure RecreateIndex;

    procedure InitRootNode;
    function  GetRootNode: PNode;

  public
    function  GetNode(Indx: DWORD): PNode;
    function  GetNodesCount: DWORD;
    function  GetFirstNode(CanReturnRoot: BOOLEAN = FALSE): PNode;
    function  GetLastNode(CanReturnRoot: BOOLEAN = FALSE): PNode;
    function  GetNumAllocatedNodes: DWORD;

    Procedure Initialize;
    Procedure Free;

    procedure PushNode(pNodeData: PNODE);
    function  InsertNode(pNodeData: PNODE; Indx: DWORD; InsAfter: BOOLEAN = false): BOOLEAN;
    function  PopNode: BOOLEAN;
    function  DeleteNode(Indx: DWORD): BOOLEAN;
    procedure ClearAll;
  end;



implementation


Procedure TList.Initialize;
begin
NumNodesAllocated := 0;
InitRootNode();
end;

Procedure TList.Free;
begin
ClearAll;
end;

procedure TList.RecreateIndex;
var
  Count: DWORD;
  Node: PNODE;
begin
Count := 0;
Node := GetRootNode;

// Loop throught the nodes until we hit the last one
while(Node.Next <> nil) do begin
  Node := Node.Next;
  Node.Indx := Count;
  Inc(Count);
end;
end;

procedure TList.InitRootNode;
begin
Root.Indx := ROOT_NODE;

// To customize...

Root.Prev := nil;
Root.Next := nil;
end;

function TList.GetRootNode: PNode;
begin
Result := @Root;
end;

function TList.GetNode(Indx: DWORD): PNode;
var
  Count: DWORD;
  Node: PNODE;
begin
Result := nil;
Count := 0;
Node := GetRootNode;

// Loop throught the nodes until we hit the last one
while(Node.Next <> nil) do begin
  Node := Node.Next;
  if(Count = Node.Indx) then begin
    Result := Node;
    break;
  end;
end;
end;

function TList.GetNodesCount: DWORD;
var
  Count: DWORD;
  Node: PNODE;
begin
Count := 0;
Node := GetRootNode;

// Loop throught the nodes until we hit the last one
while(Node.Next <> nil) do begin
  Node := Node.Next;
  Inc(Count);
end;

Result := Count;
end;

function TList.GetFirstNode(CanReturnRoot: BOOLEAN = FALSE): PNode;
var
  Node: PNODE;
begin
Node := GetRootNode;

// Loop throught the nodes until we hit the last one
if(Node.Next <> nil) then
  Node := Node.Next;

if((CanReturnRoot) and (Node = GetRootNode)) then begin
  Result := Node;
  Exit;
end;

if(Node = GetRootNode) then begin
  Result := nil;
end else begin
  Result := Node;
end;
end;

function TList.GetLastNode(CanReturnRoot: BOOLEAN = FALSE): PNode;
var
  Node: PNODE;
begin
Node := GetRootNode;

// Loop throught the nodes until we hit the last one
while(Node.Next <> nil) do
  Node := Node.Next;

if((CanReturnRoot) and (Node = GetRootNode)) then begin
  Result := Node;
  Exit;
end;

if(Node = GetRootNode) then begin
  Result := nil;
end else begin
  Result := Node;
end;
end;

function TList.GetNumAllocatedNodes: DWORD;
begin
Result := NumNodesAllocated;
end;

procedure TList.PushNode(pNodeData: PNODE);
var
  Node, NewNode: PNODE;
begin
Node := GetLastNode(True);

// Allocate the new node
GetMem(Node.Next, sizeof(TNode));
Inc(NumNodesAllocated);
NewNode := Node.Next;

// Update pointers
NewNode.Next := nil;
NewNode.Prev := Node;

//
NewNode.Indx := Node.Indx + 1;

// To customize...
end;

function TList.InsertNode(pNodeData: PNODE; Indx: DWORD; InsAfter: BOOLEAN = false): BOOLEAN;
var
  Node, NewNode, PrevNode: PNODE;
begin
// Update pointers
if(InsAfter) then
  Inc(Indx);

Node := GetNode(Indx);
if(Node = nil) then begin
  Result := False;
  Exit;
end;

// Allocate the new node
GetMem(NewNode, sizeof(TNode));
Inc(NumNodesAllocated);
PrevNode := Node.Prev;

PrevNode.Next := NewNode;
NewNode.Prev := Node.Prev;
NewNode.Next := Node;
Node.Prev := NewNode;

// To customize...


RecreateIndex;
	
// return success
Result := true;
end;

function TList.PopNode: BOOLEAN;
var
  Node, PrevNode: PNODE;
begin
Node := GetLastNode(True);

// If this the root node, we're done...
if((Node = nil) or (Node = GetRootNode)) then begin
  Result := False;
  Exit;
end;

// Update pointers
PrevNode := Node.Prev;
PrevNode.Next := nil;

// Delete the node
FreeMem(Node);
Dec(NumNodesAllocated);

// return success
Result := True;
end;

function TList.DeleteNode(Indx: DWORD): BOOLEAN;
var
  Node, NextNode, PrevNode: PNODE;
begin
Node := GetNode(Indx);

// If this the root node, we're done...
if((Node = nil) or (Node = GetRootNode)) then begin
  Result := False;
  Exit;
end;

// Update pointers
PrevNode := Node.Prev;
NextNode := Node.Next;

PrevNode.Next := NextNode;
if(NextNode <> nil) then
  NextNode.Prev := PrevNode;

// Delete the node
FreeMem(Node);
Dec(NumNodesAllocated);

RecreateIndex;

// return success
Result := True;
end;

procedure TList.ClearAll;
begin
while(PopNode = True) do begin end;
end;


end.
