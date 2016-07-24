all:libSunsetGlow.a example.out 

ALL_INCLUESlibSunsetGlow.a=

libSunsetGlow.a:  build/src_compute_SGCompute_CS_pb-c_c.o build/src_compute_SGCompute_SR_pb-c_c.o build/third_protobuf-c_protobuf-c_c.o build/third_protobuf-c-rpc_protobuf-c-rpc-client_c.o build/third_protobuf-c-rpc_protobuf-c-rpc-data-buffer_c.o build/third_protobuf-c-rpc_protobuf-c-rpc-dispatch_c.o build/third_protobuf-c-rpc_protobuf-c-rpc-server_c.o 
	rm -f libSunsetGlow.a
	ar rcs libSunsetGlow.a  build/src_compute_SGCompute_CS_pb-c_c.o build/src_compute_SGCompute_SR_pb-c_c.o build/third_protobuf-c_protobuf-c_c.o build/third_protobuf-c-rpc_protobuf-c-rpc-client_c.o build/third_protobuf-c-rpc_protobuf-c-rpc-data-buffer_c.o build/third_protobuf-c-rpc_protobuf-c-rpc-dispatch_c.o build/third_protobuf-c-rpc_protobuf-c-rpc-server_c.o ${SELF_VARIABLES}
build/src_compute_SGCompute_CS_pb-c_c.o : src/compute/SGCompute.CS.pb-c.c   ${ALL_INCLUESlibSunsetGlow.a}
	gcc -std=c11 -O3 -g -fPIC -o build/src_compute_SGCompute_CS_pb-c_c.o -c src/compute/SGCompute.CS.pb-c.c -Iinclude -Ithird
  
build/src_compute_SGCompute_SR_pb-c_c.o : src/compute/SGCompute.SR.pb-c.c   ${ALL_INCLUESlibSunsetGlow.a}
	gcc -std=c11 -O3 -g -fPIC -o build/src_compute_SGCompute_SR_pb-c_c.o -c src/compute/SGCompute.SR.pb-c.c -Iinclude -Ithird
  
build/third_protobuf-c_protobuf-c_c.o : third/protobuf-c/protobuf-c.c   ${ALL_INCLUESlibSunsetGlow.a}
	gcc -std=c11 -O3 -g -fPIC -o build/third_protobuf-c_protobuf-c_c.o -c third/protobuf-c/protobuf-c.c -Iinclude -Ithird
  
build/third_protobuf-c-rpc_protobuf-c-rpc-client_c.o : third/protobuf-c-rpc/protobuf-c-rpc-client.c   ${ALL_INCLUESlibSunsetGlow.a}
	gcc -std=c11 -O3 -g -fPIC -o build/third_protobuf-c-rpc_protobuf-c-rpc-client_c.o -c third/protobuf-c-rpc/protobuf-c-rpc-client.c -Iinclude -Ithird
  
build/third_protobuf-c-rpc_protobuf-c-rpc-data-buffer_c.o : third/protobuf-c-rpc/protobuf-c-rpc-data-buffer.c   ${ALL_INCLUESlibSunsetGlow.a}
	gcc -std=c11 -O3 -g -fPIC -o build/third_protobuf-c-rpc_protobuf-c-rpc-data-buffer_c.o -c third/protobuf-c-rpc/protobuf-c-rpc-data-buffer.c -Iinclude -Ithird
  
build/third_protobuf-c-rpc_protobuf-c-rpc-dispatch_c.o : third/protobuf-c-rpc/protobuf-c-rpc-dispatch.c   ${ALL_INCLUESlibSunsetGlow.a}
	gcc -std=c11 -O3 -g -fPIC -o build/third_protobuf-c-rpc_protobuf-c-rpc-dispatch_c.o -c third/protobuf-c-rpc/protobuf-c-rpc-dispatch.c -Iinclude -Ithird
  
build/third_protobuf-c-rpc_protobuf-c-rpc-server_c.o : third/protobuf-c-rpc/protobuf-c-rpc-server.c   ${ALL_INCLUESlibSunsetGlow.a}
	gcc -std=c11 -O3 -g -fPIC -o build/third_protobuf-c-rpc_protobuf-c-rpc-server_c.o -c third/protobuf-c-rpc/protobuf-c-rpc-server.c -Iinclude -Ithird
  

ALL_INCLUESexample.out=

example.out:  build/simple_main_cpp.o libSunsetGlow.a
	g++ -std=c++11   build/simple_main_cpp.o -O3 -g -fPIC   ./libSunsetGlow.a -o example.out ${SELF_VARIABLES}
build/simple_main_cpp.o : simple_main.cpp libSunsetGlow.a  ${ALL_INCLUESexample.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/simple_main_cpp.o -c simple_main.cpp -Iinclude -Ithird
  

clean:
	rm build/*.o
	rm libSunsetGlow.a
	rm example.out