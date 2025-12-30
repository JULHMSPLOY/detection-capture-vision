#pragma once

namespace MDS {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	public ref class LogForm : public System::Windows::Forms::Form
	{
	public:
		LogForm(void)
		{
			InitializeComponent();
		}

	protected:
		~LogForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ picPreview;
	private: System::Windows::Forms::ListView^ listView;
	private: System::Windows::Forms::ColumnHeader^ columnHeader1;
	private: System::Windows::Forms::ColumnHeader^ columnHeader2;
	private: System::Windows::Forms::Timer^ autorefreshtimer;

	private: System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->picPreview = (gcnew System::Windows::Forms::PictureBox());
			this->listView = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->autorefreshtimer = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picPreview))->BeginInit();
			this->SuspendLayout();
			// 
			// picPreview
			// 
			this->picPreview->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->picPreview->Location = System::Drawing::Point(204, 12);
			this->picPreview->Name = L"picPreview";
			this->picPreview->Size = System::Drawing::Size(351, 373);
			this->picPreview->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->picPreview->TabIndex = 0;
			this->picPreview->TabStop = false;
			// 
			// listView
			// 
			this->listView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) { this->columnHeader1, this->columnHeader2 });
			this->listView->FullRowSelect = true;
			this->listView->GridLines = true;
			this->listView->HideSelection = false;
			this->listView->Location = System::Drawing::Point(12, 12);
			this->listView->Name = L"listView";
			this->listView->Size = System::Drawing::Size(186, 373);
			this->listView->TabIndex = 1;
			this->listView->UseCompatibleStateImageBehavior = false;
			this->listView->View = System::Windows::Forms::View::Details;
			this->listView->SelectedIndexChanged += gcnew System::EventHandler(this, &LogForm::listView_SelectedIndexChanged);
			// 
			// columnHeader1
			// 
			this->columnHeader1->Text = L"Date/Time";
			this->columnHeader1->Width = 100;
			// 
			// columnHeader2
			// 
			this->columnHeader2->Text = L"File Name";
			this->columnHeader2->Width = 100;
			// 
			// autorefreshtimer
			// 
			this->autorefreshtimer->Interval = 33;
			this->autorefreshtimer->Tick += gcnew System::EventHandler(this, &LogForm::autorefreshtimer_Tick);
			// 
			// LogForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(567, 397);
			this->Controls->Add(this->listView);
			this->Controls->Add(this->picPreview);
			this->Name = L"LogForm";
			this->Text = L"LogForm";
			this->Load += gcnew System::EventHandler(this, &LogForm::LogForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picPreview))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	private:
		void UpdateLogList() {
			try {
				array<String^>^ files = Directory::GetFiles(Directory::GetCurrentDirectory(), "log_*.jpg");
				int currentCount = listView->Items->Count;

				if (files->Length != currentCount) {
					listView->Items->Clear();
					for each (String ^ path in files) {
						FileInfo^ info = gcnew FileInfo(path);
						ListViewItem^ item = gcnew ListViewItem(info->CreationTime.ToString("yyyy-MM-dd HH:mm:ss"));
						item->SubItems->Add(info->Name);
						listView->Items->Add(item);
					}
				}
			}
			catch (Exception^ ex) {
			}
		}

	private: System::Void LogForm_Load(System::Object^ sender, System::EventArgs^ e) 
	{
		UpdateLogList();
		autorefreshtimer->Start();
	}

	private: System::Void autorefreshtimer_Tick(System::Object^ sender, System::EventArgs^ e) 
	{
		UpdateLogList();
	}

	private: System::Void listView_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		if (listView->SelectedItems->Count > 0) {
			String^ fileName = listView->SelectedItems[0]->SubItems[1]->Text;

			if (picPreview->Image != nullptr) {
				delete picPreview->Image;
				picPreview->Image = nullptr;
			}

			if (File::Exists(fileName)) {
				try {
					picPreview->Image = Image::FromFile(fileName);
				}
				catch (Exception^ ex) {
				}
			}
		}
	}
};
}
