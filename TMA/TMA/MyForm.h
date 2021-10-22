#pragma once

#include <stdio.h>
#include<cmath>
#include <windows.h>
#include <string>
#include <fstream>
#include<time.h>
#include <conio.h>
#include <cstdlib>
#include "Zadc_int.h"
#pragma comment(lib, "Zadc.lib")
# include "zet_declaration.h"

#define size_of_memory 200000//������ �������� �������
int INITIALIZE_ADC();
int INITIALIZE_DAC();
void ZETOFF();
void ZET_MESURE();
FILE *fr;
bool bool_do = false;
float EXTERN_DATA[4][20000];

namespace TMA {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	/// <summary>
	/// ������ ��� MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: �������� ��� ������������
			//
		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  M_t;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  T_t;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel2;
	private: System::Windows::Forms::Button^  button_start;
	private: System::Windows::Forms::Button^  button_stop;
	private: System::Windows::Forms::Timer^  timer;
	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::ToolStripButton^  out_file;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;


	private: System::ComponentModel::IContainer^  components;
	protected:

	private:
		/// <summary>
		/// ������������ ���������� ������������.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->button_start = (gcnew System::Windows::Forms::Button());
			this->button_stop = (gcnew System::Windows::Forms::Button());
			this->M_t = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->T_t = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->out_file = (gcnew System::Windows::Forms::ToolStripButton());
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->M_t))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->T_t))->BeginInit();
			this->toolStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel2, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->M_t, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->T_t, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->toolStrip1, 0, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 3;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 5)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 70)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(1069, 532);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 2;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel2->Controls->Add(this->button_start, 1, 0);
			this->tableLayoutPanel2->Controls->Add(this->button_stop, 1, 1);
			this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel2->Location = System::Drawing::Point(3, 401);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 2;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(528, 128);
			this->tableLayoutPanel2->TabIndex = 3;
			// 
			// button_start
			// 
			this->button_start->Location = System::Drawing::Point(267, 3);
			this->button_start->Name = L"button_start";
			this->button_start->Size = System::Drawing::Size(75, 23);
			this->button_start->TabIndex = 2;
			this->button_start->Text = L"start";
			this->button_start->UseVisualStyleBackColor = true;
			this->button_start->Click += gcnew System::EventHandler(this, &MyForm::button_start_Click);
			// 
			// button_stop
			// 
			this->button_stop->Enabled = false;
			this->button_stop->Location = System::Drawing::Point(267, 67);
			this->button_stop->Name = L"button_stop";
			this->button_stop->Size = System::Drawing::Size(75, 23);
			this->button_stop->TabIndex = 3;
			this->button_stop->Text = L"stop";
			this->button_stop->UseVisualStyleBackColor = true;
			this->button_stop->Click += gcnew System::EventHandler(this, &MyForm::button_stop_Click);
			// 
			// M_t
			// 
			chartArea1->Name = L"ChartArea1";
			this->M_t->ChartAreas->Add(chartArea1);
			this->M_t->Dock = System::Windows::Forms::DockStyle::Fill;
			this->M_t->Location = System::Drawing::Point(3, 29);
			this->M_t->Name = L"M_t";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series1->IsVisibleInLegend = false;
			series1->Name = L"M_t";
			this->M_t->Series->Add(series1);
			this->M_t->Size = System::Drawing::Size(528, 366);
			this->M_t->TabIndex = 0;
			this->M_t->Text = L"M_t";
			// 
			// T_t
			// 
			chartArea2->Name = L"ChartArea1";
			this->T_t->ChartAreas->Add(chartArea2);
			this->T_t->Dock = System::Windows::Forms::DockStyle::Fill;
			this->T_t->Location = System::Drawing::Point(537, 29);
			this->T_t->Name = L"T_t";
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series2->IsVisibleInLegend = false;
			series2->Name = L"T_t";
			this->T_t->Series->Add(series2);
			this->T_t->Size = System::Drawing::Size(529, 366);
			this->T_t->TabIndex = 1;
			this->T_t->Text = L"T_t";
			// 
			// toolStrip1
			// 
			this->tableLayoutPanel1->SetColumnSpan(this->toolStrip1, 2);
			this->toolStrip1->ImageScalingSize = System::Drawing::Size(17, 17);
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->out_file });
			this->toolStrip1->Location = System::Drawing::Point(0, 0);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(1069, 25);
			this->toolStrip1->TabIndex = 4;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// out_file
			// 
			this->out_file->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->out_file->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"out_file.Image")));
			this->out_file->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->out_file->Name = L"out_file";
			this->out_file->Size = System::Drawing::Size(73, 22);
			this->out_file->Text = L"Output file";
			this->out_file->Click += gcnew System::EventHandler(this, &MyForm::out_file_Click);
			// 
			// timer
			// 
			this->timer->Enabled = true;
			this->timer->Tick += gcnew System::EventHandler(this, &MyForm::timer_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1069, 532);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->tableLayoutPanel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->M_t))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->T_t))->EndInit();
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
		// ������ ��� ���������� � �������

	//String ^path = "";
	float K_M;
	float K_A;
	float K_B;
	float dT;
	int  REGIM_NAGREVA = 0;
	float float_t_expose;

	//�������� ������� ������
	                    //���������  ������ ����������� �����
	int INT_DATA = -1;                                        //����� ���������� ����������� �������
	float FLOAT_A = 0;
	float FLOAT_A_FOR_SCREEN = 0;
	float FLOAT_M = 0;
	float FLOAT_TEMP = 0;

	float FLOAT_TEMP_U = 0;
	float FLOAT_TEMP_U_FOR_SCREEN = 0;

	int INT_A = 0;
	int INT_M = 0;
	int INT_TEMP = 0;
	float GLOBAL_T = 80;                                      //����������� �� ������� ����� ����������� ������
	float FON_T = 0;                                          //����������� ����=������� �����������
	float EXPOS_time;
	float T_UP = 0;
	float T_DOWN = 0;
	int  timer_i = 0;
	float float_now = 0;
	int size = 0;

	//������������� ������
	int INITIALIZE_DAC()
		{
			// �������� ������ ����� ���
			Err = ZSetOutputDAC(typeDevice, numberDSP, 0, 1);
			if (Err != 0)
			{
				printf("ZSetOutputDAC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}

			// �������� ���-�� ���������� ������� ���
			Err = ZGetNumberOutputDAC(typeDevice, numberDSP, &numChannelsDAC);
			if (Err != 0)
			{
				printf("Function ZGetNumberOutputDAC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}

			// �������� ��� �������� ������� ��� ��� ������� ������
			Err = ZGetDigitalResolChanDAC(typeDevice, numberDSP, 0, &resolutionDAC0);
			if (Err != 0)
			{
				printf("ZGetDigitalResolutionDAC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}


			// �������� ���-�� ���� � ����� ������� ���
			Err = ZGetWordsDAC(typeDevice, numberDSP, &numWordsDAC);
			printf("WordsDAC%d\n", numWordsDAC);
			if (Err != 0)
			{
				printf("ZGetWordsDAC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}

			// �������� ������� ������������� ���
			Err = ZGetFreqDAC(typeDevice, numberDSP, &freqDAC);
			if (Err != 0)
			{
				printf("ZGetFreqDAC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}

			// �������� ������ ������ ���������� ���
			Err = ZGetInterruptDAC(typeDevice, numberDSP, &sizeInterruptBufferDAC);
			if (Err != 0)
			{
				printf("ZGetInterruptDAC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}

			// ���������� (��������) ����. ��������� ����������� ��� �� ������� ������ ���
			Err = ZSetAttenDAC(typeDevice, numberDSP, 0, attenDAC0, &attenDAC0);
			if (Err != 0)
			{
				printf("ZSetAttenDAC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;

			}


			// �������� ����������, ����� �������� ������� �� 0
			if (numWordsDAC < 1 || numWordsDAC > 2 || freqDAC < 1. || attenDAC0 == 0. || resolutionDAC0 == 0.)
			{
				//printf("��������� �������� ���������� ���\n\r");
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}

			// ��������� ����� ���
			Err = ZGetBufferDAC(typeDevice, numberDSP, (void**)&pBuffer16DAC, &sizeBufferDAC);
			if (Err != 0)
			{
				printf("Function ZGetBufferDAC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}
			pBuffer32DAC = (long*)pBuffer16DAC;

			// �������� ������ ������ �������� ��������� ������� ������� (����������)
			sizePacketDAC = (long)freqDAC * responseTime / 1000;
			sizePacketDAC = numWordsDAC * sizePacketDAC;

			// ������ ������ ������ ���� �� ������ ���� �������� ������ ���������� � �� ������ �������� ������ ��������
			if (sizePacketDAC < 2 * sizeInterruptBufferDAC)
				sizePacketDAC = 2 * sizeInterruptBufferDAC;
			if (sizePacketDAC > sizeBufferDAC / 2)
				sizePacketDAC = sizeBufferDAC / 2;
			// ��������� ��� ��������� �������
			amplitude0 = 0;
			// ������ � ����� �������� ������ ���� �������
			size = 2 * sizePacketDAC / numWordsDAC;
			if (numWordsDAC == 1)
				for (i = 0; i < size; i++)
				{
					volt0_DAC = amplitude0;
					pBuffer16DAC[i] = (short)volt0_DAC;
				}
			else
				for (i = 0; i < size; i++)
				{
					volt0_DAC = amplitude0;
					pBuffer32DAC[i] = (long)volt0_DAC;
				}
			pointerCycleDAC = 2 * sizePacketDAC;
			// ������� ���
			Err = ZStopDAC(typeDevice, numberDSP);
			if (Err != 0)
				printf("Function ZStopDAC() return Error = 0x%X\n\r", Err);
		}
	int INITIALIZE_ADC()
		{
			// ��������  ���-�� ������� ���
			Err = ZGetQuantityChannelADC(typeDevice, numberDSP, &numChannelsADC);
			if (Err != 0)
			{
				printf("ZGetQuantityChannelADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}

			// �������� ������ ����� ���
			Err = ZSetInputADC(typeDevice, numberDSP, 0, 1);
			if (Err != 0)
			{
				printf("ZSetInputADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}

			// �������� ������ ����� ���
			Err = ZSetInputADC(typeDevice, numberDSP, 1, 1);
			if (Err != 0)
			{
				printf("ZSetInputADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}
			// ��������  ������ ����� ���
			Err = ZSetInputADC(typeDevice, numberDSP, 2, 1);
			if (Err != 0)
			{
				printf("ZSetInputADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}
			// ��������  ��������� ����� ���
			Err = ZSetInputADC(typeDevice, numberDSP, 3, 1);
			if (Err != 0)
			{
				printf("ZSetInputADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}
			// �������� ����. �������� �� ������� ������ ���
			Err = ZGetAmplifyADC(typeDevice, numberDSP, 0, &amplifyADC0);
			if (Err != 0)
			{
				printf("ZGetAmplifyADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}

			// �������� ����. �������� �� ������� ������ ���
			Err = ZGetAmplifyADC(typeDevice, numberDSP, 1, &amplifyADC1);
			if (Err != 0)
			{
				printf("ZGetAmplifyADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}
			// �������� ����. �������� �� ������� ������ ���
			Err = ZGetAmplifyADC(typeDevice, numberDSP, 2, &amplifyADC2);
			if (Err != 0)
			{
				printf("ZGetAmplifyADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}
			// �������� ����. �������� �� ���������� ������ ���
			Err = ZGetAmplifyADC(typeDevice, numberDSP, 3, &amplifyADC3);
			if (Err != 0)
			{
				printf("ZGetAmplifyADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}

			// �������� ��� �������� ������� ��� ������� ������
			Err = ZGetDigitalResolChanADC(typeDevice, numberDSP, 0, &resolutionADC0);
			if (Err != 0)
			{
				printf("ZGetDigitalResolChanADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}

			// �������� ��� �������� ������� ��� ������� ������
			Err = ZGetDigitalResolChanADC(typeDevice, numberDSP, 1, &resolutionADC1);
			if (Err != 0)
			{
				printf("ZGetDigitalResolChanADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}
			// �������� ��� �������� ������� ��� �������� ������
			Err = ZGetDigitalResolChanADC(typeDevice, numberDSP, 2, &resolutionADC2);
			if (Err != 0)
			{
				printf("ZGetDigitalResolChanADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}
			// �������� ��� �������� ������� ��� ���������� ������
			Err = ZGetDigitalResolChanADC(typeDevice, numberDSP, 3, &resolutionADC3);
			if (Err != 0)
			{
				printf("ZGetDigitalResolChanADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}
			// �������� ���-�� ���������� ������� ���
			Err = ZGetNumberInputADC(typeDevice, numberDSP, &numChannelsADC);
			if (Err != 0)
			{
				printf("Function ZGetNumberInputADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}
			printf("chanels%d\n", numChannelsADC);
			// �������� ���-�� ���� � ����� ������� ���
			Err = ZGetWordsADC(typeDevice, numberDSP, &numWordsADC);
			if (Err != 0)
			{
				printf("ZGetWordsADC() return Error = 0x%X\n\r", Err);
				getch();
				return 0;
			}

			// �������� ����������, ����� �������� ������� �� 0
			if (numWordsADC == 0 || amplifyADC0 == 0 || amplifyADC1 == 0 || amplifyADC2 == 0 || amplifyADC3 == 0)
			{
				//printf("��������� �������� ���������� ���\n\r");
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}

			// ��������� ����� ���
			Err = ZGetBufferADC(typeDevice, numberDSP, (void**)&pBuffer16ADC, &sizeBufferADC);
			if (Err != 0)
			{
				printf("Function ZGetBufferADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}
			pBuffer32ADC = (long*)pBuffer16ADC;

			// ������� ���
			Err = ZStopADC(typeDevice, numberDSP);
			if (Err != 0)
				printf("Function ZStopADC() return Error = 0x%X\n\r", Err);

		}
	//���������� ������
	void ZETOFF_DAC() {
			// ������� ���
			Err = ZStopDAC(typeDevice, numberDSP);
			if (Err != 0)
			{
				MessageBox::Show("Unable to stop ZETLAB");
				
			}

			// ������� ���
			Err = ZStopADC(typeDevice, numberDSP);
			if (Err != 0)
			{
				MessageBox::Show("Unable to stop ZETLAB");
			}

			// ���������� ����� ���
			if (pBuffer16DAC != NULL)
			{
				Err = ZRemBufferDAC(typeDevice, numberDSP, (void**)&pBuffer16DAC);
				if (Err != 0)
					printf("Function ZRemBufferDAC() return Error = 0x%X\n\r", Err);
			}
			// ���������� ����� ���
			if (pBuffer16ADC != NULL)
			{
				Err = ZRemBufferADC(typeDevice, numberDSP, (void**)&pBuffer16ADC);
				if (Err != 0)
					printf("Function ZRemBufferADC() return Error = 0x%X\n\r", Err);
			}
			// ����������� �� �������� (�����������)
			Err = ZClose(typeDevice, numberDSP);
		}
	void ZETOFF_ADC()
		{
			Err = ZStopADC(typeDevice, numberDSP);
			if (Err != 0)
				printf("Function ZStopADC() return Error = 0x%X\n\r", Err);

			// ���������� ����� ���
			if (pBuffer16ADC != NULL)
			{
				Err = ZRemBufferADC(typeDevice, numberDSP, (void**)&pBuffer16ADC);
				if (Err != 0)
					printf("Function ZRemBufferADC() return Error = 0x%X\n\r", Err);
			}

			// ����������� �� �������� (�����������)
			Err = ZClose(typeDevice, numberDSP);
			if (Err != 0)
				printf("Function ZClose() return Error = 0x%X\n\r", Err);
			MessageBox::Show("Zetlab is stoped");
		}
	//�������� ������ �������
	float ALGORITM_TEMP()
	{
		float u;
		int ALGORITM_i = 0;
		time_t start_REGIM_NAGREVA_t;
		time_t now_REGIM_NAGREVA_t;
		struct tm *start_REGIM_NAGREVA;
		struct tm *now_REGIM_NAGREVA;
		if (REGIM_NAGREVA == 0)
		{
			u = 3.5;
			if ((FLOAT_TEMP > 35) && (FLOAT_TEMP <= GLOBAL_T - 5))
			{
				REGIM_NAGREVA = 1;
			}

		}

		if (REGIM_NAGREVA == 1)
		{
			
			u = K_A * FLOAT_TEMP + K_B;// -2.5;
			if (FLOAT_TEMP >= GLOBAL_T - 5)
			{
				REGIM_NAGREVA = 2;
				time(&start_REGIM_NAGREVA_t);
				start_REGIM_NAGREVA = localtime(&start_REGIM_NAGREVA_t);
			}

		}
		if (REGIM_NAGREVA == 2)
		{
			
			u = 0.263*pow(GLOBAL_T, 0.573);// -2.5;
			time(&now_REGIM_NAGREVA_t);
			now_REGIM_NAGREVA = localtime(&now_REGIM_NAGREVA_t);
			float_t_expose = ((now_REGIM_NAGREVA->tm_hour - start_REGIM_NAGREVA->tm_hour) * 3600 + (now_REGIM_NAGREVA->tm_min - start_REGIM_NAGREVA->tm_min) * 60 + (now_REGIM_NAGREVA->tm_sec - start_REGIM_NAGREVA->tm_sec));
			if (float_t_expose >= EXPOS_time)
			{
				REGIM_NAGREVA = 3;

			}

		}

		if (REGIM_NAGREVA == 3)
		{
			u = 0.3*(K_A*FLOAT_TEMP + K_B);// -2.5;
			if (FLOAT_TEMP < 45)
			{
				REGIM_NAGREVA = 4;
			}
		}
		if (REGIM_NAGREVA == 4)
		{
			u = 0;
		}

		if (u > 9.5)
		{
			u = 9.5;
		}



		return u;
	}
	//����������� � �������� �� ����� ���
	float chrom(float u) {
			// ������� ���������� �������� �����������(� �������� �������) ��� ����� ���  � �. 
			//���������� �� 1000 ������� ������������ ������������� � ��������
			// ������� �� 100 ������� ������������� ��������� zet 411
			u = u * 1000 / 100;
			//

			float t = 0;
			//    if (u < 0){ u = -u; }
				 //u=u*1.07
			u = u * dT;
			t = (((-1.2306e-5*u + 0.002103)*u - 0.1326)*u + 15.151)*u;

			return t;


		}
	//���� ������ �� ������ ������
	void ZET_MESURE()
	{
		amplitude0 = amplitude_volt_0 / (resolutionDAC0 * attenDAC0);
		// ��������� ��������� �� ������� ������� ������
		Err = ZGetPointerDAC(typeDevice, numberDSP, &pointerDriverDAC);
		if (Err != 0)
		{
			MessageBox::Show("Can not reach the buffer");
		}
		// ���� ���������� ������ ������ ������ ��� �� ���� �����, �� ������� � ������ ����� � ���������
		if (!(pointerCycleDAC - pointerDriverDAC > sizePacketDAC))
		{
			if (!((pointerDriverDAC > pointerCycleDAC) &&
				(sizeBufferDAC - pointerDriverDAC + pointerCycleDAC > sizePacketDAC)))
			{
				// �������� ���������� �������� ��������� ��������
				pointerDriverDAC_old = pointerDriverDAC;
				// ������ � ����� �������� ���������� ������ ������
				size = sizePacketDAC;
				// ���� ����� ������� �� ������� ������ ��������, �� ��� ����� ��������� �� ��� �����
				if (pointerCycleDAC + sizePacketDAC > sizeBufferDAC)
					size = sizeBufferDAC - pointerCycleDAC;

				size = size / numWordsDAC;
				if (numWordsDAC == 1)
					for (i = 0; i < size; i++)
					{
						volt0_DAC = amplitude0;
						pBuffer16DAC[pointerCycleDAC + i] = (short)volt0_DAC;
					}
				else
					for (i = 0; i < size; i++)
					{
						volt0_DAC = amplitude0;
						pBuffer32DAC[pointerCycleDAC / numWordsDAC + i] = (long)volt0_DAC;
					}

				// ����������� ��������� �� ������ ��� ��������� ������
				pointerCycleDAC += numWordsDAC * size;
				// ���� ������� � ����� ������, �� ������� � ������
				if (pointerCycleDAC >= sizeBufferDAC)
					pointerCycleDAC = 0;

				if (size < (sizePacketDAC / numWordsDAC))
				{
					// ������ � ����� �������� ������ ����� ������ ������, ���� ����� �������� ��������� 
					size = (sizePacketDAC / numWordsDAC) - size;
					if (numWordsDAC == 1)
						for (i = 0; i < size; i++)
						{
							volt0_DAC = amplitude0;
							pBuffer16DAC[pointerCycleDAC + i] = (short)volt0_DAC;
						}
					else
						for (i = 0; i < size; i++)
						{
							volt0_DAC = amplitude0;
							pBuffer32DAC[pointerCycleDAC / numWordsDAC + i] = (long)volt0_DAC;
						}
					// ����������� ��������� �� ������ ��� ��������� ������
					pointerCycleDAC += numWordsDAC * size;
				}
			}
		}
		/////////////////////////ADC
		// ��������� ��������� �� ������� ������� ������
		Err = ZGetPointerADC(typeDevice, numberDSP, &pointerADC);
		if (Err != 0)
		{
			MessageBox::Show("Can not reach the buffer");
		}

		// ���� ����� ������ � ����� �� ��� �� ���������, �� ������� � ������ ����� � ���������
		if (pointerADC != pointerADC_old)
		{
			// �������� ���������� �������� ���������
			pointerADC_old = pointerADC;
			// ������� �� ������ ������� ����������� ������ ���������� ����� ���
			if (pointerADC - numWordsADC * numChannelsADC < 0)
				pointerADC = sizeBufferADC + pointerADC - numWordsADC * numChannelsADC;
			else
				pointerADC = pointerADC - numWordsADC * numChannelsADC;
			// ��������� �� ������ �������� ������� ��� ������������ �������� ������� (� �������)
			if (numWordsADC == 1)
				volt0 = resolutionADC0 * (pBuffer16ADC[pointerADC]) / amplifyADC0;
			else
				volt0 = resolutionADC0 * (pBuffer32ADC[pointerADC / numWordsADC]) / amplifyADC0;

			// ���� �������� ����� ������ ������ ���, �� ������� �� �� ����� ��� ������� ������
			if (numChannelsADC > 1)
			{
				// ������� �� ��������� ������ ���
				pointerADC += numWordsADC;
				// ���� ����� �� ������� ������, �� ������� � ������
				if (pointerADC >= sizeBufferADC)
					pointerADC = pointerADC - sizeBufferADC;

				if (numWordsADC == 1)
					volt1 = resolutionADC1 * (pBuffer16ADC[pointerADC]) / amplifyADC1;
				else
					volt1 = resolutionADC1 * (pBuffer32ADC[pointerADC / numWordsADC]) / amplifyADC1;

				// ������� �� ��������� ������ ���
				pointerADC += numWordsADC;
				// ���� ����� �� ������� ������, �� ������� � ������
				if (pointerADC >= sizeBufferADC)
					pointerADC = pointerADC - sizeBufferADC;

				if (numWordsADC == 1)
					volt2 = resolutionADC2 * (pBuffer16ADC[pointerADC]) / amplifyADC2;
				else
					volt2 = resolutionADC2 * (pBuffer32ADC[pointerADC / numWordsADC]) / amplifyADC2;

				// ������� �� ��������� ������ ���
				pointerADC += numWordsADC;
				// ���� ����� �� ������� ������, �� ������� � ������
				if (pointerADC >= sizeBufferADC)
					pointerADC = pointerADC - sizeBufferADC;

				if (numWordsADC == 1)
					volt3 = resolutionADC3 * (pBuffer16ADC[pointerADC]) / amplifyADC3;
				else
					volt3 = resolutionADC3 * (pBuffer32ADC[pointerADC / numWordsADC]) / amplifyADC3;
			}

		}
	}
	//����������� ����� � ������� ����� ���������� ������
private: System::Void out_file_Click(System::Object^  sender, System::EventArgs^  e)
{
	/*saveFileDialog1->Filter = "Output files|*.jr6|All files(*.*)|*.*";

	System::Windows::Forms::DialogResult result = saveFileDialog1->ShowDialog();

	if (result != System::Windows::Forms::DialogResult::OK)
		return;
	System::String^ filename = saveFileDialog1->FileName;
	//path = filename;*/
}
	//���������� ��� �������� �����
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e)
	{
		M_t->Series['M_t']->Points->Clear();
		T_t->Series['T_t']->Points->Clear();

		M_t->ChartAreas[0]->AxisX->Crossing = 0;
		M_t->ChartAreas[0]->AxisY->Crossing = 0;
		T_t->ChartAreas[0]->AxisX->Crossing = 0;
		T_t->ChartAreas[0]->AxisY->Crossing = 0;

		M_t->ChartAreas[0]->AxisX->LabelStyle->Format = "{0:0.#E+0}";
		M_t->ChartAreas[0]->AxisY->LabelStyle->Format = "{0:0.#E+0}";
		T_t->ChartAreas[0]->AxisX->LabelStyle->Format = "{0:0.#E+0}";
		T_t->ChartAreas[0]->AxisY->LabelStyle->Format = "{0:0.#E+0}";
	}
	//������ ���������
	private: System::Void button_start_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		button_start->Enabled = false;
		button_stop->Enabled = true;
		bool_do = true;
		INITIALIZE_DAC();
		INITIALIZE_ADC();
		// ������ ���
		Err = ZStartDAC(typeDevice, numberDSP);
		// ������ ���
		Err = ZStartADC(typeDevice, numberDSP);
		// ���� ������ ������ ���
		pointerADC_old = 0;
		// ���� ��������� ������ � ������ ������ ���
		pointerDriverDAC_old = 0;
		ZETOFF_DAC();
		ZETOFF_ADC();
	}
	//��������� ���������
	private: System::Void button_stop_Click(System::Object^  sender, System::EventArgs^  e)
{
	button_start->Enabled = true;
	button_stop->Enabled = false;
	bool_do = false;
	ZETOFF_DAC();
	ZETOFF_ADC();
	
}
	//������ 100 ��� ��������� ������
	private: System::Void timer_Tick(System::Object^  sender, System::EventArgs^  e) {

			 if (bool_do)
			 {				 
				ZET_MESURE();


				 //FLOAT_TE+MP = FLOAT_TEMP +chrom(volt0);��� ���� � ������ 2.7
				 FLOAT_TEMP = FLOAT_TEMP + volt0;//���   � 2.8
				 FLOAT_TEMP_U = FLOAT_TEMP_U + volt0 * 1000;
				 FLOAT_A = FLOAT_A + volt1;

				 FLOAT_M = FLOAT_M + volt2;




				 timer_i++;

				 if (timer_i == 50)
				 {
					 SetThreadExecutionState(ES_SYSTEM_REQUIRED | ES_DISPLAY_REQUIRED);

					 FLOAT_M = K_M * FLOAT_M / FLOAT_A;
					 FLOAT_TEMP = FLOAT_TEMP / 50;
					 FLOAT_TEMP = chrom(FLOAT_TEMP);//��� ����� � 2.8
					 FLOAT_TEMP_U = FLOAT_TEMP_U / 50;
					 FLOAT_TEMP_U_FOR_SCREEN = FLOAT_TEMP_U;
					 FLOAT_A_FOR_SCREEN = FLOAT_A / 50;

					 amplitude_volt_0 = ALGORITM_TEMP();
					 amplitude_volt_1 = amplitude_volt_0;

					 //����� ���� ��� ������ �������� ����������� ������ ���������� ��������� �� 1
					 INT_DATA = INT_DATA + 1;
					 FON_T = FLOAT_TEMP;

					 //���������� �������
					 EXTERN_DATA[0][INT_DATA] = FLOAT_TEMP_U_FOR_SCREEN;
					 EXTERN_DATA[1][INT_DATA] = FLOAT_M;
					 EXTERN_DATA[2][INT_DATA] = FLOAT_TEMP;
					 EXTERN_DATA[3][INT_DATA] = float_now;
					 /*
					 //������ ������ � ����
					 sprintf(n, "%10.5f", EXTERN_DATA[0][INT_DATA]);
					 fwrite(n, sizeof(char), sizeof(n), fr);
					 fwrite("\t", sizeof(char), 1, fr);
					 sprintf(n, "%10.2f", EXTERN_DATA[1][INT_DATA]);
					 fwrite(n, sizeof(char), sizeof(n), fr);
					 fwrite("\t", sizeof(char), 1, fr);
					 sprintf(n, "%10.2f", EXTERN_DATA[2][INT_DATA]);
					 fwrite(n, sizeof(char), sizeof(n), fr);
					 fwrite("\t", sizeof(char), 1, fr);
					 sprintf(n, "%10.2f", EXTERN_DATA[3][INT_DATA]);
					 fwrite(n, sizeof(char), sizeof(n), fr);
					 fwrite("\n", sizeof(char), 1, fr);

					 */



					 if (INT_DATA == size_of_memory)
					 {
						 INT_DATA = 0;
						  //���� ������ ������� ������� �� ������� ����������  ������ �������� �������
						 //�� ����������� ������ ��� �� ������, ��� ��� ��� ��� �������� � ����
						 //����� ������ ����� ������������ ������ ������ ������� ���������� �������� ������� ��� ��������� ������� 
					 };


					 FLOAT_A = 0;
					 FLOAT_M = 0;
					 FLOAT_TEMP = 0;
					 FLOAT_TEMP_U = 0;
					 timer_i = 0;


					 

				 }
			 }

		 }

};
}
