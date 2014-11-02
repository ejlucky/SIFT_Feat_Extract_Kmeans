#include <DetectionBasedTracker_jni.h>
#include <opencv2/core/core.hpp>
#include <opencv2/contrib/detection_based_tracker.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/nonfree/features2d.hpp>
#include <opencv/cv.h>

#include <string>
#include <vector>

#include <android/log.h>

#define LOG_TAG "FaceDetection/DetectionBasedTracker"
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))

using namespace std;
using namespace cv;

inline void vector_Rect_to_Mat(vector<Rect>& v_rect, Mat& mat)
{
    mat = Mat(v_rect, true);
}

JNIEXPORT jlong JNICALL Java_org_opencv_samples_facedetect_DetectionBasedTracker_nativeCreateObject
(JNIEnv * jenv, jclass, jstring jFileName, jint faceSize)
{
    LOGD("Java_org_opencv_samples_facedetect_DetectionBasedTracker_nativeCreateObject enter");
    const char* jnamestr = jenv->GetStringUTFChars(jFileName, NULL);
    string stdFileName(jnamestr);
    jlong result = 0;

    try
    {
        DetectionBasedTracker::Parameters DetectorParams;
        if (faceSize > 0)
            DetectorParams.minObjectSize = faceSize;
        result = (jlong)new DetectionBasedTracker(stdFileName, DetectorParams);
    }
    catch(cv::Exception& e)
    {
        LOGD("nativeCreateObject caught cv::Exception: %s", e.what());
        jclass je = jenv->FindClass("org/opencv/core/CvException");
        if(!je)
            je = jenv->FindClass("java/lang/Exception");
        jenv->ThrowNew(je, e.what());
    }
    catch (...)
    {
        LOGD("nativeCreateObject caught unknown exception");
        jclass je = jenv->FindClass("java/lang/Exception");
        jenv->ThrowNew(je, "Unknown exception in JNI code of DetectionBasedTracker.nativeCreateObject()");
        return 0;
    }

    LOGD("Java_org_opencv_samples_facedetect_DetectionBasedTracker_nativeCreateObject exit");
    return result;
}

JNIEXPORT void JNICALL Java_org_opencv_samples_facedetect_DetectionBasedTracker_nativeDestroyObject
(JNIEnv * jenv, jclass, jlong thiz)
{
    LOGD("Java_org_opencv_samples_facedetect_DetectionBasedTracker_nativeDestroyObject enter");
    try
    {
        if(thiz != 0)
        {
            ((DetectionBasedTracker*)thiz)->stop();
            delete (DetectionBasedTracker*)thiz;
        }
    }
    catch(cv::Exception& e)
    {
        LOGD("nativeestroyObject caught cv::Exception: %s", e.what());
        jclass je = jenv->FindClass("org/opencv/core/CvException");
        if(!je)
            je = jenv->FindClass("java/lang/Exception");
        jenv->ThrowNew(je, e.what());
    }
    catch (...)
    {
        LOGD("nativeDestroyObject caught unknown exception");
        jclass je = jenv->FindClass("java/lang/Exception");
        jenv->ThrowNew(je, "Unknown exception in JNI code of DetectionBasedTracker.nativeDestroyObject()");
    }
    LOGD("Java_org_opencv_samples_facedetect_DetectionBasedTracker_nativeDestroyObject exit");
}

JNIEXPORT void JNICALL Java_org_opencv_samples_facedetect_DetectionBasedTracker_nativeStart
(JNIEnv * jenv, jclass, jlong thiz)
{
    LOGD("Java_org_opencv_samples_facedetect_DetectionBasedTracker_nativeStart enter");
    try
    {
        ((DetectionBasedTracker*)thiz)->run();
    }
    catch(cv::Exception& e)
    {
        LOGD("nativeStart caught cv::Exception: %s", e.what());
        jclass je = jenv->FindClass("org/opencv/core/CvException");
        if(!je)
            je = jenv->FindClass("java/lang/Exception");
        jenv->ThrowNew(je, e.what());
    }
    catch (...)
    {
        LOGD("nativeStart caught unknown exception");
        jclass je = jenv->FindClass("java/lang/Exception");
        jenv->ThrowNew(je, "Unknown exception in JNI code of DetectionBasedTracker.nativeStart()");
    }
    LOGD("Java_org_opencv_samples_facedetect_DetectionBasedTracker_nativeStart exit");
}

