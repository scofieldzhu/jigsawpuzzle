/*=======================================================================
JigsawPuzzle is a kind of simple jigsaw puzzle game.
Copyright (c) scofieldzhu. All rights reserved.	

Project: jigsawpuzzle 
Module: applogger.cpp 
CreateTime: 2019-7-17 21:02
Creator: scofieldzhu
=======================================================================*/
#include "applogger.h"
#include <Windows.h>
#include <fstream>
#include "xmlConfParser.h"
#include "xmlConfParseException.h"
#include "defAppender.h"
#include "standardFormatter.h"
USING_SFLOGGER

Logger* g_LoggerInst = nullptr;

class WinConsoleAppender : public DefAppender
{
    HEAP_OBJECT(WinConsoleAppender)
public:
    bool write(const Log& log, const std::xStrT& logged_msg)
    {
        ::OutputDebugStringA(logged_msg.c_str());
        return true;
    }
    void flush(){}
    WinConsoleAppender()
        :DefAppender(1){}
    ~WinConsoleAppender() = default;
};

void InitLogger()
{
    #ifdef _DEBUG
        Logger* newlogger = new Logger("App");
        WinConsoleAppender* appender = new WinConsoleAppender();
        appender->setFormatter(new StandardFormatter());
        newlogger->addAppender(*appender);
        g_LoggerInst = newlogger;
    #else 
        const char* conffilepath = "conf/applogger.xml";    
        try{
            XmlConfParser parser(conffilepath);
            parser.parse();
        }catch(const XmlConfParseException& e){
            const std::string msg = e.what_err();
            std::ofstream errf("except.log.txt");
            errf.write(msg.c_str(), msg.size());
            errf.close();
            g_LoggerInst = nullptr;
            return;
        }    
        g_LoggerInst = LoggerMgr::GetInst()->getLogger("App");
    #endif
}
