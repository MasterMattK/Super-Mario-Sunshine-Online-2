class LevelData:
    level_data = {
        "Airstrip": {
            "FLUDD Discovery": {"lvl_id": 0x0000, "ep_command": "airport 0"},
            "Gatekeeper Boss": {"lvl_id": 0x0001, "ep_command": "airport 1"},
            "Post-Game Return": {"lvl_id": 0x1400, "ep_command": "dolpic_ex 0"}
        },
        "Delfino Plaza": {
            "Plaza 1 (Gatekeeper Boss)": {"lvl_id": 0x0100, "ep_command": "dolpic 0"},
            "Plaza 2 (Shadow Mario)": {"lvl_id": 0x0101, "ep_command": "dolpic 1"},
            "Plaza 3 (Bianco Unlocked)": {"lvl_id": 0x0105, "ep_command": "dolpic 5"},
            "Plaza 4 (Ricco and/or Gelato Gatekeeper Boss)": {"lvl_id": 0x0106, "ep_command": "dolpic 6"},
            "Plaza 5 (Peach Stolen to Pinna)": {"lvl_id": 0x0107, "ep_command": "dolpic 7"},
            "Plaza 6 (Post-Pinna)": {"lvl_id": 0x0108, "ep_command": "dolpic 8"},
            "Plaza 7 (Flooded)": {"lvl_id": 0x0109, "ep_command": "dolpic 9"},
            "Plaza 8 (Post-game Plaza)": {"lvl_id": 0x0102, "ep_command": "dolpic 2"}
        },
        "Bianco Hills": {
            "1: Road to the Big Windmill": {"lvl_id": 0x0200, "ep_command": "bianco 0"},
            "2: Down With Petey Pirahna": {"lvl_id": 0x0201, "ep_command": "bianco 1"},
            "3: The Hillside Cave Secret": {"lvl_id": 0x0202, "ep_command": "bianco 2"},
            "4: Red Coins of Windmill Village": {"lvl_id": 0x0203, "ep_command": "bianco 3"},
            "5: Petey Piranha Strikes Back": {"lvl_id": 0x0204, "ep_command": "bianco 4"},
            "6: The Secret of the Dirty Lake": {"lvl_id": 0x0205, "ep_command": "bianco 5"},
            "7: Shadow Mario on the Loose": {"lvl_id": 0x0206, "ep_command": "bianco 6"},
            "8: Red Coins of the Lake": {"lvl_id": 0x0207, "ep_command": "bianco 7"}
        },
        "Ricco Harbor": {
            "1: Gooper Blooper Breaks Out": {"lvl_id": 0x0300, "ep_command": "ricco 0"},
            "2: Blooper Surfin' Safari": {"lvl_id": 0x0301, "ep_command": "ricco 1"},
            "3: The Caged Shine Sprite": {"lvl_id": 0x0302, "ep_command": "ricco 2"},
            "4: The Secret of Ricco Tower": {"lvl_id": 0x0303, "ep_command": "ricco 3"},
            "5: Gooper Blooper Returns": {"lvl_id": 0x0304, "ep_command": "ricco 4"},
            "6: Red Coins on the Water": {"lvl_id": 0x0305, "ep_command": "ricco 5"},
            "7: Shadow Mario Revisited": {"lvl_id": 0x0306, "ep_command": "ricco 6"},
            "8: Yoshi's Fruit Adventure": {"lvl_id": 0x0307, "ep_command": "ricco 7"}
        },
        "Gelato Beach": {
            "1: The Dune Bud Sandcastle Secret": {"lvl_id": 0x0400, "ep_command": "mamma 0"},
            "2: Mirror Madness! Tilt, Slam, Bam": {"lvl_id": 0x0401, "ep_command": "mamma 1"},
            "3: Wiggler Ahoy! Full Steam Ahead": {"lvl_id": 0x0402, "ep_command": "mamma 2"},
            "4: The Sand Bird is Born": {"lvl_id": 0x0403, "ep_command": "mamma 3"},
            "5: Piantissimo's Sand Sprint": {"lvl_id": 0x0404, "ep_command": "mamma 4"},
            "6: Red Coins of the Coral Reef": {"lvl_id": 0x0405, "ep_command": "mamma 5"},
            "7: It's Shadow Mario! After Him!": {"lvl_id": 0x0406, "ep_command": "mamma 6"},
            "8: The Watermelon Festival": {"lvl_id": 0x0407, "ep_command": "mamma 7"}
        },
        "Pinna Beach": {
            "Beach 1: Mecha Bowser Appears": {"lvl_id": 0x0500, "ep_command": "pinnaBeach 0"},
            "Beach 2: The Beach Cannon's Secret": {"lvl_id": 0x0501, "ep_command": "pinnaBeach 1"},
            "Beach 3: Red Coins of the Pirate Ships": {"lvl_id": 0x0502, "ep_command": "pinnaBeach 2"},
            "Beach 4: The Wilted Sunflowers": {"lvl_id": 0x0503, "ep_command": "pinnaBeach 3"},
            "Beach 5: The Runaway Ferris Wheel": {"lvl_id": 0x0504, "ep_command": "pinnaBeach 4"},
            "Beach 6: The Yoshi-Go-Round's Secret": {"lvl_id": 0x0505, "ep_command": "pinnaBeach 5"},
            "Beach 7: Shadow Mario in the Park": {"lvl_id": 0x0506, "ep_command": "pinnaBeach 6"},
            "Beach 8: Roller Coaster Balloons": {"lvl_id": 0x0507, "ep_command": "pinnaBeach 7"},
            "Park 1: Mecha Bowser Appears": {"lvl_id": 0x0D00, "ep_command": "pinnaParco 0"},
            "Park 2: Red Coins of the Pirate Ships": {"lvl_id": 0x0D01, "ep_command": "pinnaParco 1"},
            "Park 3: The Runaway Ferris Wheel": {"lvl_id": 0x0D02, "ep_command": "pinnaParco 2"},
            "Park 4: The Yoshi-Go-Round's Secret": {"lvl_id": 0x0D03, "ep_command": "pinnaParco 3"},
            "Park 5: Shadow Mario in the Park": {"lvl_id": 0x0D04, "ep_command": "pinnaParco 4"},
            "Park 6: Roller Coaster Balloons": {"lvl_id": 0x0D05, "ep_command": "pinnaParco 5"}
        },
        "Sirena Beach": {
            "Beach 1: The Manta Storm": {"lvl_id": 0x0600, "ep_command": "sirena 0"},
            "Beach 2: The Hotel Lobby's Secret": {"lvl_id": 0x0601, "ep_command": "sirena 1"},
            "Beach 3: Mysterious Hotel Delfino": {"lvl_id": 0x0602, "ep_command": "sirena 2"},
            "Beach 4: The Secret of Casino Delfino": {"lvl_id": 0x0603, "ep_command": "sirena 3"},
            "Beach 5: King Boo Down Below": {"lvl_id": 0x0604, "ep_command": "sirena 4"},
            "Beach 6: Scrubbing Sirena Beach": {"lvl_id": 0x0605, "ep_command": "sirena 5"},
            "Beach 7: Shadow Mario Checks In": {"lvl_id": 0x0606, "ep_command": "sirena 6"},
            "Beach 8: Red Coins in the Hotel": {"lvl_id": 0x0607, "ep_command": "sirena 7"},
            "Hotel 1: The Hotel Lobby's Secret": {"lvl_id": 0x0700, "ep_command": "delfino 0"},
            "Hotel 2: Mysterious Hotel Delfino": {"lvl_id": 0x0701, "ep_command": "delfino 1"},
            "Hotel 3: The Secret of Casino Delfino": {"lvl_id": 0x0702, "ep_command": "delfino 2"},
            "Hotel 4: King Boo Down Below": {"lvl_id": 0x0702, "ep_command": "delfino 2"},
            "Hotel 5: Shadow Mario Checks In": {"lvl_id": 0x0703, "ep_command": "delfino 3"},
            "Hotel 6: Red Coins in the Hotel": {"lvl_id": 0x0704, "ep_command": "delfino 4"},
            "Casino 1: The Secret of Casino Delfino": {"lvl_id": 0x0E00, "ep_command": "casino 0"},
            "Casino 2: King Boo Down Below": {"lvl_id": 0x0E01, "ep_command": "casino 1"},
        },
        "Pianta Village": {
            "1: Chain Chomplets Unchained": {"lvl_id": 0x0800, "ep_command": "monte 0"},
            "2: Piantissimo's Crazy Climb": {"lvl_id": 0x0801, "ep_command": "monte 1"},
            "3: The Goopy Inferno": {"lvl_id": 0x0802, "ep_command": "monte 2"},
            "4: Chain Chomp's Bath": {"lvl_id": 0x0803, "ep_command": "monte 3"},
            "5: Secret of the Village Underside": {"lvl_id": 0x0804, "ep_command": "monte 4"},
            "6: Piantas in Need": {"lvl_id": 0x0805, "ep_command": "monte 5"},
            "7: Shadow Mario Runs Wild": {"lvl_id": 0x0806, "ep_command": "monte 6"},
            "8: Fluff Festival Coin Hunt": {"lvl_id": 0x0807, "ep_command": "monte 7"},
        },
        "Noki Bay": {
            "1: Uncork the Waterfall": {"lvl_id": 0x0900, "ep_command": "mare 0"},
            "2: Boss of the Tricky Ruins": {"lvl_id": 0x0901, "ep_command": "mare 1"},
            "3: Red Coins in a Bottle": {"lvl_id": 0x0902, "ep_command": "mare 2"},
            "4: Eely Mouth's Dentist": {"lvl_id": 0x0903, "ep_command": "mare 3"},
            "5: Piantissimo's Surf Swim": {"lvl_id": 0x0904, "ep_command": "mare 4"},
            "6: The Shell's Secret": {"lvl_id": 0x0905, "ep_command": "mare 5"},
            "7: Shadow Mario on the Loose": {"lvl_id": 0x0906, "ep_command": "mare 6"},
            "8: The Red Coin Fish": {"lvl_id": 0x0907, "ep_command": "mare 7"},
        },
        "Misc.": {
            "Slide": {"lvl_id": 0x1500, "ep_command": "dolpic_ex 1"},
            "Pachinko": {"lvl_id": 0x1600, "ep_command": "dolpic_ex 2"},
            "Turbo Speedway": {"lvl_id": 0x1D00, "ep_command": "bia_ex 1"},
            "Red Coin Field": {"lvl_id": 0x1700, "ep_command": "dolpic_ex 3"},
            "Poison River": {"lvl_id": 0x1800, "ep_command": "dolpic_ex 4"},
            "Bianco Secret 1": {"lvl_id": 0x2F00, "ep_command": "coro_ex 1"},
            "Bianco Secret 2": {"lvl_id": 0x2E00, "ep_command": "coro_ex 0"},
            "Gooper Blooper 1": {"lvl_id": 0x3B00, "ep_command": "ricco 8"},
            "Blooper Race": {"lvl_id": 0x1E00, "ep_command": "rico_ex 0"},
            "Ricco Secret": {"lvl_id": 0x3000, "ep_command": "coro_ex 2"},
            "Gelato Secret": {"lvl_id": 0x2000, "ep_command": "mam_ex 0"},
            "Sand Bird": {"lvl_id": 0x2100, "ep_command": "mam_ex 1"},
            "Sirena Secret 1": {"lvl_id": 0x3300, "ep_command": "coro_ex 5"},
            "Sirena Secret 2": {"lvl_id": 0x2800, "ep_command": "sirena_ex 0"},
            "King Boo": {"lvl_id": 0x3800, "ep_command": "delfinoBoss"},
            "Pianta Secret": {"lvl_id": 0x2A00, "ep_command": "monte_ex 0"},
            "Bottle": {"lvl_id": 0x2C00, "ep_command": "mare_ex 0"},
            "Eely Mouth": {"lvl_id": 0x3900, "ep_command": "mareBoss"},
            "Noki Secret": {"lvl_id": 0x1F00, "ep_command": "rico_ex 1"},
            "Noki Deep Sea": {"lvl_id": 0x1000, "ep_command": "mareUndersea"},
            "Corona Mountain": {"lvl_id": 0x3400, "ep_command": "coro_ex 6"},
            "Bowser Fight": {"lvl_id": 0x3C00, "ep_command": "coronaBoss"}
        },
        "Tag Levels": {
            "Wuhu Town": {"lvl_id": 0x1900, "ep_command": "dolpic_ex 5"},
            "Bianco 8 Plus": {"lvl_id": 0x0208, "ep_command": "bianco 8"},
            #"Tower": {"lvl_id": 0x1A00, "ep_command": "dolpic_ex 6"}
        }
    }

    # returns list of all the stage options (Like Airstrip, Delfino Plaza, etc.)
    def get_stage_options(self) -> list:
        return list(self.level_data)

    # returns a list of episode options (Like FLUDD Discovery, Gatekeeper Boss, etc.)
    def get_episode_options(self) -> list:
        return [episode_dict.keys() for episode_dict in self.level_data.values()]

    # returns the level id when given an ep_command string like dolpic 0
    def get_lvl_id(self, ep_command: str) -> int:
        for sub_dict in self.level_data.values():
            for value in sub_dict.values():
                if ep_command == value["ep_command"]:
                    return value["lvl_id"]

        return -1

    # returns the stage and episode name when given a lvl_id value
    def get_name(self, id: int) -> tuple:
        for st_name, sub_dict in self.level_data.items():
            for ep_name, value in sub_dict.items():
                if id == value["lvl_id"]:
                    return st_name, ep_name
                    
        return "", ""

if __name__ == '__main__':
    l = LevelData()
    print(l.get_episode_options())