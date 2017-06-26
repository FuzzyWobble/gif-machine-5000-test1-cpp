#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //global ofx stuffs
    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    
    mode = "idle";

    //we can now get back a list of devices.
    vector<ofVideoDevice> devices = vidGrabber1.listDevices(); //sometimes gives wrong number...
    cout << devices.size() << endl;
    if(devices.size()<NUM_CAMS){
        cout << "ERROR, NOT ALL CAMS DETECTED! EXITING!" << endl;
        ofExit();
    }
    for(int i = 0; i < devices.size(); i++){
        if(devices[i].bAvailable){
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }else{
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
        cams[i].setDeviceID(i);
        cams[i].initGrabber(CAM_WIDTH,CAM_HEIGHT);
        
        //should we allocate pixels and textures?
    }
    
    menu1_bullet.fontmain.load("bambi.ttf", 80);
    menu1_bullet.box.set(0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT*0.5);
    menu1_bullet.text = "Bullet Cam";
    menu1_bullet.bg_col.set(0,0,0);
    menu1_bullet.font_col.set(255,255,255);
    menu1_frame.fontmain.load("bambi.ttf", 80);
    menu1_frame.box.set(0,DISPLAY_HEIGHT*0.5,DISPLAY_WIDTH,DISPLAY_HEIGHT*0.5);
    menu1_frame.text = "Frame Cam";
    menu1_frame.bg_col.set(0,0,0);
    menu1_frame.font_col.set(255,255,255);

    menu2_adjust.fontmain.load("bambi.ttf", 40);
    menu2_adjust.box.set(0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT*0.07);
    menu2_adjust.text = "Adjust The Cam";
    menu2_adjust.bg_col.set(0,0,0,0);
    menu2_adjust.font_col.set(255,255,255);
    menu2_ready.fontmain.load("bambi.ttf", 80);
    menu2_ready.box.set(0,DISPLAY_HEIGHT*0.8,DISPLAY_WIDTH,DISPLAY_HEIGHT*0.2);
    menu2_ready.text = "Okay Let's GIF";
    menu2_ready.bg_col.set(0,0,0,0);
    menu2_ready.font_col.set(255,255,255);
    
    menu3_selframes.fontmain.load("bambi.ttf", 60);
    menu3_selframes.box.set(0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT*0.1);
    menu3_selframes.text = "Select Frames";
    menu3_selframes.bg_col.set(255,255,255);
    menu3_selframes.font_col.set(0,0,0);
    menu3_4frames.fontmain.load("bambi.ttf", 150);
    menu3_4frames.box.set(0,DISPLAY_HEIGHT*0.1,DISPLAY_WIDTH,DISPLAY_HEIGHT*0.3);
    menu3_4frames.text = "4";
    menu3_4frames.bg_col.set(0,0,0);
    menu3_4frames.font_col.set(255,255,255);
    menu3_8frames.fontmain.load("bambi.ttf", 150);
    menu3_8frames.box.set(0,DISPLAY_HEIGHT*0.4,DISPLAY_WIDTH,DISPLAY_HEIGHT*0.3);
    menu3_8frames.text = "8";
    menu3_8frames.bg_col.set(0,0,0);
    menu3_8frames.font_col.set(255,255,255);
    menu3_12frames.fontmain.load("bambi.ttf", 150);
    menu3_12frames.box.set(0,DISPLAY_HEIGHT*0.7,DISPLAY_WIDTH,DISPLAY_HEIGHT*0.3);
    menu3_12frames.text = "12";
    menu3_12frames.bg_col.set(0,0,0);
    menu3_12frames.font_col.set(255,255,255);

     menu4_countdown.fontmain.load("bambi.ttf", 300);
    menu4_countdown.box.set(0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT);
    menu4_countdown.text = "3";
    menu4_countdown.bg_col.set(255,255,255);
    menu4_countdown.font_col.set(0,0,0);

    menu5_retry.fontmain.load("bambi.ttf", 40);
    menu5_retry.box.set(0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT*.07);
    menu5_retry.text = "Gimme A Retry";
    menu5_retry.bg_col.set(0,0,0);
    menu5_retry.font_col.set(255,255,255);
    menu5_finish.fontmain.load("bambi.ttf", 80);
    menu5_finish.box.set(0,DISPLAY_HEIGHT*.8,DISPLAY_WIDTH,DISPLAY_HEIGHT*.2);
    menu5_finish.text = "Create GIF";
    menu5_finish.bg_col.set(0,0,0);
    menu5_finish.font_col.set(255,255,255);
    
    menu6_thanks.fontmain.load("bambi.ttf", 110);
    menu6_thanks.box.set(0,DISPLAY_HEIGHT*.4,DISPLAY_WIDTH,DISPLAY_HEIGHT*.2);
    menu6_thanks.text = "Awesome";
    menu6_thanks.bg_col.set(0,0,0);
    menu6_thanks.font_col.set(255,255,255);
    menu6_endmsg.fontmain.load("bambi.ttf", 14);
    menu6_endmsg.box.set(0,DISPLAY_HEIGHT*.5,DISPLAY_WIDTH,DISPLAY_HEIGHT*.1);
    menu6_endmsg.text = "If you would like a copy of the GIF, the front desk will happily provide.";
    menu6_endmsg.bg_col.set(0,0,0,0);
    menu6_endmsg.font_col.set(255,255,255);
    
    //touch_prev.set(0,0);
    
    bullet_latency = 100;
    bullet_timer = 0;
    captured = false;
    capturing = false;
    capture_cam = 0;
    
    frame_latency = 200;
    
    countdown_val = 4;
    
    playback_direction = true;
    playback_frame = 0;
    playback_timer = 0;
    playback_frame_speed = 250;
    playback_horizontal_offset = 35;
    playback_width = CAM_HEIGHT - (2*playback_horizontal_offset); //we rotate 90 so we use CAM_HEIGHT as width
    playback_height = (int)(playback_width*1.666); //1x1.666 ratio
    playback_vertical_offset = (int)((CAM_WIDTH - playback_height)*0.5);
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
        
        cams[1].update();
        cams_pixels[1] = cams[1].getPixels();
        //cams_pixels[1].rotate90(1); //too expensive, leads to latency
        cams_texture[1].loadData(cams_pixels[1]);
        
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

        //if 'frame' capture we can just update cam 1
//        for(int i=0;i<NUM_CAMS;i++){
//            cams[i].update();
//            cams_pixels[i] = cams[i].getPixels();
//            cams_pixels[i].rotate90(1);
//            cams_texture[i].loadData(cams_pixels[i]);
//        }
        
        if(gif_type=="bullet"){
            if(ofGetElapsedTimeMillis()-bullet_timer > bullet_latency){
                
                cams[capture_cam].update();
                cams_pixels[capture_cam] = cams[capture_cam].getPixels();
                cams_pixels[capture_cam].rotate90(1);
                cams_texture[capture_cam].loadData(cams_pixels[capture_cam]);
                
                captured_pixels.push_back(cams[capture_cam].getPixels());
                captured_pixels[capture_cam].rotate90(1);
                ofTexture t;
                captured_texture.push_back(t);
                captured_texture[capture_cam].loadData(captured_pixels[capture_cam]);
                //should we  or destroy variable t? leak over time?
                bullet_timer = ofGetElapsedTimeMillis();
                capture_cam++;
                if(capture_cam==NUM_CAMS){
                    captured = true;
                    mode="playback_edit";
                }else{
                    flash_timer = ofGetElapsedTimeMillis();
                }
            }
        }
        if(gif_type=="frame"){
            if(ofGetElapsedTimeMillis()-frame_timer > frame_latency){
                
                cams[1].update();
                cams_pixels[1] = cams[1].getPixels();
                cams_pixels[1].rotate90(1);
                cams_texture[1].loadData(cams_pixels[1]);
                
                captured_pixels.push_back(cams[1].getPixels()); //always capturing from middle cam: 1
                captured_pixels[captured_pixels.size()-1].rotate90(1);
                ofTexture t;
                captured_texture.push_back(t);
                captured_texture[captured_texture.size()-1].loadData(captured_pixels[captured_pixels.size()-1]);
                //should we  or destroy variable t? leak over time?
                frame_timer = ofGetElapsedTimeMillis();
                capture_frame++;
                if(capture_frame==num_frames){
                    captured = true;
                    mode="playback_edit";
                }else{
                    flash_timer = ofGetElapsedTimeMillis();
                }
            }
        }
        
    }else if(mode=="playback_edit"){ //menu5

        if(captured==true){
            
            if(ofGetElapsedTimeMillis()-playback_timer > playback_frame_speed){
                
                if(gif_type=="bullet"){ //wiggle
                    if(playback_direction==true){ //playing forwards
                        if(playback_frame==NUM_CAMS-1){
                            playback_direction = false;
                            playback_frame--;
                        }else{
                            playback_frame++;
                        }
                    }else{ //playing backwards
                        if(playback_frame==0){
                            playback_direction = true;
                            playback_frame++;
                        }else{
                            playback_frame--;
                        }
                    }
                }
                
                if(gif_type=="frame"){ //just play forwards
                    playback_frame++;
                    if(playback_frame>=num_frames){
                        playback_frame = 0;
                    }
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

    }else if(mode=="select_gifmode"){ //menu1
        
        menu1_bullet.draw();
        menu1_frame.draw();
        
    }else if(mode=="adjust_cam"){ //menu2
        
        //rotate texture on GPU
        cams_texture[1].setAnchorPercent(0.5, 0.5);
        ofPushMatrix();
        ofTranslate(DISPLAY_WIDTH*0.5, DISPLAY_HEIGHT*0.5);
        ofScale(-1, 1);
        ofRotateZ(90);
        cams_texture[1].draw(0,0);
        ofPopMatrix();
        
        menu2_ready.font_col.set(255,255,255, (abs(sin(ofGetElapsedTimeMillis()*0.002))*155.0)+100.0 );
        menu2_ready.draw();
        menu2_adjust.draw();

    }else if(mode=="select_frames"){ //menu3

        menu3_4frames.draw();
        menu3_8frames.draw();
        menu3_12frames.draw();
        menu3_selframes.draw();
        
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
            
            

            if(gif_type=="bullet"){ //with bullet gifs we have to do some sneaky align/crop to create a
                captured_texture[playback_frame].drawSubsection((DISPLAY_WIDTH-playback_width)*0.5, ((DISPLAY_HEIGHT-playback_height)*0.5), playback_width, playback_height, playback_horizontal_offset*playback_frame, playback_vertical_offset, playback_width, playback_height);
            }
            if(gif_type=="frame"){ //maybe we should just scale instead of crop?
                captured_texture[playback_frame].drawSubsection((DISPLAY_WIDTH-playback_width)*0.5, ((DISPLAY_HEIGHT-playback_height)*0.5), playback_width, playback_height, playback_horizontal_offset*1, playback_vertical_offset, playback_width, playback_height);
            }

        }
        
        menu5_retry.draw();
        menu5_finish.font_col.set(255,255,255, (abs(sin(ofGetElapsedTimeMillis()*0.002))*155.0)+100.0 );
        menu5_finish.draw();
        
        //ofDrawRectangle(0,0,DISPLAY_WIDTH,50);

    }else if(mode=="end_message"){ //menu6
        
        menu6_thanks.font_col.set(255,255,255, (abs(sin(ofGetElapsedTimeMillis()*0.002))*155.0)+100.0 );
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
    
    timeout_timer = ofGetElapsedTimeMillis();
    
    if(mode=="idle"){
        mode = "select_gifmode";
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
            frame_latency = 800;
            mode = "countdown";
        }
        if(menu3_8frames.inside(x, y)){
            num_frames = 8;
            frame_latency = 500;
            mode = "countdown";
        }
        if(menu3_12frames.inside(x, y)){
            num_frames = 12;
            frame_latency = 200;
            mode = "countdown";
        }
    }else if(mode=="playback_edit"){
        if(y<50){
            //playback_horizontal_offset = int(((float)x/(float)DISPLAY_WIDTH)*120.0);
            //cout << "horizontal offeset, " << playback_horizontal_offset << endl;
        }
        if(menu5_filter1.inside(x, y)){
            
        }
        if(menu5_filter2.inside(x, y)){
            
        }
        if(menu5_filter3.inside(x, y)){
            
        }
        if(menu5_filter4.inside(x, y)){
            
        }
        if(menu5_finish.inside(x, y)){ //click finish
            
            mode = "end_message";
            end_timer = ofGetElapsedTimeMillis();
            
            captured_image.clear();
            //create the images from the pixels
            for(int i=0;i<num_frames;i++){ //if bullet, num_frames=3
                ofImage img; //memory issues?
                img.setFromPixels(captured_pixels[i]);
                if(gif_type=="bullet"){
                img.crop(playback_horizontal_offset*i, playback_vertical_offset, playback_width, playback_height);
                }else{
                 img.crop(playback_horizontal_offset*1, playback_vertical_offset, playback_width, playback_height);
                }
                img.save(ofToString(i)+".jpg",OF_IMAGE_QUALITY_BEST);
                captured_image.push_back(img);
                cout << "pushed, " << i << endl;
            }
            if(gif_type=="bullet"){ //its easier just to add another frame instead of wiggling playback
                ofImage img; //memory issues?
                img.setFromPixels(captured_pixels[1]);
                img.crop(playback_horizontal_offset*1, playback_vertical_offset, playback_width, playback_height);
                img.save("3.jpg",OF_IMAGE_QUALITY_BEST);
                captured_image.push_back(img);
                num_frames = 4;
                cout << "pushed, 3" << endl;
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
