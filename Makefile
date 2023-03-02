data:
	./get_data.sh

build:
	g++ -std=c++11 src/cpp/*.cpp -o cleaner
