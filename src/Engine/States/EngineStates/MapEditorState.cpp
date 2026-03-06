//
// Created by Terrarizer on 06/03/2026.
//

#include "MapEditorState.h"

bool MapEditorState::initialize() {


    return true;
}

void MapEditorState::handleInput(const IInput& input) {

}

void MapEditorState::update(float deltaTime) const {

}

void MapEditorState::render() const {

}

void MapEditorState::cleanup() const {

}

MapEditorState::~MapEditorState() {
    MapEditorState::cleanup();
}

