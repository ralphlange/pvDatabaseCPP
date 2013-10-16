/*longArrayMonitorMain.cpp */
/**
 * Copyright - See the COPYRIGHT that is included with this distribution.
 * EPICS pvData is distributed subject to a Software License Agreement found
 * in file LICENSE that is included with this distribution.
 */
/**
 * @author mrk
 * @date 2013.08.10
 */

/* Author: Marty Kraimer */

#include <cstddef>
#include <cstdlib>
#include <cstddef>
#include <string>
#include <cstdio>
#include <memory>
#include <iostream>
#include <vector>

#include <pv/standardField.h>
#include <pv/standardPVField.h>
#include <pv/arrayPerformance.h>
#include <pv/longArrayMonitor.h>
#include <pv/traceRecord.h>
#include <pv/channelProviderLocal.h>
#include <pv/serverContext.h>
#include <pv/clientFactory.h>

using namespace std;
using std::tr1::static_pointer_cast;
using namespace epics::pvData;
using namespace epics::pvAccess;
using namespace epics::pvDatabase;

int main(int argc,char *argv[])
{
    String channelName("arrayPerformance");
    bool useQueue = false;
    if(argc==2 && String(argv[1])==String("-help")) {
        cout << "longArrayMonitorMain channelName useQueue" << endl;
        cout << "default" << endl;
        cout << "longArrayMonitorMain " << channelName << " ";
        cout << (useQueue ? "true" : "false") << endl;
        return 0;
    }
    ClientFactory::start();
    if(argc>1) channelName = argv[1];
    if(argc>2) useQueue = (String(argv[2])==String("true") ? true : false);
    cout << "longArrayMonitorMain " << channelName << " ";
    cout << (useQueue ? "true" : "false") << endl;
    LongArrayMonitorPtr longArrayMonitor
         = LongArrayMonitor::create("pvAccess",channelName,useQueue);
    longArrayMonitor->start();
    cout << "longArrayMonitor\n";
    string str;
    while(true) {
        cout << "Type exit to stop: \n";
        getline(cin,str);
        if(str.compare("exit")==0) break;

    }
    ClientFactory::stop();
    epicsThreadSleep(.1);
    longArrayMonitor->destroy();
    longArrayMonitor.reset();
    return 0;
}

