/*
  ==============================================================================

    Converters.h
    Created: 16 Dec 2022 11:04:43am
    Author:  nikid

  ==============================================================================
*/


    float hz2bark(float f) {
        float bark = 6 * asinh(f / 600);
        return bark;
    }

    float bark2hz(float b) {
        float hz = 600 * sinh(b / 6);
        return hz;
    }
