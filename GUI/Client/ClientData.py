from bitarray import bitarray
from struct import pack, unpack
import json

from Client.InGameVars import InGameVars
from Client.DolphinMemoryLib import Dolphin
from Misc.DataTypes import ServerRcvDataTypes, TagStatus

# class stored on client to keep track of other players
class Player:
    def __init__(self, index: int) -> None:
        self.peer_id = 0
        self.connected = False
        self.username = f"Player{index}"
        self.model = "mario"
        self.tag_status = TagStatus.HIDER

# this class is what reads and sets all of the client's values every frame to send to the server
# this is always called on the send thread
class ClientData:
    def __init__(self, memory: Dolphin) -> None:
        self.memory = memory
        self.previous_spam_states = [0, 0]

    def update_data(self) -> None:
        # additional pointers
        self.pMario = self.memory.read_u32(0x8040E0E8)
        self.pApplication = self.memory.read_u32(0x803E9700)
        self.pWaterGun = self.memory.read_u32(self.pMario + 0x3E4)
        self.pMarioController = self.memory.read_u32(self.pMario + 0x108)
        self.pYoshi = self.memory.read_u32(self.pMario + 0x3F0)
        self.pMarioCap = self.memory.read_u32(self.pMario + 0x3E0)
        self.pMarDirector = self.memory.read_u32(0x8040E178)
        self.pPauseMenu2 = self.memory.read_u32(self.pMarDirector + 0xAC)
        self.pTGCConsole2 = self.memory.read_u32(self.pMarDirector + 0x74)

        # position data
        self.xPos = self.memory.read_f32(self.pMario + 0x10)
        self.yPos = self.memory.read_f32(self.pMario + 0x14)
        self.zPos = self.memory.read_f32(self.pMario + 0x18)
        self.xAng = self.memory.read_u16(self.pMario + 0x94)
        self.yAng = self.memory.read_u16(self.pMario + 0x96)
        self.zAng = self.memory.read_u16(self.pMario + 0x98)
        self.accDir = self.memory.read_u16(self.pMario + 0x90)
        self.unkOne = self.memory.read_u32(self.pMario + 0x78)
        self.unkTwo = self.memory.read_f32(self.pMario + 0xEB8)
        self.baseAcc = self.memory.read_f32(self.pMario + 0x8C)

        # state data (the word state is kinda used loosely here tbh)
        self.currentState = self.memory.read_u32(self.pMario + 0x7C)
        self.previousState = self.memory.read_u32(self.pMario + 0x80)
        self.substate = self.memory.read_u32(self.pMario + 0x84)
        self.marioFlags = self.memory.read_u32(self.pMario + 0x118)
        self.fwdSpeed = self.memory.read_f32(self.pMario + 0xB0)
        self.extraAngles = self.memory.read_u16(self.pMario + 0x96) # idk why this value needed to be synced, but it did
        self.health  = self.memory.read_u16(self.pMario + 0x120)
        self.inputFlags  = self.memory.read_u32(self.pMario + 0x74)
        self.fluddAnims  = self.memory.read_u32(self.pMario + 0x380)
        self.level = self.memory.read_u8(self.pApplication + 0xE)
        self.episode = self.memory.read_u8(self.pApplication + 0xF)
        self.fluddVals = self.memory.read_u64(self.pWaterGun + 0x1C80) # water level and nozzle type
        self.marioSpamSpray  = self.memory.read_u8(self.pWaterGun + 0x715)
        self.yoshiSpamSpray  = self.memory.read_u8(self.pWaterGun + 0x153D)
        self.fluddAngle  = self.memory.read_u16(self.pWaterGun + 0x37A)
        self.rButton  = self.memory.read_u32(self.pMarioController + 0x1C)
        self.yoshiState  = self.memory.read_u8(self.pYoshi)
        self.juiceLevel  = self.memory.read_u32(self.pYoshi + 0xC)
        self.flutterState  = self.memory.read_u32(self.pYoshi + 0xB8) # also includes flutter timer
        self.sunglasses  = self.memory.read_u8(self.pMarioCap + 0x5)
        self.gameState = self.memory.read_u8(self.pMarDirector + 0x64)

        # tag timer (so that the server can store your tag time in case of crash)
        self.clientTagTime = self.memory.read_u32(InGameVars.CLIENT_TAG_TIME)
        self.currentTime = self.memory.read_u32(self.pTGCConsole2 + 0x500)
        self.tagBool = self.memory.read_u32(InGameVars.TAG_BOOL)

        # fludd/yoshi have 3 spraying states: 0 = normal spraying, 1 = spam spray, 2 = no spraying(happens after spam).
        # state 1 happens too quickly for it to properly sync over the server, so we have to set that manually
        if self.marioSpamSpray == 2 and self.previous_spam_states[0] == 0:
            self.marioSpamSpray = 1
        if self.yoshiSpamSpray == 2 and self.previous_spam_states[1] == 0:
            self.yoshiSpamSpray = 1

        self.previous_spam_states[0] = self.marioSpamSpray
        self.previous_spam_states[1] = self.yoshiSpamSpray

    # always call this to dump to json. it adds the dataType entry and is just cleaner to call
    def to_json(self) -> str:
        return json.dumps({
            'dataType': ServerRcvDataTypes.CLI_DATA.value,
            'xPos': self.xPos,
            'yPos': self.yPos,
            'zPos': self.zPos,
            'xAng': self.xAng,
            'yAng': self.yAng,
            'zAng': self.zAng,
            'accDir': self.accDir,
            'unkOne': self.unkOne,
            'unkTwo': self.unkTwo,
            'baseAcc': self.baseAcc,
            'currentState': self.currentState,
            'previousState': self.previousState,
            'substate': self.substate,
            'marioFlags': self.marioFlags,
            'fwdSpeed': self.fwdSpeed,
            'extraAngles': self.extraAngles,
            'health': self.health,
            'inputFlags': self.inputFlags,
            'fluddAnims': self.fluddAnims,
            'level': self.level,
            'episode': self.episode,
            'fluddVals': self.fluddVals,
            'marioSpamSpray': self.marioSpamSpray,
            'yoshiSpamSpray': self.yoshiSpamSpray,
            'fluddAngle': self.fluddAngle,
            'rButton': self.rButton,
            'yoshiState': self.yoshiState,
            'juiceLevel': self.juiceLevel,
            'flutterState': self.flutterState,
            'sunglasses': self.sunglasses,
            'gameState': self.gameState,
            'clientTagTime': self.clientTagTime,
            'currentTime': self.currentTime,
            'tagBool': self.tagBool
        })


