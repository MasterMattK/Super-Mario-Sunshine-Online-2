import ipaddress
from os import path
import sys

def is_ip_address(address: str) -> bool:
    try:
        ipaddress.ip_address(address)
        return True
    except ValueError:
        return False

def is_bool(value: str) -> bool:
    if value == 'True' or value == 'False':
        return True
    else:
        return False

def is_int(value: str, min: int=-sys.maxsize-1, max: int=sys.maxsize) -> bool:
    try:
        value = int(value)
        if value >= min and value <= max:
            return True
        else:
            return False
    except:
        return False

def is_path(value: str) -> bool:
    if path.exists(value):
        return True
    else:
        return False