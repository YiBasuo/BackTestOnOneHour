//------------------------------------------------------------------------
// 简称: SaveDayData
// 名称: 
// 类别: 公式应用
// 类型: 用户应用
// 输出:
//------------------------------------------------------------------------

Params		
	Numeric FastLength(12);
	Numeric SlowLength(26);
	Numeric MACDLength(9);
	Numeric TrendLength(60);
	
	//*************Adding 1Hr Filter and Day filter*******************//
	
Vars
	//******Vars for saving signal data**********//
	// Key is Date + Time; Value is signal
	string strKey;
	string signalValue;
	
	//*************Indicators*******************//
	NumericSeries DIF; 
	NumericSeries DEA;
	NumericSeries MACD;
	
	NumericSeries DIFMain;
	NumericSeries DEAMain;
	NumericSeries MidLine;
	NumericSeries MA60;
	
	Numeric changeRate;
	Numeric trend;
	
	Numeric i;// Iterator
	Numeric daysInOneDirection;
Begin
	//***********************************Day Indicators*****************************//
	// Compute MACD Value:
	DIF = XAverage( Close, FastLength ) - XAverage( Close, SlowLength ) ;	
	DEA = XAverage(DIF, MACDLength);
	MACD = DIF - DEA;
	
	
	DIFMain = MA60 + DIF * 3.9;
	DEAMain = XAverage(DIFMain, MACDLength);
	MidLine = XAverage(XAverage(C,10),10);
	MA60 = XAverage(Close, 60);
	
	PlotNumeric("Dif", DIFMain);
	PlotNumeric("DEA", DEAMain);
	PlotNumeric("Mid", MidLine);
	PlotNumeric("MA60", MA60);
	
	changeRate = RateOfChange(Close, 1);
	
	//***************************Save Signal to a File Part********************************//

	strKey = DateTimeToString(Date);
	
	//*************Save all signals into DB***************************//
	SetTBProfileString("DayHigh", strKey, Text(High));
	SetTBProfileString("DayLow", strKey, Text(Low));
	SetTBProfileString("DayOpen", strKey, Text(Open));
	SetTBProfileString("DayClose", strKey, Text(Close));
	SetTBProfileString("DayDIFMain", strKey, Text(DIFMain));
	SetTBProfileString("DayDEAMain", strKey, Text(DEAMain));
	SetTBProfileString("DayChangeRate", strKey, Text(changeRate));
	SetTBProfileString("DayDEADirection", strKey, Text(DEAMain - DEAMain[1]));
	SetTBProfileString("DayDIFDirection", strKey, Text(DIFMain - DIFMain[1]));

	if (DEAMain > MidLine && MidLine > MA60 && MidLine > MidLine[1] && MA60 > MA60[1])
	{
		trend = 1;
	}
	else if (DEAMain < MidLine && MidLine < MA60 && MidLine < MidLine[1] && MA60 < MA60[1])
	{
		trend = -1;
	}
	else 
	{
		trend = 0;
	}
	
	SetTBProfileString("DayTrend", strKey, Text(trend));
	
	daysInOneDirection = 0;
	for i = 0 to 100
	{
		if (Close[i] >= Open[i] && Close[i + 1] >= Open[i + 1] && Low[i] > Low[i + 1])
		{
			daysInOneDirection = daysInOneDirection + 1;
		}
		else if (Close[i] <= Open[i] && Close[i + 1] <= Open[i + 1] && High[i] < High[i + 1])
		{
			daysInOneDirection = daysInOneDirection - 1;
		}
		else 
		{
			break;
		}
	}
	
	PlotString("diod", Text(daysInOneDirection), Low - 25);
	SetTBProfileString("DayDaysInOneDirection", strKey, Text(daysInOneDirection));

End

//------------------------------------------------------------------------
// 编译版本	GS2015.12.25
// 用户版本	2017/06/15 10:48:38
// 版权所有	qwerrqwer
// 更改声明	TradeBlazer Software保留对TradeBlazer平台
//			每一版本的TradeBlazer公式修改和重写的权利
//------------------------------------------------------------------------