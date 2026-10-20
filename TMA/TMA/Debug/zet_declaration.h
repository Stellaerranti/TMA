long typeDevice = 16;				// Тип устройства
long numberDSP = 0;					// Порядковый номер устройства
long Err;							// Код ошибки
long enable;						// Вкл. / Выкл. (поддерживается / не поддерживается)
long numChannelsDAC;				// Кол-во включенных каналов ЦАП
long numWordsDAC;					// Кол-во слов (по два байта) в одном отсчете ЦАП
short *pBuffer16DAC;				// Указатель на начало буфера драйвера для ЦАП с разрядностью не более 16 бит
long *pBuffer32DAC;					// Указатель на начало буфера драйвера для ЦАП с разрядностью более 16 бит 
long sizeBufferDAC;					// Размер буфера драйвера в словах
long sizeInterruptBufferDAC;		// Размер буфера прерывания в словах
long sizePacketDAC;					// Кол-во отсчетов обрабатываемых за один раз
long sleepTime;						// Время ожидания в цикле (мс)
long responseTime = 1000;				// Время реакции в цикле (мс). Должно быть больше времени ожидания

long i, size;						// Счетчик цикла
long pointerDriverDAC = 0;			// Указатель драйвера на текущий элемент заполнения буфера драйвера
long pointerDriverDAC_old = 0;		// Предыдущее значение указателя драйвера на буфер драйвера
long pointerCycleDAC = 0;				// Указатель цикла обработки на текущий элемент заполнения буфера драйвера

double freqDAC;						// Частота дискретизации ЦАП
double attenDAC0 = 0.1;				// Коэф. затухания по первому каналу ЦАП
double attenDAC1 = 0.1;
double resolutionDAC0;				// Вес младшего разряда ЦАП
double resolutionDAC1;

double currentSinusTime;			// Аргумент функции синус
double deltaSinusTime;				// Значение инкремента аргумента функции синус
double volt0_DAC;						// Мгновенное текущее значение, записываемое в ЦАП (код)
double volt1_DAC;
double amplitude0 = 0;
double amplitude1 = 0;
double amplitude_volt_0 = 0;
double amplitude_volt_1 = 0;

long numChannelsADC;				// Кол-во включенных каналов АЦП
long numWordsADC;					// Кол-во слов (по два байта) в одном отсчете АЦП
short *pBuffer16ADC;				// Указатель на начало буфера драйвера для АЦП с разрядностью не более 16 бит
long *pBuffer32ADC;					// Указатель на начало буфера драйвера для АЦП с разрядностью более 16 бит 
long sizeBufferADC;					// Размер буфера драйвера в словах
long pointerADC = 0;					// Указатель на текущий элемент заполнения буфера драйвера (кратен 2)
long pointerADC_old = 0;				// Предыдущее значение указателя на буфер драйвера
double amplifyADC0;                 // Коэф. усиления по  каналам 
double amplifyADC1;
double amplifyADC2;
double amplifyADC3;


double resolutionADC0;// Вес младшего разряда АЦП
double resolutionADC1;
double resolutionADC2;
double resolutionADC3;
double volt0;// Мгновенное текущее значение АЦП (в Вольтах)
double volt1;
double volt2;
double volt3;
