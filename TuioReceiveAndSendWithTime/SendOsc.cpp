/**
 * @file SendOsc.cpp
 * @author Issei Furutani (fullonefine@gmail.com)
 * @brief
 * このプログラムは加工されたTUIOのメッセージをOSCのメッセージとして、送信するプログラムです。
 * 送られるOSCのメッセージは以下の内容である。
 * /fillter/tuio add SessionID X Y
 * /fillter/tuio update SessionID X Y
 * /fillter/tuio remove SessionID
 * @version 1.0
 * @date 2022-11-08
 */

#include "SendOsc.h"

#include "ReceiveTuio.h"

const char* send_to_address = "192.168.1.194";
const int send_to_port = 50000;
static int output_buffer_size = 1024;

static double time_array2[COUNTTIME];
struct timespec ta;
static int counter2 = 0;

namespace oscMessage {

void SendOsc::SendMessage(const char* state, int SessionID) {
    UdpTransmitSocket transmitSocket(
        IpEndpointName(send_to_address, send_to_port));

    char buffer[output_buffer_size];
    osc::OutboundPacketStream p(buffer, output_buffer_size);

    p << osc::BeginBundleImmediate << osc::BeginMessage("/fillter/tuio")
      << state << SessionID << osc::EndMessage << osc::EndBundle;

    transmitSocket.Send(p.Data(), p.Size());
}

void SendOsc::SendMessageWithPosition(const char* state, int SessionID, float x,
                                      float y) {
    UdpTransmitSocket transmitSocket(
        IpEndpointName(send_to_address, send_to_port));

    char buffer[output_buffer_size];
    osc::OutboundPacketStream p(buffer, output_buffer_size);

    p << osc::BeginBundleImmediate << osc::BeginMessage("/fillter/tuio")
      << state << SessionID << x << y << osc::EndMessage << osc::EndBundle;

    transmitSocket.Send(p.Data(), p.Size());
    TimeCheckAfter();
}

void SendOsc::SendMessageWithPositionWithTime(const char* state, int SessionID, float x,
                                      float y, timespec ts) {
    UdpTransmitSocket transmitSocket(
        IpEndpointName(send_to_address, send_to_port));

    char buffer[output_buffer_size];
    osc::OutboundPacketStream p(buffer, output_buffer_size);

    p << osc::BeginBundleImmediate << osc::BeginMessage("/fillter/tuio")
      << state << SessionID << x << y << osc::EndMessage << osc::EndBundle;

    transmitSocket.Send(p.Data(), p.Size());
    TimeCheckAfter();
}

void SendOsc::TimeCheckOut2(double time_array2[]) {
    std::ofstream ofs("test2.csv");
    for(int k = 0; k<= COUNTTIME; k++){
        ofs << std::setw(9) << std::setfill('0') << time_array2[k] << std::endl;
    }
}

void SendOsc::TimeCheckAfter() {
    clock_gettime(CLOCK_MONOTONIC, &ta);
    // std::cout << ta.tv_nsec << std::endl;
	// std::cout << ta.tv_sec << " : " << ta.tv_nsec << std::endl;
	if(ta.tv_sec > 0){
         ta.tv_sec = 0;
         ta.tv_nsec = ta.tv_nsec + 999999999 + 1;
     }
	if(counter2 < 100){
         time_array2[counter2] = ta.tv_nsec;
         counter2++;
     }else{
         TimeCheckOut2(time_array2);
         counter2 = 0;
     }
}
}  // namespace oscMessage
