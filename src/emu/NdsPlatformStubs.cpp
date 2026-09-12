#include <Platform.h>

#include <algorithm>

namespace melonDS::Platform {

struct AACDecoder {};
struct DynamicLibrary {};

AACDecoder* AAC_Init() {
    return nullptr;
}

void AAC_DeInit(AACDecoder*) {}

bool AAC_Configure(AACDecoder*, int, int) {
    return false;
}

bool AAC_DecodeFrame(AACDecoder*, const void*, int, void*, int) {
    return false;
}

void MP_Begin(void*) {}
void MP_End(void*) {}

int MP_SendPacket(u8*, int, u64, void*) {
    return 0;
}
int MP_RecvPacket(u8*, u64*, void*) {
    return 0;
}
int MP_SendCmd(u8*, int, u64, void*) {
    return 0;
}
int MP_SendReply(u8*, int, u64, u16, void*) {
    return 0;
}
int MP_SendAck(u8*, int, u64, void*) {
    return 0;
}
int MP_RecvHostPacket(u8*, u64*, void*) {
    return 0;
}
u16 MP_RecvReplies(u8*, u64, u16, void*) {
    return 0;
}
int Net_SendPacket(u8*, int, void*) {
    return 0;
}
int Net_RecvPacket(u8*, void*) {
    return 0;
}

void Camera_Start(int, void*) {}
void Camera_Stop(int, void*) {}
void Camera_CaptureFrame(int, u32* frame, int width, int height, bool, void*) {
    if (frame) {
        std::fill(frame, frame + width * height, 0);
    }
}

void Mic_Start(void*) {}
void Mic_Stop(void*) {}
int Mic_ReadInput(s16* data, int maxlength, void*) {
    if (data && maxlength > 0) {
        std::fill(data, data + maxlength, 0);
    }
    return maxlength;
}

bool Addon_KeyDown(KeyType, void*) {
    return false;
}
void Addon_RumbleStart(u32, void*) {}
void Addon_RumbleStop(void*) {}
float Addon_MotionQuery(MotionQueryType, void*) {
    return 0.f;
}

}