JNIEXPORT void JNICALL Java_org_opencv_samples_facedetect_DetectionBasedTracker_nativeStop
(JNIEnv * jenv, jclass, jlong thiz)
{
    LOGD("Java_org_opencv_samples_facedetect_DetectionBasedTracker_nativeStop enter");
    try
    {
        ((DetectionBasedTracker*)thiz)->stop();
    }
    catch(cv::Exception& e)
    {
        LOGD("nativeStop caught cv::Exception: %s", e.what());
        jclass je = jenv->FindClass("org/opencv/core/CvException");
        if(!je)
            je = jenv->FindClass("java/lang/Exception");
        jenv->ThrowNew(je, e.what());
    }
    catch (...)
    {
        LOGD("nativeStop caught unknown exception");
        jclass je = jenv->FindClass("java/lang/Exception");
        jenv->ThrowNew(je, "Unknown exception in JNI code of DetectionBasedTracker.nativeStop()");
    }
    LOGD("Java_org_opencv_samples_facedetect_DetectionBasedTracker_nativeStop exit");
}

JNIEXPORT void JNICALL Java_org_opencv_samples_facedetect_DetectionBasedTracker_nativeSetFaceSize
(JNIEnv * jenv, jclass, jlong thiz, jint faceSize)
{
    LOGD("Java_org_opencv_samples_facedetect_DetectionBasedTracker_nativeSetFaceSize enter");
    try
    {
        if (faceSize > 0)
        {
            DetectionBasedTracker::Parameters DetectorParams = \
            ((DetectionBasedTracker*)thiz)->getParameters();
            DetectorParams.minObjectSize = faceSize;
            ((DetectionBasedTracker*)thiz)->setParameters(DetectorParams);
        }
    }
    catch(cv::Exception& e)
    {
        LOGD("nativeStop caught cv::Exception: %s", e.what());
        jclass je = jenv->FindClass("org/opencv/core/CvException");
        if(!je)
            je = jenv->FindClass("java/lang/Exception");
        jenv->ThrowNew(je, e.what());
    }
    catch (...)
    {
        LOGD("nativeSetFaceSize caught unknown exception");
        jclass je = jenv->FindClass("java/lang/Exception");
        jenv->ThrowNew(je, "Unknown exception in JNI code of DetectionBasedTracker.nativeSetFaceSize()");
    }
    LOGD("Java_org_opencv_samples_facedetect_DetectionBasedTracker_nativeSetFaceSize exit");
}

