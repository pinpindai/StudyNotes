# WebRTC整理

[toc]

## WebRTC是什么

### 什么是WebRTC

WebRTC全称Web Real-Time Communication，是一项致力于把实时通信功能引入到浏览器中的技术。



### WebRTC的来源

2010年5月，Google以6829万美元从VoIP软件开发商Global IP Solutions公司购买了GIPS引擎，并于2011年将其开源，同时改名为WebRTC。



### WebRTC的含义

WebRTC在不同的语境下有不同的含义

*   WebRTC是一个标准



*   WebRTC是一个开源项目

    1、Google对WebRTC的实现是完全开源的，其核心代码用C++编写，实现了WebRTC标准里定义的API。WebRTC的代码库里也包含了Android和iOS/macOS平台的SDK封装，分别提供Java和Objective-C接口，便于这些平台的开发者调用，Windows和Linux平台则直接调用WebRTC的C++接口进行开发。

    2、除了Google的WebRTC开源实现，目前也有一些其他的WebRTC开源实现，比如亚马逊[webrtc]( https://github.com/awslabs/amazon-kinesis-video-streams-webrtc-sdk-c )和[Pion WebRTC]( https://github.com/pion/webrtc )(完全用go语言实现WebRTC API)，Google的WebRTC功能最完整，后两个更轻量。

*   WebRTC是一个实时音视频的解决方案



*   ......



虽然WebRTC首先发力于Web端(当时Google的愿景是建立一个互联网浏览器间的实时通信平台)，但是目前RTC各端都在蓬勃发展，尤其是近几年网络基础设施的不断提升和移动通信的快速发展，再叠加新冠疫情的影响，使得RTC技术更加火爆。

目前RTC涉及的各端：

*   Web端
*   Android
*   iOS
*   macOS
*   Windows
*   Linux
*   IoT(Internet of Thing)
*   AR/VR

>   注：
>
>   Native APP的效率比H5高
>
>   Native更方便对WebRTC进行更深层次的定制优化以及二次开发



### WebRTC的发展前景

#### 目前各浏览器厂商对WebRTC的支持情况



#### WebRTC在国内的发展情况



## WebRTC技术栈

WebRTC本身比较庞大，涉及很多技术

首先从整体上浏览一下WebRTC涉及技术







## WebRTC基本流程分析

### 基本流程：

*   创建PC Factory，创建PC
*   创建Capture、Source、Track、Transceiver
*   创建Offer、Answer，并相互交换
*   相互交换ICE Candidate



### 重要概念

*   Capture

    负责数据采集，只有视频才有这一层抽象，它有多种实现，包括相机采集(Android 还有Camera1/Camera2两套)、录屏采集、视频文件采集等

*   Source

    数据源，数据来自于capture，它把数据交给track

*   Track

    媒体数据交换的载体，发送端把本地的track发送给远程的接收端

*   Sink

    track数据的消费者，只有视频才有这一层封装。发送端本地视频的预览、接收端收到远程视频后的渲染都是Sink

*   Transceiver

    负责收发媒体数据

以视频为例，数据由发送端的capture进行采集，交给source，在交给本地的track，然后兵分两路，一路由本地sink进行预览，一路由Transceiver发送给接收端。接收端再收到Track后，将数据交给sink进行渲染。

Capture的创建和销毁由app层负责，只需要将其和source关联起来即可。

创建Source需要调用PC Factory的接口

创建Track也需要调用PC Factory的接口，并提供Source作为参数

Sink的创建和销毁也由app层负责，只需要把它添加到Track里即可

创建Transceiver需要调用PC的接口（在AddTrack时，内部会创建Transceiver）



### 核心API分析

*   全局初始化：

主要工作：加载动态库、设置实验性功能开关、初始化ssl、启用trace、设置日志输出等

Android端的初始化工作位于**PeerConnectionClient.java**文件中，SDK对初始化过程进行了封装，可以通过PeerConnectionFactory.InitializationOptions对象的各个字段控制初始化的过程。

*   PeerConnectionFactory

在全局初始化之后，使用PC之前，还需要先创建和初始化PeerConnectionFactory对象，因为PC的创建使用了工厂模式。

PeerConnectionFactory对象在**PeerConnectionClient.java**文件**createPeerConnectionFactoryInternal**方法中创建。

在创建PeerConnectionFactory对象之前，会根据设置决定创建硬编解码器还是软编解码的Factory。

*   PeerConnection

**PeerConnection**是WebRTC的核心类，简称PC

**createPeerConnection**会调用**createMediaConstraintsInternal**、**createPeerConnectionInternal**、**maybeCreateAndStartRtcEventLog**等函数，其中**createMediaConstraintsInternal**会对音视频约束参数进行处理。

PC对象是在**PeerConnectionClient.java**文件**createPeerConnectionInternal**方法中创建的，这个函数是在客户端拿到加入房间、建立通话所需要的的信息后被调用的。

在创建PeerConnection前，根据需要设置**RTCConfiguration**，比如是否使用tcp candidate、是否持续收集candidate、是否开启dtls、使用哪种类型的SDP等

在创建PeerConnection完成后，根据需要创建DataChannel，并设置DataChannel的相关参数

*   创建Source、Track

创建PC的目的是为了收发音视频数据，收发的载体就是Track，Track的数据来自Source。

Android端创建Source和Track的代码位于**PeerConnectionClient.java**文件**createPeerConnectionInternal**，创建完PC后会被立刻执行。

音频Source和Track的创建，是在**createAudioTrack**函数中，最终调用PC Factory的接口创建Source和Track，然后把Track添加到PC中。

视频Source和Track的创建，是在**createVideoTrack**函数中，最终调用PC Factory的接口创建Source和Track，然后把Track添加到PC中。

Android的Camera API有两套，虽然Camera1已经不建议再使用，但其仍然被广泛使用。

*   创建Offer

添加完Track之后，就明确了需要发送哪些数据，这个时候就可以开始SDP的协商过程了。

Android端创建Offer的代码在PeerConnectionClient.java的**createOffer**函数中，在创建完PC，添加Track后，就会被调用(在CallActivity.java中调用)。

是否接收音频/视频以及是否开启音频处理等是在**createMediaConstraintsInternal**函数中处理的。

创建Offer成功后，在SDPObserver的回调函数**onCreateSuccess**中，将SDP设置到PC中，在设置之前，可以通过**preferCodec**，调整SDP编解码器的顺序，将期望使用的编解码器放到前面。在PC中设置好本地SDP之后，会回调上层onSetSuccess，然后再CallActivity.java的onLocalDescription函数中，将本地SDP发送给信令服务器。

*   创建Answer

应答端收到offer后，先将其设置给PC对象，然后创建Answer并设置给PC对象，最后将Answer通过信令服务器发送给发起端。

创建Answer和创建Offer过程类似。

*   ICE Candidate回调和设置

通话双方交换并设置了SDP之后，下一步就是进行网络协商了，即交换ICE Candadate，然后建立P2P连接

Android端收到本地ICE  Candidate的回调函数是PC Observer类的onICECandidate函数。设置完本地SDP会启动ICE Candidate的收集过程，收集到Candidate之后，就会回调该函数。它会进一步回调CallActivity.java的onIceCandidate函数，并把ICE Candidate发送给对端。

对端收到ICE Candidate之后，会在**PeerConnectionClient.java**文件的addRemoteIceCandidate函数里添加给PC对象。

由于收到信令消息和本地创建PC对象是无法保证先后顺序的，因此在android demo层引入了一个消息队列，防止消息丢失。

*   ICE连接状态回调

交换了SDP之后，两端就开始尝试建立P2P连接了。对于这个过程的状态变化，我们可以监听PC的ICE连接状态回调--onIceConnectionChange(IceConnectionState newState)

常用的连接状态：

kIceConnectionConnected：ICE连接建立成功的状态，这种状态下就可以收发音视频数据了。

kIceConnectionDisconnected：ICE连接断开后的状态

kIceConnectionFailed：ICE连接建立失败的状态



## 媒体协商-SDP详解

### 什么是SDP

SDP(Session Description Protocal)，用来协商会话能力的协议



### 为什么需要媒体协商

因为参与会话的各个成员能力不对等



SDP协商不一致怎么办？



### 标准SDP



### WebRTC SDP

WebRTC SDP总体上可以分成以下几个部分：

*   session metadata

    描述整个会话的基本信息

    行开头为v=、o=、s=、t=等

*   network description

    描述网络传输的信息

    行开头为c=、a=candidate等

*   stream description

    描述媒体数据流的信息

    行开头为m=、a=rtpmap、a=fmtp、a=sendrecv等

*   security description

    描述数据加密、身份认证相关信息

    行开头为a=crypto、a=ice-frag、a=ice-pwd、a=fingerprint等

*   Qos, grouping description

    描述服务质量、传输层复用相关信息

    行开头为a=rtcp-fb、a=group、a=rtcpmux等



### Plan B vs Unified Plan

主要区别：传输多路同类型媒体流时，SDP的格式不同。（多路同类型媒体流的例子：相机+录屏、多个相机(视角)）

Plan B的SDP里同类型的媒体流只有一个m行，同类型的媒体流通过msid区分；Unified Plan是每个媒体流都有一个m line(因此，如果有两路视频，就会有两个video m line)。

现在WebRTC新版本都使用Unified Plan，Plan B已经被废弃。但需要注意，有些老版本还在使用Plan B，有时需要考虑和老版本的兼容问题。



Transceiver

WebRTC有三种media: video audio  application，mid依次是0、1、2。Transceiver表示的是收发相同mid的receiver和sender的组合体。direction字段的取值和Offer/Answer里的media section的方向是一致的，包括SendRecv、kSendOnly、kRecvOnly和KInactive。



### 操纵SDP

可以根据需要，对SDP进行修改，比如调整编解码的顺序(将最想使用的编解码格式放最前面)、修改编码格式的参数(fmtp行)、也可以删掉某些编解码格式

修改SDP的时机：**在创建完成或收到对方的SDP之后、设置给PC之前**。





## 网络协商-ICE详解

### ICE

什么是ICE

ICE是一个框架

ICE的主要功能：利用STUN、TURN等协议，完成节点之间的打洞任务



为什么需要网络协商



### STUN

什么是STUN

STUN的主要功能：

*   提供获取一个内网连接（IP+Port）对应的公网连接映射关系（NAT Binding）的机制
*   提供NAT Binding保活机制



### TURN

什么是TURN

TURN协议是STUN协议的扩展，允许一个peer只使用relay address就可以和多个peer实现通信。

节点之间穿透失败，无法建立P2P连接时，就要借助TURN服务器进行数据转发。



由于TURN是STUN协议的扩展，因此TURN也支持STUN协议的功能，因此TURN服务器和STUN服务器使用同一个服务器，都使用coturn开源实现。



### ICE Candidate

什么是ICE Candidate



Candidate的类型

*   host

    客户端从本机网络接口上获取到的地址

*   srflx(server reflexive)

    STUN Server看到的该客户端的地址，一般为外网(ip+port)

*   relayed

    TURN Server为该客户端分配的中继地址

*   prflx(peer reflexive)

    连通性测试过程中，在来自对方的数据报文里看到的地址



ICE连通性测试：

对组成的candidate对，按照顺序，逐个进行尝试





## 视频数据流程

### 视频数据流程概览

//todo  流程图

视频数据由VideoCapture采集后，交给VIdeoSource，VideoSource通过其VideoBroadcaster成员，把数据分发给每个VideoSink（VideoEncoder和LocalPreview）。VideoEncoder把视频数据编码后交给网络层进行发送，LocalPreview把视频数据渲染到屏幕上。

从网络层收到数据后，先交给VideoDecoder进行解码，解码之后交给VideoBroadcaster，最后由VideoBroadcaster分发给每个VideoSink(RemoteRenderer)。RemoteRenderer把视频数据渲染到屏幕上。

VideoSource是VideoTrack的成员，VideoTrack对外提供添加VideoSink的接口，实际上Sink都是添加到Source的VideoBroadcaster里的。值得注意的是，VideoBroadcaster分发的数据都是未压缩数据，即编码前或者解码后的视频数据。

### 视频采集

视频采集都是通过各个平台系统提供的API，因此视频采集的实现都各不相同。

WebRTC Android视频采集的接口定义为VideoCapture，其中定义了初始化、启停、销毁等操作，以及接收启停、数据的回调。

相机采集的实现是CameraCapture，由于Android相机采集有两套API，所以CameraCapture有Camera1Capture和Camera2Capture。虽然Camera1 API以及被弃用很久了，但是实际上大多数情况下，使用的还是Camera1 API。

ScreenCaptureAndroid类也实现了VideoCapture接口，用于实现屏幕录制。

WebRTC Android的相机采集主要涉及Enumerator、Capture、Session、SurfaceTextureHelper和VideoFrame。其中，Enumerator创建Capture，Capture创建Session，对相机的操作逻辑主要在Session类里，因此两套Camera API的调用分别集中在Camera1Session和Camera2Session里。SurfaceTextureHelper实现用SurfaceTexture接收数据，VideoFrame实现对视频数据的封装。

*   Enumerator

    主要是获取设备列表、检查朝向、创建Capture

*   Capture

    Capture主要进行状态维护和错误处理，开启相机、预览代码等具体操作都封装在了session里。

*   Session

    开启相机、开启预览、设置事件回调的代码都在创建session的工厂方法Camera1Session.create和Camera2Session.create中。

    停止相机和预览在stop接口中处理。

*   SurfaceTextureHelper

    SurfaceTextureHelper负责创建SurfaceTexture，接收SurfaceTexture数据，并且也负责相机操作所在的线程管理。

*   VideoFrame

    VideoFrame是WebRTC Android对视频数据的封装，包含实际的视频数据、视频的宽高、方向(旋转角度)、时间戳等信息。

    VideoFrame内部使用VideoFrame.Buffer表示实际的视频数据。VideoFrame.Buffer有多种实现，包括TextureBufferImpl、NV12Buffer、NV21Buffer和JavaI420Buffer等，分别用来表示OES texture数据、NV12格式的YUV数据、NV21格式的YUV数据和I420格式的YUV数据。

### 视频渲染

本地视频数据采集到之后，被封装为VideoFrame对象，并在本地进行预览，以及送入视频编码模块，用于编码发送。此外，从其他客户端收到的视频数据(远端视频)经过解码后，也将得到VideoFrame对象，并在本地进行渲染。

视频渲染也是调用平台相关的API实现

WebRTC Android将本地视频和远端视频按照同样的方式进行渲染：调用OpenGL ES API进行逐帧渲染。

本地视频的数据格式和远端视频的数据格式可能稍有差别，本地视频可能是OES texture的格式或YUV的格式，而远端视频则一律是YUV的格式。

WebRTC Android的渲染实现类为SurfaceViewRenderer。

SurfaceViewRenderer实现了VideoSink接口，VideoSink定义了onFrame，每次需要有新的帧需要渲染时，就会被调用。

WebRTC Android在EglRender里实现了对OpenGL上下文和渲染循环。

### 视频编解码

WebRTC目前支持VP8/VP9/H.264三种编解码方式。

通常情况下，压缩效率越高，计算复杂度越大，性能开销(编码耗时)越长，这个差异在分辨率越大时越明显。

再考虑使用哪种编码时，不仅要考虑压缩效率，还要考虑平台兼容性以及功能特性。比如iOS/macOS平台只支持H.264的硬件编解码。Safari浏览器也只支持H.264的视频编解码。

### Android 视频编码



### Android视频解码







## 音频数据流程





## 数据传输-RTP详解





## DataChannel详解





## 多人音视频通话

P2P/Mesh模式的特点：

优点：可以减少服务器和网络带宽的成本

缺点：客户端之间的连接质量难以保证(连接成功率、音视频通话质量)

SFU/MCU服务器模式特点：

优点：服务端网络质量很稳定，能有效提高音视频通话质量

缺点：成本高





## 信令





## WebRTC服务端实现

WebRTC服务端有很多开源或商用的实现

*   AppRTC
*   Janus
*   Jitsi
*   Kurento
*   Licode
*   mediasoup
*   Medooze
*   OWT