from struct import pack, unpack
from multiprocessing import shared_memory
from time import sleep
from PySide6.QtCore import QObject, Signal
import psutil

from Misc.DataTypes import ConsoleTypes

# this doesn't need to be a QObject if you end up wanting to use this, it's just here so I can emit console messages easily
class Dolphin(QObject):
    console_msg = Signal(str, ConsoleTypes)

    MEM_START = 0x80000000
    MEM_END = 0x83000000

    def __init__(self) -> None:
        super().__init__()

        self.dolphin_pid = -1
        self.dolphin_memory = None
        self.process_memory = None

    def cleanup(self) -> None:
        try:
            if self.dolphin_memory != None:
                self.dolphin_memory.close()
            if self.process_memory != None:
                self.process_memory.close()
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
                if self.hook_onto_shared_memory('smso.'+str(proc.pid)):
                    taken_pid = unpack("I", self.read_ram(0, 4))[0]
                    skip_pids.append(taken_pid)
                    print(taken_pid)
            elif proc.name() in ("Dolphin.exe", "DolphinQt2.exe", "DolphinWx.exe"):
                dolphins.append(proc)

        return [dolphin for dolphin in dolphins if dolphin.pid not in skip_pids]

    def hook_onto_shared_memory(self, shm_name: str) -> bool:
        # verify that shared memory gets cleaned up
        if self.dolphin_memory != None:
            self.dolphin_memory.close()
            self.dolphin_memory = None

        try:
            self.dolphin_memory = shared_memory.SharedMemory(shm_name)
            return True
        except FileNotFoundError:
            self.dolphin_memory = None
            return False

    def create_shared_memory(self, shm_name: str, shm_size: int) -> None:
        # verify that shared memory gets cleaned up
        if self.process_memory != None:
            self.process_memory.close()
            self.process_memory = None

        try:
            self.process_memory = shared_memory.SharedMemory(create=True, name=shm_name, size=shm_size)
        except Exception as e:
            print(e)
            self.process_memory = None

    def hook_any_dolphin(self) -> bool:
        dolphins = self.find_all_available_dolphins()

        if not dolphins:
            self.console_msg.emit("No available Dolphin found!", ConsoleTypes.ERROR)
            return False

        for dolphin in dolphins:
            # check for game instance running
            if not self.hook_onto_shared_memory('dolphin-emu.'+str(dolphin.pid)):
                self.console_msg.emit("An available Dolphin was found, but no game instance seems to be running!", ConsoleTypes.WARNING)
                continue
        
            # check for smso game id
            game_id = self.read(0x80000000, 6)
            if game_id != b'GMSE10':
                self.console_msg.emit(f"An available Dolphin game instance was found, but the game id did not match 'GMSE10'!", ConsoleTypes.WARNING)
                continue

            # check for expanded memory. I'm just reading 80 bytes at the end just to be safe compatibility-wise
            if b'opening.bnr' in self.read(0x817fffb0, 0x50) or b'opening.bnr' not in self.read(0x82FFFFb0, 0x50):
                self.console_msg.emit("An available Dolphin game instance was found, but it seems the memory hasn't been expanded correctly!", ConsoleTypes.WARNING)
                continue

            self.create_shared_memory('smso.'+str(psutil.Process().pid), 4)
            self.process_memory.buf[0:4] = pack("I", dolphin.pid)
            self.dolphin_pid = dolphin.pid
            return True

        self.console_msg.emit("No Dolphin game instance could be hooked onto!", ConsoleTypes.ERROR)
        return False

    # these are the underlying read and write functions that get called by all other reads and writes
    def read_ram(self, offset: int, size: int) -> memoryview:
        return self.dolphin_memory.buf[offset:offset+size]
    def write_ram(self, offset: int, data: int) -> None:
        self.dolphin_memory.buf[offset:offset+len(data)] = data

    # these functions are meant for writing and reading byte arrays to and from memory
    def read(self, addr: int, size: int) -> bytes:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        if addr + size > self.MEM_END:
            size = self.MEM_END - addr
        value = self.read_ram(addr - 0x80000000, size)
        return unpack('>' + str(size) + 's', value)[0]
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
        value = self.read_ram(addr-0x80000000, 1)
        return unpack(">B", value)[0]
    def read_u16(self, addr: int) -> int:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        value = self.read_ram(addr-0x80000000, 2)
        return unpack(">H", value)[0]
    def read_u32(self, addr: int) -> int:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        value = self.read_ram(addr-0x80000000, 4)
        return unpack(">I", value)[0]
    def read_u64(self, addr: int) -> int:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        value = self.read_ram(addr-0x80000000, 8)
        return unpack(">Q", value)[0]

    def read_s8(self, addr: int) -> int:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        value = self.read_ram(addr-0x80000000, 1)
        return unpack(">b", value)[0]
    def read_s16(self, addr: int) -> int:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        value = self.read_ram(addr-0x80000000, 2)
        return unpack(">h", value)[0]
    def read_s32(self, addr: int) -> int:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        value = self.read_ram(addr-0x80000000, 4)
        return unpack(">i", value)[0]
    def read_s64(self, addr: int) -> int:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        value = self.read_ram(addr-0x80000000, 8)
        return unpack(">q", value)[0]

    def read_f32(self, addr: int) -> float:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        value = self.read_ram(addr - 0x80000000, 4)
        return unpack(">f", value)[0]
    def read_f64(self, addr: int) -> float:
        if addr < self.MEM_START or addr > self.MEM_END:
            return 0
        value = self.read_ram(addr - 0x80000000, 8)
        return unpack(">d", value)[0]
    
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
    
    if dolphin.hook_any_dolphin():
        print("Found Dolphin!")
    else:
        print("Didn't find Dolphin")

    import random 
    randint = random.randint
    from timeit import default_timer
    
    start = default_timer()
    
    print("Testing Shared Memory Method")
    start = default_timer()
    count = 500000
    for i in range(count):
        value = randint(0, 2**32-1)
        dolphin.write_u32(0x80000000, value)
        
        result = dolphin.read_u32(0x80000000)
        assert result == value
    diff = default_timer()-start 
    print(count/diff, "per sec")
    print("time: ", diff)
    