#include "Windows.h"
#include "stdio.h"

int main()
{
	// Input/Output file names
	LPCSTR FNAME1 = "C:\\Temp\\Test1.bin";
	LPCSTR FNAME2 = "C:\\Temp\\Test2.bin";

	// Open/Create the files...
	FILE *f1 = fopen(FNAME1, "rb");
	FILE *f2 = fopen(FNAME2, "wb+");

	// File and buffer size
	const __int64 file_size = 1223814243;
	const int BufSize = 4096;

	int BadSector = 0;

	// Our buffer
	BYTE Buffer[BufSize];

	// If everything's ok
	if(f1 && f2){
	
		// Copy in block of 4k
		for(__int64 i = 0; i < file_size; i += BufSize){
		
			// Erase our buffer
			ZeroMemory(Buffer, BufSize);

			// Calculate the number of bytes to read and write
			__int64 BlockSize = file_size - i;
			if(BlockSize > BufSize)
				BlockSize = BufSize;

			// Read a block
			int num_read = fread(Buffer, 1, (int)BlockSize, f1);
			if(num_read != BlockSize){
				printf("\nBad Sector...\n");

				BadSector++;
				ZeroMemory(Buffer, BufSize);
				goto LCleanup;
			}

			// Write the block
			int num_write = fwrite(Buffer, 1, (int)BlockSize, f2);
			if(num_write != BlockSize){
				printf("\nError writting the file.\n");
				goto LCleanup;
			}

			// Calculate and print percentage on screen
			float p = (float)(((double)(i+BlockSize) / (double)file_size) * 100.0);
			printf("\rPercent Done: %.2f%%", p);
		}
		
		// 
		printf("\n");
	}
	
LCleanup:
	// Cleanup...
	if(f1)fclose(f1);
	if(f2)fclose(f2);

	return 0;
}