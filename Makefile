all:libSunsetGlow.a example.out 

ALL_INCLUESlibSunsetGlow.a=

libSunsetGlow.a:  build/third_protobuf-c_protobuf-c.o build/third_protobuf-c-rpc_protobuf-c-rpc-client.o build/third_protobuf-c-rpc_protobuf-c-rpc-data-buffer.o build/third_protobuf-c-rpc_protobuf-c-rpc-dispatch.o build/third_protobuf-c-rpc_protobuf-c-rpc-server.o 
	rm -f libSunsetGlow.a
	ar rcs libSunsetGlow.a  build/third_protobuf-c_protobuf-c.o build/third_protobuf-c-rpc_protobuf-c-rpc-client.o build/third_protobuf-c-rpc_protobuf-c-rpc-data-buffer.o build/third_protobuf-c-rpc_protobuf-c-rpc-dispatch.o build/third_protobuf-c-rpc_protobuf-c-rpc-server.o ${SELF_VARIABLES}
build/third_protobuf-c_protobuf-c.o : third/protobuf-c/protobuf-c.c   ${ALL_INCLUESlibSunsetGlow.a}
	gcc -std=c11 -O3 -g -fPIC -o build/third_protobuf-c_protobuf-c.o -c third/protobuf-c/protobuf-c.c -Iinclude -Ithird
  
build/third_protobuf-c-rpc_protobuf-c-rpc-client.o : third/protobuf-c-rpc/protobuf-c-rpc-client.c   ${ALL_INCLUESlibSunsetGlow.a}
	gcc -std=c11 -O3 -g -fPIC -o build/third_protobuf-c-rpc_protobuf-c-rpc-client.o -c third/protobuf-c-rpc/protobuf-c-rpc-client.c -Iinclude -Ithird
  
build/third_protobuf-c-rpc_protobuf-c-rpc-data-buffer.o : third/protobuf-c-rpc/protobuf-c-rpc-data-buffer.c   ${ALL_INCLUESlibSunsetGlow.a}
	gcc -std=c11 -O3 -g -fPIC -o build/third_protobuf-c-rpc_protobuf-c-rpc-data-buffer.o -c third/protobuf-c-rpc/protobuf-c-rpc-data-buffer.c -Iinclude -Ithird
  
build/third_protobuf-c-rpc_protobuf-c-rpc-dispatch.o : third/protobuf-c-rpc/protobuf-c-rpc-dispatch.c   ${ALL_INCLUESlibSunsetGlow.a}
	gcc -std=c11 -O3 -g -fPIC -o build/third_protobuf-c-rpc_protobuf-c-rpc-dispatch.o -c third/protobuf-c-rpc/protobuf-c-rpc-dispatch.c -Iinclude -Ithird
  
build/third_protobuf-c-rpc_protobuf-c-rpc-server.o : third/protobuf-c-rpc/protobuf-c-rpc-server.c   ${ALL_INCLUESlibSunsetGlow.a}
	gcc -std=c11 -O3 -g -fPIC -o build/third_protobuf-c-rpc_protobuf-c-rpc-server.o -c third/protobuf-c-rpc/protobuf-c-rpc-server.c -Iinclude -Ithird
  

ALL_INCLUESexample.out=

example.out:  build/simple_main.o libSunsetGlow.a
	g++ -std=c++11   build/simple_main.o -O3 -g -fPIC   ./libSunsetGlow.a -o example.out ${SELF_VARIABLES}
build/simple_main.o : simple_main.cpp libSunsetGlow.a  ${ALL_INCLUESexample.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/simple_main.o -c simple_main.cpp -Iinclude -Ithird
  

clean:
	rm build/*.o
	rm libSunsetGlow.a
	rm example.out