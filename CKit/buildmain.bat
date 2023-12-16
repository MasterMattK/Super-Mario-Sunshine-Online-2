@echo off
cd compiler
py mainproject.py

del project.o
del tmplink
rmdir tmp

py replace_var.py

cd..
cd source

del createMarios.c.o
del createMarios.c.s
del customModels.c.o
del customModels.c.s
del fludd.c.o
del fludd.c.s
del marioInteraction.c.o
del marioInteraction.c.s
del misc.c.o
del misc.c.s
del sounds.c.o
del sounds.c.s
del tag.c.o
del tag.c.s
del yoshi.c.o
del yoshi.c.s
del manhunt.c.o
del manhunt.c.s
del callbacks.c.o
del callbacks.c.s

pause