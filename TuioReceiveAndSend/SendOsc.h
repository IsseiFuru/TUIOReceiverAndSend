/**
 * @file SendOsc.h
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

#ifndef INCLUDED_SENDOSC_H
#define INCLUDED_SENDOSC_H

#include "ReceiveTuio.h"
#include "oscpack/ip/UdpSocket.h"
#include "oscpack/osc/OscOutboundPacketStream.h"
#include "oscpack/osc/OscPacketListener.h"

namespace oscMessage {

/// @brief 加工されたメッセージをOSCメッセージで送信するクラス
class SendOsc : public osc::OscPacketListener {
   public:
    /// @brief OSCメッセージを送信する（xとyの座標を扱わない）
    /// @param state 状態
    /// @param SessionID セッションID
    static void SendMessage(const char* state, int SessionID);

    /// @brief OSCメッセージを送信する（xとyの座標を扱う）
    /// @param state 状態
    /// @param SessionID セッションID
    /// @param x X座標
    /// @param y Y座標
    static void SendMessageWithPosition(const char* state, int SessionID,
                                        float x, float y);
};

}  // namespace oscMessage

#endif /* INCLUDED_SENDOSC_H */
