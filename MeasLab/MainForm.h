#pragma once
#include "Global.h";
#include "WaveFormMeasurement.h";
#include "EquipList.h";
#include "AboutForm.h";
#include "GenericDMM.h";
#include "GridObject.h";
#include "EnteringUI.h";
#include "SettingForm.h";
#include <istream>;

namespace MeasLab {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace WaveFormMeasument;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
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
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::LinkLabel^ llblRefreshGrid;
	private: System::Windows::Forms::LinkLabel^ linkLabel1;
	private: System::Windows::Forms::LinkLabel^ linkLabel2;
	private: System::Windows::Forms::GroupBox^ gbWaveFormGraph;







	private: System::Windows::Forms::ToolStrip^ toolStrip1;
	private: System::Windows::Forms::ToolStripButton^ btnExit;
	private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator;
	private: System::Windows::Forms::ToolStripButton^ btnConnect;
	private: System::Windows::Forms::ToolStripButton^ btnDisconnect;
	private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator1;
	private: System::Windows::Forms::ToolStripButton^ btnSettings;

	private: System::Windows::Forms::ToolStripButton^ btnShowLog;
	private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator3;
	private: System::Windows::Forms::ToolStripButton^ helpToolStripButton;

	private: System::Windows::Forms::TableLayoutPanel^ panelLog;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::LinkLabel^ linkClearLog;
	private: System::Windows::Forms::StatusStrip^ statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^ lblFooterCounter;
	private: System::Windows::Forms::ToolStripStatusLabel^ lblFooter;

	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::DataGridView^ dgw_Sample;




	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::Label^ lblDemoMode;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ txtLiveRMS;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ txtLivePeakRoot2;

	private: System::Windows::Forms::GroupBox^ gBoxStartStop;
	private: System::Windows::Forms::Panel^ pnlTestLive;
	private: System::Windows::Forms::Label^ lblRemainData;
	private: System::Windows::Forms::Label^ lblPassTime;

	private: System::Windows::Forms::TextBox^ txtBarcode;


	private: System::Windows::Forms::Label^ label7;



	private: System::Windows::Forms::Button^ btnStart;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::ComboBox^ cmbSampleAdet;


	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ txtLiveRMS_UUT;
	private: System::Windows::Forms::TextBox^ txtLivePeakRoot2_UUT;



	private: System::Windows::Forms::GroupBox^ gbDMM;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::TextBox^ txtsfVrms_DMM;





	private: System::Windows::Forms::Label^ label17;



	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::ComboBox^ cmbVoltageRange_DMM;



	private: System::Windows::Forms::Label^ label15;
private: System::Windows::Forms::TextBox^ txtTerminal_DMM;

	private: System::Windows::Forms::Label^ label21;
private: System::Windows::Forms::Label^ lblZinput_DMM;

private: System::Windows::Forms::TextBox^ txtZInput_DMM;

