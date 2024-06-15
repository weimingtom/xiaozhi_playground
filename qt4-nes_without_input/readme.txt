solve: use host ar to replace *-ar
cp -r ../linux-arm-gnueabihf-g++ ./mkspecs/.

./configure -static -opensource -embedded generic
-xplatform linux-arm-gnueabihf-g++
--prefix=/opt/qt
-confirm-license
-nomake demos -nomake examples -nomake docs
-no-opengl -no-webkit 
-no-openssl -no-javascript-jit

make -j4
reinterpret_cast<int32_t>-><int64_t>

sudo chown wmt:wmt /opt
make install

cd examples/wigets/digitalclock
rm Makefile
/opt/qt/bin/qmake digitalclock.pro
make





NesScreenWidget.cpp
#define USE_ORIGIN_SIZE 1


adb pull /etc/init.d/S20app
chmod +x /etc/init.d/S20app