JNIEXPORT void JNICALL Java_org_opencv_samples_facedetect_DetectionBasedTracker_bilatSingleGray
(JNIEnv * jenv, jclass, jlong thiz, jlong imageGray, jstring jFileName1, jstring jFileName2)
{
	LOGD("Java_org_opencv_samples_facedetect_DetectionBasedTracker_bilatSingleGray enter");
    const char* jnamestr1 = jenv->GetStringUTFChars(jFileName1, NULL);
    string stdFileNamePre(jnamestr1);
    const char* jnamestr2 = jenv->GetStringUTFChars(jFileName2, NULL);
    string stdFileNamePost(jnamestr2);

	Mat& image = *(Mat*) imageGray;
	// Single image denoising
	// For now, I'm assuming that the input is actually a 1-channel grayscale
	// Need to come up with method for checking if input image is single-channel
	int filt_size  = 7;
	int center     = ceil(filt_size/2)-1;
	int pad_ind    = floor(filt_size/2);	// Set initial parameters
	float sigma_d = 3;
	float sigma_i  = 0.15;

	Mat pix_center = (Mat_<int>(1,2) << center,center);
	Mat g_weight_mat;
	g_weight_mat.create(filt_size,filt_size,CV_32F);
	Mat pix; // Initialize parameters and matrices for distance weighting

	Mat g_dist_mat;
	g_dist_mat.create(filt_size,filt_size,CV_32F);
	for(int i = 0; i < filt_size; i++)
	{
		for(int j = 0; j < filt_size; j++)
		{
			pix = (Mat_<int>(1,2) << i,j);
			g_weight_mat.at<float>(i,j) = norm(pix_center-pix);
			g_dist_mat.at<float>(i,j) = exp(-pow((float)g_weight_mat.at<float>(i,j),2)/(2*pow(sigma_d,2)));
		}
	}	// Calculate distance weighting (Same process as in MATLAB)
	Mat padded_image;
	copyMakeBorder(image, padded_image, pad_ind, pad_ind, pad_ind, pad_ind, BORDER_REPLICATE, 1);	// Pad matrix
	unsigned int rows = image.rows;
	unsigned int cols = image.cols;
	Mat intensity_mat;
	intensity_mat.create(filt_size,filt_size,CV_32FC1);
	Mat intensity_mat1;
	intensity_mat1.create(filt_size,filt_size,CV_32FC1);
	Mat g_int_mat;
	g_int_mat.create(filt_size,filt_size,CV_32FC1);
	Mat bilateral_weights;
	bilateral_weights.create(filt_size,filt_size,CV_32FC1);
	Mat output_image;
	output_image.create(rows+(2*pad_ind),cols+(2*pad_ind),CV_8UC1);
	Mat temp;	// Initialize matrices for intensity weighting calculations
	for(int i = pad_ind; i < padded_image.rows-pad_ind; i++)
	{
		for(int j = pad_ind; j < padded_image.cols-pad_ind; j++)
		{
			intensity_mat  = padded_image(Range(i-pad_ind,i+pad_ind+1),Range(j-pad_ind,j+pad_ind+1));
			intensity_mat.convertTo(intensity_mat,CV_32FC1);
			intensity_mat1 = intensity_mat-intensity_mat.at<float>(center,center);
			intensity_mat1 = abs(intensity_mat1);
			pow(intensity_mat1,2,intensity_mat1);
			intensity_mat1 = -intensity_mat1 / (2*pow(sigma_i,2));
			for(int m = 0; m < filt_size; m++)
			{
				for(int n = 0; n < filt_size; n++)
				{
					g_int_mat.at<float>(m,n) = exp(intensity_mat1.at<float>(m,n));
				}
			}
			temp = g_dist_mat.mul(g_int_mat);
			bilateral_weights = temp/(cv::sum(temp)[0]);	// Calculate total weighting
			temp = bilateral_weights.mul(intensity_mat);
			temp.convertTo(temp,CV_8UC1);
			output_image.at<unsigned char>(i,j) = (unsigned char)(cv::sum(temp)[0]);
		}
	}
	output_image = output_image(Range(pad_ind,rows-pad_ind-1),Range(pad_ind,cols-pad_ind-1));	// Remove padding
	LOGD("ELUCKETT save input and output");
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
	compression_params.push_back(95);
	imwrite(stdFileNamePre,image,compression_params);
	imwrite(stdFileNamePost,output_image,compression_params);
	LOGD("ELUCKETT images saved");

	LOGD("Java_org_opencv_samples_facedetect_DetectionBasedTracker_bilatSingleGray exit");
}