	private: System::Windows::Forms::Label^ label19;
private: System::Windows::Forms::Label^ label18;
private: System::Windows::Forms::ComboBox^ cmbAddress_DMM;


private: System::Windows::Forms::Label^ label20;
private: System::Windows::Forms::Label^ label22;
private: System::Windows::Forms::Label^ lblFreqRange;

private: System::Windows::Forms::TextBox^ txtFreq;
private: System::Windows::Forms::Label^ label4;
private: System::Windows::Forms::Label^ label1;
private: System::Windows::Forms::ComboBox^ cmbMeasType;

private: System::Windows::Forms::Label^ label13;
private: System::Windows::Forms::ComboBox^ cmbAddress_UUT;
private: System::Windows::Forms::TextBox^ txtTerminal_UUT;


private: System::Windows::Forms::Label^ label23;
private: System::Windows::Forms::Label^ lblZinput_UUT;

private: System::Windows::Forms::TextBox^ txtZInput_UUT;

private: System::Windows::Forms::Label^ label25;
private: System::Windows::Forms::Label^ label26;
private: System::Windows::Forms::TextBox^ txtsfVrms_UUT;

private: System::Windows::Forms::Label^ label27;

private: System::Windows::Forms::Label^ label29;
private: System::Windows::Forms::ComboBox^ cmbVoltageRange_UUT;

private: System::Windows::Forms::ComboBox^ cmbDivider_UUT;
private: System::Windows::Forms::Label^ label6;
private: System::Windows::Forms::ComboBox^ cmbDivider_DMM;
private: System::Windows::Forms::Label^ lblTestInfo_DMM;







private: System::Windows::Forms::Panel^ pnlUUT_Param;
private: System::Windows::Forms::Panel^ pnlTestConfig;









private: System::Windows::Forms::Panel^ panel3;










private: System::Windows::Forms::Panel^ panel2;






private: System::Windows::Forms::Label^ lblTestInfo_UUT;
private: System::Windows::Forms::ToolStripButton^ tsbtnDeviceList;
private: System::Windows::Forms::Button^ btnReEnter;
private: System::Windows::Forms::Button^ btnContinue;
private: System::Windows::Forms::Label^ label3;
private: System::Windows::Forms::TextBox^ txtsfVpeak_DMM;

private: System::Windows::Forms::Label^ label11;
private: System::Windows::Forms::Label^ label12;
private: System::Windows::Forms::TextBox^ txtsfVpeak_UUT;

private: System::Windows::Forms::Label^ label24;
private: System::Windows::Forms::Label^ label28;
private: System::Windows::Forms::ComboBox^ cmbPeakType;
private: System::Windows::Forms::CheckBox^ chkRange_DMM;
private: System::Windows::Forms::CheckBox^ chkRange_UUT;
private: System::Windows::Forms::Label^ lblMaxVUnit_DMM;


private: System::Windows::Forms::TextBox^ txtAppliedVoltage_DMM;
private: System::Windows::Forms::Label^ label31;
private: System::Windows::Forms::Label^ lblMaxVUnit_UUT;


private: System::Windows::Forms::TextBox^ txtAppliedVoltage_UUT;
private: System::Windows::Forms::Label^ label33;

private: System::Windows::Forms::Panel^ panel4;


private: System::Windows::Forms::Label^ lblResultSumm_DMM;
private: System::Windows::Forms::CheckBox^ chkAddDateTime;
private: System::Windows::Forms::LinkLabel^ btnReadSTB;
private: System::Windows::Forms::ToolStripProgressBar^ toolStripProgressBar1;
private: System::Windows::Forms::ToolStripProgressBar^ toolStripProgressBar2;
private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel1;
private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel2;
private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart2;
private: System::Windows::Forms::Label^ lblMeasUnit_UUT;










private: System::Windows::Forms::Label^ lblMeasUnit_DMM;

private: System::Windows::Forms::TextBox^ txtLiveDC_UUT;
private: System::Windows::Forms::Label^ label36;
private: System::Windows::Forms::TextBox^ txtLiveDC;
private: System::Windows::Forms::Label^ label37;
private: System::Windows::Forms::TextBox^ txtsfVdc_UUT;
private: System::Windows::Forms::Label^ label38;
private: System::Windows::Forms::Label^ label39;
private: System::Windows::Forms::TextBox^ txtsfVdc_DMM;
private: System::Windows::Forms::Label^ label40;
private: System::Windows::Forms::CheckBox^ chkRangeAuto_DMM;
private: System::Windows::Forms::CheckBox^ chkRangeAuto_UUT;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column7;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column1;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ dgw_ColVrms;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ dgw_ColVroot;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column2;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column3;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column4;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column5;
private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column6;
private: System::Windows::Forms::Label^ label30;
private: System::Windows::Forms::Label^ label32;
private: System::Windows::Forms::Label^ label34;






















































































































































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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^ series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->chkAddDateTime = (gcnew System::Windows::Forms::CheckBox());
			this->btnReEnter = (gcnew System::Windows::Forms::Button());
			this->llblRefreshGrid = (gcnew System::Windows::Forms::LinkLabel());
			this->linkLabel1 = (gcnew System::Windows::Forms::LinkLabel());
			this->linkLabel2 = (gcnew System::Windows::Forms::LinkLabel());
			this->txtBarcode = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->gbWaveFormGraph = (gcnew System::Windows::Forms::GroupBox());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->btnExit = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->btnConnect = (gcnew System::Windows::Forms::ToolStripButton());
			this->btnDisconnect = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->tsbtnDeviceList = (gcnew System::Windows::Forms::ToolStripButton());
			this->btnSettings = (gcnew System::Windows::Forms::ToolStripButton());
			this->btnShowLog = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->helpToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->panelLog = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->linkClearLog = (gcnew System::Windows::Forms::LinkLabel());
			this->btnReadSTB = (gcnew System::Windows::Forms::LinkLabel());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->lblFooterCounter = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->lblFooter = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripProgressBar1 = (gcnew System::Windows::Forms::ToolStripProgressBar());
			this->toolStripStatusLabel2 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripProgressBar2 = (gcnew System::Windows::Forms::ToolStripProgressBar());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->chart2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->dgw_Sample = (gcnew System::Windows::Forms::DataGridView());
			this->Column7 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dgw_ColVrms = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dgw_ColVroot = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->lblResultSumm_DMM = (gcnew System::Windows::Forms::Label());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->txtLiveDC_UUT = (gcnew System::Windows::Forms::TextBox());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->txtLiveDC = (gcnew System::Windows::Forms::TextBox());
			this->lblMeasUnit_UUT = (gcnew System::Windows::Forms::Label());
			this->lblMeasUnit_DMM = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->txtLiveRMS_UUT = (gcnew System::Windows::Forms::TextBox());
			this->txtLivePeakRoot2_UUT = (gcnew System::Windows::Forms::TextBox());
			this->lblDemoMode = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->txtLiveRMS = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->txtLivePeakRoot2 = (gcnew System::Windows::Forms::TextBox());
			this->gBoxStartStop = (gcnew System::Windows::Forms::GroupBox());
			this->btnContinue = (gcnew System::Windows::Forms::Button());
			this->lblTestInfo_UUT = (gcnew System::Windows::Forms::Label());
			this->btnStart = (gcnew System::Windows::Forms::Button());
			this->pnlTestConfig = (gcnew System::Windows::Forms::Panel());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->cmbPeakType = (gcnew System::Windows::Forms::ComboBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->cmbMeasType = (gcnew System::Windows::Forms::ComboBox());
			this->lblFreqRange = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->txtFreq = (gcnew System::Windows::Forms::TextBox());
			this->lblTestInfo_DMM = (gcnew System::Windows::Forms::Label());
			this->pnlTestLive = (gcnew System::Windows::Forms::Panel());
			this->lblRemainData = (gcnew System::Windows::Forms::Label());
			this->lblPassTime = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->cmbSampleAdet = (gcnew System::Windows::Forms::ComboBox());
			this->gbDMM = (gcnew System::Windows::Forms::GroupBox());
			this->chkRangeAuto_DMM = (gcnew System::Windows::Forms::CheckBox());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->txtsfVdc_DMM = (gcnew System::Windows::Forms::TextBox());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->lblMaxVUnit_DMM = (gcnew System::Windows::Forms::Label());
			this->txtAppliedVoltage_DMM = (gcnew System::Windows::Forms::TextBox());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->chkRange_DMM = (gcnew System::Windows::Forms::CheckBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->txtsfVpeak_DMM = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->pnlUUT_Param = (gcnew System::Windows::Forms::Panel());
			this->chkRangeAuto_UUT = (gcnew System::Windows::Forms::CheckBox());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->txtsfVdc_UUT = (gcnew System::Windows::Forms::TextBox());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->lblMaxVUnit_UUT = (gcnew System::Windows::Forms::Label());
			this->txtAppliedVoltage_UUT = (gcnew System::Windows::Forms::TextBox());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->chkRange_UUT = (gcnew System::Windows::Forms::CheckBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->txtsfVpeak_UUT = (gcnew System::Windows::Forms::TextBox());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->cmbDivider_UUT = (gcnew System::Windows::Forms::ComboBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->cmbVoltageRange_UUT = (gcnew System::Windows::Forms::ComboBox());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->txtsfVrms_UUT = (gcnew System::Windows::Forms::TextBox());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->txtTerminal_UUT = (gcnew System::Windows::Forms::TextBox());
			this->txtZInput_UUT = (gcnew System::Windows::Forms::TextBox());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->lblZinput_UUT = (gcnew System::Windows::Forms::Label());
			this->cmbDivider_DMM = (gcnew System::Windows::Forms::ComboBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->cmbAddress_UUT = (gcnew System::Windows::Forms::ComboBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->cmbAddress_DMM = (gcnew System::Windows::Forms::ComboBox());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->txtTerminal_DMM = (gcnew System::Windows::Forms::TextBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->lblZinput_DMM = (gcnew System::Windows::Forms::Label());
			this->txtZInput_DMM = (gcnew System::Windows::Forms::TextBox());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->txtsfVrms_DMM = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->cmbVoltageRange_DMM = (gcnew System::Windows::Forms::ComboBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->panel1->SuspendLayout();
			this->gbWaveFormGraph->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->toolStrip1->SuspendLayout();
			this->panelLog->SuspendLayout();
			this->statusStrip1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->panel3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->BeginInit();
			this->panel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgw_Sample))->BeginInit();
			this->panel4->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->gBoxStartStop->SuspendLayout();
			this->pnlTestConfig->SuspendLayout();
			this->pnlTestLive->SuspendLayout();
			this->gbDMM->SuspendLayout();
			this->pnlUUT_Param->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->chkAddDateTime);
			this->panel1->Controls->Add(this->btnReEnter);
			this->panel1->Controls->Add(this->llblRefreshGrid);
			this->panel1->Controls->Add(this->linkLabel1);
			this->panel1->Controls->Add(this->linkLabel2);
			this->panel1->Controls->Add(this->txtBarcode);
			this->panel1->Controls->Add(this->label7);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel1->Location = System::Drawing::Point(3, 16);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(957, 68);
			this->panel1->TabIndex = 20;
			// 
			// chkAddDateTime
			// 
			this->chkAddDateTime->AutoSize = true;
			this->chkAddDateTime->Location = System::Drawing::Point(306, 38);
			this->chkAddDateTime->Name = L"chkAddDateTime";
			this->chkAddDateTime->Size = System::Drawing::Size(101, 17);
			this->chkAddDateTime->TabIndex = 33;
			this->chkAddDateTime->Text = L"Tarih/Saat Ekle";
			this->chkAddDateTime->UseVisualStyleBackColor = true;
			// 
			// btnReEnter
			// 
			this->btnReEnter->Location = System::Drawing::Point(516, 34);
			this->btnReEnter->Name = L"btnReEnter";
			this->btnReEnter->Size = System::Drawing::Size(163, 23);
			this->btnReEnter->TabIndex = 32;
			this->btnReEnter->Text = L"Undo";
			this->btnReEnter->UseVisualStyleBackColor = true;
			this->btnReEnter->Visible = false;
			this->btnReEnter->Click += gcnew System::EventHandler(this, &MainForm::btnReEnter_Click);
			// 
			// llblRefreshGrid
			// 
			this->llblRefreshGrid->AutoSize = true;
			this->llblRefreshGrid->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->llblRefreshGrid->Location = System::Drawing::Point(898, 11);
			this->llblRefreshGrid->Name = L"llblRefreshGrid";
			this->llblRefreshGrid->Size = System::Drawing::Size(36, 13);
			this->llblRefreshGrid->TabIndex = 27;
			this->llblRefreshGrid->TabStop = true;
			this->llblRefreshGrid->Text = L"Yenile";
			this->llblRefreshGrid->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MainForm::llblRefreshGrid_LinkClicked);
			// 
			// linkLabel1
			// 
			this->linkLabel1->AutoSize = true;
			this->linkLabel1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->linkLabel1->Location = System::Drawing::Point(15, 11);
			this->linkLabel1->Name = L"linkLabel1";
			this->linkLabel1->Size = System::Drawing::Size(79, 13);
			this->linkLabel1->TabIndex = 30;
			this->linkLabel1->TabStop = true;
			this->linkLabel1->Text = L"Sonuçları Aktar";
			this->linkLabel1->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MainForm::linkLabel1_LinkClicked);
			// 
			// linkLabel2
			// 
			this->linkLabel2->AutoSize = true;
			this->linkLabel2->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->linkLabel2->Location = System::Drawing::Point(790, 11);
			this->linkLabel2->Name = L"linkLabel2";
			this->linkLabel2->Size = System::Drawing::Size(90, 13);
			this->linkLabel2->TabIndex = 31;
			this->linkLabel2->TabStop = true;
			this->linkLabel2->Text = L"Sonuçları Temizle";
			this->linkLabel2->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MainForm::linkLabel2_LinkClicked);
			// 
			// txtBarcode
			// 
			this->txtBarcode->Location = System::Drawing::Point(78, 36);
			this->txtBarcode->Name = L"txtBarcode";
			this->txtBarcode->Size = System::Drawing::Size(222, 20);
			this->txtBarcode->TabIndex = 26;
			this->txtBarcode->Text = L"3";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label7->Location = System::Drawing::Point(15, 39);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(55, 13);
			this->label7->TabIndex = 25;
			this->label7->Text = L"Dosya Adı";
			// 
			// gbWaveFormGraph
			// 
			this->gbWaveFormGraph->Controls->Add(this->chart1);
			this->gbWaveFormGraph->Location = System::Drawing::Point(981, 284);
			this->gbWaveFormGraph->Name = L"gbWaveFormGraph";
			this->gbWaveFormGraph->Size = System::Drawing::Size(456, 446);
			this->gbWaveFormGraph->TabIndex = 49;
			this->gbWaveFormGraph->TabStop = false;
			this->gbWaveFormGraph->Text = L"Dalga Formu";
			// 
			// chart1
			// 
			chartArea1->AxisX->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::False;
			chartArea1->AxisX->Title = L"# ";
			chartArea1->AxisY->LabelStyle->Format = L"F3";
			chartArea1->AxisY->Title = L"kV (DMM)";
			chartArea1->AxisY->TitleFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			chartArea1->Name = L"ChartArea1";
			chartArea2->AxisX->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::False;
			chartArea2->AxisY->LabelStyle->Format = L"F3";
			chartArea2->AxisY->Title = L"kV (UUT)";
			chartArea2->AxisY->TitleFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold));
			chartArea2->Name = L"ChartArea2";
			this->chart1->ChartAreas->Add(chartArea1);
			this->chart1->ChartAreas->Add(chartArea2);
			this->chart1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->chart1->Location = System::Drawing::Point(3, 16);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->LegendText = L"DMM";
			series1->MarkerSize = 0;
			series1->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Diamond;
			series1->Name = L"Series1";
			series2->ChartArea = L"ChartArea2";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series2->LegendText = L"UUT";
			series2->MarkerSize = 0;
			series2->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Circle;
			series2->Name = L"Series2";
			this->chart1->Series->Add(series1);
			this->chart1->Series->Add(series2);
			this->chart1->Size = System::Drawing::Size(450, 427);
			this->chart1->TabIndex = 22;
			this->chart1->Text = L"chart1";
			// 
			// toolStrip1
			// 
			this->toolStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(10) {
				this->btnExit, this->toolStripSeparator,
					this->btnConnect, this->btnDisconnect, this->toolStripSeparator1, this->tsbtnDeviceList, this->btnSettings, this->btnShowLog,
					this->toolStripSeparator3, this->helpToolStripButton
			});
			this->toolStrip1->Location = System::Drawing::Point(0, 0);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(1676, 27);
			this->toolStrip1->TabIndex = 50;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// btnExit
			// 
			this->btnExit->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->btnExit->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnExit.Image")));
			this->btnExit->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->btnExit->Name = L"btnExit";
			this->btnExit->Size = System::Drawing::Size(36, 24);
			this->btnExit->Text = L"Çıkış";
			this->btnExit->Click += gcnew System::EventHandler(this, &MainForm::btnExit_Click);
			// 
			// toolStripSeparator
			// 
			this->toolStripSeparator->Name = L"toolStripSeparator";
			this->toolStripSeparator->Size = System::Drawing::Size(6, 27);
			// 
			// btnConnect
			// 
			this->btnConnect->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnConnect.Image")));
			this->btnConnect->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->btnConnect->Name = L"btnConnect";
			this->btnConnect->Size = System::Drawing::Size(67, 24);
			this->btnConnect->Text = L"Bağlan";
			this->btnConnect->Click += gcnew System::EventHandler(this, &MainForm::btnConnect_Click);
			// 
			// btnDisconnect
			// 
			this->btnDisconnect->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnDisconnect.Image")));
			this->btnDisconnect->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->btnDisconnect->Name = L"btnDisconnect";
			this->btnDisconnect->Size = System::Drawing::Size(80, 24);
			this->btnDisconnect->Text = L"Bağ. İptal";
			this->btnDisconnect->Visible = false;
			this->btnDisconnect->Click += gcnew System::EventHandler(this, &MainForm::btnDisconnect_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(6, 27);
			// 
			// tsbtnDeviceList
			// 
			this->tsbtnDeviceList->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->tsbtnDeviceList->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tsbtnDeviceList.Image")));
			this->tsbtnDeviceList->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->tsbtnDeviceList->Name = L"tsbtnDeviceList";
			this->tsbtnDeviceList->Size = System::Drawing::Size(92, 24);
			this->tsbtnDeviceList->Text = L"Ekipman Listesi";
			this->tsbtnDeviceList->Click += gcnew System::EventHandler(this, &MainForm::tsbtnDeviceList_Click);
			// 
			// btnSettings
			// 
			this->btnSettings->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnSettings.Image")));
			this->btnSettings->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->btnSettings->Name = L"btnSettings";
			this->btnSettings->Size = System::Drawing::Size(68, 24);
			this->btnSettings->Text = L"Ayarlar";
			this->btnSettings->Click += gcnew System::EventHandler(this, &MainForm::btnSettings_Click);
			// 
			// btnShowLog
			// 
			this->btnShowLog->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->btnShowLog->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnShowLog.Image")));
			this->btnShowLog->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->btnShowLog->Name = L"btnShowLog";
			this->btnShowLog->Size = System::Drawing::Size(135, 24);
			this->btnShowLog->Text = L"İletişim Loglarını Göster";
			this->btnShowLog->Click += gcnew System::EventHandler(this, &MainForm::btnShowLog_Click);
			// 
			// toolStripSeparator3
			// 
			this->toolStripSeparator3->Name = L"toolStripSeparator3";
			this->toolStripSeparator3->Size = System::Drawing::Size(6, 27);
			// 
			// helpToolStripButton
			// 
			this->helpToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"helpToolStripButton.Image")));
			this->helpToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->helpToolStripButton->Name = L"helpToolStripButton";
			this->helpToolStripButton->Size = System::Drawing::Size(81, 24);
			this->helpToolStripButton->Text = L"Hakkında";
			this->helpToolStripButton->Click += gcnew System::EventHandler(this, &MainForm::helpToolStripButton_Click);
			// 
			// panelLog
			// 
			this->panelLog->ColumnCount = 1;
			this->panelLog->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100)));
			this->panelLog->Controls->Add(this->richTextBox1, 0, 2);
			this->panelLog->Controls->Add(this->linkClearLog, 0, 0);
			this->panelLog->Controls->Add(this->btnReadSTB, 0, 1);
			this->panelLog->Dock = System::Windows::Forms::DockStyle::Right;
			this->panelLog->Location = System::Drawing::Point(1443, 27);
			this->panelLog->Name = L"panelLog";
			this->panelLog->RowCount = 3;
			this->panelLog->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->panelLog->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->panelLog->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->panelLog->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->panelLog->Size = System::Drawing::Size(233, 735);
			this->panelLog->TabIndex = 51;
			// 
			// richTextBox1
			// 
			this->richTextBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->richTextBox1->Location = System::Drawing::Point(3, 43);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(227, 689);
			this->richTextBox1->TabIndex = 34;
			this->richTextBox1->Text = L"";
			// 
			// linkClearLog
			// 
			this->linkClearLog->AutoSize = true;
			this->linkClearLog->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->linkClearLog->Location = System::Drawing::Point(3, 0);
			this->linkClearLog->Name = L"linkClearLog";
			this->linkClearLog->Size = System::Drawing::Size(43, 13);
			this->linkClearLog->TabIndex = 35;
			this->linkClearLog->TabStop = true;
			this->linkClearLog->Text = L"Temizle";
			this->linkClearLog->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MainForm::linkClearLog_LinkClicked);
			// 
			// btnReadSTB
			// 
			this->btnReadSTB->AutoSize = true;
			this->btnReadSTB->Location = System::Drawing::Point(3, 20);
			this->btnReadSTB->Name = L"btnReadSTB";
			this->btnReadSTB->Size = System::Drawing::Size(34, 13);
			this->btnReadSTB->TabIndex = 36;
			this->btnReadSTB->TabStop = true;
			this->btnReadSTB->Text = L"STB\?";
			this->btnReadSTB->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MainForm::btnReadSTB_LinkClicked);
			// 
			// statusStrip1
			// 
			this->statusStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->lblFooterCounter,
					this->lblFooter, this->toolStripStatusLabel1, this->toolStripProgressBar1, this->toolStripStatusLabel2, this->toolStripProgressBar2
			});
			this->statusStrip1->Location = System::Drawing::Point(0, 762);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(1676, 22);
			this->statusStrip1->TabIndex = 52;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// lblFooterCounter
			// 
			this->lblFooterCounter->Name = L"lblFooterCounter";
			this->lblFooterCounter->Size = System::Drawing::Size(33, 17);
			this->lblFooterCounter->Text = L" 3 / 5";
			// 
			// lblFooter
			// 
			this->lblFooter->Name = L"lblFooter";
			this->lblFooter->Size = System::Drawing::Size(16, 17);
			this->lblFooter->Text = L"...";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Margin = System::Windows::Forms::Padding(50, 3, 0, 2);
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(37, 17);
			this->toolStripStatusLabel1->Text = L"DMM";
			// 
			// toolStripProgressBar1
			// 
			this->toolStripProgressBar1->Name = L"toolStripProgressBar1";
			this->toolStripProgressBar1->Size = System::Drawing::Size(100, 16);
			// 
			// toolStripStatusLabel2
			// 
			this->toolStripStatusLabel2->Name = L"toolStripStatusLabel2";
			this->toolStripStatusLabel2->Size = System::Drawing::Size(29, 17);
			this->toolStripStatusLabel2->Text = L"UUT";
			// 
			// toolStripProgressBar2
			// 
			this->toolStripProgressBar2->Name = L"toolStripProgressBar2";
			this->toolStripProgressBar2->Size = System::Drawing::Size(100, 16);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->panel3);
			this->groupBox2->Controls->Add(this->panel2);
			this->groupBox2->Controls->Add(this->panel1);
			this->groupBox2->Location = System::Drawing::Point(15, 348);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(963, 385);
			this->groupBox2->TabIndex = 48;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Sonuçlar";
			// 
			// panel3
			// 
			this->panel3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->panel3->Controls->Add(this->chart2);
			this->panel3->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel3->Location = System::Drawing::Point(519, 84);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(441, 298);
			this->panel3->TabIndex = 22;
			// 
			// chart2
			// 
			chartArea3->AxisX->LabelStyle->Format = L"F2";
			chartArea3->AxisX->Title = L"V";
			chartArea3->AxisY->LabelStyle->Format = L"F3";
			chartArea3->AxisY->Title = L"s.f. UUT";
			chartArea3->Name = L"ChartArea1";
			this->chart2->ChartAreas->Add(chartArea3);
			this->chart2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->chart2->Location = System::Drawing::Point(0, 0);
			this->chart2->Name = L"chart2";
			series3->ChartArea = L"ChartArea1";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series3->LegendText = L"DMM";
			series3->MarkerStyle = System::Windows::Forms::DataVisualization::Charting::MarkerStyle::Diamond;
			series3->Name = L"Series1";
			this->chart2->Series->Add(series3);
			this->chart2->Size = System::Drawing::Size(441, 298);
			this->chart2->TabIndex = 23;
			this->chart2->Text = L"chart2";
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->dgw_Sample);
			this->panel2->Controls->Add(this->panel4);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel2->Location = System::Drawing::Point(3, 84);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(510, 298);
			this->panel2->TabIndex = 21;
			// 
			// dgw_Sample
			// 
			this->dgw_Sample->AllowUserToAddRows = false;
			this->dgw_Sample->AllowUserToDeleteRows = false;
			this->dgw_Sample->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgw_Sample->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(9) {
				this->Column7, this->Column1,
					this->dgw_ColVrms, this->dgw_ColVroot, this->Column2, this->Column3, this->Column4, this->Column5, this->Column6
			});
			this->dgw_Sample->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dgw_Sample->Location = System::Drawing::Point(0, 0);
			this->dgw_Sample->Name = L"dgw_Sample";
			this->dgw_Sample->ReadOnly = true;
			this->dgw_Sample->RowHeadersVisible = false;
			this->dgw_Sample->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dgw_Sample->Size = System::Drawing::Size(510, 271);
			this->dgw_Sample->TabIndex = 19;
			this->dgw_Sample->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MainForm::dgw_Sample_CellClick);
			// 
			// Column7
			// 
			this->Column7->DataPropertyName = L"TestNo";
			this->Column7->HeaderText = L"#";
			this->Column7->Name = L"Column7";
			this->Column7->ReadOnly = true;
			this->Column7->Width = 25;
			// 
			// Column1
			// 
			this->Column1->DataPropertyName = L"SampleNo";
			this->Column1->HeaderText = L"No";
			this->Column1->Name = L"Column1";
			this->Column1->ReadOnly = true;
			this->Column1->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Column1->Width = 25;
			// 
			// dgw_ColVrms
			// 
			this->dgw_ColVrms->DataPropertyName = L"V_kV";
			this->dgw_ColVrms->HeaderText = L"High Volt. Ref (kV)";
			this->dgw_ColVrms->Name = L"dgw_ColVrms";
			this->dgw_ColVrms->ReadOnly = true;
			this->dgw_ColVrms->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->dgw_ColVrms->Width = 150;
			// 
			// dgw_ColVroot
			// 
			this->dgw_ColVroot->DataPropertyName = L"V_kV_UUT";
			this->dgw_ColVroot->HeaderText = L"High Volt. Uuut (kV)";
			this->dgw_ColVroot->Name = L"dgw_ColVroot";
			this->dgw_ColVroot->ReadOnly = true;
			this->dgw_ColVroot->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->dgw_ColVroot->Width = 150;
			// 
			// Column2
			// 
			this->Column2->DataPropertyName = L"ScaleFactor";
			dataGridViewCellStyle1->Format = L"F4";
			this->Column2->DefaultCellStyle = dataGridViewCellStyle1;
			this->Column2->HeaderText = L"Scale Factor";
			this->Column2->Name = L"Column2";
			this->Column2->ReadOnly = true;
			// 
			// Column3
			// 
			this->Column3->DataPropertyName = L"V_Raw";
			this->Column3->HeaderText = L"V_Raw (V)";
			this->Column3->Name = L"Column3";
			this->Column3->ReadOnly = true;
			// 
			// Column4
			// 
			this->Column4->DataPropertyName = L"Ratio";
			this->Column4->HeaderText = L"Ratio";
			this->Column4->Name = L"Column4";
			this->Column4->ReadOnly = true;
			this->Column4->Visible = false;
			// 
			// Column5
			// 
			this->Column5->DataPropertyName = L"V_Raw_UUT";
			this->Column5->HeaderText = L"V_Raw_UUT (V)";
			this->Column5->Name = L"Column5";
			this->Column5->ReadOnly = true;
			// 
			// Column6
			// 
			this->Column6->DataPropertyName = L"Ratio_UUT";
			this->Column6->HeaderText = L"Ratio_UUT";
			this->Column6->Name = L"Column6";
			this->Column6->ReadOnly = true;
			this->Column6->Visible = false;
			// 
			// panel4
			// 
			this->panel4->Controls->Add(this->lblResultSumm_DMM);
			this->panel4->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel4->Location = System::Drawing::Point(0, 271);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(510, 27);
			this->panel4->TabIndex = 20;
			// 
			// lblResultSumm_DMM
			// 
			this->lblResultSumm_DMM->AutoSize = true;
			this->lblResultSumm_DMM->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblResultSumm_DMM->Location = System::Drawing::Point(6, 8);
			this->lblResultSumm_DMM->Name = L"lblResultSumm_DMM";
			this->lblResultSumm_DMM->Size = System::Drawing::Size(19, 13);
			this->lblResultSumm_DMM->TabIndex = 0;
			this->lblResultSumm_DMM->Text = L"...";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->txtLiveDC_UUT);
			this->groupBox3->Controls->Add(this->txtLiveDC);
			this->groupBox3->Controls->Add(this->lblMeasUnit_UUT);
			this->groupBox3->Controls->Add(this->lblMeasUnit_DMM);
			this->groupBox3->Controls->Add(this->label10);
			this->groupBox3->Controls->Add(this->label8);
			this->groupBox3->Controls->Add(this->txtLiveRMS_UUT);
			this->groupBox3->Controls->Add(this->txtLivePeakRoot2_UUT);
			this->groupBox3->Controls->Add(this->lblDemoMode);
			this->groupBox3->Controls->Add(this->txtLiveRMS);
			this->groupBox3->Controls->Add(this->txtLivePeakRoot2);
			this->groupBox3->Controls->Add(this->label5);
			this->groupBox3->Controls->Add(this->label36);
			this->groupBox3->Controls->Add(this->label2);
			this->groupBox3->Controls->Add(this->label30);
			this->groupBox3->Controls->Add(this->label32);
			this->groupBox3->Controls->Add(this->label34);
			this->groupBox3->Location = System::Drawing::Point(981, 30);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(456, 242);
			this->groupBox3->TabIndex = 46;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Önizleme";
			// 
			// txtLiveDC_UUT
			// 
			this->txtLiveDC_UUT->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->txtLiveDC_UUT->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtLiveDC_UUT->ForeColor = System::Drawing::SystemColors::Info;
			this->txtLiveDC_UUT->Location = System::Drawing::Point(228, 197);
			this->txtLiveDC_UUT->Name = L"txtLiveDC_UUT";
			this->txtLiveDC_UUT->ReadOnly = true;
			this->txtLiveDC_UUT->Size = System::Drawing::Size(209, 35);
			this->txtLiveDC_UUT->TabIndex = 42;
			this->txtLiveDC_UUT->Text = L"10,34 kV";
			this->txtLiveDC_UUT->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F));
			this->label36->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label36->Location = System::Drawing::Point(6, 176);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(49, 25);
			this->label36->TabIndex = 41;
			this->label36->Text = L"Vdc";
			// 
			// txtLiveDC
			// 
			this->txtLiveDC->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->txtLiveDC->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtLiveDC->ForeColor = System::Drawing::SystemColors::Info;
			this->txtLiveDC->Location = System::Drawing::Point(11, 198);
			this->txtLiveDC->Name = L"txtLiveDC";
			this->txtLiveDC->ReadOnly = true;
			this->txtLiveDC->Size = System::Drawing::Size(199, 35);
			this->txtLiveDC->TabIndex = 40;
			this->txtLiveDC->Text = L"10,34 kV";
			this->txtLiveDC->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// lblMeasUnit_UUT
			// 
			this->lblMeasUnit_UUT->AutoSize = true;
			this->lblMeasUnit_UUT->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F));
			this->lblMeasUnit_UUT->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->lblMeasUnit_UUT->Location = System::Drawing::Point(387, 45);
			this->lblMeasUnit_UUT->Name = L"lblMeasUnit_UUT";
			this->lblMeasUnit_UUT->Size = System::Drawing::Size(37, 25);
			this->lblMeasUnit_UUT->TabIndex = 39;
			this->lblMeasUnit_UUT->Text = L"kV";
			this->lblMeasUnit_UUT->Visible = false;
			// 
			// lblMeasUnit_DMM
			// 
			this->lblMeasUnit_DMM->AutoSize = true;
			this->lblMeasUnit_DMM->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F));
			this->lblMeasUnit_DMM->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->lblMeasUnit_DMM->Location = System::Drawing::Point(173, 48);
			this->lblMeasUnit_DMM->Name = L"lblMeasUnit_DMM";
			this->lblMeasUnit_DMM->Size = System::Drawing::Size(37, 25);
			this->lblMeasUnit_DMM->TabIndex = 38;
			this->lblMeasUnit_DMM->Text = L"kV";
			this->lblMeasUnit_DMM->Visible = false;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F));
			this->label10->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label10->Location = System::Drawing::Point(269, 31);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(112, 25);
			this->label10->TabIndex = 37;
			this->label10->Text = L"UUT DMM";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F));
			this->label8->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label8->Location = System::Drawing::Point(59, 31);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(108, 25);
			this->label8->TabIndex = 36;
			this->label8->Text = L"Ref. DMM";
			// 
			// txtLiveRMS_UUT
			// 
			this->txtLiveRMS_UUT->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->txtLiveRMS_UUT->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtLiveRMS_UUT->ForeColor = System::Drawing::SystemColors::Info;
			this->txtLiveRMS_UUT->Location = System::Drawing::Point(228, 77);
			this->txtLiveRMS_UUT->Name = L"txtLiveRMS_UUT";
			this->txtLiveRMS_UUT->ReadOnly = true;
			this->txtLiveRMS_UUT->Size = System::Drawing::Size(209, 35);
			this->txtLiveRMS_UUT->TabIndex = 33;
			this->txtLiveRMS_UUT->Text = L"10,34 kV";
			this->txtLiveRMS_UUT->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// txtLivePeakRoot2_UUT
			// 
			this->txtLivePeakRoot2_UUT->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->txtLivePeakRoot2_UUT->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->txtLivePeakRoot2_UUT->ForeColor = System::Drawing::SystemColors::Info;
			this->txtLivePeakRoot2_UUT->Location = System::Drawing::Point(228, 137);
			this->txtLivePeakRoot2_UUT->Name = L"txtLivePeakRoot2_UUT";
			this->txtLivePeakRoot2_UUT->ReadOnly = true;
			this->txtLivePeakRoot2_UUT->Size = System::Drawing::Size(209, 35);
			this->txtLivePeakRoot2_UUT->TabIndex = 35;
			this->txtLivePeakRoot2_UUT->Text = L"10,34 kV";
			this->txtLivePeakRoot2_UUT->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// lblDemoMode
			// 
			this->lblDemoMode->AutoSize = true;
			this->lblDemoMode->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F));
			this->lblDemoMode->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->lblDemoMode->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->lblDemoMode->Location = System::Drawing::Point(156, 7);
			this->lblDemoMode->Name = L"lblDemoMode";
			this->lblDemoMode->Size = System::Drawing::Size(128, 25);
			this->lblDemoMode->TabIndex = 32;
			this->lblDemoMode->Text = L"Demo Mode";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F));
			this->label5->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label5->Location = System::Drawing::Point(6, 112);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(103, 25);
			this->label5->TabIndex = 31;
			this->label5->Text = L"Vpeak/√2";
			// 
			// txtLiveRMS
			// 
			this->txtLiveRMS->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->txtLiveRMS->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtLiveRMS->ForeColor = System::Drawing::SystemColors::Info;
			this->txtLiveRMS->Location = System::Drawing::Point(11, 78);
			this->txtLiveRMS->Name = L"txtLiveRMS";
			this->txtLiveRMS->ReadOnly = true;
			this->txtLiveRMS->Size = System::Drawing::Size(199, 35);
			this->txtLiveRMS->TabIndex = 25;
			this->txtLiveRMS->Text = L"10,3456565 kV";
			this->txtLiveRMS->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F));
			this->label2->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label2->Location = System::Drawing::Point(7, 52);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(61, 25);
			this->label2->TabIndex = 26;
			this->label2->Text = L"Vrms";
			// 
			// txtLivePeakRoot2
			// 
			this->txtLivePeakRoot2->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->txtLivePeakRoot2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtLivePeakRoot2->ForeColor = System::Drawing::SystemColors::Info;
			this->txtLivePeakRoot2->Location = System::Drawing::Point(11, 138);
			this->txtLivePeakRoot2->Name = L"txtLivePeakRoot2";
			this->txtLivePeakRoot2->ReadOnly = true;
			this->txtLivePeakRoot2->Size = System::Drawing::Size(199, 35);
			this->txtLivePeakRoot2->TabIndex = 29;
			this->txtLivePeakRoot2->Text = L"10,34 kV";
			this->txtLivePeakRoot2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// gBoxStartStop
			// 
			this->gBoxStartStop->Controls->Add(this->btnContinue);
			this->gBoxStartStop->Controls->Add(this->lblTestInfo_UUT);
			this->gBoxStartStop->Controls->Add(this->btnStart);
			this->gBoxStartStop->Controls->Add(this->pnlTestConfig);
			this->gBoxStartStop->Controls->Add(this->lblTestInfo_DMM);
			this->gBoxStartStop->Controls->Add(this->pnlTestLive);
			this->gBoxStartStop->Controls->Add(this->label9);
			this->gBoxStartStop->Controls->Add(this->cmbSampleAdet);
			this->gBoxStartStop->Location = System::Drawing::Point(554, 30);
			this->gBoxStartStop->Name = L"gBoxStartStop";
			this->gBoxStartStop->Size = System::Drawing::Size(421, 312);
			this->gBoxStartStop->TabIndex = 47;
			this->gBoxStartStop->TabStop = false;
			this->gBoxStartStop->Text = L"Test Ayarları";
			// 
			// btnContinue
			// 
			this->btnContinue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold));
			this->btnContinue->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->btnContinue->Location = System::Drawing::Point(21, 176);
			this->btnContinue->Name = L"btnContinue";
			this->btnContinue->Size = System::Drawing::Size(200, 36);
			this->btnContinue->TabIndex = 37;
			this->btnContinue->Text = L"Devam";
			this->btnContinue->UseVisualStyleBackColor = true;
			this->btnContinue->Visible = false;
			this->btnContinue->Click += gcnew System::EventHandler(this, &MainForm::btnContinue_Click);
			// 
			// lblTestInfo_UUT
			// 
			this->lblTestInfo_UUT->AutoSize = true;
			this->lblTestInfo_UUT->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTestInfo_UUT->ForeColor = System::Drawing::Color::Red;
			this->lblTestInfo_UUT->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->lblTestInfo_UUT->Location = System::Drawing::Point(18, 154);
			this->lblTestInfo_UUT->Name = L"lblTestInfo_UUT";
			this->lblTestInfo_UUT->Size = System::Drawing::Size(139, 13);
			this->lblTestInfo_UUT->TabIndex = 36;
			this->lblTestInfo_UUT->Text = L"UUT DMM 20 örneklem";
			// 
			// btnStart
			// 
			this->btnStart->Enabled = false;
			this->btnStart->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold));
			this->btnStart->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->btnStart->Location = System::Drawing::Point(228, 215);
			this->btnStart->Name = L"btnStart";
			this->btnStart->Size = System::Drawing::Size(170, 81);
			this->btnStart->TabIndex = 18;
			this->btnStart->Text = L"Örneklem Al";
			this->btnStart->UseVisualStyleBackColor = true;
			this->btnStart->Click += gcnew System::EventHandler(this, &MainForm::btnStart_Click);
			// 
			// pnlTestConfig
			// 
			this->pnlTestConfig->Controls->Add(this->label28);
			this->pnlTestConfig->Controls->Add(this->cmbPeakType);
			this->pnlTestConfig->Controls->Add(this->label1);
			this->pnlTestConfig->Controls->Add(this->cmbMeasType);
			this->pnlTestConfig->Controls->Add(this->lblFreqRange);
			this->pnlTestConfig->Controls->Add(this->label4);
			this->pnlTestConfig->Controls->Add(this->txtFreq);
			this->pnlTestConfig->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->pnlTestConfig->Location = System::Drawing::Point(6, 13);
			this->pnlTestConfig->Name = L"pnlTestConfig";
			this->pnlTestConfig->Size = System::Drawing::Size(382, 76);
			this->pnlTestConfig->TabIndex = 35;
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label28->Location = System::Drawing::Point(12, 30);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(67, 13);
			this->label28->TabIndex = 35;
			this->label28->Text = L"Ölçüm Tipi";
			// 
			// cmbPeakType
			// 
			this->cmbPeakType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbPeakType->FormattingEnabled = true;
			this->cmbPeakType->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Vrms/ Vdc", L"Vpeak" });
			this->cmbPeakType->Location = System::Drawing::Point(132, 27);
			this->cmbPeakType->Name = L"cmbPeakType";
			this->cmbPeakType->Size = System::Drawing::Size(177, 21);
			this->cmbPeakType->TabIndex = 34;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label1->Location = System::Drawing::Point(12, 6);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(57, 13);
			this->label1->TabIndex = 30;
			this->label1->Text = L"Test Tipi";
			// 
			// cmbMeasType
			// 
			this->cmbMeasType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbMeasType->FormattingEnabled = true;
			this->cmbMeasType->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"AC", L"DC", L"AC (Peak)" });
			this->cmbMeasType->Location = System::Drawing::Point(132, 3);
			this->cmbMeasType->Name = L"cmbMeasType";
			this->cmbMeasType->Size = System::Drawing::Size(177, 21);
			this->cmbMeasType->TabIndex = 29;
			this->cmbMeasType->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::cmbMeasType_SelectedIndexChanged);
			// 
			// lblFreqRange
			// 
			this->lblFreqRange->AutoSize = true;
			this->lblFreqRange->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->lblFreqRange->Location = System::Drawing::Point(238, 55);
			this->lblFreqRange->Name = L"lblFreqRange";
			this->lblFreqRange->Size = System::Drawing::Size(84, 13);
			this->lblFreqRange->TabIndex = 33;
			this->lblFreqRange->Text = L"0.01 - 300 Hz";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label4->Location = System::Drawing::Point(12, 55);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(52, 13);
			this->label4->TabIndex = 31;
			this->label4->Text = L"Frekans";
			// 
			// txtFreq
			// 
			this->txtFreq->Location = System::Drawing::Point(132, 52);
			this->txtFreq->Name = L"txtFreq";
			this->txtFreq->Size = System::Drawing::Size(100, 20);
			this->txtFreq->TabIndex = 32;
			this->txtFreq->Text = L"3";
			this->txtFreq->TextChanged += gcnew System::EventHandler(this, &MainForm::txtFreq_TextChanged);
			// 
			// lblTestInfo_DMM
			// 
			this->lblTestInfo_DMM->AutoSize = true;
			this->lblTestInfo_DMM->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTestInfo_DMM->ForeColor = System::Drawing::Color::Red;
			this->lblTestInfo_DMM->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->lblTestInfo_DMM->Location = System::Drawing::Point(18, 128);
			this->lblTestInfo_DMM->Name = L"lblTestInfo_DMM";
			this->lblTestInfo_DMM->Size = System::Drawing::Size(109, 13);
			this->lblTestInfo_DMM->TabIndex = 34;
			this->lblTestInfo_DMM->Text = L"Ref. DMM 20 PLC";
			// 
			// pnlTestLive
			// 
			this->pnlTestLive->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->pnlTestLive->Controls->Add(this->lblRemainData);
			this->pnlTestLive->Controls->Add(this->lblPassTime);
			this->pnlTestLive->Location = System::Drawing::Point(21, 215);
			this->pnlTestLive->Name = L"pnlTestLive";
			this->pnlTestLive->Size = System::Drawing::Size(200, 81);
			this->pnlTestLive->TabIndex = 28;
			this->pnlTestLive->Visible = false;
			// 
			// lblRemainData
			// 
			this->lblRemainData->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->lblRemainData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F));
			this->lblRemainData->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->lblRemainData->Location = System::Drawing::Point(0, 45);
			this->lblRemainData->Name = L"lblRemainData";
			this->lblRemainData->Size = System::Drawing::Size(200, 36);
			this->lblRemainData->TabIndex = 27;
			this->lblRemainData->Text = L" 5 / 10";
			this->lblRemainData->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblPassTime
			// 
			this->lblPassTime->Dock = System::Windows::Forms::DockStyle::Top;
			this->lblPassTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24));
			this->lblPassTime->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->lblPassTime->Location = System::Drawing::Point(0, 0);
			this->lblPassTime->Name = L"lblPassTime";
			this->lblPassTime->Size = System::Drawing::Size(200, 64);
			this->lblPassTime->TabIndex = 26;
			this->lblPassTime->Text = L"02:45";
			this->lblPassTime->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label9->Location = System::Drawing::Point(18, 99);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(97, 13);
			this->label9->TabIndex = 16;
			this->label9->Text = L"Örneklem Sayısı";
			// 
			// cmbSampleAdet
			// 
			this->cmbSampleAdet->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cmbSampleAdet->FormatString = L"N0";
			this->cmbSampleAdet->FormattingEnabled = true;
			this->cmbSampleAdet->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"5", L"10", L"15" });
			this->cmbSampleAdet->Location = System::Drawing::Point(138, 95);
			this->cmbSampleAdet->Name = L"cmbSampleAdet";
			this->cmbSampleAdet->Size = System::Drawing::Size(100, 21);
			this->cmbSampleAdet->TabIndex = 15;
			this->cmbSampleAdet->TextChanged += gcnew System::EventHandler(this, &MainForm::cmbSampleAdet_TextChanged);
			// 
			// gbDMM
			// 
			this->gbDMM->Controls->Add(this->chkRangeAuto_DMM);
			this->gbDMM->Controls->Add(this->label39);
			this->gbDMM->Controls->Add(this->txtsfVdc_DMM);
			this->gbDMM->Controls->Add(this->label40);
			this->gbDMM->Controls->Add(this->lblMaxVUnit_DMM);
			this->gbDMM->Controls->Add(this->txtAppliedVoltage_DMM);
			this->gbDMM->Controls->Add(this->label31);
			this->gbDMM->Controls->Add(this->chkRange_DMM);
			this->gbDMM->Controls->Add(this->label3);
			this->gbDMM->Controls->Add(this->txtsfVpeak_DMM);
			this->gbDMM->Controls->Add(this->label11);
			this->gbDMM->Controls->Add(this->pnlUUT_Param);
			this->gbDMM->Controls->Add(this->cmbDivider_DMM);
			this->gbDMM->Controls->Add(this->label13);
			this->gbDMM->Controls->Add(this->cmbAddress_UUT);
			this->gbDMM->Controls->Add(this->label18);
			this->gbDMM->Controls->Add(this->cmbAddress_DMM);
			this->gbDMM->Controls->Add(this->label20);
			this->gbDMM->Controls->Add(this->label22);
			this->gbDMM->Controls->Add(this->txtTerminal_DMM);
			this->gbDMM->Controls->Add(this->label21);
			this->gbDMM->Controls->Add(this->lblZinput_DMM);
			this->gbDMM->Controls->Add(this->txtZInput_DMM);
			this->gbDMM->Controls->Add(this->label19);
			this->gbDMM->Controls->Add(this->label16);
			this->gbDMM->Controls->Add(this->txtsfVrms_DMM);
			this->gbDMM->Controls->Add(this->label17);
			this->gbDMM->Controls->Add(this->label14);
			this->gbDMM->Controls->Add(this->cmbVoltageRange_DMM);
			this->gbDMM->Controls->Add(this->label15);
			this->gbDMM->Location = System::Drawing::Point(15, 30);
			this->gbDMM->Name = L"gbDMM";
			this->gbDMM->Size = System::Drawing::Size(533, 312);
			this->gbDMM->TabIndex = 53;
			this->gbDMM->TabStop = false;
			this->gbDMM->Text = L"Multimetreler";
			// 
			// chkRangeAuto_DMM
			// 
			this->chkRangeAuto_DMM->AutoSize = true;
			this->chkRangeAuto_DMM->Location = System::Drawing::Point(181, 105);
			this->chkRangeAuto_DMM->Name = L"chkRangeAuto_DMM";
			this->chkRangeAuto_DMM->Size = System::Drawing::Size(74, 17);
			this->chkRangeAuto_DMM->TabIndex = 74;
			this->chkRangeAuto_DMM->Text = L"Auto Rng.";
			this->chkRangeAuto_DMM->UseVisualStyleBackColor = true;
			this->chkRangeAuto_DMM->CheckedChanged += gcnew System::EventHandler(this, &MainForm::chkRangeAuto_DMM_CheckedChanged);
			// 
			// label39
			// 
			this->label39->AutoSize = true;
			this->label39->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label39->Location = System::Drawing::Point(178, 211);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(19, 13);
			this->label39->TabIndex = 73;
			this->label39->Text = L"xV";
			// 
			// txtsfVdc_DMM
			// 
			this->txtsfVdc_DMM->Location = System::Drawing::Point(72, 209);
			this->txtsfVdc_DMM->Name = L"txtsfVdc_DMM";
			this->txtsfVdc_DMM->ReadOnly = true;
			this->txtsfVdc_DMM->Size = System::Drawing::Size(100, 20);
			this->txtsfVdc_DMM->TabIndex = 72;
			this->txtsfVdc_DMM->Text = L"1000,95";
			// 
			// label40
			// 
			this->label40->AutoSize = true;
			this->label40->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label40->Location = System::Drawing::Point(3, 214);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(43, 13);
			this->label40->TabIndex = 71;
			this->label40->Text = L"s.f. Vdc";
			// 
			// lblMaxVUnit_DMM
			// 
			this->lblMaxVUnit_DMM->AutoSize = true;
			this->lblMaxVUnit_DMM->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->lblMaxVUnit_DMM->Location = System::Drawing::Point(178, 133);
			this->lblMaxVUnit_DMM->Name = L"lblMaxVUnit_DMM";
			this->lblMaxVUnit_DMM->Size = System::Drawing::Size(20, 13);
			this->lblMaxVUnit_DMM->TabIndex = 70;
			this->lblMaxVUnit_DMM->Text = L"kV";
			// 
			// txtAppliedVoltage_DMM
			// 
			this->txtAppliedVoltage_DMM->Location = System::Drawing::Point(72, 131);
			this->txtAppliedVoltage_DMM->Name = L"txtAppliedVoltage_DMM";
			this->txtAppliedVoltage_DMM->ReadOnly = true;
			this->txtAppliedVoltage_DMM->Size = System::Drawing::Size(100, 20);
			this->txtAppliedVoltage_DMM->TabIndex = 69;
			this->txtAppliedVoltage_DMM->TextChanged += gcnew System::EventHandler(this, &MainForm::txtAppliedVoltage_DMM_TextChanged);
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label31->Location = System::Drawing::Point(3, 136);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(61, 13);
			this->label31->TabIndex = 68;
			this->label31->Text = L"Max Gerilim";
			// 
			// chkRange_DMM
			// 
			this->chkRange_DMM->AutoSize = true;
			this->chkRange_DMM->Location = System::Drawing::Point(204, 133);
			this->chkRange_DMM->Name = L"chkRange_DMM";
			this->chkRange_DMM->Size = System::Drawing::Size(50, 17);
			this->chkRange_DMM->TabIndex = 67;
			this->chkRange_DMM->Text = L"Calc.";
			this->chkRange_DMM->UseVisualStyleBackColor = true;
			this->chkRange_DMM->CheckedChanged += gcnew System::EventHandler(this, &MainForm::chkRange_DMM_CheckedChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label3->Location = System::Drawing::Point(178, 185);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(19, 13);
			this->label3->TabIndex = 66;
			this->label3->Text = L"xV";
			// 
			// txtsfVpeak_DMM
			// 
			this->txtsfVpeak_DMM->Location = System::Drawing::Point(72, 183);
			this->txtsfVpeak_DMM->Name = L"txtsfVpeak_DMM";
			this->txtsfVpeak_DMM->ReadOnly = true;
			this->txtsfVpeak_DMM->Size = System::Drawing::Size(100, 20);
			this->txtsfVpeak_DMM->TabIndex = 65;
			this->txtsfVpeak_DMM->Text = L"1000,95";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label11->Location = System::Drawing::Point(3, 188);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(55, 13);
			this->label11->TabIndex = 64;
			this->label11->Text = L"s.f. Vpeak";
			// 
			// pnlUUT_Param
			// 
			this->pnlUUT_Param->Controls->Add(this->chkRangeAuto_UUT);
			this->pnlUUT_Param->Controls->Add(this->label37);
			this->pnlUUT_Param->Controls->Add(this->txtsfVdc_UUT);
			this->pnlUUT_Param->Controls->Add(this->label38);
			this->pnlUUT_Param->Controls->Add(this->lblMaxVUnit_UUT);
			this->pnlUUT_Param->Controls->Add(this->txtAppliedVoltage_UUT);
			this->pnlUUT_Param->Controls->Add(this->label33);
			this->pnlUUT_Param->Controls->Add(this->chkRange_UUT);
			this->pnlUUT_Param->Controls->Add(this->label12);
			this->pnlUUT_Param->Controls->Add(this->txtsfVpeak_UUT);
			this->pnlUUT_Param->Controls->Add(this->label24);
			this->pnlUUT_Param->Controls->Add(this->label29);
			this->pnlUUT_Param->Controls->Add(this->cmbDivider_UUT);
			this->pnlUUT_Param->Controls->Add(this->label6);
			this->pnlUUT_Param->Controls->Add(this->cmbVoltageRange_UUT);
			this->pnlUUT_Param->Controls->Add(this->label27);
			this->pnlUUT_Param->Controls->Add(this->txtsfVrms_UUT);
			this->pnlUUT_Param->Controls->Add(this->label26);
			this->pnlUUT_Param->Controls->Add(this->label25);
			this->pnlUUT_Param->Controls->Add(this->txtTerminal_UUT);
			this->pnlUUT_Param->Controls->Add(this->txtZInput_UUT);
			this->pnlUUT_Param->Controls->Add(this->label23);
			this->pnlUUT_Param->Controls->Add(this->lblZinput_UUT);
			this->pnlUUT_Param->Location = System::Drawing::Point(260, 75);
			this->pnlUUT_Param->Name = L"pnlUUT_Param";
			this->pnlUUT_Param->Size = System::Drawing::Size(264, 232);
			this->pnlUUT_Param->TabIndex = 63;
			// 
			// chkRangeAuto_UUT
			// 
			this->chkRangeAuto_UUT->AutoSize = true;
			this->chkRangeAuto_UUT->Location = System::Drawing::Point(187, 31);
			this->chkRangeAuto_UUT->Name = L"chkRangeAuto_UUT";
			this->chkRangeAuto_UUT->Size = System::Drawing::Size(74, 17);
			this->chkRangeAuto_UUT->TabIndex = 75;
			this->chkRangeAuto_UUT->Text = L"Auto Rng.";
			this->chkRangeAuto_UUT->UseVisualStyleBackColor = true;
			this->chkRangeAuto_UUT->CheckedChanged += gcnew System::EventHandler(this, &MainForm::chkRangeAuto_UUT_CheckedChanged);
			// 
			// label37
			// 
			this->label37->AutoSize = true;
			this->label37->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label37->Location = System::Drawing::Point(12, 136);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(43, 13);
			this->label37->TabIndex = 74;
			this->label37->Text = L"s.f. Vdc";
			// 
			// txtsfVdc_UUT
			// 
			this->txtsfVdc_UUT->Location = System::Drawing::Point(78, 133);
			this->txtsfVdc_UUT->Name = L"txtsfVdc_UUT";
			this->txtsfVdc_UUT->ReadOnly = true;
			this->txtsfVdc_UUT->Size = System::Drawing::Size(100, 20);
			this->txtsfVdc_UUT->TabIndex = 75;
			this->txtsfVdc_UUT->Text = L"1000,95";
			// 
			// label38
			// 
			this->label38->AutoSize = true;
			this->label38->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label38->Location = System::Drawing::Point(184, 135);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(19, 13);
			this->label38->TabIndex = 76;
			this->label38->Text = L"xV";
			// 
			// lblMaxVUnit_UUT
			// 
			this->lblMaxVUnit_UUT->AutoSize = true;
			this->lblMaxVUnit_UUT->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->lblMaxVUnit_UUT->Location = System::Drawing::Point(184, 55);
			this->lblMaxVUnit_UUT->Name = L"lblMaxVUnit_UUT";
			this->lblMaxVUnit_UUT->Size = System::Drawing::Size(20, 13);
			this->lblMaxVUnit_UUT->TabIndex = 73;
			this->lblMaxVUnit_UUT->Text = L"kV";
			// 
			// txtAppliedVoltage_UUT
			// 
			this->txtAppliedVoltage_UUT->Location = System::Drawing::Point(78, 53);
			this->txtAppliedVoltage_UUT->Name = L"txtAppliedVoltage_UUT";
			this->txtAppliedVoltage_UUT->ReadOnly = true;
			this->txtAppliedVoltage_UUT->Size = System::Drawing::Size(100, 20);
			this->txtAppliedVoltage_UUT->TabIndex = 72;
			this->txtAppliedVoltage_UUT->TextChanged += gcnew System::EventHandler(this, &MainForm::txtAppliedVoltage_UUT_TextChanged);
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label33->Location = System::Drawing::Point(9, 56);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(61, 13);
			this->label33->TabIndex = 71;
			this->label33->Text = L"Max Gerilim";
			// 
			// chkRange_UUT
			// 
			this->chkRange_UUT->AutoSize = true;
			this->chkRange_UUT->Location = System::Drawing::Point(210, 54);
			this->chkRange_UUT->Name = L"chkRange_UUT";
			this->chkRange_UUT->Size = System::Drawing::Size(50, 17);
			this->chkRange_UUT->TabIndex = 66;
			this->chkRange_UUT->Text = L"Calc.";
			this->chkRange_UUT->UseVisualStyleBackColor = true;
			this->chkRange_UUT->CheckedChanged += gcnew System::EventHandler(this, &MainForm::chkRange_UUT_CheckedChanged);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label12->Location = System::Drawing::Point(12, 110);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(55, 13);
			this->label12->TabIndex = 63;
			this->label12->Text = L"s.f. Vpeak";
			// 
			// txtsfVpeak_UUT
			// 
			this->txtsfVpeak_UUT->Location = System::Drawing::Point(78, 107);
			this->txtsfVpeak_UUT->Name = L"txtsfVpeak_UUT";
			this->txtsfVpeak_UUT->ReadOnly = true;
			this->txtsfVpeak_UUT->Size = System::Drawing::Size(100, 20);
			this->txtsfVpeak_UUT->TabIndex = 64;
			this->txtsfVpeak_UUT->Text = L"1000,95";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label24->Location = System::Drawing::Point(184, 109);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(19, 13);
			this->label24->TabIndex = 65;
			this->label24->Text = L"xV";
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label29->Location = System::Drawing::Point(12, 29);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(46, 13);
			this->label29->TabIndex = 48;
			this->label29->Text = L"Kademe";
			// 
			// cmbDivider_UUT
			// 
			this->cmbDivider_UUT->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbDivider_UUT->FormattingEnabled = true;
			this->cmbDivider_UUT->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"0.1V", L"1V", L"10V", L"100V", L"1000V" });
			this->cmbDivider_UUT->Location = System::Drawing::Point(78, 3);
			this->cmbDivider_UUT->Name = L"cmbDivider_UUT";
			this->cmbDivider_UUT->Size = System::Drawing::Size(173, 21);
			this->cmbDivider_UUT->TabIndex = 62;
			this->cmbDivider_UUT->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::cmbDivider_UUT_SelectedIndexChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label6->Location = System::Drawing::Point(12, 5);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(40, 13);
			this->label6->TabIndex = 61;
			this->label6->Text = L"Bölücü";
			// 
			// cmbVoltageRange_UUT
			// 
			this->cmbVoltageRange_UUT->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbVoltageRange_UUT->FormattingEnabled = true;
			this->cmbVoltageRange_UUT->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"0.1V", L"1V", L"10V", L"100V", L"1000V" });
			this->cmbVoltageRange_UUT->Location = System::Drawing::Point(78, 27);
			this->cmbVoltageRange_UUT->Name = L"cmbVoltageRange_UUT";
			this->cmbVoltageRange_UUT->Size = System::Drawing::Size(100, 21);
			this->cmbVoltageRange_UUT->TabIndex = 47;
			this->cmbVoltageRange_UUT->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::cmbVoltageRange_UUT_SelectedIndexChanged);
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label27->Location = System::Drawing::Point(12, 83);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(47, 13);
			this->label27->TabIndex = 50;
			this->label27->Text = L"s.f. Vrms";
			// 
			// txtsfVrms_UUT
			// 
			this->txtsfVrms_UUT->Location = System::Drawing::Point(78, 80);
			this->txtsfVrms_UUT->Name = L"txtsfVrms_UUT";
			this->txtsfVrms_UUT->ReadOnly = true;
			this->txtsfVrms_UUT->Size = System::Drawing::Size(100, 20);
			this->txtsfVrms_UUT->TabIndex = 51;
			this->txtsfVrms_UUT->Text = L"1000,95";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label26->Location = System::Drawing::Point(184, 82);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(19, 13);
			this->label26->TabIndex = 52;
			this->label26->Text = L"xV";
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label25->Location = System::Drawing::Point(12, 162);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(37, 13);
			this->label25->TabIndex = 53;
			this->label25->Text = L"Z Giriş";
			// 
			// txtTerminal_UUT
			// 
			this->txtTerminal_UUT->Location = System::Drawing::Point(78, 185);
			this->txtTerminal_UUT->Name = L"txtTerminal_UUT";
			this->txtTerminal_UUT->ReadOnly = true;
			this->txtTerminal_UUT->Size = System::Drawing::Size(100, 20);
			this->txtTerminal_UUT->TabIndex = 57;
			this->txtTerminal_UUT->Text = L"1000,95";
			// 
			// txtZInput_UUT
			// 
			this->txtZInput_UUT->Location = System::Drawing::Point(78, 159);
			this->txtZInput_UUT->Name = L"txtZInput_UUT";
			this->txtZInput_UUT->ReadOnly = true;
			this->txtZInput_UUT->Size = System::Drawing::Size(100, 20);
			this->txtZInput_UUT->TabIndex = 54;
			this->txtZInput_UUT->Text = L"1000,95";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label23->Location = System::Drawing::Point(12, 188);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(47, 13);
			this->label23->TabIndex = 56;
			this->label23->Text = L"Terminal";
			// 
			// lblZinput_UUT
			// 
			this->lblZinput_UUT->AutoSize = true;
			this->lblZinput_UUT->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->lblZinput_UUT->Location = System::Drawing::Point(184, 161);
			this->lblZinput_UUT->Name = L"lblZinput_UUT";
			this->lblZinput_UUT->Size = System::Drawing::Size(15, 13);
			this->lblZinput_UUT->TabIndex = 55;
			this->lblZinput_UUT->Text = L"Ω";
			// 
			// cmbDivider_DMM
			// 
			this->cmbDivider_DMM->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbDivider_DMM->FormattingEnabled = true;
			this->cmbDivider_DMM->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"0.1V", L"1V", L"10V", L"100V", L"1000V" });
			this->cmbDivider_DMM->Location = System::Drawing::Point(72, 74);
			this->cmbDivider_DMM->Name = L"cmbDivider_DMM";
			this->cmbDivider_DMM->Size = System::Drawing::Size(164, 21);
			this->cmbDivider_DMM->TabIndex = 60;
			this->cmbDivider_DMM->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::cmbDivider_DMM_SelectedIndexChanged);
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label13->Location = System::Drawing::Point(272, 54);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(33, 13);
			this->label13->TabIndex = 59;
			this->label13->Text = L"DMM";
			// 
			// cmbAddress_UUT
			// 
			this->cmbAddress_UUT->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbAddress_UUT->FormattingEnabled = true;
			this->cmbAddress_UUT->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"None", L"Hand Type", L"34110A", L"34111",
					L"3548A"
			});
			this->cmbAddress_UUT->Location = System::Drawing::Point(338, 52);
			this->cmbAddress_UUT->Name = L"cmbAddress_UUT";
			this->cmbAddress_UUT->Size = System::Drawing::Size(173, 21);
			this->cmbAddress_UUT->TabIndex = 58;
			this->cmbAddress_UUT->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::cmbAddress_UUT_SelectedIndexChanged);
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label18->Location = System::Drawing::Point(3, 54);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(33, 13);
			this->label18->TabIndex = 44;
			this->label18->Text = L"DMM";
			// 
			// cmbAddress_DMM
			// 
			this->cmbAddress_DMM->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbAddress_DMM->FormattingEnabled = true;
			this->cmbAddress_DMM->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"34110A", L"34111", L"3548A" });
			this->cmbAddress_DMM->Location = System::Drawing::Point(72, 50);
			this->cmbAddress_DMM->Name = L"cmbAddress_DMM";
			this->cmbAddress_DMM->Size = System::Drawing::Size(164, 21);
			this->cmbAddress_DMM->TabIndex = 43;
			this->cmbAddress_DMM->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::cmbAddress_DMM_SelectedIndexChanged);
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F));
			this->label20->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label20->Location = System::Drawing::Point(333, 17);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(112, 25);
			this->label20->TabIndex = 42;
			this->label20->Text = L"UUT DMM";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F));
			this->label22->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label22->Location = System::Drawing::Point(67, 16);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(108, 25);
			this->label22->TabIndex = 41;
			this->label22->Text = L"Ref. DMM";
			// 
			// txtTerminal_DMM
			// 
			this->txtTerminal_DMM->Location = System::Drawing::Point(72, 260);
			this->txtTerminal_DMM->Name = L"txtTerminal_DMM";
			this->txtTerminal_DMM->ReadOnly = true;
			this->txtTerminal_DMM->Size = System::Drawing::Size(100, 20);
			this->txtTerminal_DMM->TabIndex = 39;
			this->txtTerminal_DMM->Text = L"1000,95";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label21->Location = System::Drawing::Point(3, 265);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(47, 13);
			this->label21->TabIndex = 38;
			this->label21->Text = L"Terminal";
			// 
			// lblZinput_DMM
			// 
			this->lblZinput_DMM->AutoSize = true;
			this->lblZinput_DMM->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->lblZinput_DMM->Location = System::Drawing::Point(178, 236);
			this->lblZinput_DMM->Name = L"lblZinput_DMM";
			this->lblZinput_DMM->Size = System::Drawing::Size(15, 13);
			this->lblZinput_DMM->TabIndex = 37;
			this->lblZinput_DMM->Text = L"Ω";
			// 
			// txtZInput_DMM
			// 
			this->txtZInput_DMM->Location = System::Drawing::Point(72, 234);
			this->txtZInput_DMM->Name = L"txtZInput_DMM";
			this->txtZInput_DMM->ReadOnly = true;
			this->txtZInput_DMM->Size = System::Drawing::Size(100, 20);
			this->txtZInput_DMM->TabIndex = 36;
			this->txtZInput_DMM->Text = L"1000,95";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label19->Location = System::Drawing::Point(3, 239);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(37, 13);
			this->label19->TabIndex = 35;
			this->label19->Text = L"Z Giriş";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label16->Location = System::Drawing::Point(178, 159);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(19, 13);
			this->label16->TabIndex = 34;
			this->label16->Text = L"xV";
			// 
			// txtsfVrms_DMM
			// 
			this->txtsfVrms_DMM->Location = System::Drawing::Point(72, 157);
			this->txtsfVrms_DMM->Name = L"txtsfVrms_DMM";
			this->txtsfVrms_DMM->ReadOnly = true;
			this->txtsfVrms_DMM->Size = System::Drawing::Size(100, 20);
			this->txtsfVrms_DMM->TabIndex = 33;
			this->txtsfVrms_DMM->Text = L"1000,95";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label17->Location = System::Drawing::Point(3, 162);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(47, 13);
			this->label17->TabIndex = 32;
			this->label17->Text = L"s.f. Vrms";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label14->Location = System::Drawing::Point(4, 106);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(46, 13);
			this->label14->TabIndex = 28;
			this->label14->Text = L"Kademe";
			// 
			// cmbVoltageRange_DMM
			// 
			this->cmbVoltageRange_DMM->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbVoltageRange_DMM->FormattingEnabled = true;
			this->cmbVoltageRange_DMM->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"0.1V", L"1V", L"10V", L"100V", L"1000V" });
			this->cmbVoltageRange_DMM->Location = System::Drawing::Point(72, 102);
			this->cmbVoltageRange_DMM->Name = L"cmbVoltageRange_DMM";
			this->cmbVoltageRange_DMM->Size = System::Drawing::Size(100, 21);
			this->cmbVoltageRange_DMM->TabIndex = 27;
			this->cmbVoltageRange_DMM->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::cmbVoltageRange_DMM_SelectedIndexChanged);
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label15->Location = System::Drawing::Point(3, 81);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(40, 13);
			this->label15->TabIndex = 25;
			this->label15->Text = L"Bölücü";
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F));
			this->label30->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label30->Location = System::Drawing::Point(223, 112);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(103, 25);
			this->label30->TabIndex = 44;
			this->label30->Text = L"Vpeak/√2";
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F));
			this->label32->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label32->Location = System::Drawing::Point(223, 172);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(49, 25);
			this->label32->TabIndex = 45;
			this->label32->Text = L"Vdc";
			// 
			// label34
			// 
			this->label34->AutoSize = true;
			this->label34->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F));
			this->label34->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->label34->Location = System::Drawing::Point(223, 52);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(61, 25);
			this->label34->TabIndex = 43;
			this->label34->Text = L"Vrms";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(1676, 784);
			this->Controls->Add(this->gBoxStartStop);
			this->Controls->Add(this->gbDMM);
			this->Controls->Add(this->gbWaveFormGraph);
			this->Controls->Add(this->panelLog);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->toolStrip1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MainForm";
			this->Text = L"TUBITAK-UME Yüksek Gerilim Ölçüm Arayüzü";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->gbWaveFormGraph->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->panelLog->ResumeLayout(false);
			this->panelLog->PerformLayout();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->EndInit();
			this->panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgw_Sample))->EndInit();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->gBoxStartStop->ResumeLayout(false);
			this->gBoxStartStop->PerformLayout();
			this->pnlTestConfig->ResumeLayout(false);
			this->pnlTestConfig->PerformLayout();
			this->pnlTestLive->ResumeLayout(false);
			this->gbDMM->ResumeLayout(false);
			this->gbDMM->PerformLayout();
			this->pnlUUT_Param->ResumeLayout(false);
			this->pnlUUT_Param->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


