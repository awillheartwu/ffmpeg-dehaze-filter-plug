CXXFLAGS := -std=c++11 -O2 -fPIC -Wall -shared
LFLAGS := -lopencv_core -lopencv_highgui -lopencv_imgproc -lm

INSTALL=install

all: libdehaze

libdehaze:
	g++ guidedfilter.cpp dehazor.cpp c_dehaze.cpp -o libdehaze.so $(CXXFLAGS) $(LFLAGS) 

clean:
	rm libdehaze.so -f

install:
	$(INSTALL) -m 644 libdehaze.so /usr/local/lib
	$(INSTALL) -m 644 c_dehaze.h /usr/local/include
	$(INSTALL) -m 644 dehaze.pc /usr/local/lib/pkgconfig

recomp : clean all
