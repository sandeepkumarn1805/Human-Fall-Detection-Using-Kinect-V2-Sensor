#include <iostream>
#include <sstream>

//#include "CoreGUI/CoreGui.h"
//#include "Kinect2Grabber.h"

#include "Core/Core.h"

using namespace std;

int main(int argc, char *argv[])
{
//    printf("argc: %d\n", argc);
//    for(int i=0; i < argc; i++)
//    {
//        printf("argv[%d]: %s\n", i, argv[i]);
//    }

    if (argc == 2)
    {
        long arg = strtol(argv[1], NULL, 10);
        try
        {
            CCore mainApp;
            switch (arg)
            {
            case 1:
                mainApp.runKinect2();
                break;
            case 2:
                mainApp.runReadNTUdata();
                break;
            case 3:
                mainApp.runCvtNTUSkeleton2CSV();
                break;
            }

        }
        catch( std::exception& ex )
        {
            std::cout << ex.what() << std::endl;
        }

    }
    return 0;
}
