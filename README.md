libecw
======
     
     
     wget https://github.com/makinacorpus/libecw/archive/master.zip
     unzip master.zip -d ecw && cd ecw
     or git clone https://github.com/makinacorpus/libecw.git
     ./configure  CFLAGS="-O0" CXXFLAGS="-O0"  --enable-shared --enable-static --prefix=/usr && make && make install
