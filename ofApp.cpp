#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(30);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	this->photo.loadImage("photo.png");

	for (int i = 0; i < 1024 + 512; i++) {
		this->particles.push_back(shared_ptr<Particle>(new Particle()));
	}

	this->fbo.allocate(512, 512);
}

//--------------------------------------------------------------
void ofApp::update() {
	ofPixels pixels = this->photo.getPixelsRef();
	ofColor pixel_color;

	for (int i = 0; i < this->particles.size(); i++) {
		this->particles[i]->update();
	}

	this->fbo.begin();
	ofClear(0);

	ofSetColor(255, 255 * mouseX / 512);
	this->photo.draw(0, 0);

	for (int i = 0; i < this->particles.size(); i++) {
		pixel_color = pixels.getColor(this->particles[i]->get_location().x, this->particles[i]->get_location().y);
		this->particles[i]->draw(this->particles, pixel_color);
	}
	this->fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw() {
	this->fbo.draw(0, 0);
}

//--------------------------------------------------------------
int main() {
	ofSetupOpenGL(512, 512, OF_WINDOW);
	ofRunApp(new ofApp());
}