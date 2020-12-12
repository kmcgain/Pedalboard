#pragma once

#define NUM_SCENES 8
#define MAX_SCENE_NAME_LENGTH 33

#include "pch.h"
#include "logger.h"

struct SceneInfo {
	short number = -1;
	char name[MAX_SCENE_NAME_LENGTH];
};

class Preset {
protected:
	byte sequenceNumber=0;

	SceneInfo scenes[NUM_SCENES];

public:
	Preset() {
		for (auto i = 0; i < NUM_SCENES; i++) {
			scenes[i].name[0] = '\0';
			scenes[i].number = -1;
		}
	}

	virtual unsigned short getPresetNumber() = 0;
	virtual unsigned short getSelectedSceneNumber() = 0;
	virtual void getPresetName(char* presetNameOut, short capacity) = 0;
	virtual const char* getSceneName(char sceneNumber) {
		return scenes[sceneNumber - 1].name;
	}

	void setScene(short sceneNumber, const char* name) {		
		int i;
		// A double space will signal end of scene name (axe lib returns space padded)
		bool lastWasSpace = false;
		for (i = 0; i < MAX_SCENE_NAME_LENGTH && name[i] != '\0'; i++) {
			if (lastWasSpace && name[i] == ' ') {
				i--; // otherwise we lead trailing space
				break;
			}

			lastWasSpace = name[i] == ' ';
			this->scenes[sceneNumber - 1].name[i] = name[i];
		}
		
		if (i == MAX_SCENE_NAME_LENGTH)
			i--;
		this->scenes[sceneNumber - 1].name[i] = '\0';
		this->scenes[sceneNumber - 1].number = sceneNumber;
		this->sequenceNumber++;
	}

	byte SequenceNumber() {
		return this->sequenceNumber;
	}

	virtual unsigned short getEffectCount() = 0;
	virtual void getEffectName(unsigned short index, char* nameOut, unsigned short capacity) = 0;
	virtual bool getEffectBypassed(unsigned short index) = 0;
};