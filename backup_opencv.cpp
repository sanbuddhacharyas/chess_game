
#include "opencv.h"
#include "Blob.h"
#include <cmath>
#include <fstream>

float x[8][8]={0},y[8][8]={0};

void matrix_rotation()
{
	float temp =0;

	for (int i = 1;i <= 3;i++)
	{
		for (int j = i;j <= (7 - i);j++)
		{
			temp = x[i][j];
			x[i][j] = x[8 - j][i];
			x[8 - j][i] = x[8 - i][8 - j];
			x[8 - i][8 - j] = x[j][8 - i];
			x[j][8 - i] = temp;

			temp = y[i][j];
			y[i][j] = y[8 - j][i];
			y[8 - j][i] = y[8 - i][8 - j];
			y[8 - i][8 - j] = y[j][8 - i];
			y[j][8 - i] = temp;
		}
	}
}

void motion_detect(VideoCapture capVideo)
{
	Mat subtract_frame;
	Mat frame;
	Mat frame1;
	int count=0;
	int count1=0;
	Rect tocrop(2*x[1][1]-x[1][2]-15,2*y[1][1]-y[2][1]-15,((2*x[7][7]-x[7][6])-(2*x[1][1]-x[1][2]))+20,((2*y[7][7]-y[6][7])-(2*y[1][1]-y[2][1]))+20);
	capVideo.read(frame);
	frame = frame(tocrop);

	while(true)
		{
			frame1 = frame.clone();
			std::vector<Blob> blobs;
			cv::Mat imgThresh;
        	capVideo.read(frame);
			frame = frame(tocrop);
			cv::subtract(frame,frame1,subtract_frame);
			cv::cvtColor(subtract_frame, subtract_frame, CV_BGR2GRAY);
			cv::GaussianBlur(subtract_frame, subtract_frame, cv::Size(5, 5), 0);
			cv::threshold(subtract_frame, imgThresh, 60, 255.0, CV_THRESH_BINARY);
	
	
			cv::Mat structuringElement3x3 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
			cv::Mat structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
			cv::Mat structuringElement7x7 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
			cv::Mat structuringElement9x9 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9));

			cv::dilate(imgThresh, imgThresh, structuringElement5x5);
			cv::dilate(imgThresh, imgThresh, structuringElement5x5);
			cv::erode(imgThresh, imgThresh, structuringElement5x5);

			cv::Mat imgThreshCopy = imgThresh.clone();

			std::vector<std::vector<cv::Point> > contours;

			cv::findContours(imgThreshCopy, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);


			if(contours.size()>0)
			{
				count++;
			}
			
			if(count > 8 && contours.size()==0)
			{
				count1++;
				if(count1>16)
				{
					cout<<"count:"<<count<<"count1"<<count1<<endl;
					break;
				}
			}
			else
			{
				count1=0;

			}

			//cout<<"count:"<<count<<"count1:"<<count1<<endl;		
		}

}

