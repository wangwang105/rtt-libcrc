# libcrc 软件包

## 介绍

`Libcrc` 是一个自1999年起便开始开发的多平台CRC（循环冗余校验）库。自那时起，其源代码的原始版本便可在[www.lammertbies.nl](https://www.lammertbies.nl/) 上获取。最近，该代码与以前未发布的开发成果进行了合并，现在该库可在Github上获取。CRC计算例程的在线版本也可在 [Github](https://github.com/lammertb/libcrc/) 上找到。

CRC库及其API参考文档的新地址位于 [www.libcrc.org](http://libcrc.org)。在该网站上，还可以找到API文档的在线版本。

作者将libcrc库移植到rtthread 软件包上。

### 目录结构

```
libcrc
├────libcrc                          // libcrc 原本的库
│   README.md                        // 软件包说明
│   SConscript                       // RT-Thread 默认的构建脚本
│   LICENSE                          // 许可证文件
├───docs 
│   |   api.md                       // API 使用说明
├───samples                          // 示例代码
│   |   libcrc_sample.c              // 软件包使用示例代码
└───src                              // 源文件
└───tab                              // crc32与crc64的表
└───include                          // 头文件
```

### 许可证

libcrc 遵循 TIM 许可，详见 `LICENSE` 文件。

### 依赖

- RT_Thread 3.0+

## 获取方式

使用 `libcrc package` 需要在 RT-Thread 的包管理中选中它，具体路径如下：

```
RT-Thread online packages  --->
    miscellaneous packages  --->
        libcrc:Multi platform MIT licensed CRC library in C. --->
```

进入 libcrc 软件包的配置菜单按自己的需求进行具体的配置

```
Version (v1.0.0)  --->
[*] crc8
[*]     using 8 bit crc
[*] crc16
[*]     using 16 bit crc
[*]     using ccitt crc, 0x1D0F
[*]     using ccitt crc, 0xFFFF
[*]     using dnp crc
[*]     using kermit crc
[*]     using modbus crc
[*]     using sick crc
[*]     using xmodem crc
[*] crc32
[*]     using 32 bit crc
[*] crc64
[*]     using 64 bit ecma crc
[*]     using 64 bit we crc
[*] using nmea checksum
[*] using sample crc
```

** using sample crc** ：开启 licrc  使用示例

配置完成后让 RT-Thread 的包管理器自动更新，或者使用 pkgs --update 命令更新包到 BSP 中。

## 使用方法

详细的使用方法可以参考[libcrc 示例程序](examples/libcrc_sample.c) 和 [API 说明文档](doc/crc_start.md)。

## MSH 测试命令

libcrc软件包提供了crc8,crc16,crc32等 测试命令，项目只要在 RT-Thread 上开启 MSH 功能，并使能 licrc  使用示例。以下是一些MSH的使用实例：

```
msh >crc8 12345678
12345678 :
CRC8               = 0xef 

msh >crc8 123456789
123456789 :
CRC8               = 0x8f 

crc: CRC algorithm sample program
Copyright (c) 2025 wangwang105(Wang rong wen)

Usage: crc [-a|-x] inputstring 

    -a Program asks for ASCII input. Following parameters ignored.
    -x Program asks for hexadecimal input. Following parameters ignored.
crc: command failed -255.
msh >crc -a 123456789

crc: CRC algorithm sample program
Copyright (c) 2025 wangwang105(Wang rong wen)

123456789 :
CRC16              = 0xbb3d 
CRC16 (Modbus)     = 0x4b37 
CRC16 (Sick)       = 0x56a6 
CRC-CCITT (0x0000) = 0x31c3 
CRC-CCITT (0xffff) = 0x29b1 
CRC-CCITT (0x1d0f) = 0xe5cc 
CRC-CCITT (Kermit) = 0x8921 
CRC-DNP            = 0x82ea 
CRC32              = 0xcbf43926 
```

## 注意事项

暂无。

## 联系方式

- 维护：[wangwang105](https://github.com/wangwang105)
- 主页：<https://github.com/RT-Thread-packages/libcrc>