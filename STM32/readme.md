# 茄子采摘机器人系统

本系统描述了一个小车机器人与机械臂配合完成茄子采摘的过程。系统通过STM32与nezha的串口通信，实现了小车、机械臂和摄像头的协调工作，并通过PID控制算法和实时图像检测实现了茄子的定位和采摘。

## 系统工作流程

1. **启动**
   - STM32与nezha通过串口连接，等待连接成功。
   - STM32发送启动标志位（flag=1）给nezha，nezha打开YOLO检测。
   - 小车等待机械臂处于检测状态后启动。

2. **循迹**
   - STM32控制小车沿着黑线（黑胶带）运动，采用PID控制算法进行运动。

3. **检测茄子**
   - nezha摄像头实时检测图像，发现茄子柄后发送检测标志位（flag=4）给STM32，并发送茄子柄横向距中线的差值给STM32。

4. **寻中线**
   - STM32接收到检测标志位后停止循迹运动，改为寻中线运动（PID算法），同时接收差值数据，控制小车前后运动，直到茄子柄在阈值内。
   - nezha发送Z值标志位（flag=5）给STM32。

5. **Z坐标对正**
   - STM32接收到Z值标志位后，nezha发送茄子柄在Z轴方向上距中线的差值给STM32。
   - STM32控制机械臂末端Z轴运动，直到茄子柄中点在阈值内。
   - nezha发送结束标志位（flag=6），并停止YOLO识别。

6. **茄子距离判定**
   - STM32接收到结束标志位后，开启激光测距检测，控制机械臂在X轴方向运动，直到检测到茄子的距离小于指定值。

7. **剪切**
   - STM32控制最后的舵机进行剪切动作，并置放置标志位（flag=8）。

8. **放置**
   - STM32控制机械臂进行抬高处理，然后旋转机械臂到篮子前，旋转第四轴关节，松开最后的舵机使茄子斜倒下。
   - 抬高处理后，使机械臂返回检测状态，然后发送启动标志位给nezha（flag=2）。

9. **“循环”启动**
   - nezha检测到启动标志位后，开启YOLO检测。
   - STM32检测到启动标志位后，继续循迹运动，重复整个采摘过程。

## 技术实现

- **通信**：STM32与nezha通过串口进行通信。
- **控制算法**：使用PID控制算法实现小车和机械臂的精确运动。
- **图像检测**：nezha使用YOLO算法进行实时图像检测，识别茄子柄的位置。

该系统通过多种技术的结合，实现了自动化的茄子采摘过程，提升了农业生产的效率。