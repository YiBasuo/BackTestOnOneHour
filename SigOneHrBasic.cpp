//------------------------------------------------------------------------
// 简称: SigOneHrBasic
// 名称: SignalOne1HrBasic
// 类别: 公式应用
// 类型: 用户应用
// 输出:
// Version: 1.0
//------------------------------------------------------------------------

Params
Vars
	//***********************Signal Vars********************//
	BoolSeries SigOneBuy;
	BoolSeries SigOneSell;
	NumericSeries signal;
	NumericSeries triggeredPrice;
	NumericSeries abortPrice;
	
	//***********************Strategy Vars******************//
	Numeric Lots(1);
	Numeric BuyPrice;

	//***********************Modifiers**********************//
	Bool ModifierLong;
	Bool ModifierShort;
	
Begin	
	//***********************************Signal Searching***************************************//
	signal = SignalSearching();
	
	//**********************************Involve Modifier***************************************//
	// Open Modifier
	ModifierLong = False;
	ModifierShort = False;
	if (Low > Low[1])
	{
		ModifierLong = True;
	}
	if (High < High[1])
	{
		ModifierShort = True;
	}
	
	//**********************************Run Strategy******************************************//
	triggeredPrice = 0;
	abortPrice = 0;
	if (signal == 1)
	{
		triggeredPrice = High;
		abortPrice = Low;
	}
	else if (signal == -1)
	{
		triggeredPrice = Low;
		abortPrice = High;
	}
	
	//**********************************Involve Modifier***************************************//
	ModifierLong = False;
	ModifierShort = False;
	if (Low > Low[1])
	{
		ModifierLong = True;
	}
	if (High < High[1])
	{
		ModifierShort = True;
	}
	
	//**********************************Run Strategy******************************************//
	if (signal[1] > 0 And ModifierLong)
	{
		// Exceed the prev bar, open buy
		if (High > High[1])
		{
			Buy(Lots, High[1]);
		}
		// If the current bar does not trigger the signal, move to the next bar
		if (High < High[1] And Low > Low[1])
		{
			signal = 1;
		}
	}
	
	if (signal[1] < 0 And ModifierShort)
	{
		// Exceed the prev bar, open buy
		if (Low < Low[1])
		{
			SellShort(Lots, Low[1]);
		}
		// If the current bar does not trigger the signal, move to the next bar
		if (Low > Low[1] And High < High[1])
		{
			signal = -1;
		}
	}
	
	if (Low < Low[1] And MarketPosition == 1)
	{
		Sell(Lots, Low[1]);
	}
	
	if (High > High[1] And MarketPosition == -1)
	{
		BuyToCover(Lots, High[1]);
	}
	//***********************************************************//
	
	PlotString("sig", Text(signal), Low - 25);
	PlotString("tp", Text(triggeredPrice), Low - 50);
	PlotString("ap", Text(abortPrice), Low - 75);
End


//------------------------------------------------------------------------
// 编译版本	GS2015.12.25
// 用户版本	2017/05/26 09:59:08
// 版权所有	qwerrqwer
// 更改声明	TradeBlazer Software保留对TradeBlazer平台
//			每一版本的TradeBlazer公式修改和重写的权利
//------------------------------------------------------------------------
