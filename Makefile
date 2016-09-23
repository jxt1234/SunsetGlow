all:libSunsetGlow.so libhdfsStream.so compute-responser.out compute-server.out test.out hdfs_tools.out 

ALL_INCLUESlibSunsetGlow.so= include//SGBasicServer.h include//SGComputeClient.h include//SGComputeResponser.h include//SGComputeServer.h include//SGDebug.h include//SGHdfsStreamFactory.h include//SGMacro.h include//SGPathUtils.h include//SGBasicServer.h include//SGComputeClient.h include//SGComputeResponser.h include//SGComputeServer.h include//SGDebug.h include//SGHdfsStreamFactory.h include//SGMacro.h include//SGPathUtils.h

libSunsetGlow.so:  build/src_compute__SGBasicServer_cpp.o build/src_compute__SGComputeClient_cpp.o build/src_compute__SGComputeResponser_cpp.o build/src_compute__SGComputeServer_cpp.o build/src_compute__SGResponserExecutor_cpp.o build/third_thread_MGPThread_cpp.o build/third_thread_MGPThread_Linux_cpp.o build/third_thread_MGPThreadPool_cpp.o build/src_compute__SGCompute_CS_pb-c_c.o build/src_compute__SGCompute_SR_pb-c_c.o build/third_protobuf-c_protobuf-c_c.o build/third_protobuf-c-rpc_protobuf-c-rpc-client_c.o build/third_protobuf-c-rpc_protobuf-c-rpc-data-buffer_c.o build/third_protobuf-c-rpc_protobuf-c-rpc-dispatch_c.o build/third_protobuf-c-rpc_protobuf-c-rpc-server_c.o 
	g++ -std=c++11   build/src_compute__SGBasicServer_cpp.o build/src_compute__SGComputeClient_cpp.o build/src_compute__SGComputeResponser_cpp.o build/src_compute__SGComputeServer_cpp.o build/src_compute__SGResponserExecutor_cpp.o build/third_thread_MGPThread_cpp.o build/third_thread_MGPThread_Linux_cpp.o build/third_thread_MGPThreadPool_cpp.o build/src_compute__SGCompute_CS_pb-c_c.o build/src_compute__SGCompute_SR_pb-c_c.o build/third_protobuf-c_protobuf-c_c.o build/third_protobuf-c-rpc_protobuf-c-rpc-client_c.o build/third_protobuf-c-rpc_protobuf-c-rpc-data-buffer_c.o build/third_protobuf-c-rpc_protobuf-c-rpc-dispatch_c.o build/third_protobuf-c-rpc_protobuf-c-rpc-server_c.o -O3 -g -fPIC  --shared  ../Renascence/libGP.a -o libSunsetGlow.so ${SELF_VARIABLES}
