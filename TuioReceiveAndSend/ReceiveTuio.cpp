/**
 * @file ReceiveTuio.cpp
 * @author Issei Furutani (fullonefine@gmail.com)
 * @brief
 * このプログラムは外部から受け取ったTUIOのバンドルを加工して、新たなOSCのメッセージとして送信するプログラムです。
 * また、TuioCursorのみを受信するようになっています。
 * 送られるOSCのメッセージは以下の内容である。
 * /fillter/tuio add SessionID X Y
 * /fillter/tuio update SessionID X Y
 * /fillter/tuio remove SessionID
 * @version 1.0
 * @date 2022-11-08
 */

#include "ReceiveTuio.h"

#include "SendOsc.h"

static bool udp = true;
static std::string receive_to_address = "127.0.0.1";
static int receive_to_port = 3333;

void ReceiveTuio::addTuioObject(TuioObject* tobj) {}

void ReceiveTuio::updateTuioObject(TuioObject* tobj) {}

void ReceiveTuio::removeTuioObject(TuioObject* tobj) {}

void ReceiveTuio::addTuioCursor(TuioCursor* tcur) {
    std::cout << "add cur " << tcur->getCursorID() << " ("
              << tcur->getSessionID() << "/" << tcur->getTuioSourceID() << ") "
              << tcur->getX() << " " << tcur->getY() << std::endl;
    oscMessage::SendOsc::SendMessageWithPosition("add", tcur->getCursorID(),
                                                 tcur->getX(), tcur->getY());
}

void ReceiveTuio::updateTuioCursor(TuioCursor* tcur) {
    std::cout << "set cur " << tcur->getCursorID() << " ("
              << tcur->getSessionID() << "/" << tcur->getTuioSourceID() << ") "
              << tcur->getX() << " " << tcur->getY() << " "
              << tcur->getMotionSpeed() << " " << tcur->getMotionAccel() << " "
              << std::endl;

    oscMessage::SendOsc::SendMessageWithPosition("update", tcur->getCursorID(),
                                                 tcur->getX(), tcur->getY());
}

void ReceiveTuio::removeTuioCursor(TuioCursor* tcur) {
    std::cout << "del cur " << tcur->getCursorID() << " ("
              << tcur->getSessionID() << "/" << tcur->getTuioSourceID() << ")"
              << std::endl;

    oscMessage::SendOsc::SendMessage("remove", tcur->getCursorID());
}

void ReceiveTuio::addTuioBlob(TuioBlob* tblb) {}

void ReceiveTuio::updateTuioBlob(TuioBlob* tblb) {}

void ReceiveTuio::removeTuioBlob(TuioBlob* tblb) {}

void ReceiveTuio::refresh(TuioTime frameTime) {}

static void init(int argc, char** argv) {
    char c;
#ifndef WIN32
    while ((c = getopt(argc, argv, "p:a:th")) != -1) {
        switch (c) {
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

int main(int argc, char* argv[]) {
    init(argc, argv);

    OscReceiver* osc_receiver;
    if (udp)
        osc_receiver = new UdpReceiver(receive_to_port);
    else {
        if (receive_to_address == "incoming")
            osc_receiver = new TcpReceiver(receive_to_port);
        else
            osc_receiver =
                new TcpReceiver(receive_to_address.c_str(), receive_to_port);
    }
    ReceiveTuio receive_tuio;
    // SendOsc send_osc;
    TuioClient client(osc_receiver);
    client.addTuioListener(&receive_tuio);
    client.connect(true);

    delete osc_receiver;
    return 0;
}
