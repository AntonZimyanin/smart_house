rm -rf build
cmake . -B build
cd build
make
cp ~/smart_house/src/Utils/m.wav ~/smart_house/build/m.wav 
./smart_house
