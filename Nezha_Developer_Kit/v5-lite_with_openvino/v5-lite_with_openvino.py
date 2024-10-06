import cv2
import numpy as np
import onnxruntime as ort
import time
import random
import serial
import tkinter as tk
# from gui import GUI  # 导入GUI类
from gui import GUI
import socket
import atexit
from openvino.inference_engine import IECore

han_flag = 0
egg_flag = 0  # 记录每张茄子和柄的数量
first_flag = 0
flag = 0
dif = 30
err = -102
last_flag = 0
# 输入茄子的差 与 茄子柄的差发送给stm32
"""
如果不茄子在x范围内
发送deta——x值给stm32，让小车移动
当茄子在x范围内
发送data——y值给stm32，控制机械臂z轴坐标，使茄子柄在y值内
"""


def send_data(data):
    # ser.open()
    ser.write(data.encode())  #
    time.sleep(0.5)
    # ser.close()


def send_data_to_server(data):
    try:
        client.send(data.encode())  # 发送接收到的数据给服务器
    except Exception as e:
        print("发送数据到服务器出错: %s", e)


def rx_stm():
    global flag
    global angle
    global xyz
    global egg_num
    global bertt
    if ser.in_waiting > 0:
        # print(12)
        received_data = ser.readline().decode().strip()
        # print(13)
        # print(f'Received data: {received_data}\n')
        send_data_to_server(received_data)
        if received_data == "arm init all right":
            time.sleep(1)
            ser.close()
            ser.open()
            # print("serial reset!\n")
        if "flag=" in received_data:
            flag = int(received_data[received_data.index("=") + 1])
            print("flag = {}".format(flag))
        if "angle:" and "xyz:" in received_data:  # angle:123,456,789,123;xyz:123,456,789
            angle[0] = int(received_data[6:9])
            angle[1] = int(received_data[10:13])
            angle[2] = int(received_data[14:17])
            angle[3] = int(received_data[18:21])
            xyz[0] = int(received_data[26:29])
            xyz[1] = int(received_data[30:33])
            xyz[2] = int(received_data[34:37])
            #gui.update_data(angle, xyz, egg_num, bertt)
        # if "Trace mode" in received_data:
        #     flag=3


def stm_uart(x, y):
    strx = 'x:%d' % x
    stry = 'y:%d' % y
    if x > 15:  # 在x值内
        send_data('a:+05')
        print('x>10/n')
        time.sleep(0.5)
    elif x < -15:
        send_data('d:-05')
        print('x<-10/n')
        time.sleep(0.3)
    else:  # 不在x值内
        if y > 15:
            send_data('z:+05')
            time.sleep(1)
            print('y>10')
            # print(stry)
        elif y < -15:
            send_data('z:-05')
            time.sleep(1)
            print('y<-10')


def stm_smp(dx, dy):  # 树莓派与stm32通信函数
    global first_flag
    global flag
    global egg_num
    if not first_flag and flag == 2:
        print("flag =======  44")
        #gui.update_status(1)
        first_flag = 1
        time.sleep(0.2)
        send_data("flag=4\r\n")
        rx_stm()
        while flag != 4:
            # ser.close()
            # time.sleep(0.2)
            # ser.open()
            # time.sleep(0.2)
            send_data("flag=4\r\n")
            print("flag=4")
            rx_stm()

        # for i in range(3):
        #     send_data("flag=4")  # 第一次发现茄子，发送“flag=4”给stm32，小车开启寻中线模式
        #     time.sleep(0.5)
        flag = 4
    if flag == 4:
        print("flag==========4")
        if (dif >= dx >= -dif) and (dif >= dy >= -dif):
            # time.sleep(1)
            send_data("flag=6\r\n")
            print("egg in area")
            # rx_stm()
            # while flag != 6:
            #     send_data("flag=6")
            #     rx_stm()
            #gui.update_status(0)
            egg_num += 1
            send_data_to_server(f"eggnum {egg_num}")
            flag = 6
            first_flag = 0
            time.sleep(0.1)
        else:
            send_data("{:04d}:::{:04d}\r\n".format(-dx, dy))
            print("{:04d},{:04d}".format(-dx, dy))


