#include"Tool.h"




Label *Tool::createLabelByKey(const std::string Key,const std::string FontType, float FontSize)
{
	auto dictionary = Dictionary::createWithContentsOfFile("texts/texts.xml");
	const char *ChineseText = ((String*)dictionary->objectForKey(Key))->_string.c_str();
	auto label = Label::create(ChineseText, FontType,FontSize);
	label->enableShadow(Color4B(58, 35, 10, 255), Size(0, -1));
	
	return label;
}

void Tool::setLabelString(Label* label, const std::string key)
{
	auto dictionary = Dictionary::createWithContentsOfFile("texts/texts.xml");
	const char *ChineseText = ((String*)dictionary->objectForKey(key))->_string.c_str();
	label->setString(ChineseText);
	/*label->setString(IConvConvert_GBKToUTF8(key).c_str());*/
}

int Tool::getGameTime()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

	struct timeval now;
	struct tm* time;

	gettimeofday(&now, NULL);


	time = localtime(&now.tv_sec);
	return time->tm_hour;
	//int year = time->tm_year + 1900;
	//log("year = %d", year);

	//char date[32] = { 0 };
	//sprintf(date, "%d%02d%02d", (int)time->tm_year + 1900, (int)time->tm_mon + 1, (int)time->tm_mday);
	//log("%s", date);
	//return StringUtils::format("%s", date);

#endif

#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )

	struct tm* tm;
	time_t timep;
	time(&timep);

	tm = localtime(&timep);
	//char date[32] = { 0 };
	//sprintf(date, "%d-%02d-%02d", (int)tm->tm_year + 1900, (int)tm->tm_mon + 1, (int)tm->tm_mday);
	//log("%s", date);
	//return StringUtils::format("%s", date);
	return tm->tm_hour;

#endif
}


/*本游戏中使用的标题型字体样式*/
Label*Tool::createTitleLabel(int size)
{
	auto label = Label::create("", "fonts/title.ttf", size);
	label->enableShadow(Color4B(58, 35, 10, 255*0.8), Size(0, -0.5));
	label->setScale(0.65);


	return label;
}
/*本游戏中使用的正文型字体样式*/
Label*Tool::createTextLabel()
{
	auto label = Label::create("", "fonts/title.ttf", 15);
	label->enableShadow(Color4B(58, 35, 10, 255*0.8), Size(-0.25, -0.25));
	label->setColor(Color3B(127, 71, 4));
	label->setScale(0.5);
	return label;
}

Label*Tool::createEnglishLabel()
{
	auto label = Label::create("", "fonts/english.ttf", 10);
	label->enableShadow(Color4B(58, 35, 10, 255), Size(0, -0.2));
	label->setScale(0.7);
	
	return label;
}

bool Tool::IConvConvert(const char *from_charset, const char *to_charset, const char *inbuf, int inlen, char *outbuf, int outlen)
{

	iconv_t cd = iconv_open(to_charset, from_charset);

	if (cd == 0) return false;

	const char **pin = &inbuf;

	char **pout = &outbuf;

	memset(outbuf, 0, outlen);

	size_t ret = iconv(cd, pin, (size_t *)&inlen, pout, (size_t *)&outlen);

	iconv_close(cd);

	return ret == (size_t)(-1) ? false : true;

}

std::string Tool::IConvConvert_GBKToUTF8(const std::string& str)
{

	const char* textIn = str.c_str();

	char textOut[256];

	bool ret = IConvConvert("gb2312", "utf-8", textIn, strlen(textIn), textOut, 256);

	return ret ? std::string(textOut) : std::string();

}