from devkit_tools import Project 
#from dol_c_kit import Project 
from doltools import write_lis, write_ori

import os
import sys
old_stdout = sys.stdout # backup current stdout
#sys.stdout = open(os.devnull, "w")



def patch_osarena_low(dol, size):
    #800eb370
    size += 0x50 # i want to have some padding to have variables initialized as 0 (doesn't work without padding)
    dol.seek(0x80341eac) # OSinit before calling OSSetarenalo
    write_lis(dol, 3, size >> 16, signed=False)
    write_ori(dol, 3, 3, size & 0xFFFF)
    
    dol.seek(0x80341e74) # also OSInit 
    write_lis(dol, 3, size >> 16, signed=False) 
    write_ori(dol, 3, 3, size & 0xFFFF)
    
    print("New size", hex(size))

p = Project("main.dol", address=0x80430000) # actually smaller
p.set_osarena_patcher(patch_osarena_low)

p.add_file("../source/createMarios.c")
p.add_file("../source/sounds.c")
p.add_file("../source/misc.c")
p.add_file("../source/customModels.c")
p.add_file("../source/tag.c")
p.add_file("../source/fludd.c")
p.add_file("../source/yoshi.c")
p.add_file("../source/marioInteraction.c")
p.add_file("../source/manhunt.c")
#p.add_file("../source/spectate.c")

p.add_linker_file("../galaxySymbols.txt")
p.apply_gecko("extraCode.txt")

p.branchlink(0x8029d7f8, "makeMarios")
p.branch(0x80276bd0, "load_MarioTrickyOverhaul")

#p.branch(0x80252bac, "spectateMode")

p.branch(0x8024fee0, "sounds")
p.branchlink(0x802853D4, "soundFixOne")
p.branchlink(0x8028581C, "soundFixTwo")
p.branchlink(0x80285858, "soundFixThree")
p.branch(0x80287340, "soundFixFour")
p.branchlink(0x80285350, "soundFixFive")
p.branchlink(0x8031b74c, "setMusicVolume")
p.branchlink(0x8031b750, "volumeAsmRestore")

p.branch(0x8024192c, "updateSeconds")
p.branchlink(0x80265c08, "sleepFix")
p.branch(0x8029922c, "stageChange")
p.branchlink(0x80250514, "movingObjectsFix")
p.branch(0x8024DF68, "dummyFix1")
p.branch(0x8024DF24, "dummyFix2")
p.branch(0x80251C84, "dummyFix3")
p.branch(0x8025BB3C, "dummyFix4")
p.branch(0x80251DEC, "dummyFix5")
p.branch(0x80251DE0, "dummyFix6")
p.branch(0x80251494, "dummyFix7")
p.branch(0x80243568, "dummyFix8")
p.branch(0x8024e5e0, "dummyFix9")
p.branch(0x8026595c, "dummyFix10")
p.branch(0x80244f88, "dummyFix11")
p.branch(0x80265a38, "dummyFix12")
p.branch(0x80265ad8, "dummyFix13")
p.branch(0x802541D4, "dummyFix14")
p.branch(0x8024bf2c, "dummyFix15")
p.branch(0x8024c244, "dummyFix16")
p.branch(0x80257498, "stopPosUpdate1")
p.branch(0x80256790, "stopPosUpdate2")
p.branch(0x80244e70, "updateFlags")
p.branchlink(0x801482d8, "allowShineDecrement")
p.branchlink(0x801475c0, "allowBlueDecrement")

p.branch(0x8024dfb4, "yoshi1")
p.branch(0x8026ed2c, "yoshi2")
p.branch(0x8026f500, "yoshi3")
p.branch(0x8026ffc0, "yoshi4")
p.branch(0x80270028, "yoshi5")
p.branch(0x8026f5e8, "yoshi6")
p.branch(0x8026f5d8, "yoshi7")
p.branch(0x8024E364, "yoshi8")
p.branch(0x8026F454, "yoshi9")
p.branch(0x80270470, "yoshi10")

p.branch(0x8027fd74, "fluddId1")
p.branch(0x8027eb10, "fluddId2")
#p.branch(0x8026d204, "fluddAngle1")
#p.branch(0x8026d13c, "fluddAngle2")
p.branch(0x8026c370, "spamSpray1")
p.branch(0x8026c6b0, "spamSpray2")
p.branch(0x8026c3b8, "spamSpray3")
p.branch(0x8026d164, "sideStepFluddAng")

p.branchlink(0x80243574, "isTakeSituation_Mario")
p.branchlink(0x8021bfb4, "marioHitActors")
p.branchlink(0x8021c024, "marioHitActors")
p.branch(0x80281b14, "headJump1")
p.branch(0x80243324, "headJump2")
p.branch(0x80282644, "headJump3")

p.branch(0x80252bac, "tagMain")
p.branchlink(0x8014b140, "setTimerSetup")
p.branchlink(0x80148414, "addPreviousTime")
#p.branch(0x8028aee4, "killMarioCheck")
p.branchlink(0x802997bc, "tagRespawnStage")
p.branchlink(0x802997c4, "tagRespawnEpisode")
p.branchlink(0x80299438, "tagRespawnStageSecret")
p.branchlink(0x8029944c, "tagRespawnEpisodeSecret")
p.branch(0x8029483c, "freezeLives")
p.branch(0x80298bac, "onChangeStage")

p.branchlink(0x802465e8, "mdl1")
p.branchlink(0x802421bc, "cap1")
p.branchlink(0x80242290, "cap3")
p.branchlink(0x802423f0, "glass1")
p.branchlink(0x80233e20, "hands")
p.branchlink(0x80246744, "handBranchOne")
p.branchlink(0x80246754, "handBranchTwo")
p.branchlink(0x80246764, "handBranchThree")
p.branchlink(0x80246774, "handBranchFour")
p.branchlink(0x80246784, "handBranchFive")
p.branch(0x802320E0, "customModelFix1")
p.branch(0x802DDB14, "customModelFix2")
p.branch(0x802dd838, "customModelFix3")

p.branchlink(0x8024e2a0, "checkForTagger")
p.branch(0x8024e744, "checkForTagger_Restore")
p.branchlink(0x8028319c, "stopRefill29")
p.branchlink(0x80283010, "stopRefill29")
p.branchlink(0x8028324c, "stopRefill29")
p.branchlink(0x802830ec, "stopRefill29")
p.branchlink(0x80282ea0, "stopRefill29")
p.branchlink(0x80282e2c, "stopRefill29")
#p.branchlink(0x80269ed0, "stopRefill30")
p.branchlink(0x802821a8, "stopRefill30")
#p.branchlink(0x8026a23c, "stopRefill31")
#p.branchlink(0x8026a284, "stopRefill31")
#p.branchlink(0x8024ec2c, "stopRefill31")

p.branch(0x80253220, "manhuntMain")

with open(".\\dol_path.txt", "r") as f:
    dol_path = f.readline()

p.build(dol_path)

