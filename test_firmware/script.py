import asyncio
from bleak import BleakClient, BleakScanner

SERVICE_UUID = "8b7e0001-5a9d-4c31-9f20-7d6a8e42b101"
CHARACTERISTIC_UUID = "8b7e0002-5a9d-4c31-9f20-7d6a8e42b101"

SNES_BUTTONS = [
    "B", "Y", "SELECT", "START", "UP", "DOWN", "LEFT", "RIGHT",
    "A", "X", "L", "R", "BIT12", "BIT13", "BIT14", "BIT15"
]

def notification_handler(sender, data):
    state = int.from_bytes(data, byteorder="little")
    pressed = []
    for i in range(16):
        # 0 = Pressionado (Active-LOW)
        if not (state & (1 << i)):
            pressed.append(SNES_BUTTONS[i])
    
    status = ", ".join(pressed) if pressed else "Nenhum (Repouso)"
    print(f"[HEX: 0x{state:04X}] Botões ativos: {status}")

async def main():
    print("Procurando SNES-BT-Controller...")
    device = await BleakScanner.find_device_by_name("SNES-BT-Controller")
    if not device:
        print("Dispositivo não encontrado!")
        return

    async with BleakClient(device) as client:
        print(f"Conectado ao ESP32! Monitorando entradas...")
        await client.start_notify(CHARACTERISTIC_UUID, notification_handler)
        while True:
            await asyncio.sleep(1)

asyncio.run(main())