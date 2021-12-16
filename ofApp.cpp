#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	float phi_deg_step = 5;
	float theta_deg_step = 5;

	vector<glm::vec3> noise_location_list;

	for (int i = 0; i < 20; i++) {

		auto noise_location = glm::vec3(
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -250, 250),
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -250, 250),
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -250, 250));
		noise_location_list.push_back(noise_location);
	}

	for (float radius = 50; radius <= 250; radius += 15) {

		for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {

			for (float theta_deg = 0; theta_deg <= 360; theta_deg += theta_deg_step) {

				auto location = glm::vec3(
					radius * sin(theta_deg * DEG_TO_RAD) * cos(phi_deg * DEG_TO_RAD),
					radius * sin(theta_deg * DEG_TO_RAD) * sin(phi_deg * DEG_TO_RAD),
					radius * cos(theta_deg * DEG_TO_RAD));

				bool draw_flag = true;
				for (int i = 0; i < noise_location_list.size(); i++) {

					if (glm::distance(location, noise_location_list[i]) < 100) {

						draw_flag = false;
						break;
					}
				}

				if (draw_flag) {

					auto index = this->face.getNumVertices();
					vector<glm::vec3> vertices;

					vertices.push_back(glm::vec3(
						radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
						radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
						radius * cos((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD)));
					vertices.push_back(glm::vec3(
						radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
						radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
						radius * cos((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD)));
					vertices.push_back(glm::vec3(
						radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
						radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
						radius * cos((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD)));
					vertices.push_back(glm::vec3(
						radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
						radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
						radius * cos((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD)));

					this->face.addVertices(vertices);
					this->frame.addVertices(vertices);

					this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
					this->face.addIndex(index + 0); this->face.addIndex(index + 3); this->face.addIndex(index + 2);

					this->frame.addIndex(index + 0); this->frame.addIndex(index + 1);
					this->frame.addIndex(index + 0); this->frame.addIndex(index + 2);
					this->frame.addIndex(index + 3); this->frame.addIndex(index + 1);
					this->frame.addIndex(index + 3); this->frame.addIndex(index + 2);
				}
				
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(90);
	ofRotateZ(ofGetFrameNum());

	ofSetColor(0);
	this->face.draw();

	ofSetColor(239);
	this->frame.draw();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}