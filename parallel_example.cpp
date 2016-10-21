#include "user/GPAPI.h"
#include <stdlib.h>
using namespace std;


static void __run()
{
    GPStream* metaStream = GP_Stream_Create("func.xml");
    auto producer = GP_Producer_Create(&metaStream, NULL, 1, GP_PRODUCER_STREAM);
    GP_Stream_Destroy(metaStream);

    metaStream = GP_Stream_Create("parallel.xml");
    auto map_reduce = GP_Stream_Create("Map-Reduce.xml");
    auto pieceProducer = GP_PiecesProducer_Create(producer, &metaStream, NULL, 1, &map_reduce, 1);

    auto pieceFunction = GP_PiecesFunction_Create(pieceProducer, "C(S(x0))","TrBmp", "server");
    unsigned int keys = 5;
    auto input = GP_Pieces_Create(pieceProducer, "server", "TrBmp", "deps/Renacence/res/pictures/", &keys, 1, GP_PIECES_INPUT);
    unsigned int outputKeys = 1;
    auto output = GP_Pieces_Create(pieceProducer, "server", "TrBmp", "output/pythonTestParallel/", &outputKeys, 1, GP_PIECES_OUTPUT);
    auto cache = GP_PiecesFunction_Run(pieceFunction, &input, 1);
    GP_Pieces_Copy(pieceProducer, "server", cache, output);

    GP_Pieces_Destroy(output);
    GP_Pieces_Destroy(cache);
    GP_Pieces_Destroy(input);


    GP_PiecesFunction_Destroy(pieceFunction);
    GP_PiecesProducer_Destroy(pieceProducer);
    GP_Producer_Destroy(producer);
}

int main()
{
    __run();
    return 1;
}