JNIEXPORT void JNICALL Java_org_opencv_samples_facedetect_DetectionBasedTracker_bilatMultiGray
(JNIEnv * jenv, jclass, jlong thiz, jlong imageGray1, jlong imageGray2, jlong imageGray3, jlong imageGray4, jlong imageGray5, jstring jFileName1, jstring jFileName2)
{
	LOGD("Java_org_opencv_samples_facedetect_DetectionBasedTracker_bilatMultiGray enter");
    const char* jnamestr1 = jenv->GetStringUTFChars(jFileName1, NULL);
    string stdFileNamePre(jnamestr1);
    const char* jnamestr2 = jenv->GetStringUTFChars(jFileName2, NULL);
    string stdFileNamePost(jnamestr2);

    Mat& image1 = *(Mat*) imageGray1;
    Mat& image2 = *(Mat*) imageGray2;
    Mat& image3 = *(Mat*) imageGray3;
    Mat& image4 = *(Mat*) imageGray4;
    Mat& image5 = *(Mat*) imageGray5;

    //Vector<Mat> in_images;
    Mat image[5];
    image[0] = image1;
    image[1] = image2;
    image[2] = image3;
    image[3] = image4;
    image[4] = image5;
    /*
    in_images.push_back(image1);
    in_images.push_back(image2);
    in_images.push_back(image3);
    in_images.push_back(image4);
    in_images.push_back(image5);
    */
    //Mat image;
    //merge(in_images, image);
    //merge(in_images,5, image);

	// Multi image denoising
	// For now, I'm assuming that the input is actually a 5-channel grayscale (each channel being an image)
	int filt_size  = 7;
	int center     = ceil(filt_size/2)-1;
	int pad_ind    = floor(filt_size/2);
	float sigma_d = 3;
	float sigma_i  = 0.15;	// Set initial parameters

	// Generate distance weights
	Mat pix_center = (Mat_<int>(1,3) << center,center,2);
	Mat pix; // Initialize parameters and matrices for distance weighting
	/*Mat g_weight_mat;
	g_weight_mat.create(filt_size,filt_size, CV_32FC(5));
	Mat g_dist_mat;
	g_dist_mat.create(filt_size,filt_size, CV_32FC(5));*/
	Mat temp;	// Initialize matrices for intensity weighting calculations
	temp.create(filt_size,filt_size, CV_32F);
	Mat g_weight_mat[5];
	Mat g_dist_mat[5];
	for(int q = 0; q < 5; q++)
	{
		g_weight_mat[q] = temp;
		g_dist_mat[q] = temp;
	}

	for(int m = 0; m < 5; m++)
	{
		for(int i = 0; i < filt_size; i++)
		{
			for(int j = 0; j < filt_size; j++)
			{
				pix = (Mat_<int>(1,3) << i,j,m);
				//g_weight_mat(i,j,m) = norm(pix_center-pix);
				g_weight_mat[m].at<float>(i,j) = norm(pix_center-pix);
				g_dist_mat[m].at<float>(i,j) = exp(-pow((float)g_weight_mat[m].at<float>(i,j),2)/(2*pow(sigma_d,2)));
			}
		}	// Calculate distance weighting (Same process as in Matlab)
	}

	// Generate intensity weights
	Mat padded_image[5];
	Mat intensity_mat[5];
	Mat intensity_mat1[5];
	Mat g_int_mat[5];
	Mat bilateral_weights[5];
	for(int q = 0; q < 5; q++)
	{
		copyMakeBorder(image[q], padded_image[q], pad_ind, pad_ind, pad_ind, pad_ind, BORDER_REPLICATE, 1);	// Pad matrix
		intensity_mat[q].create(filt_size,filt_size, CV_32F);
		intensity_mat1[q].create(filt_size,filt_size, CV_32F);
		g_int_mat[q].create(filt_size,filt_size, CV_32F);
		bilateral_weights[q].create(filt_size,filt_size, CV_32F);
	}

	int rows = image[0].rows;
	int cols = image[0].cols;

	Mat output_image;
	output_image = Mat::zeros(rows+(2*pad_ind),cols+(2*pad_ind),CV_8U);
	Mat temp1[5];	// Initialize matrices for intensity weighting calculations
	int temp_sum;
	for(int i = pad_ind; i < padded_image[0].rows-pad_ind; i++)
	{
		for(int j = pad_ind; j < padded_image[0].cols-pad_ind; j++)
		{
			for(int q = 0; q < 5; q++)
			{
				intensity_mat[q]  = padded_image[q](Range(i-pad_ind,i+pad_ind+1),Range(j-pad_ind,j+pad_ind+1));
				intensity_mat[q].convertTo(intensity_mat[q],CV_32F);
			}


			for(int q = 0; q < 5; q++)
			{
				intensity_mat1[q] = intensity_mat[q]-intensity_mat[2].at<float>(center,center);
				intensity_mat1[q] = abs(intensity_mat1[q]);
				pow(intensity_mat1[q],2,intensity_mat1[q]);
				intensity_mat1[q] = -intensity_mat1[q] / (2*pow(sigma_i,2));
			}




			for(int m = 0; m < filt_size; m++)
			{
				for(int n = 0; n < filt_size; n++)
				{
					g_int_mat[0].at<float>(m,n) = exp((float)intensity_mat1[0].at<float>(m,n));
					g_int_mat[1].at<float>(m,n) = exp((float)intensity_mat1[1].at<float>(m,n));
					g_int_mat[2].at<float>(m,n) = exp((float)intensity_mat1[2].at<float>(m,n));
					g_int_mat[3].at<float>(m,n) = exp((float)intensity_mat1[3].at<float>(m,n));
					g_int_mat[4].at<float>(m,n) = exp((float)intensity_mat1[4].at<float>(m,n));

				}
			}
			//temp = g_dist_mat.mul(g_int_mat);
			for(int q = 0; q < 5; q++)
			{
				temp1[q] = g_dist_mat[q].mul(g_int_mat[q]);

			}
			for(int q = 0; q < 5; q++)
			{
				bilateral_weights[q] = temp1[q]/(cv::sum(temp1[0])[0] + cv::sum(temp1[1])[0] + cv::sum(temp1[2])[0] + cv::sum(temp1[3])[0] + cv::sum(temp1[4])[0]);	// Calculate total weighting
				temp1[q] = bilateral_weights[q].mul(intensity_mat[q]);
				temp1[q].convertTo(temp,CV_8UC1);
			}

			//temp.convertTo(temp,CV_8UC1);
			temp_sum = cv::sum(temp1[0])[0] + cv::sum(temp1[1])[0] + cv::sum(temp1[2])[0] + cv::sum(temp1[3])[0] + cv::sum(temp1[4])[0];
			output_image.at<unsigned char>(i,j) = (unsigned char)temp_sum;
		}
	}
}

