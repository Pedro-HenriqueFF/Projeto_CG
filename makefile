all:
	gcc main.c -o main.exe -lopengl32 -lglu32 -lfreeglut
	.\main.exe