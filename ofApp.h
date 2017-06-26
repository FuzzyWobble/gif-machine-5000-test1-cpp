#pragma once

#include "ofMain.h"

#define NUM_CAMS 3
#define CAM_WIDTH 1280
#define CAM_HEIGHT 720
#define DISPLAY_HEIGHT 1920
#define DISPLAY_WIDTH 1080





class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    
        // my ClickTextBox hack class
        // allows you to easily define specific font, draw centered text, and detect click inside
        struct ClickTextBox{ //box with text in center
            ofTrueTypeFont fontmain;
            ofRectangle box;
            //int x,y,w,h;
            string text;
            ofColor bg_col,font_col;
            ofRectangle bb_text;
            void draw(){
                ofSetColor(bg_col);
                ofDrawRectangle(box);
                bb_text = fontmain.getStringBoundingBox(text,0,0);
                ofSetColor(font_col);
                fontmain.drawString(text, box.x+(box.width*0.5)-(bb_text.width*0.5), box.y+(box.height*0.5)+(bb_text.height*0.5));
            };
            bool inside(int xi, int yi){
                if( (xi>box.x && xi<(box.x+box.width)) && (yi>box.y && yi<(box.y+box.height)) ){
                    return true;
                }else{
                    return false;
                }
            }
        };
        ClickTextBox menu1_bullet;
        ClickTextBox menu1_frame;
        ClickTextBox menu2_adjust;
        ClickTextBox menu2_ready;
        ClickTextBox menu3_4frames,menu3_8frames,menu3_12frames;
        ClickTextBox menu3_selframes;
        ClickTextBox menu4_countdown;
        ClickTextBox menu5_filter1,menu5_filter2,menu5_filter3,menu5_filter4;
        ClickTextBox menu5_retry;
        ClickTextBox menu5_finish;
        ClickTextBox menu6_thanks;
        ClickTextBox menu6_endmsg;
    
        string mode;
        /*
        idle
        select_gifmode
        adjust_cam
        select_frames
        countdown
        capturing
        playback_edit
        end_message
        */
    
        string gif_type; //gif type, 'bullet' or 'frame'
    
        int num_frames; //number of frames to be captured
    
        long timeout_timer;
    
        long countdown_timer;
        int countdown_val;
    
        long end_timer;
    
        //might have to use this touch hack if we are using a basic touch display
        void touched(int x, int y);
        ofVec2f touch, touch_prev;

        ofVideoGrabber vidGrabber1; //we just use this to get the device list
    
        int bullet_latency,frame_latency;
        long bullet_timer,frame_timer;
        bool captured;
        bool capturing;
        int capture_cam; //used in bullet as we go through cams
        int capture_frame; //used in frame capture to count frames
    
        //during idle we need to know how many frames were captured as well as a playback speed
        int captured_frames;
        int captured_playspeed;
        int captured_playframe;
        long captured_playtimer;
    
        long flash_timer;
    
        bool playback_direction;
        int playback_frame;
        long playback_timer;
        int playback_frame_speed;
        int playback_horizontal_offset;
        int playback_vertical_offset;
        int playback_width;
        int playback_height;
        
        ofVideoGrabber cams [NUM_CAMS];
        ofPixels cams_pixels [NUM_CAMS];
        ofTexture cams_texture [NUM_CAMS];
        
        vector<ofPixels> captured_pixels;
        vector<ofTexture> captured_texture;
        vector<ofImage> captured_image;
    
    
    
};
