#SunsetGlow介绍
##作用
SunsetGlow是Renascense的并行计算插件，支持单机和分布式的计算，旨在建立一个最优的分布式计算架构。

##架构设计
###一期：实现master-slave分布式计算模式
数据存储于HDFS系统中，所有计算函数库及配置文件事先放到每一台计算资源上。所有计算资源共同访问同一个HDFS文件系统。

计算调度分为三个模块：
客户端(client)——中心服务端(server)——响应者(responser)

client发起计算请求，server响应请求并将任务分解传给responser，等待responser完成后返回。


###二期：加入计算函数库的编写与安装机制
支持函数库编写后推送到目标机器上编译，动态加载


##相关依赖
###Renascense

###HDFS
Version: 2.5.2
1、下载HDFS 2.5.2源码及安装包。
2、在源码包中编译hdfs的jni库，将其放入/usr/lib。
3、在.bashrc中指定 CLASSPATH，加载hdfs相应的类。
4、建立自己的hdfs配置文件，格式为四行文本：

ip（访问HDFS集群的ip地址）
username:password（用户名：密码）
hdfsBaseDir（HDFS根目录）
localBaseDir（本地根目录，目录结构与 hdfsBaseDir 一一对应）

5、修改 conf/hdfs.conf，将路径改为自己的hdf配置文件路径