JNIEXPORT void JNICALL Java_org_opencv_samples_facedetect_DetectionBasedTracker_nativeDetect
(JNIEnv * jenv, jclass, jlong thiz, jlong imageGray, jlong faces)
{
    LOGD("Java_org_opencv_samples_facedetect_DetectionBasedTracker_nativeDetect enter");
    try
    {
        vector<Rect> RectFaces;
        ((DetectionBasedTracker*)thiz)->process(*((Mat*)imageGray));
        ((DetectionBasedTracker*)thiz)->getObjects(RectFaces);
        vector_Rect_to_Mat(RectFaces, *((Mat*)faces));
    }
    catch(cv::Exception& e)
    {
        LOGD("nativeCreateObject caught cv::Exception: %s", e.what());
        jclass je = jenv->FindClass("org/opencv/core/CvException");
        if(!je)
            je = jenv->FindClass("java/lang/Exception");
        jenv->ThrowNew(je, e.what());
    }
    catch (...)
    {
        LOGD("nativeDetect caught unknown exception");
        jclass je = jenv->FindClass("java/lang/Exception");
        jenv->ThrowNew(je, "Unknown exception in JNI code DetectionBasedTracker.nativeDetect()");
    }
    LOGD("Java_org_opencv_samples_facedetect_DetectionBasedTracker_nativeDetect exit");
}

JNIEXPORT void JNICALL Java_org_opencv_549_project_SIFT_extract_feat
(JNIEnv * jenv, jclass, jlong thiz, jlong im1, jlong * descriptors)
{
	Mat& image1 = *(Mat*) im1;
	unsigned int rows_old = image1.rows;
	unsigned int cols_old = image1.cols;
	unsigned int rows_new = rows_old/10;
	unsigned int cols_new = cols_old/10;
	Size size(rows_new,cols_new);
	Mat image1_scaled;
	resize(image1,image1_scaled,size);

	// Want 500 features to cluster into 50 classes
	SiftFeatureDetector detector(500,3,0.04,10,1.6);
	SiftDescriptorExtractor extractor;
	std::vector<cv::KeyPoint> keypoints;
	detector.detect(image1_scaled, keypoints);
	//Mat descriptors;
	extractor.compute(image1_scaled, keypoints, descriptors);
	//return (jlong *)descriptors;
}

JNIEXPORT void JNICALL Java_org_opencv_549_project_SIFT_class_cluster
(JNIEnv * jenv, jclass, jlong thiz, jlong class_num, jlong total_desc, jlong * centers)
{
	Mat labels/*, centers*/;
	kmeans(total_desc, class_num, labels, TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 50, 1.0),3, KMEANS_RANDOM_CENTERS, centers);
	//return (jlong *)centers;
}