public:
	int TestNo = 0;
	int LiveReadCount = 0;
	int LiveTickCount = 0;
	bool isbusy = false;
	bool isInit = false;

	double TestDuration;
	int CollectModulus = 1;
	DateTime StartTime;
	bool TestActive = false;
	bool isPaused = false;

	/*this->pnlTestLive->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
		static_cast<System::Int32>(static_cast<System::Byte>(128)));*/

	Object^ timerstate;
	MeasLab::SampleStatus instrStatus;
	MeasLab::SampleStatus instrStatus_UUT;
	MeasLab::IDMM^ instrument;
	MeasLab::IDMM^ instrumentUUT;

	Envanter^ DMM;
	Envanter^ UUT;
	Envanter^ DMM_Divider;
	Envanter^ UUT_Divider;

	List<WaveFormMeasument::WaveFormSample^>^ ResultList = gcnew List<WaveFormMeasument::WaveFormSample^>();
	List<WaveFormMeasument::WaveFormSample^>^ ResultList_UUT = gcnew List<WaveFormMeasument::WaveFormSample^>();
	List<GridObject^>^ GridList = gcnew List< GridObject^>();

	bool StopReading;
	WaveFormMeasument::WaveFormMeasurement^ measurement;
	WaveFormMeasument::WaveFormMeasurement^ liveData;
	WaveFormMeasument::WaveFormSample^ selectedSample;
	WaveFormMeasument::WaveFormMeasurement^ measurementUUT;
	WaveFormMeasument::WaveFormMeasurement^ liveDataUUT;
	WaveFormMeasument::WaveFormSample^ selectedSampleUUT;
	System::Threading::Timer^ timer;
	System::Threading::WaitHandle^ nofity = gcnew AutoResetEvent(false);;

	 
	Thread^ thd1;
	Thread^ thd2;
	Thread^ thRead;

