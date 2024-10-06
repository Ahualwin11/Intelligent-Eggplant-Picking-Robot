import socket
import threading
import logging
import time

from datetime import datetime

tcp_port = 8888
client_num = 5
app_list = []
dev_list = []

temperature_array = []
array_size = 10
counter = 0
send_sensor_data = False
eggNum = 0
light_val = 15
temperature = 6.0
humidity = 0.0

logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')


def app_handle(app_client, data):
    try:
        logging.info("处理APP数据: %s", data)
        app_client.send((data + "\n").encode())
    except Exception as e:
        logging.error("处理APP数据失败：%s", e)
        app_handle(app_client, data)  # 重试操作

    logging.info("处理APP数据: %s", data)
    app_client.send((data + "\n").encode())  # 返回确认消息给APP端

    # data = data.encode()
    print(str(type(data)))
    if str(data) == "t" or str(data) == "r":
        print(str(type(data)))
        for dev in dev_list:
            if str(data) == "t":
                dev.send(("@" + "\r\n").encode())
            if str(data) == "r":
                dev.send(("#" + "\r\n").encode())
        logging.info("转发设备数据给dev")


def dev_handle(dev_client, data):
    logging.info("处理设备数据: %s", data)
    data = data.encode()
    for app in app_list:
        app.send(data)
    logging.info("转发设备数据给APP")


def send_sensor_data_periodically(tcp_client):
    global send_sensor_data, eggNum, light_val, temperature, humidity
    while True:
        if send_sensor_data:
          #  eggNum+=1
            sensor_data = f"{temperature}-{humidity}-{light_val}-{eggNum}"

            # current_time = datetime.strptime(datetime.now().strftime('%Y-%m-%d %H:%M:%S'), '%Y-%m-%d %H:%M:%S')
            # if 6 <= current_time.hour <= 18:  # 白天时间
            #     if temperature < 20:
            #         app_handle(tcp_client, f"daytemplow {temperature}")
            #     elif temperature > 30:
            #         app_handle(tcp_client, f"daytemphigh {temperature}")
            # else:  # 夜晚时间
            #     if temperature < 15:
            #         app_handle(tcp_client, f"nighttemplow {temperature}")
            #     elif temperature > 25:
            #         app_handle(tcp_client, f"nighttemphigh {temperature}")
            # if temperature < 10:
            #     app_handle(tcp_client, f"temptoolow {temperature}")
            # # app_handle(tcp_client, f"Sensor {sensor_data}", cursor, db)
            # if humidity > 2500:
            #     app_handle(tcp_client, f"humidityhigh {humidity}")
            # elif humidity < 1200:
            #     app_handle(tcp_client, f"humiditylow {humidity}")

            app_handle(tcp_client, f"Sensor {sensor_data}")
            time.sleep(1)  # 每秒发送一次数据


def message_handle(tcp_client, tcp_client_ip):
    global send_sensor_data, eggNum, light_val, temperature, humidity
    client_type = ""
    while True:
        try:
            recv_data = tcp_client.recv(4096)
            if recv_data:
                recv_data = recv_data.decode()
                if recv_data == "dev":
                    dev_list.append(tcp_client)
                    client_type = "dev"
                    logging.info("%s 客户端为设备", tcp_client_ip)
                    logging.info("设备：%s", dev_list)
                elif recv_data == "app":
                    app_list.append(tcp_client)
                    client_type = "app"
                    logging.info("%s 客户端为APP", tcp_client_ip)
                    logging.info("app：%s", app_list)
                    send_sensor_data = True
                    threading.Thread(target=send_sensor_data_periodically, args=(tcp_client,)).start()
                    logging.info("开始转发数据给app")
                elif "Light:" in recv_data and "Temperature:" in recv_data and "Humidity:" in recv_data:
                    light_val = int(recv_data.split("Light:")[1].split()[0])
                    temperature = round(float(recv_data.split("Temperature:")[1].split()[0]), 1)
                    humidity = float(recv_data.split("Humidity:")[1].split()[0])
                elif recv_data.startswith("eggnum"):
                    eggNum = int(recv_data.split()[1])
                else:
                    if client_type == "app":
                        app_handle(tcp_client, recv_data)
                    elif client_type == "dev":
                        dev_handle(tcp_client, recv_data)
        except Exception as e:
            logging.error("%s %s", tcp_client_ip, e)
            if client_type == "app":
                app_list.remove(tcp_client)
                logging.info("app：%s", app_list)
            elif client_type == "dev":
                dev_list.remove(tcp_client)
                logging.info("设备：%s", dev_list)
            break


if __name__ == '__main__':
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, True)
    server.bind(("", tcp_port))
    server.listen(client_num)
    while True:
        client, client_ip = server.accept()
        client.settimeout(120)
        logging.info("%s 接入", client_ip)
        thd = threading.Thread(target=message_handle, args=(client, client_ip))
        thd.setDaemon(True)
        thd.start()
