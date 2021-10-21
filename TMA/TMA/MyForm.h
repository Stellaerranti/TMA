#pragma once

#include <stdio.h>
#include<cmath>
#include <windows.h>
#include<time.h>
#include <conio.h>
#include "zadc_int.h"
//#pragma comment(lib, "Zadc.lib")
# include "zet_declaration.h"
int INITIALIZE_ADC();
int INITIALIZE_DAC();
void ZETOFF();
void ZET_MESURE();

bool bool_do = false;


namespace TMA {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
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

	private: System::ComponentModel::IContainer^  components;
	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->M_t = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->T_t = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->button_start = (gcnew System::Windows::Forms::Button());
			this->button_stop = (gcnew System::Windows::Forms::Button());
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->tableLayoutPanel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->M_t))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->T_t))->BeginInit();
			this->tableLayoutPanel2->SuspendLayout();
			this->SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->Controls->Add(this->M_t, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->T_t, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel2, 0, 1);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 70)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 30)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(1069, 532);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// M_t
			// 
			chartArea1->Name = L"ChartArea1";
			this->M_t->ChartAreas->Add(chartArea1);
			this->M_t->Dock = System::Windows::Forms::DockStyle::Fill;
			this->M_t->Location = System::Drawing::Point(3, 3);
			this->M_t->Name = L"M_t";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series1->IsVisibleInLegend = false;
			series1->Name = L"Series1";
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
			this->T_t->Location = System::Drawing::Point(537, 3);
			this->T_t->Name = L"T_t";
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series2->IsVisibleInLegend = false;
			series2->Name = L"Series1";
			this->T_t->Series->Add(series2);
			this->T_t->Size = System::Drawing::Size(529, 366);
			this->T_t->TabIndex = 1;
			this->T_t->Text = L"T_t";
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
			this->tableLayoutPanel2->Location = System::Drawing::Point(3, 375);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 2;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(528, 154);
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
			this->button_stop->Location = System::Drawing::Point(267, 80);
			this->button_stop->Name = L"button_stop";
			this->button_stop->Size = System::Drawing::Size(75, 23);
			this->button_stop->TabIndex = 3;
			this->button_stop->Text = L"stop";
			this->button_stop->UseVisualStyleBackColor = true;
			this->button_stop->Click += gcnew System::EventHandler(this, &MyForm::button_stop_Click);
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
			this->tableLayoutPanel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->M_t))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->T_t))->EndInit();
			this->tableLayoutPanel2->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	//Инициализация АЦПЦАП
	int INITIALIZE_DAC()
		{
			// Включить первый канал ЦАП
			Err = ZSetOutputDAC(typeDevice, numberDSP, 0, 1);
			if (Err != 0)
			{
				printf("ZSetOutputDAC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}

			// Опросить кол-во включенных каналов ЦАП
			Err = ZGetNumberOutputDAC(typeDevice, numberDSP, &numChannelsDAC);
			if (Err != 0)
			{
				printf("Function ZGetNumberOutputDAC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}

			// Опросить вес младшего разряда ЦАП для первого канала
			Err = ZGetDigitalResolChanDAC(typeDevice, numberDSP, 0, &resolutionDAC0);
			if (Err != 0)
			{
				printf("ZGetDigitalResolutionDAC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}


			// Опросить кол-во слов в одном отсчете ЦАП
			Err = ZGetWordsDAC(typeDevice, numberDSP, &numWordsDAC);
			printf("WordsDAC%d\n", numWordsDAC);
			if (Err != 0)
			{
				printf("ZGetWordsDAC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}

			// Опросить частоту дискретизации ЦАП
			Err = ZGetFreqDAC(typeDevice, numberDSP, &freqDAC);
			if (Err != 0)
			{
				printf("ZGetFreqDAC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}

			// Опросить размер буфера прерывания ЦАП
			Err = ZGetInterruptDAC(typeDevice, numberDSP, &sizeInterruptBufferDAC);
			if (Err != 0)
			{
				printf("ZGetInterruptDAC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}

			// Установить (опросить) коэф. затухания аттенюатора ЦАП по первому каналу ЦАП
			Err = ZSetAttenDAC(typeDevice, numberDSP, 0, attenDAC0, &attenDAC0);
			if (Err != 0)
			{
				printf("ZSetAttenDAC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;

			}


			// Проверка переменных, чтобы избежать деления на 0
			if (numWordsDAC < 1 || numWordsDAC > 2 || freqDAC < 1. || attenDAC0 == 0. || resolutionDAC0 == 0.)
			{
				printf("Ошибочные значения параметров ЦАП\n\r");
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}

			// Запросить буфер ЦАП
			Err = ZGetBufferDAC(typeDevice, numberDSP, (void**)&pBuffer16DAC, &sizeBufferDAC);
			if (Err != 0)
			{
				printf("Function ZGetBufferDAC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}
			pBuffer32DAC = (long*)pBuffer16DAC;

			// Вычислим размер пакета согласно заданному времени реакции (опережения)
			sizePacketDAC = (long)freqDAC * responseTime / 1000;
			sizePacketDAC = numWordsDAC * sizePacketDAC;

			// Размер пакета должен быть не меньше двух размеров буфера прерывания и не больше половины буфера драйвера
			if (sizePacketDAC < 2 * sizeInterruptBufferDAC)
				sizePacketDAC = 2 * sizeInterruptBufferDAC;
			if (sizePacketDAC > sizeBufferDAC / 2)
				sizePacketDAC = sizeBufferDAC / 2;
			// Параметры для генерации сигнала
			amplitude0 = 0;
			// Запись в буфер драйвера первых двух пакетов
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
			// Останов ЦАП
			Err = ZStopDAC(typeDevice, numberDSP);
			if (Err != 0)
				printf("Function ZStopDAC() return Error = 0x%X\n\r", Err);
		}
	int INITIALIZE_ADC()
		{
			// опросить  кол-во каналов АЦП
			Err = ZGetQuantityChannelADC(typeDevice, numberDSP, &numChannelsADC);
			if (Err != 0)
			{
				printf("ZGetQuantityChannelADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}

			// включить первый канал АЦП
			Err = ZSetInputADC(typeDevice, numberDSP, 0, 1);
			if (Err != 0)
			{
				printf("ZSetInputADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}

			// включить второй канал АЦП
			Err = ZSetInputADC(typeDevice, numberDSP, 1, 1);
			if (Err != 0)
			{
				printf("ZSetInputADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}
			// включить  третий канал АЦП
			Err = ZSetInputADC(typeDevice, numberDSP, 2, 1);
			if (Err != 0)
			{
				printf("ZSetInputADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}
			// включить  четвертый канал АЦП
			Err = ZSetInputADC(typeDevice, numberDSP, 3, 1);
			if (Err != 0)
			{
				printf("ZSetInputADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}
			// опросить коэф. усиления по первому каналу АЦП
			Err = ZGetAmplifyADC(typeDevice, numberDSP, 0, &amplifyADC0);
			if (Err != 0)
			{
				printf("ZGetAmplifyADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}

			// опросить коэф. усиления по второму каналу АЦП
			Err = ZGetAmplifyADC(typeDevice, numberDSP, 1, &amplifyADC1);
			if (Err != 0)
			{
				printf("ZGetAmplifyADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}
			// опросить коэф. усиления по третему каналу АЦП
			Err = ZGetAmplifyADC(typeDevice, numberDSP, 2, &amplifyADC2);
			if (Err != 0)
			{
				printf("ZGetAmplifyADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}
			// опросить коэф. усиления по четвертому каналу АЦП
			Err = ZGetAmplifyADC(typeDevice, numberDSP, 3, &amplifyADC3);
			if (Err != 0)
			{
				printf("ZGetAmplifyADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}

			// опросить вес младшего разряда АЦП первого канала
			Err = ZGetDigitalResolChanADC(typeDevice, numberDSP, 0, &resolutionADC0);
			if (Err != 0)
			{
				printf("ZGetDigitalResolChanADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}

			// опросить вес младшего разряда АЦП второго канала
			Err = ZGetDigitalResolChanADC(typeDevice, numberDSP, 1, &resolutionADC1);
			if (Err != 0)
			{
				printf("ZGetDigitalResolChanADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}
			// опросить вес младшего разряда АЦП третьего канала
			Err = ZGetDigitalResolChanADC(typeDevice, numberDSP, 2, &resolutionADC2);
			if (Err != 0)
			{
				printf("ZGetDigitalResolChanADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}
			// опросить вес младшего разряда АЦП четвертого канала
			Err = ZGetDigitalResolChanADC(typeDevice, numberDSP, 3, &resolutionADC3);
			if (Err != 0)
			{
				printf("ZGetDigitalResolChanADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}
			// опросить кол-во включенных каналов АЦП
			Err = ZGetNumberInputADC(typeDevice, numberDSP, &numChannelsADC);
			if (Err != 0)
			{
				printf("Function ZGetNumberInputADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}
			printf("chanels%d\n", numChannelsADC);
			// опросить кол-во слов в одном отсчете АЦП
			Err = ZGetWordsADC(typeDevice, numberDSP, &numWordsADC);
			if (Err != 0)
			{
				printf("ZGetWordsADC() return Error = 0x%X\n\r", Err);
				getch();
				return 0;
			}

			// Проверка переменных, чтобы избежать деления на 0
			if (numWordsADC == 0 || amplifyADC0 == 0 || amplifyADC1 == 0 || amplifyADC2 == 0 || amplifyADC3 == 0)
			{
				printf("Ошибочные значения параметров АЦП\n\r");
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}

			// запросить буфер АЦП
			Err = ZGetBufferADC(typeDevice, numberDSP, (void**)&pBuffer16ADC, &sizeBufferADC);
			if (Err != 0)
			{
				printf("Function ZGetBufferADC() return Error = 0x%X\n\r", Err);
				Err = ZClose(typeDevice, numberDSP);
				getch();
				return 0;
			}
			pBuffer32ADC = (long*)pBuffer16ADC;

			// Останов АЦП
			Err = ZStopADC(typeDevice, numberDSP);
			if (Err != 0)
				printf("Function ZStopADC() return Error = 0x%X\n\r", Err);

		}
	//Отключение АЦПЦАП
	void ZETOFF_DAC() {
			// Останов ЦАП
			Err = ZStopDAC(typeDevice, numberDSP);
			if (Err != 0)
			{
				MessageBox::Show("Unable to stop ZETLAB");
				
			}

			// Останов АЦП
			Err = ZStopADC(typeDevice, numberDSP);
			if (Err != 0)
			{
				MessageBox::Show("Unable to stop ZETLAB");
			}

			// Освободить буфер ЦАП
			if (pBuffer16DAC != NULL)
			{
				Err = ZRemBufferDAC(typeDevice, numberDSP, (void**)&pBuffer16DAC);
				if (Err != 0)
					printf("Function ZRemBufferDAC() return Error = 0x%X\n\r", Err);
			}
			// освободить буфер АЦП
			if (pBuffer16ADC != NULL)
			{
				Err = ZRemBufferADC(typeDevice, numberDSP, (void**)&pBuffer16ADC);
				if (Err != 0)
					printf("Function ZRemBufferADC() return Error = 0x%X\n\r", Err);
			}
			// Отключиться от драйвера (обязательно)
			Err = ZClose(typeDevice, numberDSP);
		}
	void ZETOFF_ADC()
		{
			Err = ZStopADC(typeDevice, numberDSP);
			if (Err != 0)
				printf("Function ZStopADC() return Error = 0x%X\n\r", Err);

			// освободить буфер АЦП
			if (pBuffer16ADC != NULL)
			{
				Err = ZRemBufferADC(typeDevice, numberDSP, (void**)&pBuffer16ADC);
				if (Err != 0)
					printf("Function ZRemBufferADC() return Error = 0x%X\n\r", Err);
			}

			// отключиться от драйвера (обязательно)
			Err = ZClose(typeDevice, numberDSP);
			if (Err != 0)
				printf("Function ZClose() return Error = 0x%X\n\r", Err);
			MessageBox::Show("Zetlab is stoped");
		}

	//ТЕмпература в цельсиях по термо ЭДС
	float chrom(float u) {
			// функция возвращает значение температуры(в градусах цельсия) для термо эдс  в В. 
			//домножение на 1000 вызвано размерностью коэффициентов в полиноме
			// деление на 100 вызвано коэффициентом усилителя zet 411
			u = u * 1000 / 100;
			//

			float t = 0;
			//    if (u < 0){ u = -u; }
				 //u=u*1.07
			u = u * dT;
			t = (((-1.2306e-5*u + 0.002103)*u - 0.1326)*u + 15.151)*u;

			return t;


		}



	//Запуск измерений
	private: System::Void button_start_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		button_start->Enabled = false;
		button_stop->Enabled = true;
		bool_do = true;
	}
//Остановка измерений
private: System::Void button_stop_Click(System::Object^  sender, System::EventArgs^  e)
{
	button_start->Enabled = true;
	button_stop->Enabled = false;
	bool_do = false;
}
	//Каждые 100 мск снимаются данные
	private: System::Void timer_Tick(System::Object^  sender, System::EventArgs^  e) {

			 if (bool_do)
			 {

			 }

		 }
};
}