def plot_one_box(x, img, color=None, label=None, line_thickness=None):
    global egg_flag
    global han_flag
    global first_flag
    tl = (
            line_thickness or round(0.002 * (img.shape[0] + img.shape[1]) / 2) + 1
    )  # line/font thickness
    color = color or [random.randint(0, 255) for _ in range(3)]
    c1, c2 = (int(x[0]), int(x[1])), (int(x[2]), int(x[3]))
    _mid = (int((x[2] + x[0]) / 2), int((x[1] + x[3]) / 2))
    y = img.shape[0]  # img的分辨率x，y
    x = img.shape[1]
    deta_x = (x // 2) - _mid[0]
    deta_y = ((y // 2) - _mid[1]) - err
    # 画中心dif方框
    cv2.rectangle(img, ((x // 2) - dif, (y // 2) - dif - err), ((x // 2) + dif, (y // 2) + dif - err), (0, 0, 0))
    if 'egg' in label:
        cv2.line(img, (x // 2, (y // 2) - err), _mid, (255, 255, 255))
        han_flag = han_flag + 1
        cv2.rectangle(img, c1, c2, color, thickness=tl, lineType=cv2.LINE_AA)
        stm_smp(deta_x, deta_y)  # stm32与树莓派交互函数



def _make_grid(nx, ny):
    xv, yv = np.meshgrid(np.arange(ny), np.arange(nx))
    return np.stack((xv, yv), 2).reshape((-1, 2)).astype(np.float32)


def cal_outputs(outs, nl, na, model_w, model_h, anchor_grid, stride):
    row_ind = 0
    grid = [np.zeros(1)] * nl
    for i in range(nl):
        h, w = int(model_w / stride[i]), int(model_h / stride[i])
        length = int(na * h * w)
        if grid[i].shape[2:4] != (h, w):
            grid[i] = _make_grid(w, h)

        outs[row_ind:row_ind + length, 0:2] = (outs[row_ind:row_ind + length, 0:2] * 2. - 0.5 + np.tile(
            grid[i], (na, 1))) * int(stride[i])
        outs[row_ind:row_ind + length, 2:4] = (outs[row_ind:row_ind + length, 2:4] * 2) ** 2 * np.repeat(
            anchor_grid[i], h * w, axis=0)
        row_ind += length
    return outs


def post_process_opencv(outputs, model_h, model_w, img_h, img_w, thred_nms, thred_cond):
    conf = outputs[:, 4].tolist()
    c_x = outputs[:, 0] / model_w * img_w
    c_y = outputs[:, 1] / model_h * img_h
    w = outputs[:, 2] / model_w * img_w
    h = outputs[:, 3] / model_h * img_h
    p_cls = outputs[:, 5:]
    if len(p_cls.shape) == 1:
        p_cls = np.expand_dims(p_cls, 1)
    cls_id = np.argmax(p_cls, axis=1)

    p_x1 = np.expand_dims(c_x - w / 2, -1)
    p_y1 = np.expand_dims(c_y - h / 2, -1)
    p_x2 = np.expand_dims(c_x + w / 2, -1)
    p_y2 = np.expand_dims(c_y + h / 2, -1)
    areas = np.concatenate((p_x1, p_y1, p_x2, p_y2), axis=-1)

    areas = areas.tolist()
    ids = cv2.dnn.NMSBoxes(areas, conf, thred_cond, thred_nms)
    if len(ids) > 0:
        return np.array(areas)[ids], np.array(conf)[ids], cls_id[ids]
    else:
        return [], [], []


# def infer_img(img0, net, model_h, model_w, nl, na, stride, anchor_grid, thred_nms=0.4, thred_cond=0.5):
#     # 图像预处理
#     img = cv2.resize(img0, [model_w, model_h], interpolation=cv2.INTER_AREA)
#     img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
#     img = img.astype(np.float32) / 255.0
#     blob = np.expand_dims(np.transpose(img, (2, 0, 1)), axis=0)
#
#     # 模型推理
#     outs = net.run(None, {net.get_inputs()[0].name: blob})[0].squeeze(axis=0)
#
#     # 输出坐标矫正
#     outs = cal_outputs(outs, nl, na, model_w, model_h, anchor_grid, stride)
#
#     # 检测框计算
#     img_h, img_w, _ = np.shape(img0)
#     boxes, confs, ids = post_process_opencv(outs, model_h, model_w, img_h, img_w, thred_nms, thred_cond)
#
#     return boxes, confs, ids

#  使用openvino进行图像推理
def infer_img(img0, exec_net, input_blob, output_blob, model_h, model_w, nl, na, stride, anchor_grid, thred_nms=0.4, thred_cond=0.5):
    img = cv2.resize(img0, (model_w, model_h))
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    img = img.astype(np.float32) / 255.0
    img = img.transpose((2, 0, 1))  # Change data layout from HWC to CHW
    res = exec_net.infer({input_blob: img})
    outs = res[output_blob].reshape(6300, 7)  # 保持检测结果的结构
    outs = cal_outputs(outs, nl, na, model_w, model_h, anchor_grid, stride)
    img_h, img_w, _ = img0.shape
    boxes, confs, ids = post_process_opencv(outs, model_h, model_w, img_h, img_w, thred_nms, thred_cond)
    return boxes, confs, ids

# gui字典
angle = [0, 135, 0, 135]
xyz = [0, 0, 0]
egg_num = 0
bertt = 100
server_ip = '192.168.1.155'
server_port = 8888
qt = 0

model_xml = 'models/1001_train.xml'
model_bin = 'models/1001_train.bin'

if __name__ == "__main__":
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.settimeout(120)
    try:
        client.connect((server_ip, server_port))
        client.send(b'dev')  # 告诉服务端自己的身份
    except Exception as e:
        print("设备端连接出错: %s", e)
    # 模型加载
    model_pb_path = "models/1001_train.onnx"
    so = ort.SessionOptions()
    # net = ort.InferenceSession(model_pb_path, so)
    # 串口初始化
    ser = serial.Serial('COM7', baudrate=115200, stopbits=serial.STOPBITS_ONE, bytesize=8, parity=serial.PARITY_NONE)
    ser.setDTR(False)
    ser.setRTS(False)
    print("serial successful!")
    send_data("1234")
    # 标签字典
    dic_labels = {0: 'egg', 1: 'han'}

    # 模型参数
    model_h = 320
    model_w = 320
    nl = 3
    na = 3
    stride = [8., 16., 32.]
    anchors = [[10, 13, 16, 30, 33, 23], [30, 61, 62, 45, 59, 119], [116, 90, 156, 198, 373, 326]]
    anchor_grid = np.asarray(anchors, dtype=np.float32).reshape(nl, -1, 2)

    # openvino
    ie = IECore()
    net = ie.read_network(model=model_xml, weights=model_bin)
    exec_net = ie.load_network(network=net, device_name="CPU")

    input_blob = next(iter(net.input_info))
    output_blob = next(iter(net.outputs))
    _, _, model_h, model_w = net.input_info[input_blob].input_data.shape


    # 保存视频配置
    # videowritepath = "video.avi"
    # fourcc = cv2.VideoWriter_fourcc(*'XVID')
    # videowirte = cv2.VideoWriter(videowritepath, fourcc, 20.0, (640, 480), True)
    video = 0  # 'D:/桌面/yolov素材/8.mp4'
    cap = cv2.VideoCapture(video)
    success, img0 = cap.read()
    #root = tk.Tk()
    #gui = GUI(root)
    #gui.update_data(angle, xyz, egg_num, bertt)
    # root.mainloop()
    client.setblocking(False)
    while True:
        rx_stm()
        try:
            data = client.recv(1024).decode()
            # print("data:"+str(data))
            if data:
                if "@" in data:  # 停止
                    qt = 0
                    send_data("qt=0\r\n")
                    # last_flag = flag
                    # flag = 9
                elif "#" in data:  # 启动
                    send_data("qt=1\r\n")
                    qt = 1
                    if flag == 3 or flag == 2:
                        send_data("flag=2\r\n")
                    # flag = last_flag
                print("flag:" + str(flag) + " data " + str(data))
        except socket.error:
            pass
        if flag == 1:
            # flag=2
            ser.close()
            ser.open()
            time.sleep(0.2)
            send_data("flag=2\r\n")  # 当接收到flag=1后，发送指令使STM32启动，并同时开启识别
            send_data("flag=3\r\n")
            rx_stm()
            print("tx_flag2")

        # 以下为工作模式 在指定flag下运行
        if flag == 3:
            flag = 2
            time.sleep(2)
        if flag == 6:
            time.sleep(1)
            send_data("flag=6\r\n")
        success, img0 = cap.read()
        t1 = time.time()
        if qt:
            # if flag == 2 or flag == 4 or flag == 5:
             if 1 :
                if success:
                    # t1 = time.time()
                    # det_boxes, scores, ids = infer_img(img0, net, model_h, model_w, nl, na, stride, anchor_grid,
                    #                                    thred_nms=0.4, thred_cond=0.5)
                    det_boxes, scores, ids = infer_img(img0, exec_net, input_blob, output_blob, model_h, model_w, nl, na,
                                                  stride, anchor_grid)
                    for box, score, id in zip(det_boxes, scores, ids):
                        label = '%s:%.2f' % (dic_labels[id], score)
                        plot_one_box(box.astype(np.int16), img0, color=(255, 0, 0), label=label, line_thickness=None)
                    egg_flag = 0
                    han_flag = 0
                    t2 = time.time()
                    # cv2.namedWindow("video", 0)
                    # cv2.resizeWindow("video", 640, 480)
                    str_FPS = "FPS: %.2f" % (1. / (t2 - t1))
                    cv2.putText(img0, str_FPS, (50, 50), cv2.FONT_HERSHEY_COMPLEX, 1, (0, 255, 0), 3)
                    # cv2.imshow("video", img0)

                cv2.waitKey(10)
                if cv2.waitKey(10) & 0xFF == 27:  # 按第27键退出窗口
                    break
        # else:
        #     cv2.destroyAllWindows()

        #gui.update_image(img0)
        # root.update()
        # videowirte.write(img0)
    #gui.on_close()
    cap.release()
    atexit.register(client.close)
