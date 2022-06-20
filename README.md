# Kinect2Grabber
Kinect2 data grabber, writer, reader

Installation of software required

-	Qt version
http://download.qt.io/new_archive/qt/5.7/5.7.0/qt-opensource-windows-x86-winrt-msvc2013-5.7.0.exe

-	MSVC 2013 (v12) (google search)

-	Kinect 2 SDK (google search)

-	NO installation of OpenCV or other 3rd party libs required, custom built versions are contained in the project folder


Toolchain, settings in Qt, and system path variable

-	Compiler settings: MSVC compiler 2013, v12, x64 build
-	3rd party libs: 
o	OpenCV 3.2 with contrib package:
Binaries are in ./bin (DO NOT DELETE THEM!) (hence, no update of PATH variable necessary)
Libs and includepath for headers are included in opencv32_contrib_vc12.pri
o	VTK v7.1.1 library:
Binaries in .\3rdParty\VTK7.1.1 (required by VIZ module of the OpenCV contrib package)
Add .\3rdParty\VTK7.1.1\bin to PATH variable
o	mkinect 2 lib:
Binaries are installed when installing the mkinect 2 SDK
Libs and includepath for headers are included in mkinect2.pri