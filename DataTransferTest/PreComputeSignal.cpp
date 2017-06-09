//------------------------------------------------------------------------
// 简称: PreComputeSignal
// 名称: Pre-Compute Signal on Long Period
// 类别: 公式应用
// 类型: 用户应用
// 输出:
//------------------------------------------------------------------------


Params	
	string signalPeriod("1HrSignal");
	string triggerPriceTableName("TriggerPrice");
	string abortPriceTableName("AbortPrice");
	
	//*************Adding 1Hr Filter and Day filter*******************//
	
Vars
	//***********Signal****************//
	// 1 for buy, -1 for sell, and 0 for no-op
	NumericSeries signal;
	
	//******Vars for saving signal data**********//
	// Key is Date + Time; Value is signal
	string strKey;
	string signalValue;
	string triggerPriceValue;
	string abortPriceValue;
	
	//*************Adding 1Hr Filter and Day filter*******************//

Begin
	//*****************************Search for Signal Part**************************//
	signal = SignalSearching();
	
	//***************************Save Signal to a File Part********************************//

	strKey = DateTimeToString(Date + Time);
	signalValue = Text(signal);
		
	SetTBProfileString(signalPeriod, strKey, signalValue);
	
	triggerPriceValue = Text(0);
	abortPriceValue = Text(0);
	If (signal > 0)
	{
		triggerPriceValue = Text(High);
		abortPriceValue = Text(Low);
	}
	Else If (signal < 0)
	{
		triggerPriceValue = Text(Low);
		abortPriceValue = Text(High);
	}
	//*************Adding 1Hr Filter and Day filter*******************//
	
	
	//*************Save all signals into DB***************************//
	SetTBProfileString(triggerPriceTableName, strKey, triggerPriceValue);
	SetTBProfileString(abortPriceTableName, strKey, abortPriceValue);
		
End

//------------------------------------------------------------------------
// 编译版本	GS2015.12.25
// 用户版本	2017/06/03 15:04:52
// 版权所有	qwerrqwer
// 更改声明	TradeBlazer Software保留对TradeBlazer平台
//			每一版本的TradeBlazer公式修改和重写的权利
//------------------------------------------------------------------------