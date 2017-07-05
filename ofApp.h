#pragma once

#include "ofMain.h"
#include "ofxCI.h" //image filters
//#include "ofxHttpUtils.h"
#include "HttpFormManager.h"
#include "ofxLibwebsockets.h"

#define NUM_CAMS 1 //initially tested multiple cams for bullet cam, but wasn't working very well...
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
		
    
        /*
         THE MODES:
         1. idle
         2. adjust_cam
         3. select_frames
         4. countdown
         5. capturing
         6. gif_approve
         7. gif_edit
         8. end_message
        */
        string mode;
        
        /* TIMERS */
        long timeout_timer;
        long end_timer;
        
        /* HACKED TOUCH */
        //might have to use this touch hack if we are using a basic touch display
        void touched(int x, int y);
        ofVec2f touch, touch_prev;
        
        /* CAPTURING */
        int num_frames; //number of frames to be captured
        int frame_latency; //ms between frames captured
        long frame_timer;
        long flash_timer;
        bool captured; //true once something captured
        long countdown_timer;
        int countdown_val;
        int capture_cam; //used in bullet as we go through cams
        int capture_frame; //used in frame capture to count frames
        
        /* CAPTURED */
        int captured_frames;
        int captured_playspeed;
        int captured_playframe;
        long captured_playtimer;
        
        /* PLAYBACK */
        int playback_frame;
        long playback_timer;
        int playback_frame_speed;
        
        /* CAM */
        ofVideoGrabber vidGrabber1; //we just use this to get the device list
        ofVideoGrabber cams [NUM_CAMS];
        ofPixels cams_pixels [NUM_CAMS];
        ofTexture cams_texture [NUM_CAMS];
        
        /* CAPTURED pixels/textures/images */
        vector<ofPixels> captured_pixels;
        vector<ofTexture> captured_texture;
        vector<ofImage> captured_image;
        
        /* CAPTION */
        ofRectangle bb_caption;
        ofTrueTypeFont caption;
        
        /* IMAGE FILTERS */
        ofxCIFilter fx_CHROME;
        ofxCIFilter fx_FADE;
        ofxCIFilter fx_INSTANT;
        ofxCIFilter fx_MONO;
        ofxCIFilter fx_NOIR;
        ofxCIFilter fx_PROCESS;
        ofxCIFilter fx_TONAL;
        ofxCIFilter fx_TRANSFER;
        ofxCIFilter filter_arr [8];
        int filter_sel_num;
        ofImage fx_demo1,fx_demo2,fx_demo3,fx_demo4,fx_demo5,fx_demo6,fx_demo7,fx_demo8;
        ofRectangle menu7_filter_sel;
        
        /* HTTP POST images */
        //        void newResponse(ofxHttpResponse & response);
        //        ofxHttpUtils httpUtils;
        //        string post_url, http_response;    
        void newResponse(HttpFormResponse &response);
        HttpFormManager fm;
    
        /* WEBSOCKETS */
        ofxLibwebsockets::Client client;
        // websocket methods
        void onConnect( ofxLibwebsockets::Event& args );
        void onOpen( ofxLibwebsockets::Event& args );
        void onClose( ofxLibwebsockets::Event& args );
        void onIdle( ofxLibwebsockets::Event& args );
        void onMessage( ofxLibwebsockets::Event& args );
        void onBroadcast( ofxLibwebsockets::Event& args );
    
    
    
    
    
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /* Make my own click-boxes with centered text */

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
                if(font_col.r==255&&font_col.g==255&&font_col.b==255){ //we have white font so lets add a dropshadow
                    ofSetColor(0,0,0,font_col.a);
                    fontmain.drawString(text, box.x+(box.width*0.5)-(bb_text.width*0.5)-2, box.y+(box.height*0.5)+(bb_text.height*0.5)+2);
                }
                ofSetColor(font_col);
                fontmain.drawString(text, box.x+(box.width*0.5)-(bb_text.width*0.5), box.y+(box.height*0.5)+(bb_text.height*0.5));
            };
            bool inside(int xi, int yi){
                if( (xi>box.x && xi<(box.x+box.width)) && (yi>box.y && yi<(box.y+box.height)) ){
                    return true;
                }else{
                    return false;
                }
            };
        };
        ClickTextBox menu2_adjust;
        ClickTextBox menu2_ready;
        ClickTextBox menu3_4frames,menu3_8frames,menu3_12frames;
        ClickTextBox menu3_selframes;
        ClickTextBox menu4_countdown;
        ClickTextBox menu5_retry;
        ClickTextBox menu5_finish;
        ClickTextBox menu6_thanks;
        ClickTextBox menu6_endmsg;
        ClickTextBox menu7_filter;
        ClickTextBox menu7_fx1,menu7_fx2,menu7_fx3,menu7_fx4,menu7_fx5,menu7_fx6,menu7_fx7,menu7_fx8;
        ClickTextBox menu7_retry;
        ClickTextBox menu7_finish;
    
    
    
    
    
    
    
    
    
    
    
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /* Made my own touch Keyboard */
    
        struct Keyboard{
            
            string caption = "ADD A MESSAGE OR YOUR NAME!";
            string captured_caption;
            int caption_x;
            ofTrueTypeFont fontmain,fontcaption;
            int width;
            int y_pos;
            int key_width,key_space;
            
            //key_box and chars MUST be same size = 50
            
            ofRectangle key_box[50];
            ofRectangle black_box[50];
            ofRectangle space_box,space_black,del_box,del_black;
            string chars[50];
            
            ofRectangle bb_text;
            void init(string font, int font_size, int w, int y){
                string use_chars[50] = {"!","@","#","$","%","-","&",":",";","'","1","2","3","4","5","6","7","8","9","0","Q","W","E","R","T","Y","U","I","O","P","A","S","D","F","G","H","J","K","L","\"","Z","X","C","V","B","N","M",",",".","?"};
                for(int i=0;i<50;i++){
                    chars[i] = use_chars[i];
                }
                fontmain.load(font, font_size);
                fontcaption.load(font, font_size*1.18);
                width = w;
                y_pos = y;
                key_width = width/11;
                key_space = key_width/11;
            };
            void draw(){
                int row = 0;
                int col = 0;
                
                //most of this is just positioning/layout/centering junk
                
                for(int i=0;i<50;i++){
                    
                    if(i%10==0 && i!=0){row++;col=0;}
                    
                    //set box position
                    key_box[i].set((key_space*(col+1))+(key_width*col)+5,y_pos+(row*(key_space+(key_width*0.8))),key_width,key_width*0.8);
                    black_box[i].set((key_space*(col+1))+(key_width*col)+5+3,y_pos+(row*(key_space+(key_width*0.8)))+3,key_width-6,(key_width*0.8)-6);
                    col++;
                    
                    //draw box with white stroke
                    ofSetColor(255,255,255); ofDrawRectangle(key_box[i]);
                    ofSetColor(0,0,0); ofDrawRectangle(black_box[i]);
                    
                    //draw text
                    bb_text = fontmain.getStringBoundingBox(chars[i],0,0);
                    ofSetColor(255,255,255);
                    fontmain.drawString(chars[i], key_box[i].x+(key_box[i].width*0.5)-(bb_text.width*0.5), key_box[i].y+(key_box[i].height*0.45)+(bb_text.height*0.5));
                }
                
                //draw spacebar
                space_box.set(key_space+4, y_pos+(key_space*5)+((key_width*0.8)*5), (width*.6)-(key_space*2), (key_width*0.8));
                space_black.set(key_space+3+4, y_pos+(key_space*5)+((key_width*0.8)*5)+3, (width*.6)-(key_space*2)-6, (key_width*0.8)-6);
                ofSetColor(255,255,255);ofDrawRectangle(space_box);
                ofSetColor(0,0,0);ofDrawRectangle(space_black);
                bb_text = fontmain.getStringBoundingBox("SPACE",0,0);
                ofSetColor(255,255,255);
                fontmain.drawString("SPACE", space_box.x+(space_box.width*0.5)-(bb_text.width*0.5), space_box.y+(space_box.height*0.45)+(bb_text.height*0.5));
                
                //draw delete
                del_box.set((width*.6)+key_space-4, y_pos+(key_space*5)+((key_width*0.8)*5), (width*.397)-(key_space*2), (key_width*0.8));
                del_black.set((width*.6)+key_space+3-4, y_pos+(key_space*5)+((key_width*0.8)*5)+3, (width*.397)-(key_space*2)-6, (key_width*0.8)-6);
                ofSetColor(255,255,255);ofDrawRectangle(del_box);
                ofSetColor(0,0,0);ofDrawRectangle(del_black);
                bb_text = fontmain.getStringBoundingBox("DELETE",0,0);
                ofSetColor(255,255,255);
                fontmain.drawString("DELETE", del_box.x+(del_box.width*0.5)-(bb_text.width*0.5), del_box.y+(del_box.height*0.45)+(bb_text.height*0.5));
                
                //draw caption
                ofSetColor(255,255,255);
                bb_text = fontcaption.getStringBoundingBox(caption,0,0);
                caption_x = int((width - bb_text.width)/2.0);
                fontcaption.drawString(caption, caption_x, y_pos-30);
                
            };
            void create_caption(int x,int y){
                
                string returned_char = "^";
                for(int i=0;i<50;i++){
                    if(key_box[i].inside(x,y)){
                        returned_char = chars[i];
                        break;
                    }
                }
                if(space_box.inside(x,y)){ returned_char = " "; }
                if(returned_char!="^"){
                    if(caption=="ADD A MESSAGE OR YOUR NAME!"){caption="";}
                    caption += returned_char;
                }
                if(del_box.inside(x,y)){
                    if(caption=="ADD A MESSAGE OR YOUR NAME!"){caption="";}
                    caption = caption.substr(0, caption.size()-1);
                }
                
            };

        };
        Keyboard myKeyboard;
    
    
    
    
    
    
    
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        /* made my own screen saver bouncy message */
    
        struct screen_saver_message{
            ofTrueTypeFont fontmain,fontmain2;
            ofRectangle bb,temp_bb;
            ofTrueTypeFont temp_text;
            string temp_string, new_string;
            int x,y,vx,vy;
            int max_width;
            bool flag_break;
            string msg,who;
            void init(string font, int font_size, string _msg, string _who){
                
                fontmain.load(font, font_size); //font size of message
                fontmain.setLineHeight((int)(font_size*1.5));
                
                fontmain2.load(font, (int)(font_size*0.6)); //font size of name
                
                temp_text.load(font, font_size);
                
                who = _who;
                
                x = (int)(ofRandom(0.1,0.5)*DISPLAY_WIDTH);
                y = (int)(ofRandom(0.1,0.6)*DISPLAY_HEIGHT);
                ofVec2f pos(x,y);
                if(ofRandom(0,1)<0.5){vx = 2;}else{vx = -2;}
                if(ofRandom(0,1)<0.5){vy = 2;}else{vy = -2;}
                
                //we need to add line breaks manually 'cause c++ hates god
                max_width = 350;
                flag_break = false;
                temp_string = "";
                new_string = "";
                for (int i = 0; i <_msg.size(); i++){
                    temp_string += _msg[i];
                    temp_bb = temp_text.getStringBoundingBox(temp_string, 0, 0);
                    if(temp_bb.width>max_width){
                        flag_break = true;
                    }
                    if(flag_break==true && _msg[i]==' '){
                        new_string += temp_string+"\n";
                        temp_string = "";
                        flag_break = false;
                    }
                }
                new_string += temp_string;
                
                msg = new_string;
                
                cout << msg << endl;
                cout << "~~~" << endl;
                

            }
            void draw(){
                ofSetColor(0,0,0,150);
                fontmain.drawString(msg, x-1, y+1);
                fontmain2.drawString("~"+who, x-1, y+bb.height+5+1);
                ofSetColor(255,255,255);
                fontmain.drawString(msg, x, y);
                fontmain2.drawString("~"+who, x, y+bb.height+5);
                
            }
            void update(){
                
                x += vx;
                y += vy;
                
                bb = fontmain.getStringBoundingBox(msg, 0, 0);
                
                if(x<=0){
                    vx *= -1;
                }
                if(y<=0){
                    vy *= -1;
                }
                if(x+bb.width>=DISPLAY_WIDTH){
                    vx *= -1;
                }
                if(y+bb.height+5>=DISPLAY_HEIGHT){
                    vy *= -1;
                }
                
            }
        };
        screen_saver_message msgs [100]; //for some reasong when i tried a vector it threw a bizarre ofTrueTypeFont error
        int message_count;
        int message_display_duration;
        long message_display_timer;
    

    
    
    

};