private: 
	System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e);
	System::Void MainForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e);
	System::Void linkClearLog_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e);
	System::Void btnReadSTB_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e);
	System::Void btnExit_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void btnConnect_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void btnDisconnect_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void tsbtnDeviceList_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void btnSettings_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void btnShowLog_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void cmbSampleAdet_TextChanged(System::Object^ sender, System::EventArgs^ e);
	System::Void helpToolStripButton_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void btnStart_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void dgw_Sample_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);
	System::Void linkLabel1_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e);
	System::Void linkLabel2_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e);
	System::Void llblRefreshGrid_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e);
	System::Void txtRatio_TextChanged(System::Object^ sender, System::EventArgs^ e);
	System::Void cmbVoltageRange_DMM_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	System::Void cmbVoltageRange_UUT_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	System::Void txtFreq_TextChanged(System::Object^ sender, System::EventArgs^ e);
	System::Void cmbMeasType_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	System::Void cmbAddress_DMM_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	System::Void cmbAddress_UUT_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	System::Void cmbDivider_DMM_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	System::Void cmbDivider_UUT_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);
	System::Void btnReEnter_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void btnContinue_Click(System::Object^ sender, System::EventArgs^ e);
	System::Void chkRange_UUT_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	System::Void chkRange_DMM_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	System::Void txtAppliedVoltage_DMM_TextChanged(System::Object^ sender, System::EventArgs^ e);
	System::Void txtAppliedVoltage_UUT_TextChanged(System::Object^ sender, System::EventArgs^ e);
	System::Void chkRangeAuto_DMM_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	System::Void chkRangeAuto_UUT_CheckedChanged(System::Object^ sender, System::EventArgs^ e);

	
	void MainForm::LoadCombo();
	void MainForm::CheckDemoMode();
	void MainForm::LoadSetting();
	void MainForm::ReadFormParam();
	void MainForm::Connect();
	void MainForm::AutoCalcVoltageRange_DMM();
	void MainForm::AutoCalcVoltageRange_UUT();
	void MainForm::UpdatePLCTiming();
	void MainForm::TimerLoop(System::Object^ state);
	void MainForm::FirstLiveDataCollect();
	void MainForm::ThreadRun1();
	void MainForm::ThreadRun2();
	void MainForm::ThreadRead();
	void MainForm::DisConnect();
	void MainForm::ReadLiveData();
	void MainForm::LiveDataLoop();
	void MainForm::UpdateLiveLabels();
	void MainForm::ReadLiveData_UUT();
	void MainForm::LiveDataLoop_UUT();
	void MainForm::UpdateLiveLabels_UUT();
	void MainForm::LiveProgress();
	void MainForm::LiveProgress_UUT();
	void MainForm::FinishTest();
	void MainForm::DrawMyChart();
	void MainForm::DrawMyChart_UUT();
	void MainForm::RefreshGrid(bool isUUT);
	void MainForm::CalculateSummary();
	void MainForm::CalculateSummary_DMM();
	void MainForm::CalculateSummary_UUT();
	//void MainForm::SaveTestSettings(List<WaveFormMeasument::WaveFormSample^>^ SampleList, String^ barkod);
	void MainForm::SaveTestSettings(List<GridObject^>^ SampleList, String^ barkod);
	void MainForm::Instrument_LogChanged(System::Object^ sender, WaveFormMeasument::LogChangeEventArgs^ e);
	void MainForm::UpdateLog(String^ msg);
	void MainForm::ShowManuelEnter();
 
};

}
