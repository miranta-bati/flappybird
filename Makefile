
all: flaby
	./flaby 

flaby: *.cpp 
	g++ -Wall *.cpp -o flaby -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

clean: 
	rm -r flaby

install dependencies:
	apt update
	apt install make g++ libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
