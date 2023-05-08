#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

/**
 * V4L2 摄像头应用编程
*/

typedef struct _mmap_buf mmap_buf;
typedef struct _v4l2_video v4l2_video;

struct _mmap_buf{
    void* addr;
    int size;
};

struct _v4l2_video{
    int fd;
    mmap_buf* mmap_buf;
    int mmap_buf_cout;
};

static int open_video_device(const char* device_name);
static int close_video_device(v4l2_video* video);
static int query_video_device(v4l2_video* video);
static int set_vedio_device_format(v4l2_video* video);
static int set_video_device_mmap(v4l2_video* video);
static int set_video_device_stream_queue(v4l2_video* video, int index);
static int set_video_device_streaming_on(v4l2_video* video);
static int read_video_device_stream_frame(v4l2_video* video, int* out_buf_index);
static int set_video_device_stream_off(v4l2_video* video);

//打开一个video设备
static int open_video_device(const char* device_name){

    int fd = 0;

    if(device_name == NULL){
        return -1;
    }

    //以读写方式打开设备
    fd = open(device_name, O_RDWR);
    if(fd < 0){
        perror("open video device failed");
        return -1;
    }

    return fd;
}

//关闭一个video设备
static int close_video_device(v4l2_video* video){
    
    int ret = 0;

    for(int i = 0; i < video->mmap_buf_cout; i++){
        if(video->mmap_buf[i].addr != 0x00){
            ret = munmap(video->mmap_buf[i].addr, video->mmap_buf[i].size);
            if (ret < 0)
            {
                perror("unmap failed");
                return -1;
            }
        }
    }

    if(video->mmap_buf != NULL){
        free(video->mmap_buf);
    }

    if(video->fd != 0x00){
        ret = close(video->fd);
        if (ret < 0)
        {
            perror("close device failed");
            return -1;
        }
    }

    return 0;
}

//查询video设备属性
static int query_video_device(v4l2_video* video){
    
    int ret =0;
    struct v4l2_capability cap = { 0 };
    struct v4l2_fmtdesc fmt = { 0 };

    ret = ioctl(video->fd, VIDIOC_QUERYCAP, &cap);
    if(ret < 0){
        perror("ioctl call \'VIDIOC_QUERYCAP\' failed");
        return -1;
    }

    //打印设备信息
    printf("video driver name:%s\n", cap.driver);
    printf("video device name:%s\n", cap.card);
    printf("video bus information:%s\n", cap.bus_info);
    printf("video version:%d\n", cap.version);
    printf("video capabilities:%x\n", cap.capabilities);

    if(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE){
        printf("video device support video capture\n");
    }

    if(cap.capabilities & V4L2_CAP_STREAMING){
        printf("video device support video streaming\n");
    }

    //枚举视频采集格式
    fmt.index = 0;
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    while((ioctl(video->fd, VIDIOC_ENUM_FMT, &fmt)) != -1){
        printf("capabilities:%d.%s\n", fmt.index + 1, fmt.description);
        fmt.index++;
    }

    return 0;
}

//设置帧输出格式
static int set_vedio_device_format(v4l2_video* video){
    
    int ret = 0;
    struct v4l2_format format = { 0 };

    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    //像素宽度
    format.fmt.pix.width = 1280;
    //像素高度
    format.fmt.pix.height = 900;
    //输出格式
    format.fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
    //视频数据的扫描方式和采集方式
    format.fmt.pix.field = V4L2_FIELD_NONE;

    ret = ioctl(video->fd, VIDIOC_S_FMT, &format);
    if(ret < 0){
        perror("ioctl call \'VIDIOC_S_FMT\' failed");
        return -1;
    }

    return ret;

}

//申请帧缓存区 将内核缓存区映射到用户态
static int set_video_device_mmap(v4l2_video* video){

    int ret = 0;
    //采集缓冲区
    struct v4l2_requestbuffers req_buf = { 0 };
    struct v4l2_buffer buf = { 0 };

    //申请内存缓冲区
    video->mmap_buf_cout = 10;
    req_buf.count = 10;
    req_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req_buf.memory = V4L2_MEMORY_MMAP;
    ret = ioctl(video->fd, VIDIOC_REQBUFS, &req_buf);
    if(ret < 0){
        perror("ioctl call \'VIDIOC_REQBUFS\' failed");
        return -1;
    }

    video->mmap_buf = malloc(req_buf.count * sizeof(mmap_buf));
    if(video->mmap_buf == NULL){
        perror("video mmap_buf malloc failed");
        return -1;
    }

    //将内核内存映射到用户态
    for(int i = 0; i < req_buf.count; ++i){
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;
        
        ret = ioctl(video->fd, VIDIOC_QUERYBUF, &buf);
        if(ret < 0){
            perror("ioctl call \'VIDIOC_QUERYBUF\' failed");
            return -1;
        }

        video->mmap_buf[i].size = buf.length;
        video->mmap_buf[i].addr = mmap(NULL, buf.length, PROT_READ|PROT_WRITE, MAP_SHARED, video->fd, buf.m.offset);
        if(MAP_FAILED == video->mmap_buf[i].addr){
            perror("map failed");
            return -1;
        }
    }
    return 0;
}

