#include "Core.h"
#include "StudentPlayground/StudentPlayground.h"
// Constructor
CCore::CCore()
{    
}

// Destructor
CCore::~CCore()
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////
///
///
///  Run the Kinect2
///
///
void CCore::runKinect2(void)
{
    CCoreGui kinect2Gui;
    CKinect2Grabber kinect2;
    myClass exampleMyClass;

    // Create Window for RAW skeleton data
    cv::viz::Viz3d skeletonViewer;
    skeletonViewer = cv::viz::Viz3d( "Skeleton" );
    skeletonViewer.showWidget( "CoordinateSystem", cv::viz::WCameraPosition::WCameraPosition( 0.5 ) );

    // Create Window for NORMALIZED skeleton data
    cv::viz::Viz3d skeletonNormViewer;
    skeletonNormViewer = cv::viz::Viz3d( "NORM Skeleton" );
    skeletonNormViewer.showWidget( "CoordinateSystem", cv::viz::WCameraPosition::WCameraPosition( 0.5 ) );


    ///////////////////////////////////////////////////////////////////////////////////////////
    ///
    /// ENDLESS PROCESSING LOOP KINECT 2
    ///
    while(true)
    {

        ///////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// Retrieve current GUI state (kinect2Gui.mGuiState) fro Kinect2
        kinect2Gui.run();
        ///
        /// Grab RGBD data from Kinect2
        kinect2.run(kinect2Gui.getGuiState(), mRGBD);
// test
//        if (kinect2Gui.getGuiState().mIsKinect2Grab == true)
//        {
//            cv::imshow("test", mRGBD.mColorMat);
//        }
        ///
        ///////////////////////////////////////////////////////////////////////////////////////////


        ///////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// Normalize skeleton data
        if (mRGBD.mSkeletonMat.data != NULL)
        {
            // Convert skeleton joint points from RGBD data container (e.g. from Kienct2)
            std::vector<cv::Point3f> skeletonDataVec = mRGBD.cvt2SkeletonVector();

            // Show 3D Skeleton
            cv::viz::WCloud skeletonCloud( skeletonDataVec );
            skeletonCloud.setRenderingProperty(cv::viz::POINT_SIZE, 3.0);            
            skeletonViewer.showWidget( "Skeleton", skeletonCloud );
            skeletonViewer.spinOnce();

            // Normalize 3D Skeleton
            NTU ntuProcessor;
            std::vector<cv::Point3f> skeletonDataNormVec = ntuProcessor.normalizeSkeleton(skeletonDataVec)            ;

            // Show NORMALIZED 3D Skeleton
            cv::viz::WCloud skeletonNormCloud( skeletonDataNormVec );
            skeletonNormCloud.setRenderingProperty(cv::viz::POINT_SIZE, 3.0);
            skeletonNormViewer.showWidget( "Skeleton", skeletonNormCloud );
            skeletonNormViewer.spinOnce();
        }



        ///////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// Here comes your part!
        /// --> mRGBD contains the data!
        exampleMyClass.run(mRGBD);
        ///
        ///////////////////////////////////////////////////////////////////////////////////////////


        ///////////////////////////////////////////////////////////////////////////////////////////
        ///
        /// Check if ESC key was pressed
        ///
        if (cv::waitKey(10) == 27) { break; }
        ///
        ///
        ///////////////////////////////////////////////////////////////////////////////////////////

    }
    ///
    ///
    ///////////////////////////////////////////////////////////////////////////////////////////

}


///////////////////////////////////////////////////////////////////////////////////////////////////
///
///
///  Run the NTU data reader
///
///
void CCore::runReadNTUdata(void)
{
    //myClass exampleMyClass;
   // exampleMyClass.run(mRGBD);

    // Create Window for RAW skeleton data
    cv::viz::Viz3d skeletonViewer;
    skeletonViewer = cv::viz::Viz3d( "Skeleton" );
    skeletonViewer.showWidget( "CoordinateSystem", cv::viz::WCameraPosition::WCameraPosition( 0.5 ) );
    // Create Window for NORMALIZED skeleton data
    cv::viz::Viz3d skeletonNormViewer;
    skeletonNormViewer = cv::viz::Viz3d( "NORM Skeleton" );
    skeletonNormViewer.showWidget( "CoordinateSystem", cv::viz::WCameraPosition::WCameraPosition( 0.5 ) );


    // filepath of skeleton data file
    std::string filePathSkeleton("C:\\Ntudataset\\nturgbd_skeletons_s001_to_s017\\nturgb+d_skeletons\\S001C001P001R001A001.skeleton");

    NTU ntuProcessor;
    int nFrames = ntuProcessor.openSkeletonFile(filePathSkeleton);
    if (nFrames>0)
    {
        // For each frame
        //
        for (int iFrame=0; iFrame<nFrames; iFrame++)
        {
            // Grab 3D Skeleton from NTU skeleton file
            std::vector<cv::Point3f> skeletonDataVec = ntuProcessor.getSkeletonFrame();

            // Show 3D Skeleton
            cv::viz::WCloud skeletonCloud( skeletonDataVec );
            skeletonCloud.setRenderingProperty(cv::viz::POINT_SIZE, 3.0);
            skeletonViewer.showWidget( "Skeleton", skeletonCloud );
            skeletonViewer.spinOnce();

            // Normalize 3D Skeleton
            std::vector<cv::Point3f> skeletonDataNormVec = ntuProcessor.normalizeSkeleton(skeletonDataVec);

            // Show NORMALIZED 3D Skeleton
            cv::viz::WCloud skeletonNormCloud( skeletonDataNormVec );
            skeletonNormCloud.setRenderingProperty(cv::viz::POINT_SIZE, 3.0);
            skeletonNormViewer.showWidget( "Skeleton", skeletonNormCloud );
            skeletonNormViewer.spinOnce();

            cv::waitKey();
        }

        ntuProcessor.closeSkeletonFile();
    }

}



// Run the NTU reader
void CCore::runCvtNTUSkeleton2CSV(void)
{
    std::string pathStr = "C:\\Ntudataset\\Edgeimpluse\\A043\\*";
//    std::string pathStr = "C:\\Ntudataset\\Edgeimpluse\\A043\\*";
    std::string prefix("A043.");
    int minNumFrames = 50; // with
    NTU ntuProcessor;
    ntuProcessor.cvtSkeleton2CSV(pathStr, prefix, minNumFrames);
}
