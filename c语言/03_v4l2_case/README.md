# v4l2采集摄像头数据

**V4L2**

V4L2全称是Video for Linux two（Video4Linux2），是V4L2改进衍生版本。V4L2是linux操作系统下的一个标注化的音频、视频设备驱动框架，向下屏蔽底层设备的差异，向上提供标准统一的访问接口，提高用户在音视频方面的应用开发效率。只要底层音视频设备（如摄像头）兼容V4L2标准，则应用程序可以无缝接入该音视频设备。

**API使用**

```c
//video 设备常用的执行码
VIDIOC_QUERYCAP     /* 查询设备属性 */
VIDIOC_ENUM_FMT		/* 查询设备支持的输出格式*/
VIDIOC_G_FMT        /* 查询设备输出帧格式 */
VIDIOC_S_FMT        /* 设置设备输出帧格式 */
VIDIOC_REQBUFS      /* 申请帧缓存 */
VIDIOC_QUERYBUF     /* 获取申请的帧缓存 */
VIDIOC_QBUF         /* 将帧缓存加入视频流采集队列 */
VIDIOC_DQBUF        /* 获取已采集视频流的缓存帧 */
VIDIOC_STREAMON     /* 开启视频流采集 */
VIDIOC_STREAMOFF    /* 关闭视频流采集 */

int ioctl(int fd, unsigned long request, ...);
/*
其中，fd是要操作的设备文件的文件描述符，request是要执行的操作码，其它参数是可选的，用于传递操作需要的参数。返回值为0表示成功，-1表示失败。
*/

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
/*
其中，nfds表示待监视的文件描述符数量，即文件描述符集合中的最大文件描述符加1。readfds、writefds和exceptfds分别是要监视读、写和异常事件的文件描述符集合，可以传入NULL表示不监视该事件。timeout指定超时时间，即select函数最多等待的时间，如果在等待期间没有任何事件发生，则select函数返回0。

作用：用于等待摄像头设备fd描述符是否准备好，未准备好会阻塞，准备好才能取数据
*/

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
int munmap(void *addr, size_t length);
/*
将内核地址直接映射到应用层，此处使用将设备缓冲区映射到应用层，加快I/O速率
*/

```

**结果**

执行完代码后，最终会打开摄像头，抓取20帧数据形成20章图片

**注意**

此代码对不同的摄像头需要进行修改，我们获取设备的属性后设置自己摄像头所具备的图像格式，以及设备名：/dev/video0.

在linux里，插上摄像头会在系统生成一个videoX的文件，从video0开始。