# this class is for retrieving client pointers for comparison in the receive thread
class ClientPointers:
    def __init__(self, memory: Dolphin) -> None:
        self.pMario = memory.read_u32(0x8040E0E8)
        self.pApplication = memory.read_u32(0x803E9700)
        self.pMarDirector = memory.read_u32(0x8040E178)
        self.pPauseMenu2 = memory.read_u32(self.pMarDirector + 0xAC)

        self.level = memory.read_u8(self.pApplication + 0xE)
        self.gameState = memory.read_u8(self.pMarDirector + 0x64)

class DummyPointers:
    def __init__(self, pDummyMario: int, memory: Dolphin) -> None:
        self.pDummyMario = pDummyMario
        self.pWaterGun = memory.read_u32(self.pDummyMario + 0x3E4)
        self.pMarioController = memory.read_u32(self.pDummyMario + 0x108)
        self.pYoshi = memory.read_u32(self.pDummyMario + 0x3F0)
        self.pMarioCap = memory.read_u32(self.pDummyMario + 0x3E0)


# this is it's own class so that I can access it independently of other client data easily
class FlagData:       
    def __init__(self, memory: Dolphin) -> None:
        self.memory = memory

        self.shines = bitarray(120)
        self.shines[:] = 0

        self.blues = bitarray(456)
        self.blues[:] = 0

        self.misc1 = bitarray(80)
        self.misc1[:] = 0

        self.misc2 = bitarray(8)
        self.misc2[:] = 0

    def update_data(self) -> None:
        # Go to the link below for the precise flag values:
        # https://docs.google.com/spreadsheets/d/1ElTW-akaTUF9OC2pIFR9-7aVPwpJ54AdEVJyJ_jvg0E/edit#gid=273297098

        # Flag Manager Pointer
        self.pFlagManager = self.memory.read_u32(0x8040E160)

        # These are all of the 120 shines in the game
        self.shines[0:64] = bitarray(bin(self.memory.read_u64(self.pFlagManager))[2:].zfill(64))
        self.shines[64:96] = bitarray(bin(self.memory.read_u32(self.pFlagManager + 0x8))[2:].zfill(32))
        self.shines[96:112] = bitarray(bin(self.memory.read_u16(self.pFlagManager + 0xC))[2:].zfill(16))
        self.shines[112:120] = bitarray(bin(self.memory.read_u8(self.pFlagManager + 0xE))[2:].zfill(8))
        self.shines.bytereverse()   # we have to reverse each byte in order to align flags with their flag ids in game

        # All 240 blue coins (a lot of these bits are unused blue coins)
        self.blues[0:8] = bitarray(bin(self.memory.read_u8(self.pFlagManager + 0xF))[2:].zfill(8))
        self.blues[8:72] = bitarray(bin(self.memory.read_u64(self.pFlagManager + 0x10))[2:].zfill(64))
        self.blues[72:136] = bitarray(bin(self.memory.read_u64(self.pFlagManager + 0x18))[2:].zfill(64))
        self.blues[136:200] = bitarray(bin(self.memory.read_u64(self.pFlagManager + 0x20))[2:].zfill(64))
        self.blues[200:264] = bitarray(bin(self.memory.read_u64(self.pFlagManager + 0x28))[2:].zfill(64))
        self.blues[264:328] = bitarray(bin(self.memory.read_u64(self.pFlagManager + 0x30))[2:].zfill(64))
        self.blues[328:392] = bitarray(bin(self.memory.read_u64(self.pFlagManager + 0x38))[2:].zfill(64))
        self.blues[392:456] = bitarray(bin(self.memory.read_u64(self.pFlagManager + 0x40))[2:].zfill(64))
        self.blues.bytereverse()    # we have to reverse each byte in order to align flags with their flag ids in game

        # this is some of the other flags, like nozzle unlocks, watched cutscenes, defeated bosses, level visits, etc.
        # the link at the start of this function will give specifics
        self.misc1[0:64] = bitarray(bin(self.memory.read_u64(self.pFlagManager + 0x6C))[2:].zfill(64))
        self.misc1[64:80] = bitarray(bin(self.memory.read_u16(self.pFlagManager + 0x74))[2:].zfill(16))
        self.misc1.bytereverse()    # we have to reverse each byte in order to align flags with their flag ids in game

        self.misc2[0:8] = bitarray(bin(self.memory.read_u8(self.pFlagManager + 0xCD))[2:].zfill(8))
        self.misc2.bytereverse()    # we have to reverse each byte in order to align flags with their flag ids in game

    # always call this to dump to json. it adds the dataType entry and is just cleaner to call
    def to_json(self) -> str:
        return json.dumps({
            'dataType': ServerRcvDataTypes.FLG_DATA.value,
            'shines': self.shines.to01(),
            'blues': self.blues.to01(),
            'misc1': self.misc1.to01(),
            'misc2': self.misc2.to01()
        })