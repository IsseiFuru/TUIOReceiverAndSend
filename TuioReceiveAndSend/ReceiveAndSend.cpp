/**
 * @file ReceiveAndSend.cpp
 * @author Issei Furutani (fullonefine@gmail.com)
 * @brief
 * このプログラムは外部から受け取ったTUIOのアドレスとメッセージを送信するプログラムです。
 * @version 0.1
 * @date 2022-10-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "ReceiveAndSend.h"

static std::string _receive_to_address("localhost");
static bool _udp = true;
static int _receive_to_port = 3333;

void ReceiveAndSend::addTuioObject(TuioObject* tobj) {
    std::cout << "add obj " << tobj->getSymbolID() << " ("
              << tobj->getSessionID() << "/" << tobj->getTuioSourceID() << ") "
              << tobj->getX() << " " << tobj->getY() << " " << tobj->getAngle()
              << std::endl;
}

void ReceiveAndSend::updateTuioObject(TuioObject* tobj) {
    std::cout << "set obj " << tobj->getSymbolID() << " ("
              << tobj->getSessionID() << "/" << tobj->getTuioSourceID() << ") "
              << tobj->getX() << " " << tobj->getY() << " " << tobj->getAngle()
              << " " << tobj->getMotionSpeed() << " "
              << tobj->getRotationSpeed() << " " << tobj->getMotionAccel()
              << " " << tobj->getRotationAccel() << std::endl;
}

void ReceiveAndSend::removeTuioObject(TuioObject* tobj) {
    std::cout << "del obj " << tobj->getSymbolID() << " ("
              << tobj->getSessionID() << "/" << tobj->getTuioSourceID() << ")"
              << std::endl;
}

void ReceiveAndSend::addTuioCursor(TuioCursor* tcur) {
    std::cout << "add cur " << tcur->getCursorID() << " ("
              << tcur->getSessionID() << "/" << tcur->getTuioSourceID() << ") "
              << tcur->getX() << " " << tcur->getY() << std::endl;
}

void ReceiveAndSend::updateTuioCursor(TuioCursor* tcur) {
    std::cout << "set cur " << tcur->getCursorID() << " ("
              << tcur->getSessionID() << "/" << tcur->getTuioSourceID() << ") "
              << tcur->getX() << " " << tcur->getY() << " "
              << tcur->getMotionSpeed() << " " << tcur->getMotionAccel() << " "
              << std::endl;
}

void ReceiveAndSend::removeTuioCursor(TuioCursor* tcur) {
    std::cout << "del cur " << tcur->getCursorID() << " ("
              << tcur->getSessionID() << "/" << tcur->getTuioSourceID() << ")"
              << std::endl;
}

void ReceiveAndSend::addTuioBlob(TuioBlob* tblb) {
    std::cout << "add blb " << tblb->getBlobID() << " (" << tblb->getSessionID()
              << "/" << tblb->getTuioSourceID() << ") " << tblb->getX() << " "
              << tblb->getY() << " " << tblb->getAngle() << " "
              << tblb->getWidth() << " " << tblb->getHeight() << " "
              << tblb->getArea() << std::endl;
}

void ReceiveAndSend::updateTuioBlob(TuioBlob* tblb) {
    std::cout << "set blb " << tblb->getBlobID() << " (" << tblb->getSessionID()
              << "/" << tblb->getTuioSourceID() << ") " << tblb->getX() << " "
              << tblb->getY() << " " << tblb->getAngle() << " "
              << tblb->getWidth() << " " << tblb->getHeight() << " "
              << tblb->getArea() << " " << tblb->getMotionSpeed() << " "
              << tblb->getRotationSpeed() << " " << tblb->getMotionAccel()
              << " " << tblb->getRotationAccel() << std::endl;
}

void ReceiveAndSend::removeTuioBlob(TuioBlob* tblb) {
    std::cout << "del blb " << tblb->getBlobID() << " (" << tblb->getSessionID()
              << "/" << tblb->getTuioSourceID() << ")" << std::endl;
}

void ReceiveAndSend::refresh(TuioTime frameTime) {
    // std::cout << "refresh " << frameTime.getTotalMilliseconds() << std::endl;
}

static void show_help() {
    std::cout << "Usage: ReceiveAndSend -p [port] -t -a [address]" << std::endl;
    std::cout << "        -p [port] for alternative port number" << std::endl;
    std::cout << "        -t for TUIO/TCP (default is TUIO/UDP)" << std::endl;
    std::cout << "        -a [address] for remote TUIO/TCP server" << std::endl;
    std::cout << "           use 'incoming' for TUIO/TCP socket" << std::endl;
    std::cout << "        -h show this help" << std::endl;
}

static void init(int argc, char** argv) {
    char c;
#ifndef WIN32
    while ((c = getopt(argc, argv, "p:a:th")) != -1) {
        switch (c) {
            case 't':
                _udp = false;
                break;
            case 'a':
                _receive_to_address = std::string(optarg);
                break;
            case 'p':
                _receive_to_port = atoi(optarg);
                break;
            case 'h':
                show_help();
                exit(0);
            default:
                show_help();
                exit(1);
        }
    }
#endif
}

int main(int argc, char* argv[]) {
    init(argc, argv);

    OscReceiver* osc_receiver;
    if (_udp)
        osc_receiver = new UdpReceiver(_receive_to_port);
    else {
        if (_receive_to_address == "incoming")
            osc_receiver = new TcpReceiver(_receive_to_port);
        else
            osc_receiver =
                new TcpReceiver(_receive_to_address.c_str(), _receive_to_port);
    }
    ReceiveAndSend receive_and_send;
    TuioClient client(osc_receiver);
    client.addTuioListener(&receive_and_send);
    client.connect(true);

    delete osc_receiver;
    return 0;
}
