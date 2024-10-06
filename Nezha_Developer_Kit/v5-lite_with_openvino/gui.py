import tkinter as tk
from PIL import Image, ImageTk
import cv2

class GUI:
    def __init__(self, master):
        self.master = master
        master.title("机械臂控制界面")
        master.geometry("880x500")  # 设置窗口大小为840x500像素
        master.configure(bg="orange")  # 设置窗口背景色为橙色

        # 创建一个Frame作为左侧面板，用于显示角度、末端位置、茄子数量和电池电量
        self.left_panel = tk.Frame(master, bg="light blue")
        self.left_panel.grid(row=0, column=0, padx=10, pady=10, sticky="nsew")

        # 创建标签显示四个角度
        self.angle_labels = []
        for i in range(4):  # 仅创建4个角度标签
            label = tk.Label(self.left_panel, text="Angle {}: ".format(i+1), padx=5, pady=5, bg="light blue", font=("Helvetica", 12))
            label.pack(anchor="w", pady=(5, 10))  # 增加行距
            self.angle_labels.append(label)

        # 创建标签显示末端位置
        self.xyz_label = tk.Label(self.left_panel, text="End Effector XYZ: ", padx=5, pady=5, bg="light blue", font=("Helvetica", 12))
        self.xyz_label.pack(anchor="w", pady=(20, 10))  # 增加行距

        # 创建标签显示收获茄子数量
        self.eggplant_label = tk.Label(self.left_panel, text="收获茄子数量: ", padx=5, pady=5, bg="light blue", font=("Helvetica", 12))
        self.eggplant_label.pack(anchor="w", pady=(10, 10))  # 增加行距

        # 创建标签显示电池电量
        self.battery_label = tk.Label(self.left_panel, text="当前电池电量: ", padx=5, pady=5, bg="light blue", font=("Helvetica", 12))
        self.battery_label.pack(anchor="w", pady=(10, 10))  # 增加行距

        # 创建一个容器用于显示状态框
        self.status_canvas = tk.Canvas(self.left_panel, width=200, height=50, highlightthickness=0, bg="light blue")
        self.status_canvas.pack(anchor="w", pady=(10, 10))  # 增加行距

        # 创建状态框文本
        self.status_box = tk.Label(self.status_canvas, text="Status: 无茄子", padx=5, pady=5, bg="gray", font=("Helvetica", 12))
        self.status_box.pack()

        # 创建一个容器用于显示OpenCV图像
        self.cv_frame = tk.Frame(master)
        self.cv_frame.grid(row=0, column=1, rowspan=7, columnspan=2, padx=10, pady=10, sticky="nsew")  # 使用sticky参数使容器填充整个空间

        # 创建用于显示图像的标签，设置大小为640x480像素
        self.image_label = tk.Label(self.cv_frame, width=640, height=480, bg="black")
        self.image_label.pack(fill="both", expand=True)

        # 创建一个空函数用于接收视频帧参数
        self.update_func = lambda frame: None

        # 在显示图像的标签外围加橙色方框
        self.cv_frame.config(bg="orange", highlightbackground="orange", highlightthickness=5)

    def update_data(self, angles, xyz, eggplant_count, battery_level):
        # 更新角度标签文本
        for i, angle in enumerate(angles):
            self.angle_labels[i].config(text="Angle {}: {:.2f}°".format(i+1, angle))

        # 更新末端位置标签文本
        self.xyz_label.config(text="End Effector XYZ: ({}, {}, {})".format(*xyz))

        # 更新收获茄子数量标签文本
        self.eggplant_label.config(text="收获茄子数量: {}".format(eggplant_count))

        # 更新电池电量标签文本
        self.battery_label.config(text="当前电池电量: {}%".format(battery_level))

    def update_image(self, frame):
        # 将传入的视频帧转换为灰度图像
        gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # 将灰度图像转换为PIL格式
        pil_image = Image.fromarray(gray_frame)
        tk_image = ImageTk.PhotoImage(image=pil_image)

        # 在标签中显示图像
        self.image_label.config(image=tk_image)
        self.image_label.image = tk_image  # 保持对图像对象的引用，防止被垃圾回收

    def update_status(self, has_egg):
        # 更新状态框文本和背景颜色
        if has_egg:
            self.status_box.config(text="Status: 有茄子", bg="green")
        else:
            self.status_box.config(text="Status: 无茄子", bg="gray")

    def on_close(self):
        # 关闭窗口
        self.master.destroy()
