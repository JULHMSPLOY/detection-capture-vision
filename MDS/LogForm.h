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

		LogForm(System::Windows::Forms::Form^ mainForm)
		{
			InitializeComponent();
			_mainForm = mainForm;
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
	private: System::Windows::Forms::Button^ btnback;
	private: System::Windows::Forms::MenuStrip^ menuStrip;

	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ folderToolStripMenuItem;
	private: System::Windows::Forms::Label^ label1;

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
			this->btnback = (gcnew System::Windows::Forms::Button());
			this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->folderToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->label1 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picPreview))->BeginInit();
			this->menuStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// picPreview
			// 
			this->picPreview->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->picPreview->Location = System::Drawing::Point(221, 75);
			this->picPreview->Name = L"picPreview";
			this->picPreview->Size = System::Drawing::Size(352, 291);
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
			this->listView->Location = System::Drawing::Point(12, 75);
			this->listView->Name = L"listView";
			this->listView->Size = System::Drawing::Size(203, 291);
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
			this->autorefreshtimer->Interval = 2000;
			this->autorefreshtimer->Tick += gcnew System::EventHandler(this, &LogForm::autorefreshtimer_Tick);
			// 
			// btnback
			// 
			this->btnback->Location = System::Drawing::Point(249, 379);
			this->btnback->Name = L"btnback";
			this->btnback->Size = System::Drawing::Size(75, 32);
			this->btnback->TabIndex = 2;
			this->btnback->Text = L"Back";
			this->btnback->UseVisualStyleBackColor = true;
			this->btnback->Click += gcnew System::EventHandler(this, &LogForm::btnback_Click);
			// 
			// menuStrip
			// 
			this->menuStrip->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip->Location = System::Drawing::Point(0, 0);
			this->menuStrip->Name = L"menuStrip";
			this->menuStrip->Size = System::Drawing::Size(585, 28);
			this->menuStrip->TabIndex = 3;
			this->menuStrip->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->folderToolStripMenuItem });
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(46, 24);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// folderToolStripMenuItem
			// 
			this->folderToolStripMenuItem->Name = L"folderToolStripMenuItem";
			this->folderToolStripMenuItem->Size = System::Drawing::Size(134, 26);
			this->folderToolStripMenuItem->Text = L"Folder";
			this->folderToolStripMenuItem->Click += gcnew System::EventHandler(this, &LogForm::folderToolStripMenuItem_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(222)));
			this->label1->Location = System::Drawing::Point(236, 42);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(110, 20);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Show Image";
			// 
			// LogForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(585, 432);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->btnback);
			this->Controls->Add(this->listView);
			this->Controls->Add(this->picPreview);
			this->Controls->Add(this->menuStrip);
			this->MainMenuStrip = this->menuStrip;
			this->Name = L"LogForm";
			this->Text = L"LogForm";
			this->Load += gcnew System::EventHandler(this, &LogForm::LogForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picPreview))->EndInit();
			this->menuStrip->ResumeLayout(false);
			this->menuStrip->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		System::Windows::Forms::Form^ _mainForm;

	private:
		void UpdateLogList() {
			try {
				System::String^ folderPath = System::IO::Path::Combine(System::Windows::Forms::Application::StartupPath, "Detected Images");

				if (System::IO::Directory::Exists(folderPath)) {
					array<System::String^>^ files = System::IO::Directory::GetFiles(folderPath, "log_*.jpg");
					int currentCount = listView->Items->Count;

					if (files->Length != currentCount) {
						listView->Items->Clear();
						for each (System::String ^ path in files) {
							System::IO::FileInfo^ info = gcnew System::IO::FileInfo(path);
							ListViewItem^ item = gcnew ListViewItem(info->CreationTime.ToString("yyyy-MM-dd HH:mm:ss"));
							item->SubItems->Add(info->Name);
							listView->Items->Add(item);
						}
					}
				}
			}
			catch (System::Exception^ ex) {}
		}

	private: System::Void LogForm_Load(System::Object^ sender, System::EventArgs^ e) 
	{
		UpdateLogList();
		autorefreshtimer->Start();
	}

	private: System::Void folderToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		System::String^ folderPath = System::IO::Path::Combine(System::Windows::Forms::Application::StartupPath, "Detected Images");
		if (System::IO::Directory::Exists(folderPath)) {
			System::Diagnostics::Process::Start("explorer.exe", folderPath);
		}
		else {
			System::Windows::Forms::MessageBox::Show("Folder 'Detected Images' not found. It will be created when an intruder is detected.");
		}
	}

	private: System::Void btnback_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		this->autorefreshtimer->Stop();

		if (_mainForm != nullptr) {
			_mainForm->Location = this->Location;
			_mainForm->StartPosition = FormStartPosition::Manual;
			_mainForm->Show();
		}

		this->Close();
	}

	private: System::Void autorefreshtimer_Tick(System::Object^ sender, System::EventArgs^ e) 
	{
		UpdateLogList();
	}

	private: System::Void listView_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		if (listView->SelectedItems->Count > 0) {
			System::String^ fileName = listView->SelectedItems[0]->SubItems[1]->Text;
			System::String^ folderPath = System::IO::Path::Combine(System::Windows::Forms::Application::StartupPath, "Detected Images");
			System::String^ fullPath = System::IO::Path::Combine(folderPath, fileName);

			if (picPreview->Image != nullptr) {
				delete picPreview->Image;
				picPreview->Image = nullptr;
			}

			if (System::IO::File::Exists(fullPath)) {
				try {
					System::IO::FileStream^ fs = gcnew System::IO::FileStream(fullPath, System::IO::FileMode::Open, System::IO::FileAccess::Read);
					picPreview->Image = Image::FromStream(fs);
					fs->Close();
				}
				catch (System::Exception^ ex) {
				}
			}
		}
	}
};
}
