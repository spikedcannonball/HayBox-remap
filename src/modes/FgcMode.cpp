#include "modes/FgcMode.hpp"

FgcMode::FgcMode(socd::SocdType horizontal_socd, socd::SocdType vertical_socd) {
    _socd_pair_count = 2;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{&InputState::left,   &InputState::right, horizontal_socd         },
 /* Mod X override C-Up input if both are pressed. Without this, neutral SOCD doesn't work
  properly if Down and both Up buttons are pressed, because it first resolves Down + Mod X
  to set both as unpressed, and then it sees C-Up as pressed but not Down, so you get an up
  input instead of neutral. 
        Uncomment line 15 if we use c_up as up and comment out line 14
    Default &InputState::mod_x changed to remapped button
  */
        socd::SocdPair{ &InputState::down,  &InputState::up, vertical_socd           },
        //socd::SocdPair{ &InputState::down,  &InputState::c_up,  vertical_socd           },

        //If using WASD, uncomment the below line and comment the above lines
        //socd::SocdPair{ &InputState::down,   &InputState::w, vertical_socd     },
    };
}

void FgcMode::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    // Directions
    outputs.dpadLeft = inputs.left;
    outputs.dpadRight = inputs.right;
    outputs.dpadDown = inputs.down;
    //modified since mod_x and up were swapped, this is now still up
    outputs.dpadUp = inputs.up;

    // Menu keys
    outputs.select = inputs.a;
    //function layer
    if (inputs.mod_y){
        outputs.home = inputs.start;
    } else {
        outputs.start = inputs.start;
    }
    outputs.leftStickClick = inputs.c_left;
    outputs.rightStickClick = inputs.c_up;

    // Right hand bottom row
    outputs.a = inputs.b;
    outputs.b = inputs.x;
    outputs.triggerRDigital = inputs.z;
    // remapped this to add left hand button and keep original button
    outputs.triggerLDigital = inputs.l || inputs.mod_x;

    // Right hand top row
    outputs.x = inputs.r;
    outputs.y = inputs.y;
    outputs.buttonR = inputs.lightshield;
    outputs.buttonL = inputs.midshield;
}

void FgcMode::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    outputs.leftStickX = 128;
    outputs.leftStickY = 128;
    outputs.rightStickX = 128;
    outputs.rightStickY = 128;
    outputs.triggerLAnalog = outputs.triggerLDigital ? 255 : 0;
    outputs.triggerRAnalog = outputs.triggerRDigital ? 255 : 0;
}