bool Detect_moves(Mat imgFrame1,Mat imgFrame2,cv::Point &cent)
{
	bool ok=false;
	int threshold = 70;
	int c =0;

	std::vector<Blob> blobs;

	//cv::Mat imgFrame1Copy = imgFrame1.clone();
	//cv::Mat imgFrame2Copy = imgFrame2.clone();

	//Rect tocrop(2*x[1][1]-x[1][2]-15,2*y[1][1]-y[2][1]-15,((2*x[7][7]-x[7][6])-(2*x[1][1]-x[1][2]))+20,((2*y[7][7]-y[6][7])-(2*y[1][1]-y[2][1]))+20);
	//imgFrame1 = imgFrame1(tocrop);
	//imgFrame2 = imgFrame2(tocrop);

	cv::Mat imgDifference;
	cv::Mat imgThresh;
	cv::Mat imgDifference_shadow;


	cv::subtract(imgFrame1, imgFrame2, imgDifference);
//	imshow("subtractimage",imgDifference);
	

	//cv::subtract(imgFrame3,imgDifference,imgDifference_shadow);
	//imshow("Shadow_removed",imgDifference_shadow);


	cv::cvtColor(imgDifference, imgDifference, CV_BGR2GRAY);



	//cv::cvtColor(imgFrame1Copy, imgFrame1Copy, CV_BGR2GRAY);
	//cv::cvtColor(imgFrame2Copy, imgFrame2Copy, CV_BGR2GRAY);

	cv::GaussianBlur(imgDifference, imgDifference, cv::Size(5, 5), 0);
	//cv::GaussianBlur(imgFrame2Copy, imgFrame2Copy, cv::Size(5, 5), 0);

	while(!ok)
	{
		cv::threshold(imgDifference, imgThresh,threshold , 255.0, CV_THRESH_BINARY);

		//cv::imshow("imgThresh", imgThresh);

		cv::Mat structuringElement3x3 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
		cv::Mat structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
		cv::Mat structuringElement7x7 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
		cv::Mat structuringElement9x9 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9));

		cv::dilate(imgThresh, imgThresh, structuringElement5x5);
		cv::dilate(imgThresh, imgThresh, structuringElement5x5);
		cv::erode(imgThresh, imgThresh, structuringElement5x5);

		cv::Mat imgThreshCopy = imgThresh.clone();

		std::vector<std::vector<cv::Point> > contours;

		cv::findContours(imgThreshCopy, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

		cv::Mat imgContours(imgThresh.size(), CV_8UC3, SCALAR_BLACK);

		cv::drawContours(imgContours, contours, -1, SCALAR_WHITE, -1);
		if(contours.size()==0)
		{
			return false;
		}

	//	cv::imshow("imgContours", imgContours);

		std::vector<std::vector<cv::Point> > convexHulls(contours.size());

		//cout<<"contour_size:"<<contours.size()<<endl;

		for (unsigned int i = 0; i < contours.size(); i++) {
			cv::convexHull(contours[i], convexHulls[i]);
		}

		for (auto &convexHull : convexHulls) {
			Blob possibleBlob(convexHull);
			
			if (possibleBlob.boundingRect.area() > 600 && possibleBlob.boundingRect.area() < 3500 ) 
			{
				cout<<"aspectRatio:"<<possibleBlob.dblAspectRatio<<endl;
				blobs.push_back(possibleBlob);
				ok=true;
				cent = possibleBlob.centerPosition;
				cv::Mat imgConvexHulls(imgThresh.size(), CV_8UC3, SCALAR_BLACK);

				convexHulls.clear();

				for (auto &blob : blobs)
			    {
					convexHulls.push_back(blob.contour);
				}

				cv::drawContours(imgConvexHulls, convexHulls, -1, SCALAR_WHITE, -1);

			//	cv::imshow("imgConvexHulls", imgConvexHulls);
					
						// get another copy of frame 2 since we changed the previous frame 2 copy in the processing above

					for (auto &blob : blobs) {                                                  // for each blob
					cv::rectangle( imgFrame2, blob.boundingRect, SCALAR_RED, 2);             // draw a red box around the blob
					cv::circle( imgFrame2, blob.centerPosition, 3, SCALAR_GREEN, -1);        // draw a filled-in green circle at the center
				}
			//	imshow("Frame",imgFrame2);

				break;

			}
			
			else
			{
				ok = false;	
				c++;
				
				if(c>100)
				{
					cout<<"i am from loop 100"<<endl;
					cent = possibleBlob.centerPosition;
					return true;
				}
				
				threshold = threshold + (float)(0.015*(possibleBlob.boundingRect.area()-1500)/2400)*threshold;
				cout<<"Threshold"<<threshold<<" "<<possibleBlob.boundingRect.area()<<endl;
				

			}

		}

	}
	return ok;
}