//将帧缓存放入对列
static int set_video_device_stream_queue(v4l2_video* video , int index){
    
    int ret = 0;
    struct v4l2_buffer buf = { 0 };

    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    buf.index = index;
    
    ret = ioctl(video->fd, VIDIOC_QBUF, &buf);
    if(ret < 0){
        perror("ioctl call \'VIDIOC_QBUF\' failed");
        return -1;
    }

    return 0;
}

//开启视频流
static int set_video_device_streaming_on(v4l2_video* video){
    
    int ret = 0;
    enum v4l2_buf_type type;

    for (int i = 0; i < video->mmap_buf_cout; i++)
    {
        ret = set_video_device_stream_queue(video, i);
        if(ret < 0){
            return -1;
        }  
    }

    //开启视频流
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ret = ioctl(video->fd, VIDIOC_STREAMON, &type);
    if(ret < 0){
        perror("ioctl call \'VIDIOC_STREAMON\' failed");
        return -1;
    }
    
    return 0;
}

//从缓冲区内获取视频帧
static int read_video_device_stream_frame(v4l2_video* video, int* out_buf_index){

    int ret = 0;
    struct v4l2_buffer buf = { 0 };

    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    
    ret = ioctl(video->fd, VIDIOC_DQBUF, &buf);
    if(ret < 0){
        perror("ioctl call \'VIDIOC_DQBUF\' failed");
        return -1;
    }

    if(buf.index > video->mmap_buf_cout){
        printf("buf overflow[%d]\n", buf.index);
    }

    *out_buf_index = buf.index;

    return 0;
}

static int set_video_device_stream_off(v4l2_video* video){
    int ret = 0;
    enum v4l2_buf_type type;

    //开启视频流
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ret = ioctl(video->fd, VIDIOC_STREAMOFF, &type);
    if(ret < 0){
        perror("ioctl call \'VIDIOC_STREAMOFF\' failed");
        return -1;
    }
    
    return 0;
}

int main(int argc, char* argv[]){

    FILE* fp = NULL;
    int ret = 0;
    int index = 0;
    v4l2_video video = { 0 };
    char buf[15];
    struct v4l2_capability cap = { 0 };
    fd_set fds;
    struct timeval tv;

    if(argc < 2){
        printf("parameter invaild\n");
        return -1;
    }

    //1.先打开设备
    video.fd = open_video_device((const char*)argv[1]);
    if(video.fd < 0){
        return -1;
    }

    //2.查询设备属性
    ret = query_video_device(&video);
    if(ret < 0){
        goto close_video;
    }

    //3.设置video设备输出格式
    ret = set_vedio_device_format(&video);
    if(ret < 0){
        goto close_video;
    }

    //4.申请帧缓存 5.内存映射
    ret = set_video_device_mmap(&video);
    if(ret < 0){
        goto close_video;
    }
    
    //6.帧缓存加入队列 7.开启视频流采集
    ret = set_video_device_streaming_on(&video);
    if(ret < 0){
        goto close_video;
    }

    //获取二十帧数据
    for(int i = 0; i < 2000; i++){
        FD_ZERO(&fds);
        FD_SET(video.fd, &fds);

        tv.tv_sec = 5;
        tv.tv_usec = 0;
        //使用select判断文件描述符是否已准备就绪
        ret = select(video.fd+1, &fds, NULL, NULL, &tv);
        if(ret < 0){
            perror("select error");
            goto exit;
        }else if(ret == 0){
            printf("select timeout\n");
            goto exit;
        }

        //读取一帧数据
        ret = read_video_device_stream_frame(&video, &index);
        if(ret < 0){
            goto exit;
        }

        //将一帧数据保存为图像
        sprintf(buf, "./img%d.jpg", i+1);
        fp = fopen(buf, "wb");
        if(fp == NULL){
            perror("open image file failed");
            goto exit;
        }

        printf("save %s\n", buf);
        fwrite(video.mmap_buf[index].addr, video.mmap_buf[index].size, 1, fp);
        fclose(fp);

        //将缓存加入队列
        set_video_device_stream_queue(&video, index);
        usleep(1000);
    }
    
    return 0;

exit:
    set_video_device_stream_off(&video);
close_video:
    close_video_device(&video);
    return -1;
}
