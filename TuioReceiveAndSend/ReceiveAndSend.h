/***
 * TUIO C++
 * Copyright (c) 2022 Issei Furutani
 *
 * このプログラムは外部から受け取ったTUIOのアドレスとメッセージを送信するプログラムです。
 * TUIOの公式デモであるSimpleSimulatorとTuioDumpのコードを参考にして作成を行っています。
 */

#ifndef INCLUDED_RECEIVEANDSEND_H
#define INCLUDED_RECEIVEANDSEND_H

#include <math.h>

// #include <list>

// #include "FlashSender.h"
#include "TcpReceiver.h"
// #include "TcpSender.h"
#include "TuioClient.h"
// #include "TuioCursor.h"
#include "TuioListener.h"
// #include "TuioServer.h"
#include "UdpReceiver.h"
// #include "WebSockSender.h"
// #include "osc/OscTypes.h"

using namespace TUIO;

class ReceiveAndSend : public TuioListener {
   public:
    void addTuioObject(TuioObject *tobj);
    void updateTuioObject(TuioObject *tobj);
    void removeTuioObject(TuioObject *tobj);

    void addTuioCursor(TuioCursor *tcur);
    void updateTuioCursor(TuioCursor *tcur);
    void removeTuioCursor(TuioCursor *tcur);

    void addTuioBlob(TuioBlob *tblb);
    void updateTuioBlob(TuioBlob *tblb);
    void removeTuioBlob(TuioBlob *tblb);

    void refresh(TuioTime frameTime);
};

#endif /* INCLUDED_RECEIVEANDSEND_H */
