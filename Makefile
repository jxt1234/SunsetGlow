all:libSunsetGlow.so example.out compute-responser.out compute-server.out test.out 

ALL_INCLUESlibSunsetGlow.so= include//fs/SGFile.h include//pieces/SGCachePieces.h include//SGComputeClient.h include//SGComputeServer.h include//SGDebug.h include//fs/SGFile.h include//pieces/SGCachePieces.h include//SGComputeClient.h include//SGComputeServer.h include//SGDebug.h

libSunsetGlow.so:  build/src_compute_SGComputeClient_cpp.o build/src_compute_SGComputeServer_cpp.o build/src_fs_SGFile_cpp.o build/src_pieces_SGCachePieces_cpp.o build/src_compute_SGCompute_CS_pb-c_c.o build/src_compute_SGCompute_SR_pb-c_c.o build/third_protobuf-c_protobuf-c_c.o build/third_protobuf-c-rpc_protobuf-c-rpc-client_c.o build/third_protobuf-c-rpc_protobuf-c-rpc-data-buffer_c.o build/third_protobuf-c-rpc_protobuf-c-rpc-dispatch_c.o build/third_protobuf-c-rpc_protobuf-c-rpc-server_c.o 
	g++ -std=c++11   build/src_compute_SGComputeClient_cpp.o build/src_compute_SGComputeServer_cpp.o build/src_fs_SGFile_cpp.o build/src_pieces_SGCachePieces_cpp.o build/src_compute_SGCompute_CS_pb-c_c.o build/src_compute_SGCompute_SR_pb-c_c.o build/third_protobuf-c_protobuf-c_c.o build/third_protobuf-c-rpc_protobuf-c-rpc-client_c.o build/third_protobuf-c-rpc_protobuf-c-rpc-data-buffer_c.o build/third_protobuf-c-rpc_protobuf-c-rpc-dispatch_c.o build/third_protobuf-c-rpc_protobuf-c-rpc-server_c.o -O3 -g -fPIC  --shared  ../Renascence/libGP.a -o libSunsetGlow.so ${SELF_VARIABLES}
