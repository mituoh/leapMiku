#pragma once

#include "ofMain.h"
#include "Leap.h"

// LeapMotionの名前空間
using namespace Leap;

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        // LeapMotionのコントローラ
        Controller controller;
        // カメラ
        ofCamera camera;
        // 球体の描画処理
        void drawSphere(Leap::Vector vector, float radius);
        // 球体と線の描画処理
        void drawPointLine(Leap::Vector vector, Leap::Vector originVector, float radius);
        // 点の描画処理
        void drawPoint(ofPoint point);
        // 指の描画処理
        void drawFinger(Finger finger);
        // 速度,角度判定
        void handSpeed(Leap::Vector vector, Leap::Vector vectorSpeed);
        // 動画の再生
        ofVideoPlayer playMovie;
};
