import serial
import time
import datetime

port = 'COM3'
baud_rate = 9600
file_path = f'./data/{datetime.datetime.now().strftime("%B %d, %Y.%H-%M-%S")}.csv'

# Abre el puerto serie
ser = serial.Serial(port, baud_rate)

# Espera que el puerto serie se estabilice
time.sleep(2)

# Abre el archivo para guardar los datos
with open(file_path, 'w') as f:
    # Lee y guarda los datos hasta que se interrumpa
    try:
        f.write('Tiempo Real, Tiempo, Iluminacion\n')  # Guarda la línea en el archivo
        print('Tiempo Real, Tiempo Ejecucion, Iluminacion')  # Muestra la línea en la consola
        while True:
            line = ser.readline().decode('utf-8').strip()
            current_time = datetime.datetime.now().strftime("%H-%M-%S")
            record=f'{current_time},{line}\n'
            print(record,end='')  # Muestra ek registro en la consola
            f.write(record)  # Guarda ek registro en el archivo
    except KeyboardInterrupt:
        print("Detenido por el usuario.")
    except Exception as e:
        print(f"Error: {e}")
    finally:
        ser.close()  # Asegúrate de cerrar el puerto serie
