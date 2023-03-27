/**
 * @file ReceiveTuio.h
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

#ifndef INCLUDED_RECEIVETUIO_H
#define INCLUDED_RECEIVETUIO_H

#include <math.h>

#include "SendOsc.h"
#include "TUIO/TcpReceiver.h"
#include "TUIO/TuioClient.h"
#include "TUIO/TuioListener.h"
#include "TUIO/UdpReceiver.h"

using namespace TUIO;

/// @brief TUIOメッセージの受信クラス
class ReceiveTuio : public TuioListener
{
public:
    void addTuioObject(TuioObject *tobj);
    void updateTuioObject(TuioObject *tobj);
    void removeTuioObject(TuioObject *tobj);

    /// @brief カーソルが追加された時に読み込まれる
    /// @param tcur カーソルの情報
    void addTuioCursor(TuioCursor *tcur);

    /// @brief カーソルが移動させた時に読み込まれる
    /// @param tcur カーソルの情報
    void updateTuioCursor(TuioCursor *tcur);

    /// @brief カーソルから離れた時に読み込まれる
    /// @param tcur カーソルの情報
    void removeTuioCursor(TuioCursor *tcur);

    void addTuioBlob(TuioBlob *tblb);
    void updateTuioBlob(TuioBlob *tblb);
    void removeTuioBlob(TuioBlob *tblb);

    void refresh(TuioTime frameTime);
};

#endif /* INCLUDED_RECEIVETUIO_H */
