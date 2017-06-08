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
	
	//***********************Strategy Vars******************//
	Numeric Lots(1);
	Numeric BuyPrice;

	//***********************Modifiers**********************//
	Bool ModifierLong;
	Bool ModifierShort;
	
Begin	
	//***********************************Signal Searching***************************************//
	signal = SignalSearching();
	
	if (signal < 0)
	{
		SigOneSell = True;
	}
	else
	{
		SigOneSell = False;
	}
	if (signal > 0)
	{
		SigOneBuy = True;
	}
	else
	{
		SigOneBuy = False;
	}
	
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
	// Test SigOne
	if (SigOneBuy[1] And ModifierLong)
	{
		// Exceed the prev bar, open buy
		if (High > High[1])
		{
			Buy(Lots, High[1]);
		}
		// If the current bar does not trigger the signal, move to the next bar
		if (High < High[1] And Low > Low[1])
		{
			SigOneBuy = True;
		}
	}
	if (Low < Low[1] And MarketPosition == 1)
	{
		Sell(Lots, Low[1]);
	}
	
	if (SigOneSell[1] And ModifierShort)
	{
		// Exceed the prev bar, open buy
		if (Low < Low[1])
		{
			SellShort(Lots, Low[1]);
		}
		// If the current bar does not trigger the signal, move to the next bar
		if (Low > Low[1] And High < High[1])
		{
			SigOneSell = True;
		}
	}
	if (High > High[1] And MarketPosition == -1)
	{
		BuyToCover(Lots, High[1]);
	}	
	//***********************************************************//
End


//------------------------------------------------------------------------
// 编译版本	GS2015.12.25
// 用户版本	2017/05/26 09:59:08
// 版权所有	qwerrqwer
// 更改声明	TradeBlazer Software保留对TradeBlazer平台
//			每一版本的TradeBlazer公式修改和重写的权利
//------------------------------------------------------------------------
