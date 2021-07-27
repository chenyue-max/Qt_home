import sqlite3
import time
import serial

dict={"temp1":[0xFE,0xFE,0x00,0xFF,0xFF,0x0A,0x20,0x18,0x01,0xFF],
      "temp2":[0xFE,0xFE,0x00,0xFF,0xFF,0x0A,0x40,0x1F,0x01,0xFF],
      "CO2":[0xFE,0xFE,0x00,0xFF,0xFF,0x0A,0x20,0x16,0x01,0xFF],
      "UA":[0xFE,0xFE,0x00,0xFF,0xFF,0x0A,0x20,0x17,0x01,0xFF],
      "light":[0xFE,0xFE,0x00,0xFF,0xFF,0x0A,0x20,0x2C,0x01,0xFF],
      "hum1":[0xFE,0xFE,0x00,0xFF,0xFF,0x0A,0x20,0x19,0x01,0xFF],
      "CH4":[0xFE,0xFE,0x00,0xFF,0xFF,0x0A,0x30,0x1A,0x01,0x0F],
      "hire":[0xFE,0xFE,0x00,0xFF,0xFF,0x0A,0x30,0x1B,0x01,0x0F],
      "smoke":[0xFE,0xFE,0x00,0xFF,0xFF,0x0A,0x30,0x1C,0x01,0x0F],
      "person":[0xFE,0xFE,0x00,0xFF,0xFF,0x0A,0x30,0x1D,0x01,0x0F],
      "PM2":[0xFE,0xFE,0x00,0xFF,0xFF,0x0A,0x40,0x1E,0x01,0xFF],
      "hum2":[0xFE,0xFE,0x00,0xFF,0xFF,0x0A,0x40,0x20,0x01,0xFF]}

def send_rece_type(idname):
    senddata=dict[idname]
    lis_data=[]
    ser.write(senddata)
    for i in range(1,20):
        list_shao=[int(x) for x in bytes(ser.readline())]
        lis_data+=list_shao
        # print(idname,len(lis_data))
        if len(lis_data)>=13:
            return float(str(lis_data[8])+'.'+str(lis_data[9]))
        else:
            continue
    return -1
temp=0
while 1:
    nowtime = str(time.strftime('%Y-%m-%d %H:%M:%S', time.localtime()))
    if (nowtime[15] == '0' or nowtime[15] == '5') and nowtime[:16]!=temp:
        temp=nowtime[:16]
        ser = serial.Serial("COM9", 9600, timeout=0.5)
        print(nowtime)
        list_a=[]
        list_a.append(nowtime[:16])
        list_a.append(send_rece_type("temp1"))
        list_a.append(send_rece_type("temp2"))
        list_a.append(send_rece_type("CO2"))
        list_a.append(send_rece_type("UA"))
        list_a.append(send_rece_type("light"))
        list_a.append(send_rece_type("hum1"))
        list_a.append(send_rece_type("CH4"))
        list_a.append(send_rece_type("hire"))
        list_a.append(send_rece_type("smoke"))
        list_a.append(send_rece_type("person"))
        list_a.append(send_rece_type("PM2"))
        list_a.append(send_rece_type("hum2"))
        ser.close()
        print(list_a)
        conn = sqlite3.connect("build-SmartHome-Desktop_Qt_5_9_2_MinGW_32bit-Debug\id.db")
        cursor = conn.cursor()
        cursor.execute('insert into sensordata values(?,?,?,?,?,?,?,?,?,?,?,?,?)', list_a)
        conn.commit()
        cursor.close()
        conn.close()