void detectchessboard()
{
	Mat frame;
	Mat drawToFrame;
	bool found=false;
	VideoCapture vid;
	vid.open("http://192.168.43.1:8080/video?x.mjpeg");
	std::ofstream chess_file("chess.dat");


	vector<Vec2f> foundPoints;
	if (!vid.isOpened()) {                                                 // if unable to open video file
		std::cout << "\nerror reading video file" << std::endl << std::endl;      // show error message
	                                                    
	}

    while(!found)
	{
		if (!vid.read(frame))
		{
			cout << "Could'nt read frame" << endl;

		}
		found = findChessboardCorners(frame, chessboardDimension, foundPoints, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE);
		frame.copyTo(drawToFrame);

		if (found)
		{
			cout << "Found" << found << endl;
			namedWindow("Croped_image", WINDOW_AUTOSIZE);
			drawChessboardCorners(drawToFrame, chessboardDimension, foundPoints, found);
			imshow("Croped_image",drawToFrame);
			int k = 0;
			//Code for copping 49 vector int 7x7 2d vector
			for (int i = 1; i < 8;i++)
			{
				for (int j = 1; j < 8; j++)
				{
					x[i][j] = foundPoints[k][0];
					y[i][j] = foundPoints[k][1];
					k++;
				}
				
			}
			
			if((x[1][1]>x[7][7]) && (y[1][7]>y[7][1]) &&(x[1][7]>x[7][1]))
				{
					cout<<"point1"<<endl;
					matrix_rotation();
				}
			else if((x[1][1]>x[7][7]) && (y[1][1]>y[7][7])&&(x[7][1]>x[1][7]))
			{
				cout<<"Two Times Rotation"<<endl;
				matrix_rotation();
				matrix_rotation();
			
			}

			

			else if((x[7][1]>x[1][7]) && (y[1][1]>y[7][7]))
			{
				cout<<"Three Times Roatation"<<endl;
				matrix_rotation();
				matrix_rotation();
				matrix_rotation();
				
			}

		
			Rect tocrop(2*x[1][1]-x[1][2]-15,2*y[1][1]-y[2][1]-15,((2*x[7][7]-x[7][6])-(2*x[1][1]-x[1][2]))+20,((2*y[7][7]-y[6][7])-(2*y[1][1]-y[2][1]))+20);
			Mat croped_image = frame(tocrop);
			imshow("croped_image",croped_image);
			cout<<"size of croped Image"<<croped_image.size();		
		
		}
	}

	for(int i=0; i<8; i++)
	{
		for(int j=0; j<8; j++)
		{
			chess_file<<x[i][j]<<"\t";
		}
		chess_file<<endl;
	}
	chess_file<<endl;
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<8; j++)
		{
			chess_file<<y[i][j]<<"\t";
		}
		chess_file<<endl;
	}

	vid.release();
}
void chess_read()
{
	ifstream chess_open("chess.dat");
	for(int i=0; i<8; i++)
	{
		for(int j=0;j<8;j++)
		{
			chess_open>>x[i][j];
		}
	}

	for(int i=0; i<8; i++)
	{
		for(int j=0; j<8; j++)
		{
			chess_open>>y[i][j];
		}
	}
	

	for(int i=0; i<8; i++)
	{
		for(int j=0;j<8;j++)
		{
			cout<<x[i][j]<<"\t";
		}
		cout<<endl;
	}

	for(int i=0; i<8; i++)
	{
		for(int j=0;j<8;j++)
		{
			cout<<y[i][j]<<"\t";
		}
		cout<<endl;
	}

	//cv::circle( imgFrame2, blob.centerPosition, 3, SCALAR_GREEN, -1);


}


void calibration()
{

	Mat frame;
	VideoCapture vid;
	vid.open("http://192.168.43.1:8080/video?x.mjpeg");

	vector<Vec2f> foundPoints;
	if (!vid.isOpened()) {                                                 // if unable to open video file
		std::cout << "\nerror reading video file" << std::endl << std::endl;      // show error message
	                                                    
	}

	std::vector<cv::Point> chess_axis;
	cv::Point san;

	for(int i =1;i<8;i++)
	{
		
		for(int j=1;j<8;j++)
		{
			san.x = x[i][j];
			san.y = y[i][j];
 			chess_axis.push_back(san);
		}
	}

    while(true)
	{
		vid.read(frame);
		
		for( auto &chess_points : chess_axis )
		{
			cv::circle( frame, chess_points, 3, SCALAR_RED, -1);
		}
		
		imshow("Frame",frame);

		if(waitKey(5)== 115)
		{
			cout<<"Kicked out"<<endl;
			vid.release();
			break;
		}
		
	}

	vid.release();

}
void crop(int& xx,int& yy,int& width, int& height)
{
	xx = 2*x[1][1]-x[1][2]-15;
	yy = 2*y[1][1]-y[2][1]-15;
	width = ((2*x[7][7]-x[7][6])-(2*x[1][1]-x[1][2]))+20;
	height = ((2*y[7][7]-y[6][7])-(2*y[1][1]-y[2][1]))+20;
	//(2*x[1][1]-x[1][2]-15,2*y[1][1]-y[2][1]-15,((2*x[7][7]-x[7][6])-(2*x[1][1]-x[1][2]))+20,((2*y[7][7]-y[6][7])-(2*y[1][1]-y[2][1]))+20);
}
int find_move(cv::Point centroid)
{
	
	int i=0,j=0;
	centroid.x += 2*x[1][1]-x[1][2]-15;
	centroid.y += 2*y[1][1]-y[2][1]-15;
 
	for(i=0;i<7;i++)
	{
		
		if(x[1][i]< centroid.x && x[1][i+1]>centroid.x)
		{
		  break;	
		}
		else if(centroid.y > x[1][7])
		{
			i=7;
			break;
		}
	}
	
	for(j=0;j<7;j++)
	{
		
		if(y[j][1]< centroid.y && y[j+1][1]>centroid.y)
		{
		  break;	
		}
		else if(centroid.y > y[7][1])
		{
			j=7;
			break;
		}
	}	
	i++;
	j++;
	cout<<"Moves"<<(10*i+j)<<endl;
	return (10*i+j);

}

