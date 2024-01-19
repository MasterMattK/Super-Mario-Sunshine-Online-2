import ctypes
from struct import pack, unpack
import psutil
from multiprocessing.shared_memory import SharedMemory
from ctypes import POINTER
from PySide6.QtCore import QObject, Signal

from Misc.DataTypes import ConsoleTypes

# Various Linux structs needed for operation

class iovec(ctypes.Structure):
    _fields_ = [("iov_base",ctypes.c_void_p),("iov_len",ctypes.c_size_t)]

libc = ctypes.cdll.LoadLibrary("libc.so.6")
vm_read = libc.process_vm_readv
vm_read.argtypes = [ctypes.c_int, POINTER(iovec), ctypes.c_ulong, POINTER(iovec), ctypes.c_ulong, ctypes.c_ulong]
vm_write = libc.process_vm_writev
vm_write.argtypes = [ctypes.c_int, POINTER(iovec), ctypes.c_ulong, POINTER(iovec), ctypes.c_ulong, ctypes.c_ulong]


# The following code is a port of aldelaro5's Dolphin memory access methods 
# for Linux into Python+ctypes.
# https://github.com/aldelaro5/Dolphin-memory-engine

class Dolphin(QObject):
    console_msg = Signal(str, ConsoleTypes)

    MEM_START = 0x80000000
    MEM_END = 0x83000000
    VANILLA_MEM_END = 0x81800000

    def __init__(self) -> None:
        super().__init__()

        self.dolphin_pid = -1
        self.smso_memory = None
        self.address_start = 0

    def cleanup(self) -> None:
        try:
            if self.smso_memory != None:
                self.smso_memory.unlink()
        except:
            pass
        
    def find_all_available_dolphins(self) -> list:
        skip_pids = []
        dolphins = []

        # find any other instances of smso and check for which dolphin instances they've hooked onto.
        # the pid that an smso instance has hooked onto is stored in a shared memory block, which is how we check
        # we also find any instances of dolphin
        for proc in psutil.process_iter():
            if proc.name() == psutil.Process().name() and proc.pid != psutil.Process().pid:
                success, taken_pid = self.check_for_dolphin_pid(proc.pid)
                if success:
                    skip_pids.append(taken_pid)
            elif proc.name() in ("dolphin-emu", "dolphin-emu-qt2", "dolphin-emu-wx"):
                dolphins.append(proc)

        return [dolphin for dolphin in dolphins if dolphin.pid not in skip_pids]
        
    def get_emu_info(self, mem_size) -> bool:
        try:
            maps_file = open(f"/proc/{self.dolphin_pid}/maps", 'r')
        except IOError:
            print(f"Cant open maps for process {self.dolphin_pid}")

        for line in maps_file:
            # depending on the linux distro, /run may be used instead of /dev
            if ('/run/shm/dolphinmem' in line or '/run/shm/dolphin-emu' in line or 
                '/dev/shm/dolphinmem' in line or '/dev/shm/dolphin-emu'):
                heap_info = line.split()
            else:
                continue

            # I was sometimes getting an 'rw-p' entry, which would lead to errors
            if heap_info[1] != 'rw-s':
                continue
            
            # I'm only looking for MEM1, so I don't need any offset other than 0
            offset = int(heap_info[2], 16)
            if offset != 0:
                continue

            first_address_str, second_address_str = heap_info[0].split('-')
            first_address = int(first_address_str, 16)
            second_address = int(second_address_str, 16)
            
            if (second_address - first_address) == mem_size:
                self.address_start = first_address
        
        if self.address_start == 0:
            return False

        return True

    def check_for_dolphin_pid(self, pid: int) -> tuple:
        try:
            other_smso_memory = SharedMemory('smso.'+str(pid))
            taken_pid = unpack("I", self.read_shared_memory(0, 4, other_smso_memory))[0]
            return True, taken_pid
        except FileNotFoundError:
            return False, None

    def write_dolphin_pid(self, self_pid: int) -> None:
        # verify that shared memory gets cleaned up
        if self.smso_memory != None:
            self.smso_memory.unlink()
            self.smso_memory = None

        try:
            self.smso_memory = SharedMemory(create=True, name='smso.'+str(self_pid), size=4)
            self.write_shared_memory(0, pack("I", self.dolphin_pid), self.smso_memory)
        except Exception as e:
            print(e)
            self.smso_memory = None

    def hook_any_dolphin(self) -> bool:
        dolphins = self.find_all_available_dolphins()

        if not dolphins:
            self.console_msg.emit("No available Dolphin found!", ConsoleTypes.ERROR)
            return False

        for dolphin in dolphins:
            self.dolphin_pid = dolphin.pid

            # check for game instance running
            if not self.get_emu_info(0x4000000):
                if self.get_emu_info(0x2000000):    # 0x2000000 is the vanilla memory size
                    self.console_msg.emit("An available Dolphin game instance was found, but it seems the memory hasn't been expanded correctly!", ConsoleTypes.WARNING)
                else:
                    self.console_msg.emit("An available Dolphin was found, but no game instance seems to be running!", ConsoleTypes.WARNING)
                self.dolphin_pid = -1
                continue
        
            # check for smso game id
            game_id = self.read(0x80000000, 6)
            if game_id != b'GMSE10':
                self.console_msg.emit(f"An available Dolphin game instance was found, but the game id did not match 'GMSE10'!", ConsoleTypes.WARNING)
                self.dolphin_pid = -1
                continue

            # check for expanded memory (note: i need to edit this in the future if we expand compatibility to other sms versions besides ntsc-u)
            if b'opening.bnr' in self.read(0x817fffb0, 0x50) or b'opening.bnr' not in self.read(0x82FFFFb0, 0x50):
                self.console_msg.emit("An available Dolphin game instance was found, but it seems the memory hasn't been expanded correctly!", ConsoleTypes.WARNING)
                self.dolphin_pid = -1
                continue

            self.write_dolphin_pid(psutil.Process().pid)
            return True

        self.console_msg.emit("No Dolphin game instance could be hooked onto!", ConsoleTypes.ERROR)
        return False

    def read_shared_memory(self, offset: int, size: int, shm: SharedMemory) -> memoryview:
        return shm.buf[offset:offset+size]
    def write_shared_memory(self, offset: int, data: int, shm: SharedMemory) -> None:
        shm.buf[offset:offset+len(data)] = data

    def read_ram(self, offset, size) -> tuple:
        buffer_ = (ctypes.c_char*size)()
        nread = ctypes.c_size_t
        local = (iovec*1)()
        remote = (iovec*1)()
        local[0].iov_base = ctypes.addressof(buffer_)
        local[0].iov_len = size
        remote[0].iov_base = ctypes.c_void_p(self.address_start + offset)
        remote[0].iov_len = size
        nread = vm_read(self.dolphin_pid, local, 1, remote, 1, 0)
        if nread != size:
            return False, buffer_
        return True, buffer_
    def write_ram(self, offset, data) -> bool:
        buffer_ = (ctypes.c_char*len(data))(*data)
        nwrote = ctypes.c_size_t
        local = (iovec*1)()
        remote = (iovec*1)()
        local[0].iov_base = ctypes.addressof(buffer_)
        local[0].iov_len = len(data)
        remote[0].iov_base = ctypes.c_void_p(self.address_start + offset)
        remote[0].iov_len = len(data)
        nwrote = vm_write(self.dolphin_pid, local, 1, remote, 1, 0)
        if nwrote != len(data):
            return False
        return True

    # these functions are meant for writing and reading byte arrays to and from memory
    def read(self, addr: int, size: int) -> bytes:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        if addr + size > self.MEM_END:
            size = self.MEM_END - addr

        success, value = self.read_ram(addr - 0x80000000, size)
        if success:
            return unpack('>' + str(size) + 's', value)[0]
        else:
            return 0
    def write(self, addr: int, data: int) -> None:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        if addr + len(data) > self.MEM_END:
            data = data[:self.MEM_END - addr]
        return self.write_ram(addr - 0x80000000, pack('>' + str(len(data)) + 's', data))

    # the rest of the functions are the specific read and write calls. I have them all as separate
    # calls to prevent any sort of mistakes with passing in incorrect data types. 
    # It also helps with readability in general.
    def read_u8(self, addr: int) -> int:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        success, value = self.read_ram(addr-0x80000000, 1)
        if success:
            return unpack(">B", value)[0]
        else:
            return 0
    def read_u16(self, addr: int) -> int:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        success, value = self.read_ram(addr-0x80000000, 2)
        if success:
            return unpack(">H", value)[0]
        else:
            return 0
    def read_u32(self, addr: int) -> int:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        success, value = self.read_ram(addr-0x80000000, 4)
        if success:
            return unpack(">I", value)[0]
        else:
            return 0
    def read_u64(self, addr: int) -> int:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        success, value = self.read_ram(addr-0x80000000, 8)
        if success:
            return unpack(">Q", value)[0]
        else:
            return 0

    def read_s8(self, addr: int) -> int:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        success, value = self.read_ram(addr-0x80000000, 1)
        if success:
            return unpack(">b", value)[0]
        else:
            return 0
    def read_s16(self, addr: int) -> int:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        success, value = self.read_ram(addr-0x80000000, 2)
        if success:
            return unpack(">h", value)[0]
        else:
            return 0
    def read_s32(self, addr: int) -> int:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        success, value = self.read_ram(addr-0x80000000, 4)
        if success:
            return unpack(">i", value)[0]
        else:
            return 0
    def read_s64(self, addr: int) -> int:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        success, value = self.read_ram(addr-0x80000000, 8)
        if success:
            return unpack(">q", value)[0]
        else:
            return 0

    def read_f32(self, addr: int) -> float:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        success, value = self.read_ram(addr - 0x80000000, 4)
        if success:
            return unpack(">f", value)[0]
        else:
            return 0
    def read_f64(self, addr: int) -> float:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        success, value = self.read_ram(addr - 0x80000000, 8)
        if success:
            return unpack(">d", value)[0]
        else:
            return 0
        
    # be super careful using this function as it doesn't do much error checking.
    # possible errors could arise from invalid pointers or invalid strings in general
    def read_string(self, addr_ptr: int, limit: int=50) -> str:
        if addr_ptr < self.MEM_START or addr_ptr > self.MEM_END:
            return ""

        addr = self.read_u32(addr_ptr)

        data = bytearray()
        count = 0
        while count < limit:
            char = self.read_u8(addr)
            if char == 0:
                break
            data.append(char)
            addr += 1
            count += 1

        return data.decode('shift-jis')


    def write_u8(self, addr: int, val: int) -> None:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        return self.write_ram(addr - 0x80000000, pack(">B", val))
    def write_u16(self, addr: int, val: int) -> None:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        return self.write_ram(addr - 0x80000000, pack(">H", val))
    def write_u32(self, addr: int, val: int) -> None:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        return self.write_ram(addr - 0x80000000, pack(">I", val))
    def write_u64(self, addr: int, val: int) -> None:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        return self.write_ram(addr - 0x80000000, pack(">Q", val))

    def write_s8(self, addr: int, val: int) -> None:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        return self.write_ram(addr - 0x80000000, pack(">b", val))
    def write_s16(self, addr: int, val: int) -> None:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        return self.write_ram(addr - 0x80000000, pack(">h", val))
    def write_s32(self, addr: int, val: int) -> None:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        return self.write_ram(addr - 0x80000000, pack(">i", val))
    def write_s64(self, addr: int, val: int) -> None:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        return self.write_ram(addr - 0x80000000, pack(">q", val))

    def write_f32(self, addr: int, val: int) -> None:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        return self.write_ram(addr - 0x80000000, pack(">f", val))
    def write_f64(self, addr: int, val: int) -> None:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        return self.write_ram(addr - 0x80000000, pack(">d", val))
        

# THIS DOESN'T WORK CURRENTLY 
if __name__ == "__main__":
    dolphin = Dolphin()

    if dolphin.find_dolphin():

        print("Found Dolphin! ")
    else:
        print("Didn't find Dolphin")
        
    print(dolphin.dolphin_pid)
        
    if dolphin.get_emu_info():
        print("We found MEM1 and/or MEM2!", dolphin.address_start, dolphin.mem2_start)
    else:
        print("We didn't find it...")
    print(dolphin.write_ram(0, b"GMS"))
    success, result = dolphin.read_ram(0, 8)
    print(result[0:8])
    
    print(dolphin.write_ram(0, b"AWA"))
    success, result = dolphin.read_ram(0, 8)
    print(result[0:8])