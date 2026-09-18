#include "calc/Labels.hpp"

#include "calc/Ability.hpp"

namespace emulocke {

const char* statusAbbrev(uint32_t status) {
    if (status & 7) {
        return "SLP";
    }
    if (status & kStFrz) {
        return "FRZ";
    }
    if (status & kStPar) {
        return "PAR";
    }
    if (status & kStBurn) {
        return "BRN";
    }
    if (status & kStToxic) {
        return "TOX";
    }
    if (status & kStPsn) {
        return "PSN";
    }
    return nullptr;
}

}