/*
int main(int argv, char** argc)
{	
	
	//detectchessboard();
	chess_read();
	cv::Point centroid;
	int san = true;
	
	cv::VideoCapture capVideo;
	capVideo.open("http://192.168.43.1:8080/video?x.mjpeg");
	cv::Mat imgFrame1;
	cv::Mat imgFrame2;
	cv::Mat imgFrame3;
	Mat find_blobs;
    //namedWindow("edges",1);
	

	if (!capVideo.isOpened()) {                                                
		std::cout << "\nerror reading video file" << std::endl << std::endl;     
		return(0);                                                             
	}
	
	capVideo.read(imgFrame1);
	capVideo.read(imgFrame2);

	char chCheckForEscKey = 0;

	while (true) 
	{
		
		if(san)
		{
			imgFrame2 = imgFrame1.clone();
			motion_detect(capVideo);

		}
		
		capVideo.read(imgFrame1);
	//	imshow("Frame1",imgFrame1);
	//	imshow("Frame2",imgFrame2);
	     if(Detect_moves(imgFrame1,imgFrame2,centroid))
		 {
			 cout<<"frame detected"<<endl;
			 
			 san = true;

		 }
		 else
		 {
			 san = false;
		 }
		
        if(waitKey(5) == 27) 
		{
			capVideo.release();
			break;
		}
	

	}
	
	return 0;
}
*/
//2d array passing in function by reference
/*

float** chess_points_x;
float** chess_points_y;
chess_points_x = getArray();
chess_points_y = getArray();

float **getArray()
{
	float** arr = new float*[8];
	for (int i = 0;i < 8;i++)
	{
		arr[i] = new float[8];
	}
	return arr;
}
void printArray(float **san)
{
	for (int i = 0;i < 7;i++) {
		for (int j = 0;j < 7;j++)
		{
			san[i][j] = i + j;

		}
		cout << endl;
	}
}
*/

//Arranging in accending order
/*
			for (int i = 0; i < 7; i++)
			{
				
				for (int j = 0; j < 7; j++)
				{
					for (int k = j + 1;k < 7;k++)
					{
						if (chess_points[i][j](0) > chess_points[i][k](0) )
						{
							temp = chess_points[i][j];
							chess_points[i][j] = chess_points[i][k];
							chess_points[i][k] = temp;
						}
					}
				}
				temp = (0, 0);
				
			}

			for (int i = 0; i < 7; i++)
			{

				for (int j = 0; j < 7; j++)
				{
					for (int k = j + 1;k < 7;k++)
					{
						if (chess_points[j][i](1) > chess_points[k][i](1))
						{
							temp = chess_points[j][i];
							chess_points[j][i] = chess_points[k][i];
							chess_points[k][i] = temp;
						}
					}
				}
				temp = (0, 0);

			}

			

			
			for (int i = 0; i < 7; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					cout << "["<<chess_points_x[i][j] << ","<<chess_points_y[i][j]<<"]"<<"\t";
				}
				cout << endl;
			}
			*/
