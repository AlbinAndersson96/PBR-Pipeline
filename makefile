run: * RenderEngine/* RenderEngine/Renderers/* Shaders/*
	g++ -c *.cpp RenderEngine/*.cpp RenderEngine/Renderers/*.cpp Shaders/*.cpp -lglfw -lGL -ldl -lm -lGLEW
	gcc -c -o c1.o Utilities/loadobj.c -lGL
	gcc -c -o c2.o Utilities/LoadTGA.c -lGL
	g++ -o run *.o -lGL -lGLEW -lglfw
	mv *.o run Build/
	cp -r Resources/ Build/
	cp -r Shaders/ Build/