build/src_compute_SGComputeClient_cpp.o : src/compute/SGComputeClient.cpp   ${ALL_INCLUESlibSunsetGlow.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_compute_SGComputeClient_cpp.o -c src/compute/SGComputeClient.cpp -Iinclude -I../Renascence/include/ -Ithird
  
build/src_compute_SGComputeServer_cpp.o : src/compute/SGComputeServer.cpp   ${ALL_INCLUESlibSunsetGlow.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_compute_SGComputeServer_cpp.o -c src/compute/SGComputeServer.cpp -Iinclude -I../Renascence/include/ -Ithird
  
build/src_fs_SGFile_cpp.o : src/fs/SGFile.cpp   ${ALL_INCLUESlibSunsetGlow.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_fs_SGFile_cpp.o -c src/fs/SGFile.cpp -Iinclude -I../Renascence/include/ -Ithird
  
build/src_pieces_SGCachePieces_cpp.o : src/pieces/SGCachePieces.cpp   ${ALL_INCLUESlibSunsetGlow.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_pieces_SGCachePieces_cpp.o -c src/pieces/SGCachePieces.cpp -Iinclude -I../Renascence/include/ -Ithird
  
build/src_compute_SGCompute_CS_pb-c_c.o : src/compute/SGCompute.CS.pb-c.c   ${ALL_INCLUESlibSunsetGlow.so}
	gcc -std=c11 -O3 -g -fPIC -o build/src_compute_SGCompute_CS_pb-c_c.o -c src/compute/SGCompute.CS.pb-c.c -Iinclude -I../Renascence/include/ -Ithird
  
build/src_compute_SGCompute_SR_pb-c_c.o : src/compute/SGCompute.SR.pb-c.c   ${ALL_INCLUESlibSunsetGlow.so}
	gcc -std=c11 -O3 -g -fPIC -o build/src_compute_SGCompute_SR_pb-c_c.o -c src/compute/SGCompute.SR.pb-c.c -Iinclude -I../Renascence/include/ -Ithird
  
build/third_protobuf-c_protobuf-c_c.o : third/protobuf-c/protobuf-c.c   ${ALL_INCLUESlibSunsetGlow.so}
	gcc -std=c11 -O3 -g -fPIC -o build/third_protobuf-c_protobuf-c_c.o -c third/protobuf-c/protobuf-c.c -Iinclude -I../Renascence/include/ -Ithird
  
build/third_protobuf-c-rpc_protobuf-c-rpc-client_c.o : third/protobuf-c-rpc/protobuf-c-rpc-client.c   ${ALL_INCLUESlibSunsetGlow.so}
	gcc -std=c11 -O3 -g -fPIC -o build/third_protobuf-c-rpc_protobuf-c-rpc-client_c.o -c third/protobuf-c-rpc/protobuf-c-rpc-client.c -Iinclude -I../Renascence/include/ -Ithird
  
build/third_protobuf-c-rpc_protobuf-c-rpc-data-buffer_c.o : third/protobuf-c-rpc/protobuf-c-rpc-data-buffer.c   ${ALL_INCLUESlibSunsetGlow.so}
	gcc -std=c11 -O3 -g -fPIC -o build/third_protobuf-c-rpc_protobuf-c-rpc-data-buffer_c.o -c third/protobuf-c-rpc/protobuf-c-rpc-data-buffer.c -Iinclude -I../Renascence/include/ -Ithird
  
build/third_protobuf-c-rpc_protobuf-c-rpc-dispatch_c.o : third/protobuf-c-rpc/protobuf-c-rpc-dispatch.c   ${ALL_INCLUESlibSunsetGlow.so}
	gcc -std=c11 -O3 -g -fPIC -o build/third_protobuf-c-rpc_protobuf-c-rpc-dispatch_c.o -c third/protobuf-c-rpc/protobuf-c-rpc-dispatch.c -Iinclude -I../Renascence/include/ -Ithird
  
build/third_protobuf-c-rpc_protobuf-c-rpc-server_c.o : third/protobuf-c-rpc/protobuf-c-rpc-server.c   ${ALL_INCLUESlibSunsetGlow.so}
	gcc -std=c11 -O3 -g -fPIC -o build/third_protobuf-c-rpc_protobuf-c-rpc-server_c.o -c third/protobuf-c-rpc/protobuf-c-rpc-server.c -Iinclude -I../Renascence/include/ -Ithird
  

ALL_INCLUESexample.out=

example.out:  build/simple_main_cpp.o libSunsetGlow.so
	g++ -std=c++11   build/simple_main_cpp.o -O3 -g -fPIC   ./libSunsetGlow.so -o example.out ${SELF_VARIABLES}
build/simple_main_cpp.o : simple_main.cpp libSunsetGlow.so  ${ALL_INCLUESexample.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/simple_main_cpp.o -c simple_main.cpp -Iinclude -I../Renascence/include/ -Ithird
  

ALL_INCLUEScompute-responser.out=

compute-responser.out:  build/__compute-responser_cpp.o libSunsetGlow.so
	g++ -std=c++11   build/__compute-responser_cpp.o -O3 -g -fPIC   ./libSunsetGlow.so -o compute-responser.out ${SELF_VARIABLES}
build/__compute-responser_cpp.o : ./compute-responser.cpp libSunsetGlow.so  ${ALL_INCLUEScompute-responser.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/__compute-responser_cpp.o -c ./compute-responser.cpp -Iinclude -I../Renascence/include/ -Ithird
  

ALL_INCLUEScompute-server.out=

compute-server.out:  build/__compute-server_cpp.o libSunsetGlow.so
	g++ -std=c++11   build/__compute-server_cpp.o -O3 -g -fPIC   ./libSunsetGlow.so -o compute-server.out ${SELF_VARIABLES}
build/__compute-server_cpp.o : ./compute-server.cpp libSunsetGlow.so  ${ALL_INCLUEScompute-server.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/__compute-server_cpp.o -c ./compute-server.cpp -Iinclude -I../Renascence/include/ -Ithird
  

ALL_INCLUEStest.out= include//fs/SGFile.h include//pieces/SGCachePieces.h include//SGComputeClient.h include//SGComputeServer.h include//SGDebug.h

test.out:  build/test_GPCreatorClientTest_cpp.o build/test_GPTest_cpp.o build/test_GPTestMain_cpp.o libSunsetGlow.so
	g++ -std=c++11   build/test_GPCreatorClientTest_cpp.o build/test_GPTest_cpp.o build/test_GPTestMain_cpp.o -O3 -g -fPIC   ./libSunsetGlow.so -lpthread -ldl -o test.out ${SELF_VARIABLES}
build/test_GPCreatorClientTest_cpp.o : test/GPCreatorClientTest.cpp libSunsetGlow.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/test_GPCreatorClientTest_cpp.o -c test/GPCreatorClientTest.cpp -Iinclude -I../Renascence/include/ -Ithird
  
build/test_GPTest_cpp.o : test/GPTest.cpp libSunsetGlow.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/test_GPTest_cpp.o -c test/GPTest.cpp -Iinclude -I../Renascence/include/ -Ithird
  
build/test_GPTestMain_cpp.o : test/GPTestMain.cpp libSunsetGlow.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/test_GPTestMain_cpp.o -c test/GPTestMain.cpp -Iinclude -I../Renascence/include/ -Ithird
  

clean:
	rm build/*.o
	rm libSunsetGlow.so
	rm example.out
	rm compute-responser.out
	rm compute-server.out
	rm test.out