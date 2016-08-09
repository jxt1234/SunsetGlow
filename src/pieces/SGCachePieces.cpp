#include "lowlevelAPI/GPPieces.h"
#include <sstream>
#include "SGDebug.h"
#include "pieces/SGCachePieces.h"

SGCachePieces::SGCachePieces(unsigned int* pKey, unsigned int keynum)
{
    
}
SGCachePieces::~SGCachePieces()
{
    
}

GPContents* SGCachePieces::vLoad(unsigned int* pKey, unsigned int keynum)
{
    return NULL;
}

long SGCachePieces::vPreMeasure(unsigned int* pKey, unsigned int keynum) const
{
    return -1;
}

void SGCachePieces::vSave(unsigned int* pKey, unsigned int keynum, GPContents* c)
{
    
}
