/**
 * @file SendOsc.cpp
 * @author Issei Furutani
 * このプログラムは加工されたTUIOのメッセージをOSCのメッセージとして、送信するプログラムです。
 * 送られるOSCのメッセージは以下の内容である。
 * /fillter/tuio add SessionID X Y
 * /fillter/tuio update SessionID X Y
 * /fillter/tuio remove SessionID X Y
 * @version 1.0
 * @date 2022-11-08
 */

#include "SendOsc.h"

#include "ReceiveTuio.h"

// 送信先のIPアドレスとポート番号
const char *send_to_address = "127.0.0.1";
const int send_to_port = 50000;
static int output_buffer_size = 1024;

namespace oscMessage
{

  void SendOsc::SendMessage(const char *state, int SessionID)
  {
    UdpTransmitSocket transmitSocket(
        IpEndpointName(send_to_address, send_to_port));

    char buffer[output_buffer_size];
    osc::OutboundPacketStream p(buffer, output_buffer_size);

    p << osc::BeginBundleImmediate << osc::BeginMessage("/fillter/tuio")
      << state << SessionID << osc::EndMessage << osc::EndBundle;

    transmitSocket.Send(p.Data(), p.Size());
  }

  void SendOsc::SendMessageWithPosition(const char *state, int SessionID, float x,
                                        float y)
  {
    UdpTransmitSocket transmitSocket(
        IpEndpointName(send_to_address, send_to_port));

    char buffer[output_buffer_size];
    osc::OutboundPacketStream p(buffer, output_buffer_size);

    p << osc::BeginBundleImmediate << osc::BeginMessage("/fillter/tuio")
      << state << SessionID << x << y << osc::EndMessage << osc::EndBundle;

    transmitSocket.Send(p.Data(), p.Size());
  }

} // namespace oscMessage
