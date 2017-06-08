//------------------------------------------------------------------------
// 简称: SignalSearching
// 名称: Signal Searching
// 类别: 用户函数
// 类型: 用户函数
// 输出: 数值型
//------------------------------------------------------------------------

Params	
	Numeric FastLength(12);
	Numeric SlowLength(26);
	Numeric MACDLength(9);
	Numeric TrendLength(60);
	
Vars
	// MACD Vars
	NumericSeries DIF; 
	Numeric DEA;
	Numeric MACD;
	
	NumericSeries DIFMain;
	NumericSeries DEAMain;
	NumericSeries MidLine;
	NumericSeries MA60;
	// Sig Vars
	Bool currentTrendRise;
	Bool currentTrendFall;
	Bool riseIndicator;
	Bool fallIndicator;
	
	//***********Signal****************//
	// 1 for buy, -1 for sell, and 0 for no-op
	NumericSeries signal;
	
Begin
	//*****************************Search for Signal Part**************************//
	// Compute MACD Value:
	DIF = XAverage( Close, FastLength ) - XAverage( Close, SlowLength ) ;	
	DEA = XAverage(DIF, MACDLength);
	MACD = DIF - DEA;
	
	
	DIFMain = MA60 + DIF * 3.9;
	DEAMain = XAverage(DIFMain, MACDLength);
	MidLine = XAverage(XAverage(C,10),10);
	MA60 = XAverage(Close, 60);
	
	PlotNumeric("MidLine", MidLine);
	PlotNumeric("MA60", MA60);
	
	// Figure out current trend
	if (MACD > 0)
	{
		currentTrendRise = True;
		currentTrendFall = False;
	}
	Else if (MACD < 0)
	{
		currentTrendRise = False;
		currentTrendFall = True;
	}
	Else
	{
		currentTrendRise = True;
		currentTrendFall = True;
	}
	
	// Figure out current direction
	if (Low[1] > Low[2] || Close[1] >= Open[1])
	{
		riseIndicator = True;
	}
	Else
	{
		riseIndicator = False;
	}
	if (High[1] < High[2] || Close[1] <= Open[1])
	{
		fallIndicator = True;
	}
	Else
	{	
		fallIndicator = False;
	}
	
	// Find Signal One
	If (currentTrendFall && riseIndicator && High >= High[1] && Close <= Open)
	{
		signal = -1;
	}
	Else If (currentTrendRise && fallIndicator && Low <= Low[1] && Close >= Open)
	{
		signal = 1;
	}
	Else
	{
		signal = 0;
	}
	
	return signal;
	
End

//------------------------------------------------------------------------
// 编译版本	GS2015.12.25
// 用户版本	2017/06/03 17:08:32
// 版权所有	qwerrqwer
// 更改声明	TradeBlazer Software保留对TradeBlazer平台
//			每一版本的TradeBlazer公式修改和重写的权利
//------------------------------------------------------------------------
