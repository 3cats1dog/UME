#pragma once

#include "Global.h";

namespace MeasLab {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Reflection;
	/// <summary>
	/// Summary for AboutForm
	/// </summary>
	public ref class AboutForm : public System::Windows::Forms::Form
	{
	public:
		AboutForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~AboutForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::Label^ lblVersion;
	private: System::Windows::Forms::Label^ lblProgramName;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(AboutForm::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->lblVersion = (gcnew System::Windows::Forms::Label());
			this->lblProgramName = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(127, 142);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(104, 106);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 262);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(347, 16);
			this->label1->TabIndex = 1;
			this->label1->Text = L"U2 Yazılım Ve Bilişim Teknolojileri Limited Şirketi";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(79, 288);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(206, 16);
			this->label2->TabIndex = 2;
			this->label2->Text = L"İletişim : info@u2yazilim.com";
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(15, 46);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->Size = System::Drawing::Size(318, 54);
			this->richTextBox1->TabIndex = 3;
			this->richTextBox1->Text = L"TUBİTAK UME Yüksek Gerilim Laboratuvarı ölçü cihazlarının kontrol ve senkronizasy"
				L"onu için geliştrilmiştir.";
			// 
			// lblVersion
			// 
			this->lblVersion->AutoSize = true;
			this->lblVersion->Location = System::Drawing::Point(12, 112);
			this->lblVersion->Name = L"lblVersion";
			this->lblVersion->Size = System::Drawing::Size(35, 13);
			this->lblVersion->TabIndex = 4;
			this->lblVersion->Text = L"label3";
			// 
			// lblProgramName
			// 
			this->lblProgramName->AutoSize = true;
			this->lblProgramName->Location = System::Drawing::Point(12, 19);
			this->lblProgramName->Name = L"lblProgramName";
			this->lblProgramName->Size = System::Drawing::Size(35, 13);
			this->lblProgramName->TabIndex = 5;
			this->lblProgramName->Text = L"label3";
			// 
			// AboutForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(366, 312);
			this->Controls->Add(this->lblProgramName);
			this->Controls->Add(this->lblVersion);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"AboutForm";
			this->Text = L"Hakkında";
			this->Load += gcnew System::EventHandler(this, &AboutForm::AboutForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void AboutForm_Load(System::Object^ sender, System::EventArgs^ e) {
		lblProgramName->Text = String::Format("Product: {0}", G::ProductTitle);
		lblVersion->Text = String::Format("Version: {0}", G::ProductVersion);
	}

#pragma region Assembly Attribute Accessors

	property  String^ AssemblyTitle
	{
		String^ get()
		{
			array<Object^>^ attributes  = Assembly::GetExecutingAssembly()->GetCustomAttributes(AssemblyTitleAttribute::typeid, false);
			if (attributes->Length > 0)
			{
				AssemblyTitleAttribute^ titleAttribute = (AssemblyTitleAttribute^)attributes[0];
				if (titleAttribute->Title != "")
				{
					return titleAttribute->Title;
				}
			}
			return System::IO::Path::GetFileNameWithoutExtension(Assembly::GetExecutingAssembly()->CodeBase);
		}
	}

	property String^ AssemblyVersion
	{
		String^ get()
		{
			return Assembly::GetExecutingAssembly()->GetName()->Version->ToString();
		}
	}

	property String^ AssemblyDescription
	{ String^ get()
	{
		array<Object^>^ attributes = Assembly::GetExecutingAssembly()->GetCustomAttributes(AssemblyDescriptionAttribute::typeid, false);
		if (attributes->Length == 0)
		{
			return "";
		}
		return ((AssemblyDescriptionAttribute^)attributes[0])->Description;
	}
	}

	property String^ AssemblyProduct
	{ String^ get()
	{
		array<Object^>^ attributes = Assembly::GetExecutingAssembly()->GetCustomAttributes(AssemblyProductAttribute::typeid, false);
		if (attributes->Length == 0)
		{
			return "";
		}
		return ((AssemblyProductAttribute^)attributes[0])->Product;
	}
	}

	property String^ AssemblyCopyright
	{ String^ get()
	{
		array<Object^>^ attributes = Assembly::GetExecutingAssembly()->GetCustomAttributes(AssemblyCopyrightAttribute::typeid, false);
		if (attributes->Length == 0)
		{
			return "";
		}
		return ((AssemblyCopyrightAttribute^)attributes[0])->Copyright;
	}
	}

	property String^ AssemblyCompany
	{String^ get()
	{
		array<Object^>^ attributes = Assembly::GetExecutingAssembly()->GetCustomAttributes(AssemblyCompanyAttribute::typeid, false);
		if (attributes->Length == 0)
		{
			return "";
		}
		return ((AssemblyCompanyAttribute^)attributes[0])->Company;
	}
	}
	#pragma  endregion


};
}
