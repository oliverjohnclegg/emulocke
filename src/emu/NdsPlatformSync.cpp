#include <Platform.h>

#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>

namespace melonDS::Platform {

struct Thread {
    std::thread worker;
};

struct Semaphore {
    std::mutex mutex;
    std::condition_variable cv;
    int count{0};
};

struct Mutex {
    std::mutex mutex;
};

Thread* Thread_Create(std::function<void()> func) {
    auto* thread = new Thread();
    thread->worker = std::thread(std::move(func));
    return thread;
}

void Thread_Wait(Thread* thread) {
    if (thread && thread->worker.joinable()) {
        thread->worker.join();
    }
}

void Thread_Free(Thread* thread) {
    Thread_Wait(thread);
    delete thread;
}

Semaphore* Semaphore_Create() {
    return new Semaphore();
}

void Semaphore_Free(Semaphore* sema) {
    delete sema;
}

void Semaphore_Reset(Semaphore* sema) {
    std::lock_guard lock(sema->mutex);
    sema->count = 0;
}

void Semaphore_Wait(Semaphore* sema) {
    std::unique_lock lock(sema->mutex);
    sema->cv.wait(lock, [&] { return sema->count > 0; });
    --sema->count;
}

bool Semaphore_TryWait(Semaphore* sema, int timeout_ms) {
    std::unique_lock lock(sema->mutex);
    if (timeout_ms <= 0) {
        if (sema->count <= 0) {
            return false;
        }
        --sema->count;
        return true;
    }
    const bool ok = sema->cv.wait_for(lock, std::chrono::milliseconds(timeout_ms), [&] { return sema->count > 0; });
    if (ok) {
        --sema->count;
    }
    return ok;
}

void Semaphore_Post(Semaphore* sema, int count) {
    std::lock_guard lock(sema->mutex);
    sema->count += count;
    sema->cv.notify_all();
}

Mutex* Mutex_Create() {
    return new Mutex();
}

void Mutex_Free(Mutex* mutex) {
    delete mutex;
}

void Mutex_Lock(Mutex* mutex) {
    mutex->mutex.lock();
}

void Mutex_Unlock(Mutex* mutex) {
    mutex->mutex.unlock();
}

bool Mutex_TryLock(Mutex* mutex) {
    return mutex->mutex.try_lock();
}

void Sleep(u64 usecs) {
    std::this_thread::sleep_for(std::chrono::microseconds(usecs));
}

u64 GetMSCount() {
    using clock = std::chrono::steady_clock;
    return static_cast<u64>(std::chrono::duration_cast<std::chrono::milliseconds>(clock::now().time_since_epoch()).count());
}

u64 GetUSCount() {
    using clock = std::chrono::steady_clock;
    return static_cast<u64>(std::chrono::duration_cast<std::chrono::microseconds>(clock::now().time_since_epoch()).count());
}

}