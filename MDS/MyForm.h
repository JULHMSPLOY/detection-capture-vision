#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <algorithm> 
#include <msclr/marshal_cppstd.h>

using namespace cv;

namespace MDS {

	using namespace System;
	using namespace System::Runtime::InteropServices;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			image = new cv::Mat();
			lastFrame = new cv::Mat();
			roi = System::Drawing::Rectangle(50, 50, 100, 100);
		}

	protected:
		~MyForm()
		{
			if (timer != nullptr) {
				timer->Stop();
			}

			if (capture != nullptr) {
				if (capture->isOpened()) {
					capture->release();
				}
				delete capture;
			}

			if (image) delete image;
			if (lastFrame) delete lastFrame;
			if (components) delete components;
		}
	private: System::Windows::Forms::PictureBox^ picMonitor;
	private: System::Windows::Forms::Timer^ timer;
	private: System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->picMonitor = (gcnew System::Windows::Forms::PictureBox());
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picMonitor))->BeginInit();
			this->SuspendLayout();
			// 
			// picMonitor
			// 
			this->picMonitor->Location = System::Drawing::Point(12, 12);
			this->picMonitor->Name = L"picMonitor";
			this->picMonitor->Size = System::Drawing::Size(476, 321);
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
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(500, 345);
			this->Controls->Add(this->picMonitor);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picMonitor))->EndInit();
			this->ResumeLayout(false);

		}

#pragma endregion
	private:
		cv::Mat* image;
		cv::Mat* lastFrame;
		cv::VideoCapture* capture;
		System::Drawing::Rectangle roi;
		bool isDragging = false;
		System::Drawing::Point startPoint;

		Bitmap^ ConvertToBitmap(Mat* img) {
			if (img == nullptr || img->empty()) return nullptr;
			Bitmap^ bmp = gcnew Bitmap(img->cols, img->rows, System::Drawing::Imaging::PixelFormat::Format24bppRgb);
			System::Drawing::Imaging::BitmapData^ bmpData = bmp->LockBits(
				System::Drawing::Rectangle(0, 0, bmp->Width, bmp->Height),
				System::Drawing::Imaging::ImageLockMode::WriteOnly, bmp->PixelFormat);

			cv::Mat matbmp(img->rows, img->cols, CV_8UC3, bmpData->Scan0.ToPointer(), bmpData->Stride);
			img->copyTo(matbmp);

			bmp->UnlockBits(bmpData);
			return bmp;
		}

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) 
	{
		capture = new cv::VideoCapture(0);
		if (capture->isOpened())
		{
			timer->Start();
		}
		else {
			MessageBox::Show("Camera Error!");
		}
	}

	private: System::Void timer_Tick(System::Object^ sender, System::EventArgs^ e)
	{
		if (capture == nullptr || !capture->isOpened()) return;
		capture->read(*image);
		if (image->empty()) return;

		float ratioX = (float)image->cols / picMonitor->Width;
		float ratioY = (float)image->rows / picMonitor->Height;

		cv::Rect cvRoi(
			(int)(roi.X * ratioX), (int)(roi.Y * ratioY),
			(int)(roi.Width * ratioX), (int)(roi.Height * ratioY)
		);

		cvRoi.x = (std::max)(0, (std::min)(cvRoi.x, image->cols - 1));
		cvRoi.y = (std::max)(0, (std::min)(cvRoi.y, image->rows - 1));
		cvRoi.width = (std::min)(cvRoi.width, image->cols - cvRoi.x);
		cvRoi.height = (std::min)(cvRoi.height, image->rows - cvRoi.y);

		if (cvRoi.width > 10 && cvRoi.height > 10) {
			cv::Mat gray, blur, diff, thresh;
			cv::cvtColor((*image)(cvRoi), gray, cv::COLOR_BGR2GRAY);
			cv::GaussianBlur(gray, blur, cv::Size(21, 21), 0);

			if (!lastFrame->empty() && lastFrame->size() == blur.size()) {
				cv::absdiff(*lastFrame, blur, diff);
				cv::threshold(diff, thresh, 25, 255, cv::THRESH_BINARY);

				if (cv::countNonZero(thresh) > 500) {
					cv::rectangle(*image, cvRoi, cv::Scalar(0, 0, 255), 2); // บุกรุก = แดง
					cv::putText(*image, "INTRUDER!", cv::Point(cvRoi.x, cvRoi.y - 10),
						cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 0, 255), 2);

					System::DateTime now = System::DateTime::Now;
					System::String^ fileName = "log_" + now.ToString("yyyyMMdd_HHmmss") + ".jpg";
					std::string stdPath = msclr::interop::marshal_as<std::string>(fileName);
					cv::imwrite(stdPath, *image);
				}
				else {
					cv::rectangle(*image, cvRoi, cv::Scalar(0, 255, 0), 1); // ปกติ = เขียว
				}
			}
			*lastFrame = blur.clone();
		}

		if (isDragging) {
			cv::Rect previewRoi(
				(int)(roi.X * ratioX), (int)(roi.Y * ratioY),
				(int)(roi.Width * ratioX), (int)(roi.Height * ratioY)
			);
			cv::rectangle(*image, previewRoi, cv::Scalar(0, 255, 255), 1); // สีเหลือง

		}

		cv::Mat display;
		cv::cvtColor(*image, display, cv::COLOR_BGR2RGB);
		if (picMonitor->Image != nullptr) delete picMonitor->Image;
		picMonitor->Image = ConvertToBitmap(&display);
	}

	private: System::Void picMonitor_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) 
	{
		isDragging = true;
		startPoint = e->Location;
		roi = System::Drawing::Rectangle(e->X, e->Y, 0, 0);
	}

	private: System::Void picMonitor_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) 
	{
		if (isDragging) {
			roi.X = Math::Min(startPoint.X, e->X);
			roi.Y = Math::Min(startPoint.Y, e->Y);
			roi.Width = Math::Abs(startPoint.X - e->X);
			roi.Height = Math::Abs(startPoint.Y - e->Y);
		}
	}
	private: System::Void picMonitor_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) 
	{
		isDragging = false;
	}

	private: System::Void picMonitor_Click(System::Object^ sender, System::EventArgs^ e) {}
};
}
