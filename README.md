## 前言

本仓库旨在记录和总结本人于2024年8月开始的EtherCAT学习。

开始学习EtherCAT时，我遇到了很大的困难，所幸在网上看到了很多网友整理的资料，其中特别是 [@最美的愿望一定最疯狂](https://blog.csdn.net/g360250466?type=blog) 这位CSDN大佬的[“Ethercat”专栏](https://blog.csdn.net/g360250466/category_12241674.html?spm=1001.2014.3001.5482)，从 EetherCAT从站源码的生成、解析、移植到SOEM QT主站的搭建，写的非常详细，给了我极大的帮助和启发，在此特别感谢！

本仓库的很多内容也是参考了他的文章，自己再整理复现一遍，并加上一些自己的理解和补充，也希望借此仓库表达对前辈的敬意。

## 文件结构

- GD32C113CB_ECATSlave_demo：GD32C113 AX58100 EtherCAT从站的实现
- QT_ECAT_tool：QT SOEM EtherCAT主站的实现
- PLC_validation：EtherCAT从站在TwinCAT、PLC上的验证

- note：相关笔记

