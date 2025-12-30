#pragma once
#include <opencv2/opencv.hpp>
#include <msclr/marshal_cppstd.h>

namespace MDS {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace cv;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			lastFrame = new cv::Mat();
			currentFrame = new cv::Mat();
			roi = System::Drawing::Rectangle(10, 10, 100, 100);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
			if (capture) { 
				capture->release(); 
				delete capture;
			}
			if (lastFrame) {
				delete lastFrame;
			}
			if (currentFrame) {
				delete currentFrame;
			}
		}
	private: System::Windows::Forms::PictureBox^ picMonitor;
	private: System::Windows::Forms::Timer^ timer;
	protected:



	private: System::Windows::Forms::Button^ btnStart;
	private: System::Windows::Forms::Button^ btnStop;


	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->picMonitor = (gcnew System::Windows::Forms::PictureBox());
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->btnStart = (gcnew System::Windows::Forms::Button());
			this->btnStop = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picMonitor))->BeginInit();
			this->SuspendLayout();
			// 
			// picMonitor
			// 
			this->picMonitor->Location = System::Drawing::Point(26, 24);
			this->picMonitor->Name = L"picMonitor";
			this->picMonitor->Size = System::Drawing::Size(446, 243);
			this->picMonitor->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->picMonitor->TabIndex = 0;
			this->picMonitor->TabStop = false;
			this->picMonitor->Click += gcnew System::EventHandler(this, &MyForm::picMonitor_Click);
			this->picMonitor->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::picMonitor_MouseDown);
			this->picMonitor->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::picMonitor_MouseMove);
			this->picMonitor->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::picMonitor_MouseUp);
			// 
			// timer
			// 
			this->timer->Interval = 33;
			this->timer->Tick += gcnew System::EventHandler(this, &MyForm::timer_Tick);
			// 
			// btnStart
			// 
			this->btnStart->Location = System::Drawing::Point(55, 296);
			this->btnStart->Name = L"btnStart";
			this->btnStart->Size = System::Drawing::Size(75, 23);
			this->btnStart->TabIndex = 1;
			this->btnStart->Text = L"Start";
			this->btnStart->UseVisualStyleBackColor = true;
			this->btnStart->Click += gcnew System::EventHandler(this, &MyForm::btnStart_Click);
			// 
			// btnStop
			// 
			this->btnStop->Location = System::Drawing::Point(370, 296);
			this->btnStop->Name = L"btnStop";
			this->btnStop->Size = System::Drawing::Size(75, 23);
			this->btnStop->TabIndex = 2;
			this->btnStop->Text = L"Stop";
			this->btnStop->UseVisualStyleBackColor = true;
			this->btnStop->Click += gcnew System::EventHandler(this, &MyForm::btnStop_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(500, 345);
			this->Controls->Add(this->btnStop);
			this->Controls->Add(this->btnStart);
			this->Controls->Add(this->picMonitor);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picMonitor))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private:
		// ประกาศตัวแปร (Variables)
		cv::VideoCapture* capture;
		cv::Mat* lastFrame;
		cv::Mat* currentFrame;
		System::Drawing::Rectangle roi;
		bool isSelecting = false;
		System::Drawing::Point startPoint;

		// ฟังก์ชันแปลง Mat เป็น Bitmap
		System::Drawing::Bitmap^ MatToBitmap(cv::Mat& img) {
			if (img.empty()) return nullptr;
			return gcnew System::Drawing::Bitmap(img.cols, img.rows, (int)img.step,
				System::Drawing::Imaging::PixelFormat::Format24bppRgb, (System::IntPtr)img.data);
		}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {}
	private: System::Void btnStart_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		capture->open(0);
		if (capture->isOpened()) {
			timer->Start();
		}
		else {
			MessageBox::Show("Camera not found!");
		}
	}
	private: System::Void btnStop_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		timer->Stop();
		capture->release();
	}
	private: System::Void timer_Tick(System::Object^ sender, System::EventArgs^ e) 
	{
		if (!capture->isOpened()) return;
		capture->read(*currentFrame);
		if (currentFrame->empty()) return;

		// Process Motion Detection inside ROI
		cv::Rect cvRoi(roi.X, roi.Y, roi.Width, roi.Height);

		// Boundary check for ROI
		cvRoi.x = (std::max)(0, (std::min)(cvRoi.x, currentFrame->cols - 1));
		cvRoi.y = (std::max)(0, (std::min)(cvRoi.y, currentFrame->rows - 1));
		cvRoi.width = (std::min)(cvRoi.width, currentFrame->cols - cvRoi.x);
		cvRoi.height = (std::min)(cvRoi.height, currentFrame->rows - cvRoi.y);

		if (cvRoi.width > 10 && cvRoi.height > 10) {
			cv::Mat gray, blur, diff, thresh;
			cv::cvtColor((*currentFrame)(cvRoi), gray, cv::COLOR_BGR2GRAY);
			cv::GaussianBlur(gray, blur, cv::Size(21, 21), 0);

			if (!lastFrame->empty() && lastFrame->size() == blur.size()) {
				// Absolute Difference
				cv::absdiff(*lastFrame, blur, diff);
				// Threshold to binary
				cv::threshold(diff, thresh, 25, 255, cv::THRESH_BINARY);

				if (cv::countNonZero(thresh) > 500) {
					// Motion detected: Draw RED rectangle
					cv::rectangle(*currentFrame, cvRoi, cv::Scalar(0, 0, 255), 2);
					cv::putText(*currentFrame, "MOTION DETECTED", cv::Point(roi.X, roi.Y - 10),
						cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 1);
				}
				else {
					// Normal state: Draw GREEN rectangle
					cv::rectangle(*currentFrame, cvRoi, cv::Scalar(0, 255, 0), 1);
				}
			}
			*lastFrame = blur.clone();
		}

		// Update PictureBox and prevent Memory Leak
		if (picMonitor->Image != nullptr) delete picMonitor->Image;
		picMonitor->Image = MatToBitmap(*currentFrame);
	}
	private: System::Void picMonitor_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) 
	{
		isSelecting = true;
		startPoint = e->Location;
		roi = System::Drawing::Rectangle(e->X, e->Y, 0, 0);
	}

	private: System::Void picMonitor_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) 
	{
		if (isSelecting) {
			roi.X = Math::Min(startPoint.X, e->X);
			roi.Y = Math::Min(startPoint.Y, e->Y);
			roi.Width = Math::Abs(startPoint.X - e->X);
			roi.Height = Math::Abs(startPoint.Y - e->Y);
		}
	}
	private: System::Void picMonitor_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) 
	{
		isSelecting = false;
	}

	private: System::Void picMonitor_Click(System::Object^ sender, System::EventArgs^ e) {}
};
}
