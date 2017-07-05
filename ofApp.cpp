#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //global ofx stuffs
    ofSetFrameRate(30);
    ofSetVerticalSync(true);
    
    mode = "idle";
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
    
    //we can now get back a list of devices.
    vector<ofVideoDevice> devices = vidGrabber1.listDevices();
    cout << "You have " << devices.size() << " cams connected" << endl;
    
    cams[0].setDeviceID(devices.size()-1); //if 1 cam connected: 0, if 2 cams connected: 1 
    cams[0].initGrabber(CAM_WIDTH,CAM_HEIGHT);

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
    menu5_finish.box.set(0,DISPLAY_HEIGHT*.80,DISPLAY_WIDTH,DISPLAY_HEIGHT*.2);
    menu5_finish.text = "Next";
    menu5_finish.bg_col.set(0,0,0,0);
    menu5_finish.font_col.set(255,255,255);
    
    menu7_fx1.box.set(15,DISPLAY_HEIGHT*.6,118,210);
    menu7_fx1.bg_col.set(50,50,50);
    menu7_fx2.box.set(148,DISPLAY_HEIGHT*.6,118,210);
    menu7_fx2.bg_col.set(50,50,50);
    menu7_fx3.box.set(281,DISPLAY_HEIGHT*.6,118,210);
    menu7_fx3.bg_col.set(50,50,50);
    menu7_fx4.box.set(414,DISPLAY_HEIGHT*.6,118,210);
    menu7_fx4.bg_col.set(50,50,50);
    menu7_fx5.box.set(547,DISPLAY_HEIGHT*.6,118,210);
    menu7_fx5.bg_col.set(50,50,50);
    menu7_fx6.box.set(680,DISPLAY_HEIGHT*.6,118,210);
    menu7_fx6.bg_col.set(50,50,50);
    menu7_fx7.box.set(813,DISPLAY_HEIGHT*.6,118,210);
    menu7_fx7.bg_col.set(50,50,50);
    menu7_fx8.box.set(946,DISPLAY_HEIGHT*.6,118,210);
    menu7_fx8.bg_col.set(50,50,50);
    menu7_finish.fontmain.load("KGHAPPY.ttf", 100);
    menu7_finish.box.set(0,DISPLAY_HEIGHT*.80,DISPLAY_WIDTH,DISPLAY_HEIGHT*.2);
    menu7_finish.text = "Create GIF";
    menu7_finish.bg_col.set(0,0,0,0);
    menu7_finish.font_col.set(255,255,255);
    menu7_filter.fontmain.load("KGHAPPY.ttf", 40);
    menu7_filter.box.set(0,DISPLAY_HEIGHT*.47,DISPLAY_WIDTH,DISPLAY_HEIGHT*.2);
    menu7_filter.text = "SELECT A GIF FILTER";
    menu7_filter.bg_col.set(0,0,0,0);
    menu7_filter.font_col.set(255,255,255);
    menu7_retry.fontmain.load("KGHAPPY.ttf", 50);
    menu7_retry.box.set(0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT*.07);
    menu7_retry.text = "Gimme A Retry";
    menu7_retry.bg_col.set(0,0,0,0);
    menu7_retry.font_col.set(255,255,255);
    menu7_filter_sel.set(menu7_fx1.box.x-3, menu7_fx1.box.y-3, menu7_fx1.box.width+6, menu7_fx1.box.height+6);
    
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
    
    myKeyboard.init("KGHAPPY.ttf", 35, DISPLAY_WIDTH, 500);
    
    caption.load("KGHAPPY.ttf", 42);
    
    message_count = 0;
   
    //touch_prev.set(0,0);
    
    captured = false;

    capture_cam = 0;
    
    frame_latency = 200;
    
    countdown_val = 4;
    
    playback_frame = 0;
    playback_timer = 0;
    playback_frame_speed = 160;

    /* FILTERS */
    fx_CHROME.setup(OFX_FILTER_TYPE_PHOTO_EFFECT_CHROME);
    fx_FADE.setup(OFX_FILTER_TYPE_PHOTO_EFFECT_FADE);
    fx_INSTANT.setup(OFX_FILTER_TYPE_PHOTO_EFFECT_INSTANT);
    fx_MONO.setup(OFX_FILTER_TYPE_PHOTO_EFFECT_MONO);
    fx_NOIR.setup(OFX_FILTER_TYPE_PHOTO_EFFECT_NOIR);
    fx_PROCESS.setup(OFX_FILTER_TYPE_PHOTO_EFFECT_PROCESS);
    fx_TONAL.setup(OFX_FILTER_TYPE_PHOTO_EFFECT_TONAL);
    fx_TRANSFER.setup(OFX_FILTER_TYPE_PHOTO_EFFECT_TRANSFER);
    filter_arr[0] = fx_CHROME;
    filter_arr[1] = fx_FADE;
    filter_arr[2] = fx_INSTANT;
    filter_arr[3] = fx_MONO;
    filter_arr[4] = fx_NOIR;
    filter_arr[5] = fx_PROCESS;
    filter_arr[6] = fx_TONAL;
    filter_arr[7] = fx_TRANSFER;
    filter_sel_num = 0;
    
    /* HTTP POST */
    
    //    post_url = "http://46c9a82a.ngrok.io/gif"; //!!! add your post url !!!
    //    ofAddListener(httpUtils.newResponseEvent,this,&ofApp::newResponse);
    //    httpUtils.start();
    
    //https://github.com/armadillu/ofxHttpForm
    //FormManager that will deal with the form, add a listener to get an answer when submitted
    fm.setVerbose(true);	//we want to see what's going on internally
    ofAddListener(fm.formResponseEvent, this, &ofApp::newResponse);
    
    /* WEBSOCKETS */
    client.connect("ws://65.254.17.130", 8080);
    client.addListener(this);
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
        
        for(int i=0;i<message_count;i++){
            msgs[i].update();
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
                mode="gif_approve";
            }else{
                flash_timer = ofGetElapsedTimeMillis();
            }
            
        }
        
    }else if(mode=="gif_approve"){ //menu5

        if(captured==true){
            
            if(ofGetElapsedTimeMillis()-playback_timer > playback_frame_speed){
                
                playback_frame++;
                if(playback_frame>=num_frames){
                    playback_frame = 0;
                }
                
                playback_timer = ofGetElapsedTimeMillis();
                
            }
            
        }
        
    }else if(mode=="gif_edit"){ //menu7

        //nothing
        
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
            bb_caption = caption.getStringBoundingBox(myKeyboard.captured_caption,0,0);
            ofSetColor(0,0,0,0.5);
            caption.drawString(myKeyboard.captured_caption, int((DISPLAY_WIDTH - bb_caption.width)/2.0)-2, (DISPLAY_HEIGHT*0.96)+2);
            ofSetColor(255,255,255);
            caption.drawString(myKeyboard.captured_caption, int((DISPLAY_WIDTH - bb_caption.width)/2.0), DISPLAY_HEIGHT*0.96);
        }
        
        ofSetColor(255,255,255);
        for(int i=0;i<message_count;i++){
            msgs[i].draw();
        }
        
    }else if(mode=="select_gifmode"){ //menu1
        
        //not using this anymore
        
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

        
    }else if(mode=="gif_approve"){ //menu5
        
        if(captured==true){
            captured_texture[playback_frame].draw(0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT);
        }
        
        menu5_retry.box.setX(sin(ofGetElapsedTimeMillis()*0.002)*30.0);
        menu5_retry.draw();
        
        menu5_finish.font_col.set(255,255,255, (abs(sin(ofGetElapsedTimeMillis()*0.003))*200.0)+55.0 );
        menu5_finish.draw();
        
    }else if(mode=="gif_edit"){ //menu7
        
        myKeyboard.draw();

        ofSetColor(255,255,255);
        ofDrawRectangle(menu7_filter_sel);
        
        menu7_filter.draw();
        
        menu7_fx1.draw(); fx_demo1.draw(15,DISPLAY_HEIGHT*.6,118,210);
        menu7_fx2.draw(); fx_demo2.draw(148,DISPLAY_HEIGHT*.6,118,210);
        menu7_fx3.draw(); fx_demo3.draw(281,DISPLAY_HEIGHT*.6,118,210);
        menu7_fx4.draw(); fx_demo4.draw(414,DISPLAY_HEIGHT*.6,118,210);
        menu7_fx5.draw(); fx_demo5.draw(547,DISPLAY_HEIGHT*.6,118,210);
        menu7_fx6.draw(); fx_demo6.draw(680,DISPLAY_HEIGHT*.6,118,210);
        menu7_fx7.draw(); fx_demo7.draw(813,DISPLAY_HEIGHT*.6,118,210);
        menu7_fx8.draw(); fx_demo8.draw(946,DISPLAY_HEIGHT*.6,118,210);

        menu7_retry.box.setX(sin(ofGetElapsedTimeMillis()*0.002)*30.0);
        menu7_retry.draw();
        
        menu7_finish.font_col.set(255,255,255, (abs(sin(ofGetElapsedTimeMillis()*0.003))*200.0)+55.0 );
        menu7_finish.draw();

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
//    if(key == 's' || key == 'S'){
//        vidGrabber1.videoSettings();
//    }
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
        
        mode="adjust_cam";
        
    }else if(mode=="adjust_cam"){
        
        if(menu2_ready.inside(x, y)){
            mode = "select_frames";
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
        
    }else if(mode=="gif_approve"){
        
        if(menu5_finish.inside(x, y)){ //click next
            mode = "gif_edit";
        }
        
        if(menu5_retry.inside(x, y)){ //click retry
            mode = "countdown";
            captured_pixels.clear();
            captured_texture.clear();
            capture_cam = 0;
            countdown_val = 4;
            capture_frame = 0;
        }
        
    }else if(mode=="gif_edit"){
        
        myKeyboard.create_caption(x,y);
        
        fx_FADE.setup(OFX_FILTER_TYPE_PHOTO_EFFECT_FADE);
        fx_INSTANT.setup(OFX_FILTER_TYPE_PHOTO_EFFECT_INSTANT);
        
        //click to change fx
        if(menu7_fx1.inside(x, y)){
            menu7_filter_sel.set(menu7_fx1.box.x-3, menu7_fx1.box.y-3, menu7_fx1.box.width+6, menu7_fx1.box.height+6);
            filter_sel_num = 0;
        }
        if(menu7_fx2.inside(x, y)){
            menu7_filter_sel.set(menu7_fx2.box.x-3, menu7_fx2.box.y-3, menu7_fx2.box.width+6, menu7_fx2.box.height+6);
            filter_sel_num = 1;
        }
        if(menu7_fx3.inside(x, y)){
            menu7_filter_sel.set(menu7_fx3.box.x-3, menu7_fx3.box.y-3, menu7_fx3.box.width+6, menu7_fx3.box.height+6);
            filter_sel_num = 2;
        }
        if(menu7_fx4.inside(x, y)){
            menu7_filter_sel.set(menu7_fx4.box.x-3, menu7_fx4.box.y-3, menu7_fx4.box.width+6, menu7_fx4.box.height+6);
            filter_sel_num = 3;
        }
        if(menu7_fx5.inside(x, y)){
            menu7_filter_sel.set(menu7_fx5.box.x-3, menu7_fx5.box.y-3, menu7_fx5.box.width+6, menu7_fx5.box.height+6);
            filter_sel_num = 4;
        }
        if(menu7_fx6.inside(x, y)){
            menu7_filter_sel.set(menu7_fx6.box.x-3, menu7_fx6.box.y-3, menu7_fx6.box.width+6, menu7_fx6.box.height+6);
            filter_sel_num = 5;
        }
        if(menu7_fx7.inside(x, y)){
            menu7_filter_sel.set(menu7_fx7.box.x-3, menu7_fx7.box.y-3, menu7_fx7.box.width+6, menu7_fx7.box.height+6);
            filter_sel_num = 6;
        }
        if(menu7_fx8.inside(x, y)){
            menu7_filter_sel.set(menu7_fx8.box.x-3, menu7_fx8.box.y-3, menu7_fx8.box.width+6, menu7_fx8.box.height+6);
            filter_sel_num = 7;
        }
        if(menu7_finish.inside(x, y)){
            
            mode = "end_message";
            
            message_count = 0;
            
            myKeyboard.captured_caption = myKeyboard.caption;
            
            end_timer = ofGetElapsedTimeMillis();
            
            ofSetColor(0,0,0);
            ofDrawRectangle(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);
            
            //should thread this?!?!?
            
            captured_image.clear();
            for(int i=0;i<num_frames;i++){
                ofImage img;
                img.setFromPixels(captured_pixels[i]);
                filter_arr[filter_sel_num].setInputImage(img);
                filter_arr[filter_sel_num].getOutput(img);
                captured_image.push_back(img);
            }
            
            //save images to file
            for(int i=0;i<num_frames;i++){
                captured_image[i].save(ofToString(i)+".png",OF_IMAGE_QUALITY_BEST);
                cout << "saved image, " << i << endl;
            }
            
            //http post form with image frames
            //            ofxHttpForm form;
            //            form.action = post_url;
            //            form.method = OFX_HTTP_POST;
            //            form.addHeaderField("Content-Type","multipart/form-data");
            //            //form.addHeaderField('Content-Type', 'multipart/form-data')
            //            form.addFormField("caption", myKeyboard.captured_caption);
            //            form.addFormField("frames", ofToString(num_frames+1));
            //            for(int i=0;i<num_frames;i++){
            //                form.addFile("frame-"+ofToString(i),ofToString(i)+".png");
            //            }
            //            httpUtils.addForm(form);
            HttpForm f = HttpForm( "http://46c9a82a.ngrok.io/gif" );
            f.addFormField("caption", myKeyboard.captured_caption);
            f.addFormField("frames", ofToString(num_frames+1));
            for(int i=0;i<num_frames;i++){
                f.addFile("frame-"+ofToString(i),ofToString(i)+".png", "image/jpg");
            }
            fm.submitForm( f, false );	//false == ignoreReply
            
            //reset
            captured_frames = num_frames;
            captured = true;
            captured_playspeed = 120;
            captured_playframe = 0;
            captured_pixels.clear();
            captured_texture.clear();
            countdown_val = 4;
            capture_frame = 0;
            myKeyboard.caption = "ADD A MESSAGE OR YOUR NAME!";
            filter_sel_num = 0;
            menu7_filter_sel.set(menu7_fx1.box.x-3, menu7_fx1.box.y-3, menu7_fx1.box.width+6, menu7_fx1.box.height+6);
            
        }
        if(menu7_retry.inside(x, y)){ //click retry
            
            mode = "countdown";
            captured_pixels.clear();
            captured_texture.clear();
            capture_cam = 0;
            countdown_val = 4;
            capture_frame = 0;
            myKeyboard.caption = "ADD A MESSAGE OR YOUR NAME!";
            filter_sel_num = 0;
            menu7_filter_sel.set(menu7_fx1.box.x-3, menu7_fx1.box.y-3, menu7_fx1.box.width+6, menu7_fx1.box.height+6);
            
        }
    }
    

}

