
from pynq import MMIO

def fixed_point_to_binary(fixed_point_data, num_bits, fractional_bits):
    # Calculate the maximum integer value that can be represented with the given number of bits
    max_int_value = 2**(num_bits - 1) - 1

    # Scale the fixed-point data to fit within the representable integer range
    scaled_data = int(fixed_point_data * (2**fractional_bits))

    # Clip the scaled data to stay within the representable integer range
    clipped_data = max(-max_int_value, min(scaled_data, max_int_value))

    # Convert the clipped data to binary representation
    binary_representation = bin(clipped_data & int("1"*num_bits, 2))[2:].zfill(num_bits)

    return binary_representation

#------------------------Address Info-------------------
# 0x00 : reserved
# 0x04 : reserved
# 0x08 : reserved
# 0x0c : reserved
# 0x10 : Data signal of bypass
#        bit 0  - bypass[0] (Read/Write)
#        others - reserved
# 0x14 : reserved
# 0x18 : Data signal of f
#        bit 31~0 - f[31:0] (Read/Write)
# 0x1c : reserved
# (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)


class Contrast:

    def __init__(self, base_addr: int):
        self.mmio = MMIO(base_addr, 0x10000)
        self.bypass_addr = 0x10
        self.f_addr = 0x18

    def set_scaler(self, scaler: float):
        fp = int(fixed_point_to_binary(scaler, 32, 16), 2)
        self.mmio.write(self.f_addr, fp)

    def enable(self):
        self.mmio.write(self.bypass_addr, 0x0)
    
    def disable(self):
        self.mmio.write(self.bypass_addr, 0x1)
       

#------------------------Address Info-------------------
# 0x00 : reserved
# 0x04 : reserved
# 0x08 : reserved
# 0x0c : reserved
# 0x10 : Data signal of bypass
#        bit 0  - bypass[0] (Read/Write)
#        others - reserved
# 0x14 : reserved
# (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

class Sharpen:

    def __init__(self, base_addr):
        self.mmio = MMIO(base_addr, 0x10000)
        self.bypass_addr = 0x10

    def enable(self):
        self.mmio.write(self.bypass_addr, 0x0)

    def disable(self):
        self.mmio.write(self.bypass_addr, 0x1)