Action()
{
	double trans_time, think_time, wasted_Time, real_time; 
	char* trans_name;

	web_set_sockets_option("SSL_VERSION", "2&3");
	
	trans_name = "HomePage_Transaction";

	lr_start_transaction(trans_name);

	web_url("www.amdocs.com", 
		"URL=https://www.amdocs.com/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		EXTRARES, 
		//"Url=https://www.googletagmanager.com/gtm.js?id=GTM-KV8QBC", ENDITEM, 
		"Url=/amdocsOmega/styles/fonts/webfonts/32F19E_0_0.eot?", ENDITEM, 
		//"Url=https://m.addthis.com/live/red_lojson/300lo.json?si=5a6ffae4456cac0a&bkl=0&bl=1&pdt=147&sid=5a6ffae4456cac0a&pub=amdocs&rev=v8.1.5-wp&ln=en&pc=men&cb=0&ab=-&dp=www.amdocs.com&fp=&fr=&of=0&pd=0&irt=1&vcl=1&md=0&ct=1&tct=0&abt=0&cdn=0&pi=1&rb=0&gen=100&chr=utf-8&mk=Amdocs&colc=1517288164813&jsl=1&uvs=5a6ffae4d3e2fae6000&skipb=1&callback=addthis.cbs.oln9_79091208899493390", ENDITEM, 
		"Url=/amdocsOmega/images/icons/magnify.svg", ENDITEM, 
		"Url=https://647-ojr-802.mktoresp.com/webevents/visitWebPage?_mchNc=1517288166836&_mchCn=&_mchId=647-OJR-802&_mchTk=_mch-amdocs.com-1505800004665-42620&_mchHo=www.amdocs.com&_mchPo=&_mchRu=%2F&_mchPc=https%3A&_mchVr=151&_mchHa=&_mchRe=&_mchQp=", ENDITEM, 
		//"Url=https://secure.quantserve.com/aquant.js?a=p-31hzpeuCq88Uf", ENDITEM, 
		//"Url=https://pixel.quantserve.com/pixel;r=277516884;a=p-31hzpeuCq88Uf;orderid=;revenue=;labels=_fp.event.Homepage;rf=3;fpan=0;fpa=P0-324910482-1505800006934;ns=0;ce=1;cm=;je=1;sr=1600x900x24;enc=n;dst=0;et=1517288194916;tzo=-330;ref=;url=https%3A%2F%2Fwww.amdocs.com%2F;ogl=", ENDITEM, 
		//"Url=https://scripts.demandbase.com/wlw2c259.min.js", ENDITEM, 
		//"Url=https://api.company-target.com/api/v2/ip.json?referrer=&page=https%3A%2F%2Fwww.amdocs.com%2F&page_title=Amdocs%20digital%20network%20transformation%20communications&key=54aad186b3db8a4a437e66686a7411b6", ENDITEM, 
		LAST);
	
	// Get transaction time to this point 
	trans_time = lr_get_transaction_duration(trans_name);	
	think_time = lr_get_transaction_think_time(trans_name);
	wasted_Time = lr_get_transaction_wasted_time(trans_name);

	lr_end_transaction(trans_name, LR_AUTO);
	
	if (trans_time)
	     lr_output_message("The duration up to the submit is %f seconds", trans_time);
	else
	     lr_output_message("The duration cannot be determined.");	
	
	if (think_time)
    	lr_output_message("The transaction think time is %f seconds", think_time);
	else
    	lr_output_message("The think time cannot be determined.");
	
	if (wasted_Time)
    	lr_output_message("The transaction wasted time is %f seconds", wasted_Time);
	else
    	lr_output_message("The wasted time cannot be determined.");
	
	real_time = trans_time - (wasted_Time + think_time);
		
	lr_output_message("The transaction Real time is %f seconds", real_time);	
	
//	strcpy(fullpath, "transaction_time,source=vugen,site=amdocs value=");
//	strcat(fullpath, lr_eval_string(real_time));
	
	lr_param_sprintf("data", "loadrunner,transaction=%s,application=amdocs TransT=%.3f", trans_name, real_time);
	
	lr_log_message(lr_eval_string("{data}"));

	web_custom_request("web_custom_request",
		"URL=http://10.234.168.26:8086/write?db=PROD_MONITOR",
		"Method=POST",
		"TargetFrame=",
		"Resource=0",
		"Referer=",
		"EncType=text/binary",
		"BodyBinary={data}",
		LAST);
	
	return 0;
}