#include "pch.h"

#include <sapi.h>
#include <opencv2/objdetect/objdetect.hpp> 
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp> 
#include <iostream> 
#include <fstream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/core/cvstd.hpp>
#include <opencv2/face.hpp>
#include "bif.cpp"
#include "eigen_faces.cpp"
#include  "face_alignment.cpp"
#include "face_basic.cpp"
#include "facemark.cpp"
#include "facemarkAAM.cpp"
#include "facemarkLBF.cpp"
#include "facerec.cpp"
#include "fisher_faces.cpp"
#include "getlandmarks.cpp"
#include "lbph_faces.cpp"
#include "mace.cpp"
#include "predict_collector.cpp"
#include "regtree.cpp"
#include "trainFacemark.cpp"
#include <windows.h>
#include <locale>
#include <sstream>
#include <conio.h>
using namespace std;
using namespace cv;
using namespace cv::face;
// Function for Face Detection 
vector <string> questionset;
vector <string> answerset;
vector<Rect> leyes;
vector<Rect> reyes;
class student {

private:
	
	string name;
	int marks;
public:
		static int label;
		student() {}
		student(string& var,int& var1):name(var),marks(var1){
			label++;
		}
		
		void insert(int& var) 
		{
			marks = var;
		}
		void get(string& var) {
			var = name;
		}
};
int student::label = 0;
wchar_t qwx[50];
LPCWSTR g_szClassName = L"myWindowClass";
LRESULT CALLBACK wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM sparam);
Ptr<FisherFaceRecognizer> model = FisherFaceRecognizer::create();
vector<Mat> vec;
vector<int> sdf;
vector<string> names;
int detectAndDraw(Mat& img, CascadeClassifier& cascade,
	CascadeClassifier& nestedCascade, double scale,int& i);
string cascadeName, nestedCascadeName;
void startsession();
void quiz(int& var);
int g = 0;
// VideoCapture class for playing video for which faces to be detected 
VideoCapture capture;
Mat frame, image;

// PreDefined trained XML classifiers with facial features 
CascadeClassifier cascade, nestedCascade,myCascade;
double scale = 1;

// Load classifiers from "opencv/data/haarcascades" directory  
//nestedCascade.load("../../haarcascade_eye_tree_eyeglasses.xml");

// Change path before execution  

int  main()
{
	cascade.load("C:/Users/acer/desktop/face.xml");
	nestedCascade.load("C:/Users/acer/desktop/reye.xml");
	myCascade.load("C:/Users/acer/desktop/leye.xml");
	fstream question("question.txt");
	string str;
	string answer;
	while (getline(question, str, ';')) {
		questionset.push_back(str);
		getline(question, str);
		answerset.push_back(str);
	}
	cout << answerset.size();
	ISpVoice * pVoice = NULL;
	//model->train(vec, sdf);
	if (FAILED(::CoInitialize(NULL)))
		return FALSE;

	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
	if (SUCCEEDED(hr))
	{
		pVoice->Speak(L"hello", 0, NULL);
		pVoice->Release();
		pVoice = NULL;
	}
	
	::CoUninitialize();
	//---------------------------------------------------------------------
	
	//cascade.load("finger.xml");
	Mat qa = imread("Prisha.pmg", 1);
	Mat as = imread("Ishan.pmg", 1);
	Mat sd,xc;
	vector<Rect> qer;
	vector<Rect> res;
	cv::cvtColor(qa, sd, COLOR_BGR2GRAY);
	cv::cvtColor(as, xc, COLOR_BGR2GRAY);
	cascade.detectMultiScale(sd, qer);
	cascade.detectMultiScale(xc, res);
	
	Mat inp = sd(qer[0]);
	Mat er = xc(res[0]);
	// Start Video..1) 0 for WebCam 2) "Path to Video" for a Local Video 
	for (int i = 0; i <= 9; i++) {
		vec.push_back(inp);
	}
	for (int i = 0; i <= 9; i++) {
		cv::resize(er, er, Size(vec[0].cols, vec[0].rows), 1.0, 1.0, INTER_CUBIC);
		vec.push_back(er);
	}
	for (int i = 0; i <= 9; i++) {
		sdf.push_back(1);
	}
	for (int i = 0; i <= 9; i++) {
		sdf.push_back(0);
	}
	model->train(vec, sdf);

	names = { "Ishaan","Prisha" };
	system("cls");
	system("color 0");
	for (int i = 0; i <= 255; i++) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
		cout << "OpenCv" << "\t";
	}cout << "\n";
	cout.setf(ios::internal, ios::adjustfield);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	cout << "Press any key to get started.....";
	_getch();
	startsession();
		

	
  return 0;

}	
	