void ofApp::newResponse(HttpFormResponse &response){
    //printf("form '%s' returned : %s\n", response.url.c_str(), response.ok ? "OK" : "KO" );
    //cout << ofToString(response.status) + ": " + (string)response.responseBody << endl;
    if(ofToString(response.responseBody)=="Received images"){
        cout << "Image POST OKAY" << endl;
    }else{
        cout << "Image POST ERROR" << endl;
    }
}

//--------------------------------------------------------------
//void ofApp::newResponse(ofxHttpResponse & response){
//    http_response = ofToString(response.status) + ": " + (string)response.responseBody;
//    cout << http_response << endl;
//}

//--------------------------------------------------------------
void ofApp::onConnect( ofxLibwebsockets::Event& args ){
    ofLogVerbose()<<"on connected";
}
//--------------------------------------------------------------
void ofApp::onOpen( ofxLibwebsockets::Event& args ){
    ofLogVerbose()<<"on open";
}
//--------------------------------------------------------------
void ofApp::onClose( ofxLibwebsockets::Event& args ){
    ofLogVerbose()<<"on close";
}
//--------------------------------------------------------------
void ofApp::onIdle( ofxLibwebsockets::Event& args ){
    ofLogVerbose()<<"on idle";
}
//--------------------------------------------------------------
void ofApp::onMessage( ofxLibwebsockets::Event& args ){
    cout << "msg" << endl;
    cout << args.data.getData() << endl;
    if(message_count<100){
        msgs[message_count].init("KGHAPPY.ttf", 20, "This is message "+ofToString(message_count), "Alex Staudt");
        message_count++;
    }
    
}
//--------------------------------------------------------------
void ofApp::onBroadcast( ofxLibwebsockets::Event& args ){
    cout<<"got broadcast "<<args.message<<endl;
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
