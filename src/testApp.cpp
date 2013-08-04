#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    // カメラの初期位置と方向を決定
    camera.setFov(60);
    camera.setPosition(0, 200, ofGetWidth()/3);
    camera.lookAt(ofVec3f(0, 200, 0));
    // 画面の基本設定
    ofBackground(0, 0, 0);
    ofEnableSmoothing();
    // ムービーを読み込む
    playMovie.loadMovie("rightMovie.mov");
    playMovie.setLoopState(OF_LOOP_NONE);
    playMovie.play();
}

//--------------------------------------------------------------
void testApp::update(){
    playMovie.idleMovie();
}

//--------------------------------------------------------------
void testApp::draw(){
    camera.begin();
    ofBackground(0, 0, 0);
    // 動画を画面に表示
    ofPushMatrix();
    ofRotateZ(180);
    ofTranslate(0, 0, -200);
    playMovie.draw(-1024/2, -520);
    ofPopMatrix();
    // フレーム定義
    Frame frame = controller.frame();
    // Handをあるだけ列挙
    for (int i=0; i<frame.hands().count(); i++) {
        Hand hand = frame.hands()[i];
        // 手のひらの位置に球体を描画
        drawSphere(hand.palmPosition(), 20);
        drawPointLine(hand.palmPosition() + hand.palmNormal()*50, hand.palmPosition(), 4);
        // Hand内のFingerをあるだけ描画
        for (int j=0; j<hand.fingers().count(); j++) {
            Finger finger = hand.fingers()[j];
            drawFinger(finger);
        }
        // 速度,角度(撫で)判定
        handSpeed(hand.palmNormal(), hand.palmVelocity());
    }
    camera.end();
}

void testApp::handSpeed(Vector vector, Vector vectorSpeed) {
    if (vectorSpeed.x > 120) {
        // 撫でる速度判定
        if (playMovie.isPlaying() == 0) {
            // 動画が再生されていなければ実行
            if (vector.x > 0) {
                // 右から撫でる
                playMovie.stop();
                playMovie.loadMovie("leftMovie.mov");
                playMovie.play();
            }
            else {
                // 左から撫でる
                playMovie.stop();
                playMovie.loadMovie("rightMovie.mov");
                playMovie.play();
            }
        }
    }
}

void testApp::drawFinger(Finger finger) {
    // 指先の球体を描画
    ofPoint tip(finger.tipPosition().x, finger.tipPosition().y, finger.tipPosition().z);
    drawSphere(finger.tipPosition(), 8);
    // 指の付け根の計算
    ofPoint base = ofPoint(tip.x + finger.direction().x * finger.length() * -1,
                           tip.y + finger.direction().y * finger.length() * -1,
                           tip.z + finger.direction().z * finger.length() * -1);
    drawPoint(base);
    // 指先から付け根に線を描く
    ofLine(base.x, base.y, base.z, tip.x, tip.y, tip.z);
    // 付け根から拳に線を描く
    ofLine(base.x, base.y, base.z, finger.hand().palmPosition().x, finger.hand().palmPosition().y, finger.hand().palmPosition().z);
}

void testApp::drawSphere(Vector vector, float radius) {
    // 球体の描画処理
    ofNoFill();
    ofPushMatrix();
    ofPoint point = ofPoint(vector.x, vector.y, vector.z);
    ofTranslate(point);
    ofRotateX(point.x);
    ofRotateY(point.y);
    ofRotateZ(point.z);
    ofSetColor(0xCC, 0xCC, 0xCC, 255);
    ofSphere(radius);
    ofPopMatrix();
}

void testApp::drawPoint(ofPoint point) {
    // 点を描画
    ofPushMatrix();
    ofTranslate(point);
    ofNoFill();
    ofSetColor(0xDD, 0xDD, 0xDD, 255);
    ofSphere(3);
    ofPopMatrix();
}

void testApp::drawPointLine(Vector vector, Vector vectorOrigin,float radius) {
    // 点&線の描画処理
    ofNoFill();
    ofPushMatrix();
    ofPoint point = ofPoint(vector.x, vector.y, vector.z);
    ofPoint origin = ofPoint(vectorOrigin.x, vectorOrigin.y, vectorOrigin.z);
    // 線を描画
    ofLine(point.x, point.y, point.z, origin.x, origin.y, origin.z);
    // 点の描画
//    ofTranslate(point);
//    ofRotateX(point.x);
//    ofRotateY(point.y);
//    ofRotateZ(point.z);
//    ofSetColor(0xCC, 255, 0, 0);
//    ofSphere(radius);
//    ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch(key){
        case '0':
            //「0」キーを押すと、ムービーを最初のフレームに巻き戻し
            playMovie.stop();
            playMovie.loadMovie("leftMovie.mov");
            playMovie.play();
            break;
        case '1':
            //「0」キーを押すと、ムービーを最初のフレームに巻き戻し
            playMovie.stop();
            playMovie.loadMovie("rightMovie.mov");
            playMovie.play();
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}