#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //global ofx stuffs
    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    
    mode = "idle";

    //we can now get back a list of devices.
    vector<ofVideoDevice> devices = vidGrabber1.listDevices();
    cout << "You have " << devices.size() << "cams connected" << endl;
    
    cams[0].setDeviceID(0);
    cams[0].initGrabber(CAM_WIDTH,CAM_HEIGHT);
    
//    menu1_bullet.fontmain.load("KGHAPPY.ttf", 80);
//    menu1_bullet.box.set(0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT*0.5);
//    menu1_bullet.text = "Bullet Cam";
//    menu1_bullet.bg_col.set(0,0,0);
//    menu1_bullet.font_col.set(255,255,255);
    
    menu1_frame.fontmain.load("KGHAPPY.ttf",70);
    menu1_frame.box.set(0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT);
    menu1_frame.text = "Let's Make A GIF";
    menu1_frame.bg_col.set(0,0,0);
    menu1_frame.font_col.set(255,255,255);

    menu2_adjust.fontmain.load("KGHAPPY.ttf", 50);
    menu2_adjust.box.set(0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT*0.07);
    menu2_adjust.text = "Adjust The Cam";
    menu2_adjust.bg_col.set(0,0,0,0);
    menu2_adjust.font_col.set(255,255,255);
    menu2_ready.fontmain.load("KGHAPPY.ttf", 80);
    menu2_ready.box.set(0,DISPLAY_HEIGHT*0.8,DISPLAY_WIDTH,DISPLAY_HEIGHT*0.2);
    menu2_ready.text = "Okay Let's GIF";
    menu2_ready.bg_col.set(0,0,0,0);
    menu2_ready.font_col.set(255,255,255);
    
    menu3_selframes.fontmain.load("KGHAPPY.ttf", 50);
    menu3_selframes.box.set(0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT*0.1);
    menu3_selframes.text = "How Many GIF Frames?";
    menu3_selframes.bg_col.set(255,255,255);
    menu3_selframes.font_col.set(0,0,0);
    menu3_4frames.fontmain.load("KGHAPPY.ttf", 130);
    menu3_4frames.box.set(0,DISPLAY_HEIGHT*0.1,DISPLAY_WIDTH,DISPLAY_HEIGHT*0.3);
    menu3_4frames.text = "4";
    menu3_4frames.bg_col.set(0,0,0);
    menu3_4frames.font_col.set(255,255,255);
    menu3_8frames.fontmain.load("KGHAPPY.ttf", 130);
    menu3_8frames.box.set(0,DISPLAY_HEIGHT*0.4,DISPLAY_WIDTH,DISPLAY_HEIGHT*0.3);
    menu3_8frames.text = "8";
    menu3_8frames.bg_col.set(0,0,0);
    menu3_8frames.font_col.set(255,255,255);
    menu3_12frames.fontmain.load("KGHAPPY.ttf", 130);
    menu3_12frames.box.set(0,DISPLAY_HEIGHT*0.7,DISPLAY_WIDTH,DISPLAY_HEIGHT*0.3);
    menu3_12frames.text = "12";
    menu3_12frames.bg_col.set(0,0,0);
    menu3_12frames.font_col.set(255,255,255);

    menu4_countdown.fontmain.load("KGHAPPY.ttf", 260);
    menu4_countdown.box.set(0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT);
    menu4_countdown.text = "3";
    menu4_countdown.bg_col.set(255,255,255);
    menu4_countdown.font_col.set(0,0,0);

    menu5_retry.fontmain.load("KGHAPPY.ttf", 50);
    menu5_retry.box.set(0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT*.07);
    menu5_retry.text = "Gimme A Retry";
    menu5_retry.bg_col.set(0,0,0,0);
    menu5_retry.font_col.set(255,255,255);
    menu5_finish.fontmain.load("KGHAPPY.ttf", 100);
    menu5_finish.box.set(0,DISPLAY_HEIGHT*.70,DISPLAY_WIDTH,DISPLAY_HEIGHT*.2);
    menu5_finish.text = "Create GIF";
    menu5_finish.bg_col.set(0,0,0,0);
    menu5_finish.font_col.set(255,255,255);
    
    menu5_fx1.box.set(15,DISPLAY_HEIGHT*.883,118,210);
    menu5_fx1.bg_col.set(0,0,0);
    menu5_fx2.box.set(148,DISPLAY_HEIGHT*.883,118,210);
    menu5_fx2.bg_col.set(0,0,0);
    menu5_fx3.box.set(281,DISPLAY_HEIGHT*.883,118,210);
    menu5_fx3.bg_col.set(0,0,0);
    menu5_fx4.box.set(414,DISPLAY_HEIGHT*.883,118,210);
    menu5_fx4.bg_col.set(0,0,0);
    menu5_fx5.box.set(547,DISPLAY_HEIGHT*.883,118,210);
    menu5_fx5.bg_col.set(0,0,0);
    menu5_fx6.box.set(680,DISPLAY_HEIGHT*.883,118,210);
    menu5_fx6.bg_col.set(0,0,0);
    menu5_fx7.box.set(813,DISPLAY_HEIGHT*.883,118,210);
    menu5_fx7.bg_col.set(0,0,0);
    menu5_fx8.box.set(946,DISPLAY_HEIGHT*.883,118,210);
    menu5_fx8.bg_col.set(0,0,0);
    
    menu6_thanks.fontmain.load("KGHAPPY.ttf", 90);
    menu6_thanks.box.set(0,DISPLAY_HEIGHT*.4,DISPLAY_WIDTH,DISPLAY_HEIGHT*.2);
    menu6_thanks.text = "Awesome";
    menu6_thanks.bg_col.set(0,0,0);
    menu6_thanks.font_col.set(255,255,255);
    menu6_endmsg.fontmain.load("KGHAPPY.ttf", 20);
    menu6_endmsg.box.set(0,DISPLAY_HEIGHT*.5,DISPLAY_WIDTH,DISPLAY_HEIGHT*.1);
    menu6_endmsg.text = "Something Something Something Something";
    menu6_endmsg.bg_col.set(0,0,0,0);
    menu6_endmsg.font_col.set(255,255,255);
    
    myKeyboard.init("KGHAPPY.ttf", 35, DISPLAY_WIDTH, 300);
    
    //touch_prev.set(0,0);
    
    captured = false;
    capturing = false;
    capture_cam = 0;
    
    frame_latency = 200;
    
    countdown_val = 4;
    
    playback_direction = true;
    playback_frame = 0;
    playback_timer = 0;
    playback_frame_speed = 160;
    playback_horizontal_offset = 35;
    playback_width = CAM_HEIGHT - (2*playback_horizontal_offset); //we rotate 90 so we use CAM_HEIGHT as width
    playback_height = (int)(playback_width*1.666); //1x1.666 ratio
    playback_vertical_offset = (int)((CAM_WIDTH - playback_height)*0.5);
    
    fx_CHROME.setup(OFX_FILTER_TYPE_PHOTO_EFFECT_CHROME);
    fx_FADE.setup(OFX_FILTER_TYPE_PHOTO_EFFECT_FADE);
    fx_INSTANT.setup(OFX_FILTER_TYPE_PHOTO_EFFECT_INSTANT);
    fx_MONO.setup(OFX_FILTER_TYPE_PHOTO_EFFECT_MONO);
    fx_NOIR.setup(OFX_FILTER_TYPE_PHOTO_EFFECT_NOIR);
    fx_PROCESS.setup(OFX_FILTER_TYPE_PHOTO_EFFECT_PROCESS);
    fx_TONAL.setup(OFX_FILTER_TYPE_PHOTO_EFFECT_TONAL);
    fx_TRANSFER.setup(OFX_FILTER_TYPE_PHOTO_EFFECT_TRANSFER);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofBackground(0,0,0);

    if(mode=="idle"){
        
        if(captured==true){ //we play last gif created
            if(ofGetElapsedTimeMillis() - captured_playtimer > captured_playspeed){
                captured_playframe++;
                captured_playtimer = ofGetElapsedTimeMillis();
                if(captured_playframe>=captured_frames){
                    captured_playframe = 0;
                }
            }
        }
        
    }else if(mode=="select_gifmode"){ //menu1
        
        //nothing
        
    }else if(mode=="adjust_cam"){ //menu2
        
        cams[0].update();
        cams_pixels[0] = cams[0].getPixels();
        //cams_pixels[1].rotate90(1); //too expensive, leads to latency
        cams_texture[0].loadData(cams_pixels[0]);
        
    }else if(mode=="select_frames"){ //menu3
        
        //nothing
        
    }else if(mode=="countdown"){ //menu4
        
        if(ofGetElapsedTimeMillis()-countdown_timer > 1000){
            countdown_val--;
            countdown_timer = ofGetElapsedTimeMillis();
            if(countdown_val<=0){
                mode = "capturing";
            }
        }
        
    }else if(mode=="capturing"){ //NOMENU

        if(ofGetElapsedTimeMillis()-frame_timer > frame_latency){
            
            cams[0].update();
            cams_pixels[0] = cams[0].getPixels();
            cams_pixels[0].rotate90(1);
            cams_texture[0].loadData(cams_pixels[0]);
            
            captured_pixels.push_back(cams[0].getPixels()); //always capturing from middle cam: 1
            captured_pixels[captured_pixels.size()-1].rotate90(1);
            ofTexture t;
            captured_texture.push_back(t);
            captured_texture[captured_texture.size()-1].loadData(captured_pixels[captured_pixels.size()-1]);
            //should we  or destroy variable t? leak over time?
            
            
            if(captured_pixels.size()==1){ //just create fx preview with first image
                ofImage img; //memory issues?
                img.setFromPixels(captured_pixels[0]);
                fx_CHROME.setInputImage(img); //apply fx to img
                fx_CHROME.getOutput(fx_demo1); //get output img with fx
                fx_FADE.setInputImage(img); //apply fx to img
                fx_FADE.getOutput(fx_demo2); //get output img with fx
                fx_INSTANT.setInputImage(img); //apply fx to img
                fx_INSTANT.getOutput(fx_demo3); //get output img with fx
                fx_MONO.setInputImage(img); //apply fx to img
                fx_MONO.getOutput(fx_demo4); //get output img with fx
                fx_NOIR.setInputImage(img); //apply fx to img
                fx_NOIR.getOutput(fx_demo5); //get output img with fx
                fx_PROCESS.setInputImage(img); //apply fx to img
                fx_PROCESS.getOutput(fx_demo6); //get output img with fx
                fx_TONAL.setInputImage(img); //apply fx to img
                fx_TONAL.getOutput(fx_demo7); //get output img with fx
                fx_TRANSFER.setInputImage(img); //apply fx to img
                fx_TRANSFER.getOutput(fx_demo8); //get output img with fx
            }
            
            
            frame_timer = ofGetElapsedTimeMillis();
            capture_frame++;
            if(capture_frame==num_frames){
                captured = true;
                mode="playback_edit";
            }else{
                flash_timer = ofGetElapsedTimeMillis();
            }
            
        }
        
    }else if(mode=="playback_edit"){ //menu5

        if(captured==true){
            
            if(ofGetElapsedTimeMillis()-playback_timer > playback_frame_speed){
                
                playback_frame++;
                if(playback_frame>=num_frames){
                    playback_frame = 0;
                }
                
                playback_timer = ofGetElapsedTimeMillis();
                
            }
            
        }
        
    }else if(mode=="end_message"){ //menu6
        
        if(ofGetElapsedTimeMillis()-end_timer > 5000){
            mode = "idle";
        }
        
    }else{
        
        cout << "uhoh" << endl;
        
    }

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofSetColor(255,255,255);
    

    if(mode=="idle"){
        
        if(captured==true){
            captured_image[captured_playframe].draw(0,0,1080,1920);
        }
        
        myKeyboard.draw();

    }else if(mode=="select_gifmode"){ //menu1
        
        menu1_bullet.draw();
        menu1_frame.draw();
        
    }else if(mode=="adjust_cam"){ //menu2
        
        //rotate texture on GPU
        cams_texture[0].setAnchorPercent(0.5, 0.5);
        ofPushMatrix();
        ofTranslate(DISPLAY_WIDTH*0.5, DISPLAY_HEIGHT*0.5);
        ofScale(-1, 1);
        ofRotateZ(90);
        cams_texture[0].draw(0,0,1920,1080);
        ofPopMatrix();
        
        menu2_adjust.box.setY(sin(ofGetElapsedTimeMillis()*0.002)*20.0);
        menu2_adjust.draw(); //modulate y?
        
        menu2_ready.font_col.set(255,255,255, (abs(sin(ofGetElapsedTimeMillis()*0.003))*200.0)+55.0 );
        menu2_ready.draw();
        

    }else if(mode=="select_frames"){ //menu3

        menu3_selframes.draw();
        
        menu3_4frames.draw();
        menu3_8frames.draw();
        menu3_12frames.draw();
        
        
    }else if(mode=="countdown"){ //menu4
        
        menu4_countdown.text = ofToString(countdown_val);
        menu4_countdown.draw();
        
    }else if(mode=="capturing"){
        
        if(ofGetElapsedTimeMillis() - flash_timer < 100){
            ofSetColor(255, 255, 255);
        }else{
            ofSetColor(0, 0, 0);
        }
        ofDrawRectangle(0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT);

        
    }else if(mode=="playback_edit"){ //menu5
        
        if(captured==true){

//                captured_texture[playback_frame].drawSubsection((DISPLAY_WIDTH-playback_width)*0.5, ((DISPLAY_HEIGHT-playback_height)*0.5), playback_width, playback_height, playback_horizontal_offset*1, playback_vertical_offset, playback_width, playback_height);
            
            captured_texture[playback_frame].draw(0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT);

        }
        
        menu5_retry.box.setX(sin(ofGetElapsedTimeMillis()*0.002)*30.0);
        menu5_retry.draw();
        
        menu5_finish.font_col.set(255,255,255, (abs(sin(ofGetElapsedTimeMillis()*0.003))*200.0)+55.0 );
        menu5_finish.draw();
        
        menu5_fx1.draw(); fx_demo1.draw(15,DISPLAY_HEIGHT*.883,118,210);
        menu5_fx2.draw(); fx_demo2.draw(148,DISPLAY_HEIGHT*.883,118,210);
        menu5_fx3.draw(); fx_demo3.draw(281,DISPLAY_HEIGHT*.883,118,210);
        menu5_fx4.draw(); fx_demo4.draw(414,DISPLAY_HEIGHT*.883,118,210);
        menu5_fx5.draw(); fx_demo5.draw(547,DISPLAY_HEIGHT*.883,118,210);
        menu5_fx6.draw(); fx_demo6.draw(680,DISPLAY_HEIGHT*.883,118,210);
        menu5_fx7.draw(); fx_demo7.draw(813,DISPLAY_HEIGHT*.883,118,210);
        menu5_fx8.draw(); fx_demo8.draw(946,DISPLAY_HEIGHT*.883,118,210);
        

    }else if(mode=="end_message"){ //menu6
        
        menu6_thanks.font_col.set(255,255,255, (abs(sin(ofGetElapsedTimeMillis()*0.003))*200.0)+55.0 );
        menu6_thanks.draw();
        
        menu6_endmsg.draw();
        
    }else{
        
        cout << "uhoh no mode" << endl;
        
    }
    
    
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 's' || key == 'S'){
        vidGrabber1.videoSettings();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::touched(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    touch.set(x,y);
    if(touch.distance(touch_prev)>20){
        touched(x,y);
        touch_prev.set(x,y);
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    myKeyboard.create_caption(x,y);
    
    timeout_timer = ofGetElapsedTimeMillis();
    
    if(mode=="idle"){
        //mode = "select_gifmode";
    }else if(mode=="select_gifmode"){
        if(menu1_bullet.inside(x, y)){
            gif_type = "bullet";
            mode = "adjust_cam";
            num_frames = 3;
            cout << "touched bullet" << endl;
        }
        if(menu1_frame.inside(x, y)){
            gif_type = "frame";
            mode = "adjust_cam";
            cout << "touched frame" << endl;
        }
    }else if(mode=="adjust_cam"){
        if(menu2_ready.inside(x, y)){
            if(gif_type=="frame"){
                mode = "select_frames";
            }
            if(gif_type=="bullet"){
                mode = "countdown";
            }
        }
    }else if(mode=="select_frames"){
        if(menu3_4frames.inside(x, y)){
            num_frames = 4;
            frame_latency = 500;
            mode = "countdown";
        }
        if(menu3_8frames.inside(x, y)){
            num_frames = 8;
            frame_latency = 400;
            mode = "countdown";
        }
        if(menu3_12frames.inside(x, y)){
            num_frames = 12;
            frame_latency = 300;
            mode = "countdown";
        }
    }else if(mode=="playback_edit"){
        if(y<50){
            //playback_horizontal_offset = int(((float)x/(float)DISPLAY_WIDTH)*120.0);
            //cout << "horizontal offeset, " << playback_horizontal_offset << endl;
        }
        if(menu5_fx1.inside(x, y)){
            
        }
        if(menu5_fx2.inside(x, y)){
            
        }
        if(menu5_fx3.inside(x, y)){
            
        }
        if(menu5_fx4.inside(x, y)){
            
        }
        if(menu5_fx5.inside(x, y)){
            
        }
        if(menu5_fx6.inside(x, y)){
            
        }
        if(menu5_fx7.inside(x, y)){
            
        }
        if(menu5_fx8.inside(x, y)){
            
        }
        if(menu5_finish.inside(x, y)){ //click finish
            
            mode = "end_message";
            end_timer = ofGetElapsedTimeMillis();
            
            captured_image.clear();
            //create the images from the pixels
            for(int i=0;i<num_frames;i++){ //if bullet, num_frames=3
                
                ofImage img; //memory issues?
                
                img.setFromPixels(captured_pixels[i]);
                
                fx_CHROME.setInputImage(img); //apply fx to img

                fx_CHROME.getOutput(img); //get output img with fx
                
                img.save(ofToString(i)+".png",OF_IMAGE_QUALITY_BEST);
                
                captured_image.push_back(img);
                
                cout << "pushed, " << i << endl;
            }
            
            captured_frames = num_frames;
            captured = true;
            captured_playspeed = 120;
            captured_playframe = 0;
            
            captured_pixels.clear();
            captured_texture.clear();
            capture_cam = 0;
            countdown_val = 4;
            capture_frame = 0;
            
        }
        if(menu5_retry.inside(x, y)){ //click retry
            
            mode = "countdown";
            captured_pixels.clear();
            captured_texture.clear();
            capture_cam = 0;
            countdown_val = 4;
            capture_frame = 0;
            
        }
    }
    

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
