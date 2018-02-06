#include "Maze.h"

//-----------------------------------------------------------------------------
// Constructor...
//-----------------------------------------------------------------------------
Maze::Maze()
{
	Reset();
}

//-----------------------------------------------------------------------------
// Destructor...
//-----------------------------------------------------------------------------
Maze::~Maze()
{
	Free();
}

//-----------------------------------------------------------------------------
// Reset variables 
//-----------------------------------------------------------------------------
void Maze::Reset()
{
	Width    = 0;
	Height   = 0;
	NumCells = 0;
	pCells   = NULL;
}

//-----------------------------------------------------------------------------
// Return true if the cells have been allocated
//-----------------------------------------------------------------------------
bool Maze::IsAllocated()
{
	return pCells != NULL;
}

//-----------------------------------------------------------------------------
// Allocate the maze cells and save it's size
//-----------------------------------------------------------------------------
void Maze::Allocate(int w, int h)
{
	if(IsAllocated())
		Free();

	if(!w || !h)
		return;

	Width    = w;
	Height   = h;
	NumCells = w * h;
	
	pCells = new int[NumCells];
	ZeroMemory(pCells, sizeof(Cell) * NumCells);
}

//-----------------------------------------------------------------------------
// Deallocate cells memory
//-----------------------------------------------------------------------------
void Maze::Free()
{
	SAFE_DELETE_ARRAY(pCells);
	Reset();
}

//-----------------------------------------------------------------------------
// Return the number of cells
//-----------------------------------------------------------------------------
int Maze::GetNumCells()
{
	return NumCells;
}

//-----------------------------------------------------------------------------
// Return 1d index from a 2d index
//-----------------------------------------------------------------------------
int Maze::GetIndex(int x, int y)
{
	return (y * Width) + x;
}

//-----------------------------------------------------------------------------
// Return true if the index range's is valid (too prevent buffer overflow)
//-----------------------------------------------------------------------------
bool Maze::InRange(int Indx)
{
	return Indx < GetNumCells();
}

//-----------------------------------------------------------------------------
// Save as above, but with 2d indexes
//-----------------------------------------------------------------------------
bool Maze::IsValidRanges(int x, int y)
{
	return InRange(GetIndex(x,y));
}

//-----------------------------------------------------------------------------
// Return a cell value (PASSABLE or IMPASSABLE)
//-----------------------------------------------------------------------------
Cell Maze::GetCell(int x, int y)
{
	if(IsAllocated() &&IsValidRanges(x,y))
		return pCells[GetIndex(x,y)];

	return IMPASSABLE;
}

//-----------------------------------------------------------------------------
// Set the cell state (see above)
//-----------------------------------------------------------------------------
void Maze::SetCell(int x, int y, Cell state)
{
	if(!IsAllocated())
		return;
	
	int Indx = GetIndex(x,y);
	
	if(InRange(Indx))
		pCells[Indx] = state == IMPASSABLE ? IMPASSABLE : PASSABLE;
}

//-----------------------------------------------------------------------------
// Load the maze from a text file
//-----------------------------------------------------------------------------
bool Maze::LoadFromTextFile(char *fname)
{
	if(!IsAllocated())
		return false;

	FILE *f = fopen(fname, "rt");
	if(!f)
		return false;
	
	const int BufSize = 4096;
	char Buffer[BufSize];

	ZeroMemory(Buffer, BufSize);
	fgets(Buffer, BufSize, f);

	int w,h;
	sscanf(Buffer, "%d %d", &w, &h);

	Allocate(w, h);

	for(int y = 0; y < h; y++){
		ZeroMemory(Buffer, BufSize);
		fgets(Buffer, BufSize, f);

		for(int x = 0; x < w; x++){
			
			switch(Buffer[x])
			{
			case '0': SetCell(x,y, IMPASSABLE);
			case '1': SetCell(x,y, PASSABLE);
			}
			
		}
	}
	
	fclose(f);
	return true;
}

//-----------------------------------------------------------------------------
// Save the maze in a text file
//-----------------------------------------------------------------------------
bool Maze::SaveToTextFile(char *fname)
{
	if(!IsAllocated())
		return false;

	FILE *f = fopen(fname, "wt+");
	if(!f)
		return false;
	
	fprintf(f, "%d %d", Width, Height);

	for(int y = 0; y < Height; y++){
		for(int x = 0; x < Width; x++){

			switch(GetCell(x,y))
			{
			case IMPASSABLE: fputc('0', f);
			case PASSABLE:   fputc('0', f);
			}

		}
		if(y < Height-1)
			fprintf(f, "\n");
	}
	
	fclose(f);
	return true;
}