build/src_compute__SGBasicServer_cpp.o : src/compute//SGBasicServer.cpp   ${ALL_INCLUESlibSunsetGlow.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_compute__SGBasicServer_cpp.o -c src/compute//SGBasicServer.cpp -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  
build/src_compute__SGComputeClient_cpp.o : src/compute//SGComputeClient.cpp   ${ALL_INCLUESlibSunsetGlow.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_compute__SGComputeClient_cpp.o -c src/compute//SGComputeClient.cpp -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  
build/src_compute__SGComputeResponser_cpp.o : src/compute//SGComputeResponser.cpp   ${ALL_INCLUESlibSunsetGlow.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_compute__SGComputeResponser_cpp.o -c src/compute//SGComputeResponser.cpp -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  
build/src_compute__SGComputeServer_cpp.o : src/compute//SGComputeServer.cpp   ${ALL_INCLUESlibSunsetGlow.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_compute__SGComputeServer_cpp.o -c src/compute//SGComputeServer.cpp -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  
build/src_compute__SGResponserExecutor_cpp.o : src/compute//SGResponserExecutor.cpp   ${ALL_INCLUESlibSunsetGlow.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_compute__SGResponserExecutor_cpp.o -c src/compute//SGResponserExecutor.cpp -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  
build/third_thread_MGPThread_cpp.o : third/thread/MGPThread.cpp   ${ALL_INCLUESlibSunsetGlow.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/third_thread_MGPThread_cpp.o -c third/thread/MGPThread.cpp -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  
build/third_thread_MGPThread_Linux_cpp.o : third/thread/MGPThread_Linux.cpp   ${ALL_INCLUESlibSunsetGlow.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/third_thread_MGPThread_Linux_cpp.o -c third/thread/MGPThread_Linux.cpp -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  
build/third_thread_MGPThreadPool_cpp.o : third/thread/MGPThreadPool.cpp   ${ALL_INCLUESlibSunsetGlow.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/third_thread_MGPThreadPool_cpp.o -c third/thread/MGPThreadPool.cpp -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  
build/src_compute__SGCompute_CS_pb-c_c.o : src/compute//SGCompute.CS.pb-c.c   ${ALL_INCLUESlibSunsetGlow.so}
	gcc -std=c11 -O3 -g -fPIC -o build/src_compute__SGCompute_CS_pb-c_c.o -c src/compute//SGCompute.CS.pb-c.c -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  
build/src_compute__SGCompute_SR_pb-c_c.o : src/compute//SGCompute.SR.pb-c.c   ${ALL_INCLUESlibSunsetGlow.so}
	gcc -std=c11 -O3 -g -fPIC -o build/src_compute__SGCompute_SR_pb-c_c.o -c src/compute//SGCompute.SR.pb-c.c -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  
build/third_protobuf-c_protobuf-c_c.o : third/protobuf-c/protobuf-c.c   ${ALL_INCLUESlibSunsetGlow.so}
	gcc -std=c11 -O3 -g -fPIC -o build/third_protobuf-c_protobuf-c_c.o -c third/protobuf-c/protobuf-c.c -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  
build/third_protobuf-c-rpc_protobuf-c-rpc-client_c.o : third/protobuf-c-rpc/protobuf-c-rpc-client.c   ${ALL_INCLUESlibSunsetGlow.so}
	gcc -std=c11 -O3 -g -fPIC -o build/third_protobuf-c-rpc_protobuf-c-rpc-client_c.o -c third/protobuf-c-rpc/protobuf-c-rpc-client.c -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  
build/third_protobuf-c-rpc_protobuf-c-rpc-data-buffer_c.o : third/protobuf-c-rpc/protobuf-c-rpc-data-buffer.c   ${ALL_INCLUESlibSunsetGlow.so}
	gcc -std=c11 -O3 -g -fPIC -o build/third_protobuf-c-rpc_protobuf-c-rpc-data-buffer_c.o -c third/protobuf-c-rpc/protobuf-c-rpc-data-buffer.c -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  
build/third_protobuf-c-rpc_protobuf-c-rpc-dispatch_c.o : third/protobuf-c-rpc/protobuf-c-rpc-dispatch.c   ${ALL_INCLUESlibSunsetGlow.so}
	gcc -std=c11 -O3 -g -fPIC -o build/third_protobuf-c-rpc_protobuf-c-rpc-dispatch_c.o -c third/protobuf-c-rpc/protobuf-c-rpc-dispatch.c -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  
build/third_protobuf-c-rpc_protobuf-c-rpc-server_c.o : third/protobuf-c-rpc/protobuf-c-rpc-server.c   ${ALL_INCLUESlibSunsetGlow.so}
	gcc -std=c11 -O3 -g -fPIC -o build/third_protobuf-c-rpc_protobuf-c-rpc-server_c.o -c third/protobuf-c-rpc/protobuf-c-rpc-server.c -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  

ALL_INCLUESlibhdfsStream.so= include//SGBasicServer.h include//SGComputeClient.h include//SGComputeResponser.h include//SGComputeServer.h include//SGDebug.h include//SGHdfsStreamFactory.h include//SGMacro.h include//SGPathUtils.h

libhdfsStream.so:  build/src_fs_SGHdfsStream_cpp.o build/src_fs_SGHdfsStreamFactory_cpp.o build/src_fs_SGHdfsWStream_cpp.o build/src_fs_SGPathUtils_cpp.o 
	g++ -std=c++11   build/src_fs_SGHdfsStream_cpp.o build/src_fs_SGHdfsStreamFactory_cpp.o build/src_fs_SGHdfsWStream_cpp.o build/src_fs_SGPathUtils_cpp.o -O3 -g -fPIC  --shared   ./third/libhdfs/libhdfs.a_mac /Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/jre/lib/server/libjvm.dylib -o libhdfsStream.so ${SELF_VARIABLES}
build/src_fs_SGHdfsStream_cpp.o : src/fs/SGHdfsStream.cpp   ${ALL_INCLUESlibhdfsStream.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_fs_SGHdfsStream_cpp.o -c src/fs/SGHdfsStream.cpp -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  
build/src_fs_SGHdfsStreamFactory_cpp.o : src/fs/SGHdfsStreamFactory.cpp   ${ALL_INCLUESlibhdfsStream.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_fs_SGHdfsStreamFactory_cpp.o -c src/fs/SGHdfsStreamFactory.cpp -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  
build/src_fs_SGHdfsWStream_cpp.o : src/fs/SGHdfsWStream.cpp   ${ALL_INCLUESlibhdfsStream.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_fs_SGHdfsWStream_cpp.o -c src/fs/SGHdfsWStream.cpp -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  
build/src_fs_SGPathUtils_cpp.o : src/fs/SGPathUtils.cpp   ${ALL_INCLUESlibhdfsStream.so}
	g++ -std=c++11 -O3 -g -fPIC -o build/src_fs_SGPathUtils_cpp.o -c src/fs/SGPathUtils.cpp -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  

ALL_INCLUEScompute-responser.out=

compute-responser.out:  build/__compute-responser_cpp.o libSunsetGlow.so
	g++ -std=c++11   build/__compute-responser_cpp.o -O3 -g -fPIC   ./libSunsetGlow.so -o compute-responser.out ${SELF_VARIABLES}
build/__compute-responser_cpp.o : ./compute-responser.cpp libSunsetGlow.so  ${ALL_INCLUEScompute-responser.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/__compute-responser_cpp.o -c ./compute-responser.cpp -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  

ALL_INCLUEScompute-server.out=

compute-server.out:  build/__compute-server_cpp.o libSunsetGlow.so
	g++ -std=c++11   build/__compute-server_cpp.o -O3 -g -fPIC   ./libSunsetGlow.so -o compute-server.out ${SELF_VARIABLES}
build/__compute-server_cpp.o : ./compute-server.cpp libSunsetGlow.so  ${ALL_INCLUEScompute-server.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/__compute-server_cpp.o -c ./compute-server.cpp -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  

ALL_INCLUEStest.out= include//SGBasicServer.h include//SGComputeClient.h include//SGComputeResponser.h include//SGComputeServer.h include//SGDebug.h include//SGHdfsStreamFactory.h include//SGMacro.h include//SGPathUtils.h

test.out:  build/test_GPCreatorClientTest_cpp.o build/test_GPPathUtilsTest_cpp.o build/test_GPTest_cpp.o build/test_GPTestMain_cpp.o libSunsetGlow.so libhdfsStream.so
	g++ -std=c++11   build/test_GPCreatorClientTest_cpp.o build/test_GPPathUtilsTest_cpp.o build/test_GPTest_cpp.o build/test_GPTestMain_cpp.o -O3 -g -fPIC   ./libSunsetGlow.so ./libhdfsStream.so -lpthread -ldl -o test.out ${SELF_VARIABLES}
build/test_GPCreatorClientTest_cpp.o : test/GPCreatorClientTest.cpp libSunsetGlow.so libhdfsStream.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/test_GPCreatorClientTest_cpp.o -c test/GPCreatorClientTest.cpp -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  
build/test_GPPathUtilsTest_cpp.o : test/GPPathUtilsTest.cpp libSunsetGlow.so libhdfsStream.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/test_GPPathUtilsTest_cpp.o -c test/GPPathUtilsTest.cpp -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  
build/test_GPTest_cpp.o : test/GPTest.cpp libSunsetGlow.so libhdfsStream.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/test_GPTest_cpp.o -c test/GPTest.cpp -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  
build/test_GPTestMain_cpp.o : test/GPTestMain.cpp libSunsetGlow.so libhdfsStream.so  ${ALL_INCLUEStest.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/test_GPTestMain_cpp.o -c test/GPTestMain.cpp -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  

ALL_INCLUEShdfs_tools.out=

hdfs_tools.out:  build/hdfs_tools_cpp.o ../Renascence/libGP.a libhdfsStream.so
	g++ -std=c++11   build/hdfs_tools_cpp.o -O3 -g -fPIC  ../Renascence/libGP.a libhdfsStream.so -o hdfs_tools.out ${SELF_VARIABLES}
build/hdfs_tools_cpp.o : hdfs_tools.cpp ../Renascence/libGP.a libhdfsStream.so  ${ALL_INCLUEShdfs_tools.out}
	g++ -std=c++11 -O3 -g -fPIC -o build/hdfs_tools_cpp.o -c hdfs_tools.cpp -Iinclude -I../Renascence/include/ -Ithird -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/darwin/ -I/Library/Java/JavaVirtualMachines/jdk1.8.0_40.jdk/Contents/Home/include/ -Ithird/libhdfs/
  

clean:
	rm build/*.o
	rm libSunsetGlow.so
	rm libhdfsStream.so
	rm compute-responser.out
	rm compute-server.out
	rm test.out
	rm hdfs_tools.out