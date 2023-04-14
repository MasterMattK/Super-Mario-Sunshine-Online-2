mapDir = "D:\\EVERYTHING\\Projects\\Multiplayer\\SMSO CKit\\compiler\\project.map"   # specify which directory the .map file is
scriptDir = "C:\\SMSO Dev\\Source\\Client\\InGameVars.py"   # specify which file the vars should be stored in. make sure it's a .py file so you can import it
varsToGet = [("gamemode", "GAMEMODE"), ("tagBool", "TAG_BOOL"), ("isTagger", "IS_TAGGER"), ("clientTagTime", "CLIENT_TAG_TIME"),  
	("connected", "CONNECTED"), ("marios", "MARIOS"), ("bmdPointers", "BMD_POINTERS"), ("modelIndex", "MODEL_INDEX"), ("musicVolume", "MUSIC_VOLUME"), 
	("fluddRefills", "FLUDD_REFILLS"), ("currentTime", "CURRENT_TIME"), ("flagToUpdate", "FLAG_TO_UPDATE"), ("bResetFlags", "RESET_FLAGS"),
	("tagReset", "TAG_RESET")]  # specify which var addresses to look for, and what to name them in the script

with open(mapDir) as m:
    mapLines = m.readlines()

with open(scriptDir, "w") as s:
	d = {}
	for line in mapLines:
		for var, upper_var in varsToGet:
			if line.endswith(var+"\n"):
				d[upper_var] = line.replace(" ", "").replace(var+"\n","")[-8:]

	s.write("class InGameVars:\n")
	for key, value in d.items():
		s.write(f"\t{key.upper()} = 0x{value}\n")