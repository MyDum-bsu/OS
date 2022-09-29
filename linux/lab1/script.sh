g++ -c -o trash/number.o number/number.cpp
ar rcs trash/libnumber.a trash/number.o

g++ -fpic -c -o trash/vector.o vector/vector.cpp -B static -L trash -lnumber
g++ -shared -o trash/libvector.so trash/vector.o

export LD_LIBRARY_PATH="trash"
g++ -o trash/oao.out dungeon_master/dungeon_master.cpp -B dynamic -L trash -lvector -B static -L trash -lnumber
./trash/oao.out

