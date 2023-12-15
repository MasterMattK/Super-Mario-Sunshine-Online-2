from threading import Lock
from bitarray import bitarray
import json

from Misc.DataTypes import ClientRcvDataTypes, TagStatus, ManhuntStatus

# class stored on server to keep track of incoming peers
class Player:
    def __init__(self, index: int) -> None:
        self.peer_id = 0
        self.connected = False
        self.address = ""
        self.username = f"Player{index}"
        self.model = "mario"
        self.tag_status = TagStatus.HIDER
        self.flags_paused = False
        self.manhunt_status = ManhuntStatus.HUNTER

# class stored on the server to sync incoming flag data from the clients
class FlagSync:
    def __init__(self) -> None:
        self.shines = bitarray(120)
        self.shines[:] = 0

        self.blues = bitarray(456)
        self.blues[:] = 0

        self.misc1 = bitarray(80)
        self.misc1[:] = 0
        self.misc1_id_start = 0x10360

        self.misc2 = bitarray(8)
        self.misc2[:] = 0
        self.misc2_id_start = 0x30008

    def reset_self(self) -> None:
        self.shines[:] = 0
        self.blues[:] = 0
        self.misc1[:] = 0
        self.misc2[:] = 0

    # syncs the incoming flag data to the previous flag data
    def sync(self, data: dict) -> tuple:
        data.shines = bitarray(data.shines)
        data.blues = bitarray(data.blues)
        data.misc1 = bitarray(data.misc1)
        data.misc2 = bitarray(data.misc2)

        # the bitwise operations here return a 1 for every 1 present in self.shines and not
        # present in data.shines. The list it returns
        # just retrieves the id for these 1's.
        shines_ids = [index for index in (self.shines & ~data.shines).search(1)]
        blues_ids = [index for index in (self.blues & ~data.blues).search(1)]
        misc1_ids = [self.misc1_id_start + index for index in (self.misc1 & ~data.misc1).search(1)]
        misc2_ids = [self.misc2_id_start + index for index in (self.misc2 & ~data.misc2).search(1)]
        if len(shines_ids) != 0 or len(blues_ids) != 0 or len(misc1_ids) != 0 or len(misc2_ids) != 0:
            return "sync_current_peer", self.to_json(shines_ids, blues_ids, misc1_ids, misc2_ids)

        # if it makes it here, we're now just checking the opposite of what we checked above. 
        # the bitwise operations return a 1 for every bit where data.shines is 1 and self.shines is 0.
        # then we're retrieving the respective ids for all of those 1's. We also sync those new flags to
        # the server's master flags.
        shines_ids = [index for index in (data.shines & ~self.shines).search(1)]
        self.shines = data.shines | self.shines

        blues_ids = [index for index in (data.blues & ~self.blues).search(1)]
        self.blues = data.blues | self.blues

        misc1_ids = [self.misc1_id_start + index for index in (data.misc1 & ~self.misc1).search(1)]
        self.misc1 = data.misc1 | self.misc1
    
        misc2_ids = [self.misc2_id_start + index for index in (data.misc2 & ~self.misc2).search(1)]
        self.misc2 = data.misc2 | self.misc2

        if len(shines_ids) != 0 or len(blues_ids) != 0 or len(misc1_ids) != 0 or len(misc2_ids) != 0:
            return "sync_other_peers", self.to_json(shines_ids, blues_ids, misc1_ids, misc2_ids)
        else:
            return None, None

    def to_json(self, shines_ids: list, blues_ids: list, misc1_ids: list, misc2_ids: list) -> str:
        return json.dumps({
            'dataType': ClientRcvDataTypes.FLG_DATA.value,
            'shines_ids': shines_ids,
            'blues_ids': blues_ids,
            'misc1_ids': misc1_ids,
            'misc2_ids': misc2_ids
        })