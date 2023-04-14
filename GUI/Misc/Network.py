from Misc.DataTypes import DisconnectSource
from time import sleep
import json
import enet

class NetworkServer:
    def __init__(self, ip: str, port: int, max_conns: int=4) -> None:
        self.host = enet.Host(enet.Address(ip.encode(), port), max_conns, 0, 0, 0)

    def cleanup(self) -> None:
        self.host.flush()
        for peer in self.host.peers:
            peer.disconnect_now(data=DisconnectSource.SVR_END.value)
        
        del self.host

    # sends packets to the peer
    def send(self, data: str, peer: enet.Peer, reliable: bool=False) -> None:
        if reliable:
            peer.send(0, enet.Packet(data.encode(encoding='utf-8'), enet.PACKET_FLAG_RELIABLE))
        else:
            peer.send(0, enet.Packet(data.encode(encoding='utf-8')))

    def receive(self) -> enet.Event:
        return self.host.service(0)

    def decode_data(self, data: bytes) -> dict:
        data = data.decode(encoding='utf-8')
        data = json.loads(data)
        return self.dotdict(data)

    def encode_data(self, data: dict) -> str:
        return json.dumps(data)

    def get_peer(self, peer_id: int) -> enet.Peer:
        for p in self.host.peers:
            if p.incomingPeerID == peer_id:
                return p

    def get_other_peers(self, peer_id: int) -> list:
        return [v for i, v in enumerate(self.host.peers) if v.incomingPeerID != peer_id]

    # allows you to access a dictionary like a class (with dot syntax)
    class dotdict(dict):
        def __init__(self, *args, **kwargs) -> None:
            super().__init__(*args, **kwargs)
            for key, value in self.items():
                if isinstance(value, dict):
                    self[key] = __class__(value)
        __getattr__ = dict.get
        __setattr__ = dict.__setitem__
        __delattr__ = dict.__delitem__
    
class NetworkClient:
    def __init__(self) -> None:
        self.host = enet.Host(None, 1, 0, 0, 0)

    def reset_host(self) -> None:
        del self.host
        del self.peer
        self.host = enet.Host(None, 1, 0, 0, 0)

    def cleanup(self) -> None:
        self.host.flush()
        if hasattr(self, "peer"):  # this is the cleanest way of doing this due to limited enet implementation 
            self.peer.disconnect_now(data=DisconnectSource.CLT_END.value)
        
        del self.host

    # connects to the specified ip and port and checks for connection verification
    # the data argument needs to already have the CONNECT enum type from DataTypes
    def connect(self, ip: str, port: int, data: dict) -> bool:
        self.peer = self.host.connect(enet.Address(ip.encode(), port), 1)
        
        for i in range(30):
            sleep(0.1)
            event = self.host.service(0)
            if event.type == enet.EVENT_TYPE_CONNECT:
                self.send(json.dumps(data), reliable=True)
                return True
            else:
                continue
            
        self.reset_host()
        return False

    def disconnect(self) -> None:
        self.peer.disconnect_now(data=DisconnectSource.CLT_END.value)

    # sends packets to the peer
    def send(self, data: str, reliable: bool=False) -> None:
        if reliable:
            self.peer.send(0, enet.Packet(data.encode(encoding='utf-8'), enet.PACKET_FLAG_RELIABLE))
        else:
            self.peer.send(0, enet.Packet(data.encode(encoding='utf-8')))

    def receive(self) -> enet.Event:
        return self.host.service(0)

    def decode_data(self, data: bytes) -> dict:
        data = data.decode(encoding='utf-8')
        data = json.loads(data)
        return self.dotdict(data)

    # allows you to access a dictionary like a class (with dot syntax)
    class dotdict(dict):
        def __init__(self, *args, **kwargs):
            super().__init__(*args, **kwargs)
            for key, value in self.items():
                if isinstance(value, dict):
                    self[key] = self.__class__(value)
        __getattr__ = dict.get
        __setattr__ = dict.__setitem__
        __delattr__ = dict.__delitem__