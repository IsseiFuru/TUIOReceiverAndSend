/**
 * @file ReceiveTuio.cpp
 * @author Issei Furutani
 * @brief
 * このプログラムは外部から受け取ったTUIOのバンドルを加工して、新たなOSCのメッセージとして送信するプログラムです。
 * また、TuioCursorのみを受信するようになっています。
 * 送られるOSCのメッセージは以下の内容である。
 * /fillter/tuio add SessionID X Y
 * /fillter/tuio update SessionID X Y
 * /fillter/tuio remove SessionID X Y
 * @version 1.0
 * @date 2022-11-08
 */

#include "ReceiveTuio.h"

#include "SendOsc.h"

static bool udp = true;
// 受信するクライアントマシンのIPアドレスとポート番号
static std::string receive_to_address = "127.0.0.1";
static int receive_to_port = 40000;

void ReceiveTuio::addTuioObject(TuioObject *tobj) {}

void ReceiveTuio::updateTuioObject(TuioObject *tobj) {}

void ReceiveTuio::removeTuioObject(TuioObject *tobj) {}

void ReceiveTuio::addTuioCursor(TuioCursor *tcur)
{
    oscMessage::SendOsc::SendMessageWithPosition("add", tcur->getCursorID(),
                                                 tcur->getX(), tcur->getY());
}

void ReceiveTuio::updateTuioCursor(TuioCursor *tcur)
{
    oscMessage::SendOsc::SendMessageWithPosition("update", tcur->getCursorID(),
                                                 tcur->getX(), tcur->getY());
}

void ReceiveTuio::removeTuioCursor(TuioCursor *tcur)
{
    oscMessage::SendOsc::SendMessageWithPosition("remove", tcur->getCursorID(),
                                                 tcur->getX(), tcur->getY());
}

void ReceiveTuio::addTuioBlob(TuioBlob *tblb) {}

void ReceiveTuio::updateTuioBlob(TuioBlob *tblb) {}

void ReceiveTuio::removeTuioBlob(TuioBlob *tblb) {}

void ReceiveTuio::refresh(TuioTime frameTime) {}

static void init(int argc, char **argv)
{
    char c;
#ifndef WIN32
    while ((c = getopt(argc, argv, "p:a:th")) != -1)
    {
        switch (c)
        {
        case 't':
            udp = false;
            break;
        case 'a':
            receive_to_address = std::string(optarg);
            break;
        case 'p':
            receive_to_port = atoi(optarg);
            break;
        default:
            exit(1);
        }
    }
#endif
}

int main(int argc, char *argv[])
{
    init(argc, argv);

    OscReceiver *osc_receiver;
    if (udp)
        osc_receiver = new UdpReceiver(receive_to_port);
    else
    {
        if (receive_to_address == "incoming")
            osc_receiver = new TcpReceiver(receive_to_port);
        else
            osc_receiver =
                new TcpReceiver(receive_to_address.c_str(), receive_to_port);
    }
    ReceiveTuio receive_tuio;
    TuioClient client(osc_receiver);
    client.addTuioListener(&receive_tuio);
    client.connect(true);

    delete osc_receiver;
    return 0;
}