int detectAndDraw(Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale,int& u)
{   
	
	
	vector<Rect> faces, faces2;
	Mat gray, smallImg;

	cvtColor(img, gray, COLOR_BGR2GRAY); // Convert to Gray Scale 
	double fx = 1 / scale;

	// Resize the Grayscale Image  
	//resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR);
	//equalizeHist(smallImg, smallImg);

	// Detect faces of different sizes using cascade classifier  
	//cascade.detectMultiScale(gray, faces, 1.1,
		//2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
	cascade.detectMultiScale(gray, faces);
		//fstream obj;
	//obj.open("ram.bin");
	//obj.seekg(0, ios::beg);
	
		//obj.read((char *)& faces2, sizeof(Rect));
		//u = 1;
	
	// Draw circles around the faces 
	for (size_t i = 0; i < faces.size(); i++)
	{
		Rect r = faces[i];
		Mat smallImgROI;
		vector<Rect> nestedObjects;
		
		Scalar color = Scalar(255, 0, 0); // Color for Drawing tool 
		int radius;
		Mat gs = gray(r);
		Mat out;
		cv::resize(gs, out, Size(vec[0].cols, vec[0].rows), 1.0, 1.0, INTER_CUBIC);
		 u = model->predict(out);
		cout << "\n"<<"predicted label:\n"<<u;
		double aspect_ratio = (double)r.width / r.height;
		
		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
			/*center.x = cvRound((r.x + r.width*0.5)*scale);
			center.y = cvRound((r.y + r.height*0.5)*scale);*/
			radius = cvRound((r.width + r.height)*0.25*scale);
			circle(img, center, radius, color, 3, 8, 0);
			
		/*else
			rectangle(img, cvPoint(cvRound(r.x*scale), cvRound(r.y*scale)),
				cvPoint(cvRound((r.x + r.width - 1)*scale),
					cvRound((r.y + r.height - 1)*scale)), color, 3, 8, 0);*/
					/*if (nestedCascade.empty())
						continue;*/
						/*smallImgROI = smallImg(r);

						// Detection of eyes int the input image
						nestedCascade.detectMultiScale(smallImgROI, nestedObjects, 1.1, 2,
							0 | CASCADE_SCALE_IMAGE, Size(30, 30));

						// Draw circles around eyes
						for (size_t j = 0; j < nestedObjects.size(); j++)
						{
							Rect nr = nestedObjects[j];
							center.x = cvRound((r.x + nr.x + nr.width*0.5)*scale);
							center.y = cvRound((r.y + nr.y + nr.height*0.5)*scale);
							radius = cvRound((nr.width + nr.height)*0.25*scale);
							circle(img, center, radius, color, 3, 8, 0);
						}*/
	}

	// Show Processed Image with detected faces 
	//imshow("Face Detection", img);
	return faces.size();
}
 void startsession() {
	capture.open(0);
	int returnedlabel;
	int numberofperson;
	if (capture.isOpened())
	{
		string sw;

		// Capture frames from video and detect faces 
		cout << "Face Detection Started...." << endl;
		while (1)
		{
			capture >> frame;
			if (frame.empty())
				break;
			Mat frame1 = frame.clone();

			numberofperson = detectAndDraw(frame1, cascade, nestedCascade, scale, returnedlabel);
			//wstring qw=to_wstring(numberofperson);
			


			wsprintf(qwx, L"I am alive! I can see you, number of persons in my front =%d,Let give me time! if am I recognise any of you", numberofperson);
			ISpVoice * pVoice = NULL;
			//model->train(vec, sdf);
			::CoInitialize(NULL);


			HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
			if (SUCCEEDED(hr))
			{
				pVoice->Speak(qwx, 0, NULL);
				pVoice->Release();
				pVoice = NULL;
			}

			::CoUninitialize();
			//imshow("Face Detection", frame1);
			char c = (char)waitKey(10);

			// Press q to exit from window 
			if (c == 27 || c == 'q' || c == 'Q')
				break;
			if (numberofperson > 0) {
				break;


			}
		}
	}
	else
		cout << "Could  not open camera";
	quiz(returnedlabel);
 }

 void quiz(int& var) {
	 int score = 0;
	 student ramu;
	 fstream obj("santa.txt");
	 obj.seekg(var, ios::beg);
	 obj.read((char*)&ramu, sizeof(student));
	 string kake;
	 ramu.get(kake);
	 

	 wchar_t qw[31];
	 string kuo = "I think this is you " + names[var]  + " let us start the quize";
	 wsprintf(qwx, L"");
	 for (int i = 0; i <= kuo.length() - 1;i++) {
		 qw[i] = wchar_t(kuo[i]);
	 }
	 ISpVoice * pVoice = NULL;
	 //model->train(vec, sdf);
	 ::CoInitialize(NULL);


	 HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
	 if (SUCCEEDED(hr))
	 {
		 pVoice->Speak(qw, 0, NULL);
		 
		 pVoice->Release();
		
		/* pVoice->Speak(qwx, 0, NULL);
		 pVoice->Release();*/
		 pVoice = NULL;
	 
	 }

	 ::CoUninitialize();
	 
	 wchar_t qa[31];
	 for (int i = 0; i <= questionset.size() - 1; i++) {
		 //score = 0;
		 wcscpy_s(qa, L"");
		 string sw = format(" question number %d", i + 1);
		 sw = sw + " " + questionset[i];
		 cout << sw<<"\n";
		 for (int u = 0; u <= sw.length() - 1; u++) {
			 qa[u] = wchar_t(sw[u]);
		 }
		 ISpVoice * pVoice = NULL;
		 //model->train(vec, sdf);
		 ::CoInitialize(NULL);


		 HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
		 if (SUCCEEDED(hr))
		 {
			 pVoice->Speak(qa, 0, NULL);

			 pVoice->Release();

			 /* pVoice->Speak(qwx, 0, NULL);
			  pVoice->Release();*/
			 pVoice = NULL;

		 }

		 ::CoUninitialize();
	 
		 Mat frame,gray;
		 while ((leyes.size() == 0 and reyes.size() == 0) || (leyes.size() == 1 and reyes.size() == 1) or leyes.size()==2 or reyes.size()==2) {
			 capture >> frame;
			 cvtColor(frame, gray, COLOR_BGR2GRAY);
			 nestedCascade.detectMultiScale(gray, leyes);
			 myCascade.detectMultiScale(gray, reyes);
		 }
		 int response = reyes.size() > leyes.size() ? 1 : 0;
		 cout << response<<endl;
		 int originalanswer = strtol(answerset[0].c_str(), NULL, 10);
		 
		 if (originalanswer == response) {
			 score++;
			 ramu.insert(score);
			 ISpVoice * pVoice = NULL;
			 //model->train(vec, sdf);
			 ::CoInitialize(NULL);


			 HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
			 if (SUCCEEDED(hr))
			 {
				 pVoice->Speak(L"correct! ", 0, NULL);

				 pVoice->Release();

				 /* pVoice->Speak(qwx, 0, NULL);
				  pVoice->Release();*/
				 pVoice = NULL;

			 }
		 }
		 else {
			 score--;
			 ramu.insert(score);
			 ISpVoice * pVoice = NULL;
			 //model->train(vec, sdf);
			 ::CoInitialize(NULL);


			 HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
			 if (SUCCEEDED(hr))
			 {
				 pVoice->Speak(L"wrong! ", 0, NULL);

				 pVoice->Release();

				 /* pVoice->Speak(qwx, 0, NULL);
				  pVoice->Release();*/
				 pVoice = NULL;

			 }
		 }
		
		 leyes.clear();
		 reyes.clear();
	 }
	 wcscpy_s(qa, L"");
	 wsprintf(qa, L"You have scored %d", score);
	 ISpVoice * pVoic = NULL;
	 //model->train(vec, sdf);
	 ::CoInitialize(NULL);


	 HRESULT hra = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoic);
	 if (SUCCEEDED(hra))
	 {
		 pVoic->Speak(qa, 0, NULL);

		 pVoic->Release();

		 /* pVoice->Speak(qwx, 0, NULL);
		  pVoice->Release();*/
		 pVoic = NULL;

	 }
 
	 student shamu;
	 fstream temp("temp.txt");
	 obj.seekg(0, ios::beg);
	 int f = 0;
	 while (obj.read((char*)& shamu, sizeof(student))) {
		 temp.seekp(f * sizeof(student), ios::beg);
		 if (f == var) {
			 temp.write((char*)& ramu, sizeof(student));
		 }
		 else {
			 temp.write((char*)& shamu, sizeof(student));
		 }
		 f++;
	 }
	 remove("santa.txt");
	 rename("temp.txt", "santa.txt");
	 cout << "\nYour score is succesfuly saved....";
}
 